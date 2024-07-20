## Wyvern Kernel Driver

**Wyvern** is a kernel driver designed to facilitate the transmission and reception of memory from any process via the computer's kernel.

**Wyvern** based for cs2 hacking. But, if you recode the source, it can be used for any games/apps.

### Features
- **Direct Memory Access:** Transmit and receive memory from any process.

### Installation

To install the Wyvern kernel driver, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/snyakocode/wyvernkern.git
   cd wyvern
   ```

2. **Build the Project in x64 Version:**
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

```cpp
Driver driver_handle;
const std::uintptr_t client = driver::module_base(); // client.dll

driver::write_memory(driver_handle, memory_address(client + offset), value);

driver::read_memory(driver_handle, memory_address(client + offset));
```
---
