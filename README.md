# AE-SMI Tool

![AE Logo](images/logo_color_horizontal.png)

`ae-smi-tool` is a small AE-SMI utility package for RPP accelerator cards. It provides one tool to monitor card status and one tool to exercise chip-level thermal control on hardware that supports fan management.

The current toolkit includes:
- `rpp-info`: read card telemetry such as temperature, power, and RPP loading
- `ae-smi-fan-control`: switch fan policy between auto/manual and validate manual speed levels

## What This Module Does

This project is aimed at bring-up, validation, and field diagnostics for RPP cards. The host program runs on the CPU, talks to the AE-SMI driver/runtime, and either:
- collects telemetry from detected devices
- sends thermal control commands to a selected device

## Hardware And Runtime Notes

- **RPP** in this repository refers to the accelerator card managed by the AE-SMI runtime.
- `rpp-info` uses the telemetry path exposed by APIs such as `get_rdev_count`, `init_odev`, `get_dev_info`, `get_pow_on`, `get_pow_off`, and `get_gpu_loading_info`.
- `ae-smi-fan-control` uses `rpp_dev_ctrl` with `SUBCMD_SET_THERMAL_CTRL` plus `get_dev_info(INFO_FAN_SPEED)` to validate thermal control.
- **Fan control is supported only on PCIe cards.**
- **M.2 cards do not support fan control.**
- `rpp-info` can still be used on both PCIe and M.2 cards when the device is detected by the driver.

## Workflow

### `rpp-info`

1. Call `get_rdev_count` to discover how many devices the driver exposes.
2. Call `init_odev` to open the AE-SMI device context.
3. For each device:
   - read `INFO_TEMP`
   - enable power readout with `get_pow_on`, read `INFO_POW`, then call `get_pow_off`
   - call `get_gpu_loading_info` to sample RPP loading
4. Call `close_odev` to release all device handles.

### `ae-smi-fan-control`

1. Call `get_rdev_count` and `init_odev`.
2. Select device `0` in the demo flow.
3. Read the current fan speed with `get_dev_info(INFO_FAN_SPEED)`.
4. Enable auto mode.
5. Disable auto mode and sweep manual levels `0` through `6`.
6. After each write, refresh the register view with `init_reg` and read back the current fan speed.
7. Re-enable auto mode and close the device context with `close_odev`.

## Workflow Diagram

```text
+------------------+
| rpp-info         |
+------------------+
         |
         v
+------------------+
| get_rdev_count   |
+------------------+
         |
         v
+------------------+
| init_odev        |
+------------------+
         |
         v
+--------------------------------------+
| for each detected device             |
| - get_dev_info(INFO_TEMP)            |
| - get_pow_on                         |
| - get_dev_info(INFO_POW)             |
| - get_pow_off                        |
| - get_gpu_loading_info               |
| - print TEMP / POW / RPP             |
+--------------------------------------+
         |
         v
+------------------+
| close_odev       |
+------------------+

+----------------------+
| ae-smi-fan-control   |
+----------------------+
           |
           v
+------------------+
| get_rdev_count   |
+------------------+
           |
           v
+------------------+
| init_odev        |
+------------------+
           |
           v
+------------------------------+
| select device 0              |
| init_reg                     |
| get_dev_info(INFO_FAN_SPEED) |
+------------------------------+
           |
           v
+------------------------------+
| set_fan_auto_mode(1)         |
| set_fan_speed_manual(0..6)   |
| init_reg + read back speed   |
+------------------------------+
           |
           v
+------------------+
| set_fan_auto(1)  |
| close_odev       |
+------------------+
```

## Summary

| Tool | Main APIs | Purpose |
| --- | --- | --- |
| `rpp-info` | `get_rdev_count`, `init_odev`, `get_dev_info`, `get_pow_on`, `get_pow_off`, `get_gpu_loading_info`, `close_odev` | Monitor RPP card telemetry |
| `ae-smi-fan-control` | `get_rdev_count`, `init_odev`, `init_reg`, `get_dev_info`, `rpp_dev_ctrl`, `close_odev` | Validate chip fan-control behavior on PCIe cards |

## Project Layout

Source-controlled files:

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

`build/` is not part of the repository layout. It is a generated build directory created locally when you run CMake.

## Build

From the project root, create an out-of-tree `build/` directory first:

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

### Monitor RPP Status

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

### Validate Fan Control

```bash
./build/tools/fan-control/ae-smi-fan-control
```

This demo walks through:
- query current fan speed
- enable automatic fan mode
- switch to manual mode and set fan levels `0..6`
- read back fan speed after each change
- restore automatic mode before exit

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

- Fan level mapping for manual control is firmware-dependent; this demo documents the common `0-6` validation flow only.
- `ae-smi-fan-control` currently targets device `0`; extend the source if you need a device-selection CLI.
- The telemetry and fan-control tools are both demos, so they currently print results directly instead of emitting machine-readable output.
