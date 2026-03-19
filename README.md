# AE-SMI Tool (RPP Status Monitor)

![AE Logo](images/logo_color_horizontal.png)

`ae-smi-tool` is a lightweight C/C++ utility toolkit for AE-SMI that helps users monitor RPP runtime status and validate device-management capabilities on supported hardware.

It currently includes:
- `rpp-info`: monitor RPP runtime status (temperature, power, RPP loading)
- `ae-smi-fan-control`: test fan control (auto/manual mode and speed levels)

## Description

This project is intended for bring-up, validation, and diagnostics of RPP accelerator cards. It provides:
- A status monitor tool for telemetry collection (temperature, power, RPP loading)
- A fan-control tool for thermal policy verification on hardware that supports fan management

## Hardware Support Notice

- **Fan control is supported only on PCIe cards.**
- **M.2 cards do not support fan control.**
- `rpp-info` monitoring can still be used on both PCIe and M.2 cards when the device is detected by the driver.

## Features

- Monitor per-device RPP status:
  - Temperature (`INFO_TEMP`)
  - Power (`INFO_POW`)
  - RPP loading/utilization
- Enumerate and query multiple devices
- Fan control validation:
  - Enable/disable auto fan mode
  - Set manual fan speed level (`0-6`)
  - Read current fan speed percentage
- Self-contained build dependencies from `lib/`

## Project Layout

```text
ae-smi-tool/
├── CMakeLists.txt
├── tools/
│   ├── fan-control/
│   │   ├── CMakeLists.txt
│   │   └── fan_speed_control_demo.c
│   └── rpp-info/
│       ├── CMakeLists.txt
│       └── rpp_info.c
├── images/
│   └── logo_color_horizontal.png
├── inc/
│   ├── ae_smi_common.h
│   ├── ae_smi_version.h
│   ├── hl_api_developer.h
│   ├── hl_api.h
│   └── rpp_info.h
└── lib/
    ├── librpp_smi.a
    ├── librpp_osal_a.a
    └── libuv_a.a
```

## Build

From project root:

```bash
mkdir -p build
cd build
cmake ..
make -j
```

Generated binaries:
- `build/tools/rpp-info/rpp-info`
- `build/tools/fan-control/ae-smi-fan-control`

## Usage

### 1) Monitor RPP Status (`rpp-info`)

```bash
./build/tools/rpp-info/rpp-info
```

Expected output format:

```text
device 0:
TEMP: 45.23C
POW: 12.345W
RPP: 35.67%
```

For each detected device, the tool:
1. Initializes device context
2. Reads temperature
3. Enables power measurement, reads power, then disables power measurement
4. Reads RPP loading
5. Cleans up device resources

### 2) Fan Control Tool (`ae-smi-fan-control`)

```bash
./build/tools/fan-control/ae-smi-fan-control
```

This tool walks through:
- Query current fan speed
- Enable automatic fan mode
- Switch to manual mode and set fan levels `0..6`
- Restore automatic mode

> **Important:** Run `ae-smi-fan-control` only on PCIe cards. M.2 cards do not provide fan-control capability.

## Dependencies

Bundled static libraries in `lib/`:
- `librpp_smi.a`
- `librpp_osal_a.a`
- `libuv_a.a`

System libraries linked by CMake:
- `pthread`
- `dl`
- `rt`

## Troubleshooting

- **No devices found**
  - Confirm RPP device is connected and powered
  - Check driver/module status
- **Permission denied**
  - Run with `sudo` if your device node permissions require it
- **Link/build failures**
  - Verify files in `lib/` exist and are readable
  - Clean rebuild:
    ```bash
    rm -rf build
    mkdir build && cd build
    cmake ..
    make -j
    ```

## Version

- AE-SMI: `3.0.3.17`
- Platform: Linux
- Build: CMake + Make

## Notes

- Fan level mapping (`0-6` to percentage) may differ by hardware/firmware.
- Fan control API behavior applies to PCIe cards only; M.2 cards do not support fan control.
- For multi-device scenarios, update source logic if you want custom filtering behavior.
