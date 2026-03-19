/**
 * @file fan_speed_control_demo.c
 * @brief Tool code demonstrating how to control fan speed using the thermal control API
 * 
 * This tool shows:
 * - How to set fan speed manually (typically 0-6 for 0%, 17%, 33%, 50%, 67%, 83%, 100%)
 * - How to enable/disable automatic fan control
 * - Proper error handling and device initialization
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
 * @brief Set fan speed manually (disable auto mode and set specific speed)
 * 
 * @param dev_id Device ID (0 for single card, or specific device ID for multiple cards)
 * @param fan_speed Fan speed value (0-31, where 0-6 typically map to: 0%, 17%, 33%, 50%, 67%, 83%, 100%)
 * @return RPPReturn_t RPP_SUCCESS on success, error code on failure
 */
RPPReturn_t set_fan_speed_manual(uint32_t dev_id, uint32_t fan_speed)
{
    thermal_rw thermal_control;
    RPPReturn_t ret;
    
    // Clear all valid flags
    RESET_ALL(thermal_control.valid);
    
    // Disable auto mode to enable manual control
    thermal_control.set_auto = AUTO_DISABLE;
    SET_VALID(sys_cmd_set_auto_valid, thermal_control.valid);
    
    // Set fan speed (typically use 0-6)
    thermal_control.fan_speed_w = fan_speed & 0x1f;  // Mask to ensure valid range
    SET_VALID(sys_cmd_fan_speed_w_valid, thermal_control.valid);
    
    // Apply the thermal control settings
    ret = rpp_dev_ctrl(dev_id, SUBCMD_SET_THERMAL_CTRL, &thermal_control);
    
    if (ret == RPP_SUCCESS) {
        printf("Successfully set fan speed to %u\n", fan_speed);
    } else {
        printf("Failed to set fan speed: error code %d\n", ret);
    }
    
    return ret;
}

/**
 * @brief Enable or disable automatic fan control
 * 
 * @param dev_id Device ID (0 for single card, or specific device ID for multiple cards)
 * @param enable 1 to enable auto mode, 0 to disable auto mode
 * @return RPPReturn_t RPP_SUCCESS on success, error code on failure
 */
RPPReturn_t set_fan_auto_mode(uint32_t dev_id, int enable)
{
    thermal_rw thermal_control;
    RPPReturn_t ret;
    
    // Clear all valid flags
    RESET_ALL(thermal_control.valid);
    
    // Set auto mode
    thermal_control.set_auto = enable ? AUTO_ENABLE : AUTO_DISABLE;
    SET_VALID(sys_cmd_set_auto_valid, thermal_control.valid);
    
    // Apply the thermal control settings
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
 * @brief Get current fan speed
 * 
 * @param dev_id Device ID
 * @param fan_speed Output parameter to store fan speed (0-100%)
 * @return RPPReturn_t RPP_SUCCESS on success, error code on failure
 */
RPPReturn_t get_fan_speed_current(uint32_t dev_id, uint32_t *fan_speed)
{
    info_type type;
    uint32_t len;
    RPPReturn_t ret;
    
    ret = get_dev_info(dev_id, INFO_FAN_SPEED, &type, fan_speed, &len);
    
    if (ret == RPP_SUCCESS) {
        printf("Current fan speed: %u%%\n", *fan_speed);
    } else {
        printf("Failed to get fan speed: error code %d\n", ret);
    }
    
    return ret;
}

/**
 * @brief Main function for fan speed control
 */
int main(int argc, char **argv)
{
    RPPReturn_t ret;
    uint32_t dev_id = 0;  // Use device 0 (change if you have multiple devices)
    uint32_t device_count;
    uint32_t current_fan_speed;
    int exit_code = EXIT_SUCCESS;
    
    printf("=== Fan Speed Control Tool ===\n\n");
    printf("WARNING: Fan control is supported on PCIe cards only.\n");
    printf("WARNING: M.2 cards do not support fan control APIs.\n\n");
    
    // Get device count
    device_count = get_rdev_count();
    if (device_count == 0) {
        printf("Error: No devices found!\n");
        return EXIT_FAILURE;
    }
    
    printf("Found %u device(s)\n", device_count);
    
    // Initialize devices
    printf("\nInitializing devices...\n");
    ret = init_odev();
    if (ret != RPP_SUCCESS) {
        printf("Error: Failed to initialize devices: %d\n", ret);
        return EXIT_FAILURE;
    }
    printf("Devices initialized successfully\n");
    
    // Example 1: Get current fan speed
    printf("\n--- Example 1: Get current fan speed ---\n");
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("reading current fan speed", ret);
    
    // Example 2: Enable automatic fan control
    printf("\n--- Example 2: Enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("enabling automatic fan mode", ret);
    
    // Wait a moment for the change to take effect
    sleep(1);
    
    // Example 3: Disable auto mode and set manual speed to 0% (speed level 0 = 0%)
    printf("\n--- Example 3: Set manual fan speed to 0%% (speed level 0) ---\n");
    ret = set_fan_speed_manual(dev_id, 0);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 0", ret);
    
    // Verify the change
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 0", ret);
    
   
    // Example 4: Set fan to 17% speed (speed level 1 = 17%)
    printf("\n--- Example 5: Set fan to minimum speed (speed level 1 = 17%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 1", ret);
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 1", ret);
    
    // Example 5: Set fan to 33% speed (speed level 2 = 33%)
    printf("\n--- Example 6: Set fan to 25%% speed (speed level 2 = 33%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 2);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 2", ret);
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 2", ret);

    // Example 6: Set fan to 50% speed (speed level 3 = 50%)
    printf("\n--- Example 6: Set fan to 50%% speed (speed level 3 = 50%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 3);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 3", ret);
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 3", ret);

   // Example 7: Set fan to 67% speed (speed level 4 = 67%)
   printf("\n--- Example 6: Set fan to 67%% speed (speed level 4 = 67%%) ---\n");
   ret = set_fan_speed_manual(dev_id, 4);
   FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 4", ret);
   
   sleep(1);
   init_reg( dev_id);
   ret = get_fan_speed_current(dev_id, &current_fan_speed);
   FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 4", ret);

    // Example 8: Set fan to 83% speed (speed level 5 = 83%)
   printf("\n--- Example 6: Set fan to 83%% speed (speed level 5 = 83%%) ---\n");
   ret = set_fan_speed_manual(dev_id, 5);
   FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 5", ret);
   
   sleep(1);
   init_reg( dev_id);
   ret = get_fan_speed_current(dev_id, &current_fan_speed);
   FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 5", ret);

    // Example 9: Set fan to maximum speed (speed level 6 = 100%)
    printf("\n--- Example 4: Set fan to maximum speed (speed level 6 = 100%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 6);
    FAIL_AND_EXIT_ON_ERROR("setting manual fan speed to level 6", ret);
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    FAIL_AND_EXIT_ON_ERROR("verifying fan speed after level 6", ret);

    // Example 10: Re-enable automatic fan control
    printf("\n--- Example 6: Re-enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    FAIL_AND_EXIT_ON_ERROR("re-enabling automatic fan mode", ret);
    
cleanup:
    // Clean up
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

