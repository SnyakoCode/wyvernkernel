   ## Wyvern Kernel Driver

**Wyvern** is a kernel driver designed to facilitate the transmission and reception of memory from any process via the computer's kernel.

### Features
- **Direct Memory Access:** Transmit and receive memory from any process.

### Installation

To install the Wyvern kernel driver, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/snyakocode/wyvernkernel.git
   cd wyvern
   ```

2. **Build the Project in x64 Version + Run VS as Administrator :**
   Ensure you have the necessary development tools and dependencies for building the project in x64.

3. **Drag `kernel.sys` into `KDMAPPER.exe`:**
   Use [kdmapper](https://github.com/TheCruZ/kdmapper) to map the driver into memory. Simply drag and drop the `kernel.sys` file into `KDMAPPER.exe`.

4. **Start CS2:**
   Launch CS2 before starting Wyvern.

5. **Start `wyvern.exe`:**
   Run the `wyvern.exe` executable to begin using the driver.

### Usage

After installation, you can use Wyvern to access process memory directly through provided interfaces. Refer to the documentation for detailed usage instructions.

## Exmaple of working with memory data

**This example is based on memory handling in CS2**
```cpp
HANDLE driver = driver_utills::open_driver_handle();

DWORD procid = driver_utills::find_proccess_id(L"cs2.exe"): 
const std::uintptr_t client = driver_utills::module_base(procid, L"client.dll"); 

driver::attach_to_process(driver, procid)

driver::write_memory<int>(driver_handle, memory_address(client + offset), value);
driver::read_memory<int>(driver_handle, memory_address(client + offset));
```

## Troubleshooting
**Failed to create driver handle** 

Make sure that driver is installed(drag kernel.sys into kdmapper.exe).

**Wyvern.exe deleting by windows defender**

Disable windows defender, try to build application again.

**Your vulnerable driver list is enabled and have blocked the driver loading, you must disable vulnerable driver list to use kdmapper with intel driver**

Disable antivirus, check if there's no enabled AC(faceit, valorant etc.).
Try to find your error in [kdmapper issues](github.com/thecruz/kdmapper/issues/).

**Cant build project**

Make sure that VS runned as administrator and you already download [WindowsDriverKit](https://learn.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk).
Download the individual components with the Spectre add-ons. (Step 1 when installing the driver kit)

