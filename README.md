# AE-SMI Fan Control Demo

## Overview

This project provides a demonstration application for controlling fan speed on RPP devices using the AE-SMI API. The demo shows how to:

- Set fan speed manually (0-6 levels, typically mapping to 0%, 17%, 33%, 50%, 67%, 83%, 100%)
- Enable/disable automatic fan control
- Query current fan speed
- Properly initialize and manage devices

## Project Structure

```
ae-smi-fan-control/
├── CMakeLists.txt          # Root CMake configuration
├── demo/                   # Demo application directory
│   ├── CMakeLists.txt      # Demo CMake configuration
│   └── fan_speed_control_demo.c  # Main demo source code
├── inc/                    # Header files
│   ├── ae_smi_common.h
│   ├── ae_smi_version.h
│   ├── hl_api_developer.h
│   ├── hl_api.h
│   └── rpp_info.h
└── lib/                    # Static libraries (all dependencies included)
    ├── librpp_smi.a        # AE-SMI library
    ├── librpp_osal_a.a     # RPP OS Abstraction Layer library
    └── libuv_a.a           # libuv static library
```

## Prerequisites

### Required Dependencies

All required libraries are included in the `lib/` directory:

1. **librpp_smi.a** - Main AE-SMI library
2. **librpp_osal_a.a** - RPP OS Abstraction Layer library
3. **libuv_a.a** - libuv static library (for mutex functions)

### System Libraries

The following system libraries are automatically linked:
- `pthread` - POSIX threads
- `dl` - Dynamic linking
- `rt` - Real-time extensions

**Note:** All static libraries are bundled in the `lib/` directory. No additional library installation or path configuration is required.

## Building the Demo

### Option 1: Using CMake (Recommended)

1. **Create a build directory:**
   ```bash
   cd ae-smi-fan-control
   mkdir build
   cd build
   ```

2. **Configure the build:**
   ```bash
   cmake ..
   ```

3. **Build the demo:**
   ```bash
   make
   ```

The executable will be created as `build/demo/ae-smi-fan-demo`.

### Clean Build Artifacts

To clean build artifacts when using CMake:
```bash
cd build
make clean
```

## Running the Demo

### Prerequisites

1. **Device Connection:**
   - Ensure the RPP device is properly connected and recognized by the system
   - Verify device drivers are loaded

2. **Permissions:**
   - The application may require root/sudo privileges to access hardware devices
   - Run with appropriate permissions if needed:
     ```bash
     sudo ./build/demo/ae-smi-fan-demo
     ```

### Running the Demo

The demo takes no command-line arguments and runs automatically through a series of examples:

```bash
cd build/demo
./ae-smi-fan-demo
```

Or from the project root:
```bash
./build/demo/ae-smi-fan-demo
```

### Demo Execution Flow

The demo automatically executes the following sequence:

1. **Device Detection & Initialization:**
   - Detects available RPP devices
   - Initializes the device (default: device ID 0)
   - Reports device count and initialization status

2. **Example 1: Query Current Fan Speed**
   - Reads and displays the current fan speed percentage

3. **Example 2: Enable Automatic Fan Control**
   - Enables automatic fan control mode
   - System will manage fan speed based on temperature

4. **Example 3-9: Manual Fan Speed Control**
   - Disables automatic mode
   - Sets fan to various speed levels:
     - Level 0: 0% speed
     - Level 1: 17% speed (minimum)
     - Level 2: 33% speed
     - Level 3: 50% speed
     - Level 4: 67% speed
     - Level 5: 83% speed
     - Level 6: 100% speed (maximum)
   - After each change, waits 1 second and verifies the new speed

5. **Example 10: Re-enable Automatic Mode**
   - Restores automatic fan control

6. **Cleanup:**
   - Properly closes and cleans up device resources

### Expected Output

```
=== Fan Speed Control Demo ===

Found 1 device(s)

Initializing devices...
Devices initialized successfully

--- Example 1: Get current fan speed ---
Current fan speed: 50%

--- Example 2: Enable automatic fan control ---
Successfully enabled automatic fan control

--- Example 3: Set manual fan speed to 0% (speed level 0) ---
Successfully set fan speed to 0
Current fan speed: 0%

[... continues through all speed levels ...]

--- Example 10: Re-enable automatic fan control ---
Successfully enabled automatic fan control

--- Cleaning up ---
Cleanup successful

=== Demo completed ===
```

### Fan Speed Levels

The demo uses speed levels 0-6, which typically map to the following percentages:

