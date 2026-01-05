/**
 * @file fan_speed_control_demo.c
 * @brief Demo code demonstrating how to control fan speed using the thermal control API
 * 
 * This demo shows:
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
 * @brief Main function demonstrating fan speed control
 */
int main(int argc, char **argv)
{
    RPPReturn_t ret;
    uint32_t dev_id = 0;  // Use device 0 (change if you have multiple devices)
    uint32_t device_count;
    uint32_t current_fan_speed;
    
    printf("=== Fan Speed Control Demo ===\n\n");
    
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
    if (ret != RPP_SUCCESS) {
        printf("Warning: Could not read current fan speed\n");
    }
    
    // Example 2: Enable automatic fan control
    printf("\n--- Example 2: Enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to enable auto mode\n");
    }
    
    // Wait a moment for the change to take effect
    sleep(1);
    
    // Example 3: Disable auto mode and set manual speed to 0% (speed level 0 = 0%)
    printf("\n--- Example 3: Set manual fan speed to 0%% (speed level 0) ---\n");
    ret = set_fan_speed_manual(dev_id, 0);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to set manual fan speed\n");
    }
    
    // Verify the change
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    
   
    // Example 4: Set fan to 17% speed (speed level 1 = 17%)
    printf("\n--- Example 5: Set fan to minimum speed (speed level 1 = 17%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 1);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to set fan to minimum speed\n");
    }
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);
    
    // Example 5: Set fan to 33% speed (speed level 2 = 33%)
    printf("\n--- Example 6: Set fan to 25%% speed (speed level 2 = 33%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 2);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to set fan to 33%% speed\n");
    }
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);

    // Example 6: Set fan to 50% speed (speed level 3 = 50%)
    printf("\n--- Example 6: Set fan to 50%% speed (speed level 3 = 50%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 3);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to set fan to 50%% speed\n");
    }
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);

   // Example 7: Set fan to 67% speed (speed level 4 = 67%)
   printf("\n--- Example 6: Set fan to 67%% speed (speed level 4 = 67%%) ---\n");
   ret = set_fan_speed_manual(dev_id, 4);
   if (ret != RPP_SUCCESS) {
       printf("Warning: Failed to set fan to 67%% speed\n");
   }
   
   sleep(1);
   init_reg( dev_id);
   ret = get_fan_speed_current(dev_id, &current_fan_speed);

    // Example 8: Set fan to 83% speed (speed level 5 = 83%)
   printf("\n--- Example 6: Set fan to 83%% speed (speed level 5 = 83%%) ---\n");
   ret = set_fan_speed_manual(dev_id, 5);
   if (ret != RPP_SUCCESS) {
       printf("Warning: Failed to set fan to 83%% speed\n");
   }
   
   sleep(1);
   init_reg( dev_id);
   ret = get_fan_speed_current(dev_id, &current_fan_speed);

    // Example 9: Set fan to maximum speed (speed level 6 = 100%)
    printf("\n--- Example 4: Set fan to maximum speed (speed level 6 = 100%%) ---\n");
    ret = set_fan_speed_manual(dev_id, 6);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to set fan to maximum speed\n");
    }
    
    sleep(1);
    init_reg( dev_id);
    ret = get_fan_speed_current(dev_id, &current_fan_speed);

    // Example 10: Re-enable automatic fan control
    printf("\n--- Example 6: Re-enable automatic fan control ---\n");
    ret = set_fan_auto_mode(dev_id, 1);
    if (ret != RPP_SUCCESS) {
        printf("Warning: Failed to re-enable auto mode\n");
    }
    
    // Clean up
    printf("\n--- Cleaning up ---\n");
    ret = close_odev();
    if (ret != RPP_SUCCESS) {
        printf("Warning: Error during cleanup: %d\n", ret);
    } else {
        printf("Cleanup successful\n");
    }
    
    printf("\n=== Demo completed ===\n");
    return EXIT_SUCCESS;
}

