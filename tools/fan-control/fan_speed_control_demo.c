/**
 * @file fan_speed_control_demo.c
 * @brief Exercise AE-SMI fan-control APIs for an RPP card. See ae-smi-tool/README.md for workflow details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ae_smi_common.h"
#include "hl_api_developer.h"
#include "hl_api.h"
#include "string.h"

#define FAIL_AND_EXIT_ON_ERROR(step_desc, ret_code)                                      \
    do {                                                                                  \
        if ((ret_code) != RPP_SUCCESS) {                                                  \
            printf("ERROR: %s failed (error code %d).\n", (step_desc), (ret_code));      \
            printf("Fan control is supported on PCIe cards only; M.2 cards are not supported.\n"); \
            exit_code = EXIT_FAILURE;                                                     \
            goto cleanup;                                                                 \
        }                                                                                 \
    } while (0)
/**
 * @brief Switch a device into manual mode and request a specific fan-speed level.
 * @param dev_id Device index reported by the AE-SMI runtime.
 * @param fan_speed Fan-speed level written into thermal control; this demo uses levels 0-6.
 * @return RPP_SUCCESS on success, otherwise the AE-SMI error code from rpp_dev_ctrl.
 */
RPPReturn_t set_fan_speed_manual(uint32_t dev_id, uint32_t fan_speed)
{
    thermal_rw thermal_control;
    RPPReturn_t ret;
    
    // Start from a clean thermal control payload before setting only the fields this command needs.
    RESET_ALL(thermal_control.valid);
    
    // Tell firmware to leave automatic fan policy and accept a manual speed request.
    thermal_control.set_auto = AUTO_DISABLE;
    SET_VALID(sys_cmd_set_auto_valid, thermal_control.valid);
    
    // Provide the requested fan-speed level in the writable thermal-control field.
    thermal_control.fan_speed_w = fan_speed & 0x1f;
    SET_VALID(sys_cmd_fan_speed_w_valid, thermal_control.valid);
    
    // rpp_dev_ctrl: send the thermal control command to the selected device.
    ret = rpp_dev_ctrl(dev_id, SUBCMD_SET_THERMAL_CTRL, &thermal_control);
    
    if (ret == RPP_SUCCESS) {
        printf("Successfully set fan speed to %u\n", fan_speed);
    } else {
        printf("Failed to set fan speed: error code %d\n", ret);
    }
    
    return ret;
}

/**
 * @brief Enable or disable the device's automatic thermal policy.
 * @param dev_id Device index reported by the AE-SMI runtime.
 * @param enable Non-zero to enable auto mode, zero to disable it.
 * @return RPP_SUCCESS on success, otherwise the AE-SMI error code from rpp_dev_ctrl.
 */
RPPReturn_t set_fan_auto_mode(uint32_t dev_id, int enable)
{
    thermal_rw thermal_control;
    RPPReturn_t ret;
    
    // Start from a clean thermal control payload before setting the auto-mode field.
    RESET_ALL(thermal_control.valid);
    
    // Select whether firmware should own fan decisions or wait for manual requests.
    thermal_control.set_auto = enable ? AUTO_ENABLE : AUTO_DISABLE;
    SET_VALID(sys_cmd_set_auto_valid, thermal_control.valid);
    
    // rpp_dev_ctrl: send the thermal control command to the selected device.
    ret = rpp_dev_ctrl(dev_id, SUBCMD_SET_THERMAL_CTRL, &thermal_control);
    
    if (ret == RPP_SUCCESS) {
        printf("Successfully %s automatic fan control\n", enable ? "enabled" : "disabled");
    } else {
        printf("Failed to %s automatic fan control: error code %d\n", 
               enable ? "enable" : "disable", ret);
    }
    
    return ret;
}

/**
 * @brief Read the current fan-speed percentage exposed by the telemetry path.
 * @param dev_id Device index reported by the AE-SMI runtime.
 * @param fan_speed Output parameter that receives the current fan percentage.
 * @return RPP_SUCCESS on success, otherwise the AE-SMI error code from get_dev_info.
 */
RPPReturn_t get_fan_speed_current(uint32_t dev_id, uint32_t *fan_speed)
{
    info_type type;
    uint32_t len;
    RPPReturn_t ret;
    
    // get_dev_info(INFO_FAN_SPEED): read the fan-speed telemetry item for this device.
    ret = get_dev_info(dev_id, INFO_FAN_SPEED, &type, fan_speed, &len);
    
    if (ret == RPP_SUCCESS) {
        printf("Current fan speed: %u%%\n", *fan_speed);
    } else {
        printf("Failed to get fan speed: error code %d\n", ret);
    }
    
    return ret;
}

