#ifndef DRIVER_H
#define DRIVER_H

#include <windows.h>
#include <TLHELP32.h>
#include <iostream>

namespace driver {
    namespace codes {
        constexpr ULONG attach =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

        constexpr ULONG read =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);

        constexpr ULONG write =
            CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }

    struct Request {
        HANDLE process_id;
        PVOID target;
        PVOID buffer;
        SIZE_T size;
        SIZE_T return_size;
    };

    bool attach_to_process(HANDLE driver_handle, const DWORD pid);

    template <class T>
    inline T read_memory(HANDLE driver_handle, const std::uintptr_t addr);

    template <class T>
    inline void write_memory(HANDLE driver_handle, const std::uintptr_t addr, const T& value);


}


namespace driver_utills {    
    extern HANDLE driver_handle_;
    extern DWORD pid_;

    HANDLE open_driver_handle();
    DWORD find_process_id(const wchar_t* process_name);
    const std::uintptr_t module_base(DWORD pid, const wchar_t* module_name);
}

#endif // DRIVER_H