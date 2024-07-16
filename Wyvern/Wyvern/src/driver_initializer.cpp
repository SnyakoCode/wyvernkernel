#include "driver.h"
#include "driver_initializer.h"
#include <iostream>
#include <TLHELP32.h>


static std::uintptr_t get_module_base(const DWORD pid, const wchar_t* module_name) {
    std::uintptr_t module_base = 0;

    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (snap_shot == INVALID_HANDLE_VALUE)
        return module_base;

    MODULEENTRY32W entry = {};
    entry.dwSize = sizeof(decltype(entry));

    if (Module32FirstW(snap_shot, &entry) == TRUE) {
        if (wcsstr(module_name, entry.szModule) != nullptr)
            module_base = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
        else {
            while (Module32NextW(snap_shot, &entry) == TRUE) {
                if (wcsstr(module_name, entry.szModule) != nullptr) {
                    module_base = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
                    break;
                }
            }
        }
    }

    CloseHandle(snap_shot);

    return module_base;
}


DriverInitializer::DriverInitializer()
    : driver_handle_(open_driver_handle()), pid_(find_process_id(L"cs2.exe")) {}

void DriverInitializer::initialize() {
    if (pid_ == 0) {
        std::cout << "[-] Failed to find cs2.exe process \n";
        std::cin.get();
        return;
    }

    if (driver_handle_ == INVALID_HANDLE_VALUE) {
        std::cout << "[-] Failed to create device handle \n";
        std::cin.get();
        return;
    }

    if (driver::attach_to_process(driver_handle_, pid_)) {
        std::cout << "[+] Attachment successful \n";

        const std::uintptr_t client = get_module_base(pid_, L"client.dll");
        if (client != 0) {
            std::cout << "[+] Client.dll found \n";
            std::cin.get();
        }

    }

    CloseHandle(driver_handle_);
}

HANDLE DriverInitializer::open_driver_handle() {
    HANDLE handle = CreateFile(L"\\\\.\\WyvernDriver", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    return handle;
}



DWORD DriverInitializer::find_process_id(const wchar_t* process_name) {
    DWORD process_id = 0;

    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snap_shot == INVALID_HANDLE_VALUE)
        return process_id;

    PROCESSENTRY32 entry = {};
    entry.dwSize = sizeof(entry);

    if (Process32FirstW(snap_shot, &entry) == TRUE) {
        if (_wcsicmp(process_name, entry.szExeFile) == 0)
            process_id = entry.th32ProcessID;
        else {
            while (Process32NextW(snap_shot, &entry) == TRUE) {
                if (_wcsicmp(process_name, entry.szExeFile) == 0) {
                    process_id = entry.th32ProcessID;
                    break;
                }
            }
        }
    }

    CloseHandle(snap_shot);
    return process_id;
}
