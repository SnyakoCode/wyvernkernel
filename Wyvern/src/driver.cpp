// driver.cpp
#include "driver.h"

namespace driver {

    bool attach_to_process(HANDLE driver_handle, const DWORD pid) {
        Request r;
        r.process_id = reinterpret_cast<HANDLE>(pid);

        return DeviceIoControl(driver_handle, codes::attach, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }
}

namespace driver_utills {

    HANDLE driver_handle_;
    DWORD pid_;

    DWORD find_process_id(const wchar_t* process_name) {
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

    const std::uintptr_t module_base(DWORD pid, const wchar_t* module_name) {
        std::uintptr_t module_base = 0;

        HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        if (snap_shot == INVALID_HANDLE_VALUE)
            return module_base;

        MODULEENTRY32W entry = {};
        entry.dwSize = sizeof(entry);

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

    HANDLE open_driver_handle() {
        HANDLE handle = CreateFile(L"\\\\.\\WyvernDriver", GENERIC_READ, 0, nullptr, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, nullptr);
        return handle;
    }
}
