/**
 * @file rpp_info.c
 * @brief Demo application to query and display RPP device information
 * 
 * This program demonstrates how to retrieve device information including:
 * - Device temperature
 * - Power consumption
 * - GPU loading/utilization
 */

#include "ae_smi_common.h"
#include "hl_api.h"
#include "hl_api_developer.h"


/**
 * @brief Main function to query and display RPP device information
 * 
 * @param argc Number of command-line arguments (unused)
 * @param argv Command-line arguments (unused)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char **argv) {
    int count;              // Number of RPP devices detected
    info_type type;         // Type of information returned (unused in this demo)
    info_name module;       // Information module to query (TEMP, POW, etc.)
    uint32_t len;           // Length of returned data (unused in this demo)
    double double_value;    // Value returned from device info queries
    
    // Get the number of available RPP devices in the system
    count = get_rdev_count();
    
    // Initialize all RPP devices - must be called before querying device information
    init_odev();
    
    // Iterate through each detected device and query its information
    for(int i = 0; i < count; i++) {
        printf("device %d:\n", i);
        
        // Query device temperature
        // INFO_TEMP requests the current temperature reading from the device
        module = INFO_TEMP;
        get_dev_info(i, module, &type, &double_value, &len);
        printf("TEMP: %-.2lfC\n", double_value);
        
        // Query device power consumption
        // Note: Power measurement requires the device to be powered on
        // get_pow_on() enables power measurement, get_pow_off() disables it
        module = INFO_POW;
        get_pow_on(i);  // Enable power measurement for device i
        get_dev_info(i, module, &type, &double_value, &len);
        get_pow_off(i); // Disable power measurement to save resources
        printf("POW: %-.3lfW\n", double_value);
        
        // Query GPU loading/utilization
        // get_gpu_loading_info() measures GPU utilization over a time period
        // Parameter 1 = measurement duration in units (approximately 200ms per unit)
        // Returns utilization as a fraction (0.0 to 1.0), multiply by 100 for percentage
        get_gpu_loading_info(i, &type, &double_value, &len, 1);  // 1 unit ≈ 200ms
        printf("GPU: %.2f%%\n", 100 * double_value);
        
        printf("\n");  // Blank line between devices for readability
    }
    
    // Clean up: close all initialized devices and release resources
    close_odev();
    
    return EXIT_SUCCESS;
}