/**
 * @brief Run a simple end-to-end fan-control validation flow on device 0.
 * @param argc Number of command-line arguments; unused because this demo has no CLI options.
 * @param argv Command-line arguments; unused because this demo has no CLI options.
 * @return EXIT_SUCCESS when the flow completes, otherwise EXIT_FAILURE.
 */
int main(int argc, char **argv)
{
    RPPReturn_t ret;
    uint32_t dev_id = 0;  // Demo target: first detected device.
    uint32_t device_count;
    uint32_t current_fan_speed;
    int exit_code = EXIT_SUCCESS;
    
    printf("=== Fan Speed Control Tool ===\n\n");
    printf("WARNING: Fan control is supported on PCIe cards only.\n");
    printf("WARNING: M.2 cards do not support fan control APIs.\n\n");
    
    // get_rdev_count: discover how many AE-SMI devices the driver currently exposes.
    device_count = get_rdev_count();
    if (device_count == 0) {
        printf("Error: No devices found!\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %u device(s)\n", device_count);
    
    // init_odev: open the driver-side device context before sending thermal commands.
    printf("\nInitializing devices...\n");
    ret = init_odev();
    if (ret != RPP_SUCCESS) {
        printf("Error: Failed to initialize devices: %d\n", ret);
        return EXIT_FAILURE;
    }
    printf("Devices initialized successfully\n");
    
    // Read the baseline fan-speed telemetry before changing thermal policy.
    printf("\n--- Example 1: Get current fan speed ---\n");
    // init_reg: refresh the register view used by this device-management path.
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("reading current fan speed", ret);
    
    // Switch the device into automatic fan mode first so the demo starts from the default policy.
    printf("\n--- Example 2: Enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("enabling automatic fan mode", ret);
    
    // Give firmware a moment to apply the thermal-policy change.
    sleep(1);
    
    // Move into manual mode and start from the lowest fan-speed level.
    printf("\n--- Example 3: Set manual fan speed to 0%% (speed level 0) ---\n");
    ret = set_fan_speed_manual(dev_id, 0);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 0", ret);
    
    // Re-read telemetry after each write so the operator can verify the applied result.
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 0", ret);
    
   
    // Walk the remaining manual levels so bring-up engineers can validate the fan table.
    printf("\n--- Example 5: Set fan to minimum speed (speed level 1 = 17%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 1", ret);
    
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 1", ret);
    
    // Keep stepping the manual setpoint upward and verify after each command.
    printf("\n--- Example 6: Set fan to 25%% speed (speed level 2 = 33%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 2);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 2", ret);
    
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 2", ret);

    // Keep stepping the manual setpoint upward and verify after each command.
    printf("\n--- Example 6: Set fan to 50%% speed (speed level 3 = 50%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 3);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 3", ret);
    
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 3", ret);

    // Keep stepping the manual setpoint upward and verify after each command.
    printf("\n--- Example 6: Set fan to 67%% speed (speed level 4 = 67%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 4);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 4", ret);
   
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 4", ret);

    // Keep stepping the manual setpoint upward and verify after each command.
    printf("\n--- Example 6: Set fan to 83%% speed (speed level 5 = 83%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 5);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 5", ret);
   
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 5", ret);

    // Finish the manual sweep at the highest demo level.
    printf("\n--- Example 4: Set fan to maximum speed (speed level 6 = 100%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 6);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 6", ret);
    
    sleep(1);
    init_reg(dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 6", ret);

    // Hand thermal control back to firmware before the tool exits.
    printf("\n--- Example 6: Re-enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("re-enabling automatic fan mode", ret);
    
cleanup:
    // close_odev: release the AE-SMI device handles opened by init_odev.
    printf("\n--- Cleaning up ---\n");
    ret = close_odev();
    if (ret != RPP_SUCCESS) {
        printf("Warning: Error during cleanup: %d\n", ret);
    } else {
        printf("Cleanup successful\n");
    }
    
    if (exit_code == EXIT_SUCCESS) {
        printf("\n=== Tool completed ===\n");
    } else {
        printf("\n=== Tool aborted due to fan-control API failure ===\n");
    }
    return exit_code;
}
