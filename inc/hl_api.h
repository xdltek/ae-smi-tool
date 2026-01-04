#ifndef __HL_API_H__
#define __HL_API_H__

#include <stdint.h>
#include "ae_smi_common.h"
#include "rpp_info.h"

extern i2c_rw_t rpp_i2c_rw_cmd;
extern pcie_rw rpp_pcie_rw_cmd;
extern struct hal_dev *hdev[RPP_DEVICE_MAX_COUNT];
extern char *Platform[];
extern char *Bar_mode[];
extern char *Enable[];
extern char *BoostModeTriggerLimit[];
extern char *DDR_PRO[];
extern char *DDR_VEN[];
extern char *Chip_version[];
extern uint8_t log_filename[200];
extern uint32_t save_sn;
extern uint32_t cmd_bar;
extern uint32_t cmd_base_addr;
extern uint32_t close_status_init;
extern power_mode_cmd_e power_status;

extern uint32_t get_pmic_status;

RPPReturn_t init_odev(void);
RPPReturn_t init_reg(uint32_t dev_id);
RPPReturn_t close_odev(void);
void start_rpp_status(void);
void stop_rpp_status(void);
void g_set_power_status(uint32_t status);
uint32_t g_get_power_status(void);
void wait_ms_ready(int mode);
/**
 * Obtain basic device information.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * name - Enter the command you want to extract the data;
 * type - Returns the extracted data type;
 * value - Returns the extracted data;
 * len - Returns the length of the "value";
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t get_dev_info(uint32_t dev_id, info_name name, info_type *type, void *value, uint32_t *len);

/**
 * Rescan mpu
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t rpp_rescan(void);


/**
 * Upgrade bootloader
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * b_fname - The bin file for upgarding
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t upgrade_bootloader(uint32_t dev_id, uint8_t *b_fname);

/**
 * Upgrade bootloader config
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * e_fname - The bin file for upgarding
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t upgrade_bootloader_config(uint32_t dev_id, uint8_t *e_fname);

/**
 * Upgrade firmware
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * f_fname - The bin file for upgarding
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t upgrade_firmware(uint32_t dev_id, uint8_t *f_fname);

/**
 * Upgrading the main code in the old architecture
 * !!!!!!Only old architecture
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * k_fname - The bin file for upgarding
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t upgrade_main_code(uint32_t dev_id, uint8_t *k_fname);

/**
 * Upgrade firmware config
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * c_fname - The bin file for upgarding
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t upgrade_firmware_config(uint32_t dev_id, uint8_t *c_fname);

/**
 * printf device info
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * module - Specify the information to be printed;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t rpp_query(uint32_t dev_id, info_name module);

/**
 * Dump status information
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t dump_status(uint32_t dev_id);

/**
 * Dump clock information
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t dump_clock(uint32_t dev_id);

/**
 * Dump version
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t dump_version(uint32_t dev_id);
/**
 * Dump bl/fw config
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t dump_config(uint32_t dev_id);


/**
 * Obtain GPU loading.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * type - Returns the extracted data type;
 * gpu_loading - Returns the extracted data;
 * len - Returns the length of the "value";
 * time - The gpu loading interval can be specified for data extraction;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t get_gpu_loading_info(uint32_t dev_id, info_type* type, double* gpu_loading, uint32_t* len, uint32_t time);

RPPReturn_t pcie_bar_read(uint32_t dev_id, uint32_t bar, uint32_t addr, uint32_t len, void *value);
RPPReturn_t pcie_bar_write(uint32_t dev_id, uint32_t bar, uint32_t addr, uint32_t len, void *value);
RPPReturn_t pcie_dma_read(uint32_t dev_id, uint32_t chan, uint32_t wei, uint64_t addr, uint32_t len, void *value, int isfile);
RPPReturn_t pcie_dma_write(uint32_t dev_id, uint32_t chan, uint32_t wei, uint64_t addr, uint32_t len, void *value, int isfile);
unsigned int get_rdev_count();
RPPReturn_t analysis_bl_config(uint8_t *buf);
RPPReturn_t analysis_fw_config(uint8_t *buf);
RPPReturn_t compare_bl_config(uint8_t *src, uint8_t *dst);
RPPReturn_t compare_fw_config(uint8_t *src, uint8_t *dst);

#endif /* __HL_API_H__ */

