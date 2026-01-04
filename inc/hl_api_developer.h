#ifndef __HL_API_DEVELOPER_H__
#define __HL_API_DEVELOPER_H__

#include <stdint.h>
#include "ae_smi_common.h"
#include "rpp_info.h"

typedef struct {
  int64_t tv_sec;
  int32_t tv_usec;
} rpp_timeval64_t;

/**
 * Modified Parameters that control the mpu
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * cmd - CMD to control device;
 * host_ctrl - Relevant parameters in the control process;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t rpp_dev_ctrl(uint32_t dev_id, ctrl_cmd_e cmd, void *host_ctrl);

/**
 * Reset mpu
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t rpp_reset(uint32_t dev_id);

/**
 * Watchdog enable
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * mode - 0 - off, 1 - on
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t wdt_status(uint32_t dev_id, int mode);

/**
 * I2C read rpp address data.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * slave_id - Slave address;
 * addr - Address to read;
 * len - Length of data to read;
 * buf - Buffer where data is stored;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t i2c_read(uint32_t dev_id, i2c_rw_t i2c_ctrl, uint8_t *buf);

/**
 * I2C write rpp address data.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * slave_id - Slave address;
 * addr - Address to write;
 * len - Length of data to write;
 * buf - Buffer where data is stored;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t i2c_write(uint32_t dev_id, i2c_rw_t i2c_ctrl, uint8_t *buf);

/**
 * Internal read rpp address data.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * addr - Address to read;
 * len - Length of data to read;
 * buf - Buffer where data is stored;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t internal_read(uint32_t dev_id, uint32_t addr, uint32_t len, uint8_t *buf);

/**
 * Internal write rpp address data.
 *
 * Parameters:
 * dev_id - In the case of multiple cards, you can grab the data of the specified board, the single card case is 0;
 * addr - Address to write;
 * len - Length of data to write;
 * buf - Buffer where data is stored;
 *
 * Returns:
 * RPP_SUCCESS, RPP_ERROR_INVALID_VALUE
 */
RPPReturn_t internal_write(uint32_t dev_id, uint32_t addr, uint32_t len, uint8_t *buf);

RPPReturn_t get_pow_on(uint32_t dev_id);

RPPReturn_t get_pow_off(uint32_t dev_id);

RPPReturn_t dev_reboot_and_rescan(uint32_t dev_id, int i);

int set_rpp_pwrmode(uint32_t dev_id, power_mode_cmd_e cmd, char *status);

int set_rpp_working_mode(uint32_t dev_id, working_mode_cmd_t *working_mode);

int file_exist(const char *filename);

int rpp_gettimeofday(void *time);

int write_to_file(uint8_t *fname, uint8_t *buf, uint32_t len);

int read_from_file(uint8_t *fname, uint8_t *buf, uint32_t len);

RPPReturn_t set_mfg_id(uint32_t dev_id, uint8_t *sn);

#endif /* __HL_API_H__ */
