/**
 * @file rpp_info.c
 * @brief Query RPP telemetry from AE-SMI devices. See ae-smi-tool/README.md for workflow details.
 */

#include "ae_smi_common.h"
#include "hl_api.h"
#include "hl_api_developer.h"


/**
 * @brief Enumerate detected devices and print temperature, power, and RPP loading for each one.
 * @param argc Number of command-line arguments; unused because this demo has no CLI options.
 * @param argv Command-line arguments; unused because this demo has no CLI options.
 * @return EXIT_SUCCESS after the monitoring pass completes.
 */
int main(int argc, char **argv) {
    int count;              // Number of AE-SMI devices reported by the driver.
    info_type type;         // Metadata returned by get_dev_info/get_gpu_loading_info.
    info_name module;       // Telemetry selector passed into get_dev_info.
    uint32_t len;           // Payload length returned by the driver for the query.
    double double_value;    // Numeric telemetry value returned by the current query.
    
    // get_rdev_count: discover how many RPP devices the AE-SMI driver currently exposes.
    count = get_rdev_count();
    
    // init_odev: open the driver-side device context before reading telemetry.
    init_odev();
    
    // Walk each detected device and print the three telemetry values this monitor exposes.
    for(int i = 0; i < count; i++) {
        printf("device %d:\n", i);
        
        // Read the current board temperature from the AE-SMI telemetry interface.
        module = INFO_TEMP;
        get_dev_info(i, module, &type, &double_value, &len);
        printf("TEMP: %-.2lfC\n", double_value);
        
        // Enable the power sensor, fetch board power, then turn the measurement path back off.
        module = INFO_POW;
        // get_pow_on: enable the power-read path for this device.
        get_pow_on(i);
        // get_dev_info: read the selected telemetry item from the driver.
        get_dev_info(i, module, &type, &double_value, &len);
        // get_pow_off: close the temporary power-read path after the sample is collected.
        get_pow_off(i);
        printf("POW: %-.3lfW\n", double_value);
        
        // Sample accelerator loading over one short observation window and report it as a percentage.
        // get_gpu_loading_info: measure RPP busy ratio for the requested device.
        get_gpu_loading_info(i, &type, &double_value, &len, 1);  // One sample window; library returns 0.0-1.0.
        printf("RPP: %.2f%%\n", 100 * double_value);
        
        // Keep one blank line between devices so multi-card output is easier to scan.
        printf("\n");
    }
    
    // close_odev: release the AE-SMI device handles opened by init_odev.
    close_odev();
    
    return EXIT_SUCCESS;
}

