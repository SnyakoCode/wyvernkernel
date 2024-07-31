#include "driver.h"

void main() {

    HANDLE driver = driver_utills::open_driver_handle();

    if (driver_utills::driver_handle_ == INVALID_HANDLE_VALUE) {
        std::cout << "[-] Failed to create device handle \n";
        return;
    }

    DWORD procid = driver_utills::find_process_id(L"cs2.exe");
    const std::uintptr_t client = driver_utills::module_base(procid, L"client.dll");
    std::cout << "Proccess id: " << procid << std::endl;
    std::cout << "Client.dll: " << client << std::endl;

    /*          Write/Read memory example
    driver::attach_to_process(driver_handle, procid);
    driver::write_memory(driver_handle, memory_address(client + offset), value);
    driver::read_memory(driver_handle, memory_address(client + offset));
    */
        

    CloseHandle(driver);
    std::cin.get();
}