| Speed Level | Fan Speed | Description |
|------------|-----------|-------------|
| 0 | 0% | Fan off |
| 1 | 17% | Minimum speed |
| 2 | 33% | Low speed |
| 3 | 50% | Medium speed |
| 4 | 67% | Medium-high speed |
| 5 | 83% | High speed |
| 6 | 100% | Maximum speed |

**Note:** The actual fan speed percentages may vary depending on your specific hardware implementation.

## API Usage Examples

### Setting Fan Speed Manually

```c
RPPReturn_t ret = set_fan_speed_manual(dev_id, fan_speed);
// fan_speed: 0-6 (typically maps to 0%, 17%, 33%, 50%, 67%, 83%, 100%)
```

### Enabling/Disabling Automatic Fan Control

```c
// Enable automatic mode
RPPReturn_t ret = set_fan_auto_mode(dev_id, 1);

// Disable automatic mode (enable manual control)
RPPReturn_t ret = set_fan_auto_mode(dev_id, 0);
```

### Querying Current Fan Speed

```c
uint32_t current_speed;
RPPReturn_t ret = get_fan_speed_current(dev_id, &current_speed);
// current_speed will contain the percentage (0-100)
```

## Troubleshooting

### Library Not Found Errors

If you encounter library not found errors during linking:

1. **Verify all libraries are present:**
   ```bash
   ls -la lib/
   ```
   You should see:
   - `librpp_smi.a`
   - `librpp_osal_a.a`
   - `libuv_a.a`

2. **Check library file permissions:**
   ```bash
   file lib/*.a
   ```
   All files should be valid static library archives

3. **Clean and rebuild:**
   ```bash
   cd build
   rm -rf *
   cmake ..
   make
   ```

### Device Initialization Errors

- **"No devices found!"**
  - Ensure the RPP device is properly connected via PCIe
  - Verify device drivers are loaded: `lsmod | grep rpp`
  - Check device visibility: `lspci | grep -i rpp` (or your device identifier)
  - Ensure the device is powered on

- **"Failed to initialize devices"**
  - Check device status and system logs: `dmesg | tail -50`
  - Verify you have proper permissions (try running with `sudo`)
  - Ensure no other process is using the device

- **Permission denied errors**
  - Run with sudo: `sudo ./build/demo/ae-smi-fan-demo`
  - Or add your user to the appropriate device group (if configured)

- **"Failed to set fan speed" or "Failed to get fan speed"**
  - Verify the device supports thermal control
  - Check that the device is fully initialized
  - Review error codes in the output for specific failure reasons

### Build Errors

- **CMake version:** Requires CMake 2.8 or higher (3.5 recommended)
- **Compiler:** Requires GCC or compatible C compiler
- **Missing headers:** Ensure all header files are present in the `inc/` directory

## Version Information

- **AE-SMI Version:** 3.0.3.17
- **Build System:** CMake 2.8+ / Make
- **Platform:** Linux

## Support

For issues or questions:
1. Check the troubleshooting section above
2. Verify all dependencies are installed correctly
3. Ensure the RPP device is properly configured
4. Review system logs for additional error information

## License

[Specify your license here]

## Additional Notes

### Important Considerations

- **Fan Speed Mapping:** The fan speed values (0-6) and their percentage mappings may vary depending on your specific hardware implementation. Refer to your hardware documentation for exact mappings.

- **Manual vs Automatic Mode:** Manual fan control requires disabling automatic mode first. The demo automatically handles this sequence.

- **Error Handling:** Always check return codes (`RPPReturn_t`) to ensure operations succeed. The demo includes error checking and will report failures.

- **Device ID:** The demo uses device ID 0 by default. For multi-device systems, modify the `dev_id` variable in `main()` to target a specific device.

- **Timing:** The demo includes 1-second delays (`sleep(1)`) between operations to allow the hardware to process changes. In production code, you may want to verify changes have taken effect rather than using fixed delays.

- **Cleanup:** The demo properly cleans up device resources at the end. Always call `close_odev()` when finished to release device handles.

### Modifying the Demo

To customize the demo behavior, edit `demo/fan_speed_control_demo.c`:

- Change the default device ID: Modify `uint32_t dev_id = 0;` in `main()`
- Add custom speed sequences: Add additional `set_fan_speed_manual()` calls
- Adjust timing: Modify `sleep()` durations or add verification loops
- Add command-line arguments: Parse `argc`/`argv` to accept device ID or speed level as parameters

