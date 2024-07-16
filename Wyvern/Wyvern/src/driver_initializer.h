#ifndef DRIVER_INITIALIZER_H
#define DRIVER_INITIALIZER_H

#include <windows.h>
#include <iostream>

class DriverInitializer {
public:
    DriverInitializer();

    void initialize();

private:
    HANDLE driver_handle_;
    DWORD pid_;

    HANDLE open_driver_handle();
    DWORD find_process_id(const wchar_t* process_name);
};

#endif // DRIVER_INITIALIZER_H