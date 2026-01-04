#ifndef RTOP_COMMON_H__
#define RTOP_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>

#include "rpp_info.h"
#include "ae_smi_version.h"

typedef uint64_t RPPdevice;                                     /**< RPP device */

#define MAX_PATH_LEN                255
#define MAX_DEVICE_NAME 128
#define PDEV_LEN 16


#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef NULL
#define NULL (0)
/**<
 * @file rpp_typedef.h
 * @ingroup rpp_typedef
 * NULL definition. */
#endif

#ifdef RPP_SIM_RT
#define RPP_DEVICE_MAX_COUNT 1
#else
#define RPP_DEVICE_MAX_COUNT 32
#endif

#ifndef RPP_SIM_RT
#define RPP_DIR_NAME  "/dev"
#define RPP_DEV_NAME  "%s/rpp%d_entire_ctrl"
#else
#define RPP_DIR_NAME  "/dev"
#define RPP_DEV_NAME  "%s/rpp_sim"
#endif

#ifndef TRUE
#define TRUE (1==1)
/**<
 * @file rpp_typedef.h
 * @ingroup rpp_typedef
 * True value definition. */
#endif
#ifndef FALSE
#define FALSE (0==1)
/**<
 * @file rpp_typedef.h
 * @ingroup rpp_typedef
 * False value definition. */
#endif

/**
 * Error codes
 */
typedef enum rppError_enum {
    /**
     * The API call returned with no errors. In the case of query calls, this
     * can also mean that the operation being queried is complete (see
     * ::rppEventQuery() and ::rppStreamQuery()).
     */
    RPP_SUCCESS                              = 0,

    /**
     * This indicates that one or more of the parameters passed to the API call
     * is not within an acceptable range of values.
     */
    RPP_ERROR_INVALID_VALUE                  = 1,

    /**
     * The API call failed because it was unable to allocate enough memory to
     * perform the requested operation.
     */
    RPP_ERROR_OUT_OF_MEMORY                  = 2,

    /**
     * This indicates that the RPP driver has not been initialized with
     * ::rppInit() or that initialization has failed.
     */
    RPP_ERROR_NOT_INITIALIZED                = 3,

    /**
     * This indicates that the RPP driver is in the process of shutting down.
     */
    RPP_ERROR_DEINITIALIZED                  = 4,

    /**
     * This indicates profiler is not initialized for this run.
     * This can happen when the application is running with external profiling tools like visual profiler.
    */
    RPP_ERROR_PROFILER_DISABLED           = 5,
    /**
     * This indicates profiling has not been initialized for this context.
     * Call rppProfilerInitialize() to resolve this.
    */
    RPP_ERROR_PROFILER_NOT_INITIALIZED       = 6,
    /**
     * This indicates profiler has already been started and probably
     * rppProfilerStart() is incorrectly called.
    */
    RPP_ERROR_PROFILER_ALREADY_STARTED       = 7,
    /**
     * This indicates profiler has already been stopped and probably
     * rppProfilerStop() is incorrectly called.
    */
    RPP_ERROR_PROFILER_ALREADY_STOPPED       = 8,
    /**
     * This indicates that no RPP-capable devices were detected by the installed
     * RPP driver.
     */
    RPP_ERROR_NO_DEVICE                      = 100,

    /**
     * This indicates that the device ordinal supplied by the user does not
     * correspond to a valid RPP device.
     */
    RPP_ERROR_INVALID_DEVICE                 = 101,


    /**
     * This indicates that the device kernel image is invalid. This can also
     * indicate an invalid RPP module.
     */
    RPP_ERROR_INVALID_IMAGE                  = 200,

    /**
     * This most frequently indicates that there is no context bound to the
     * current thread. This can also be returned if the context passed to an
     * API call is not a valid handle (such as a context that has had
     * ::rppCtxDestroy() invoked on it). This can also be returned if a user
     * mixes different API versions (i.e. 3010 context with 3020 API calls).
     * See ::rppCtxGetApiVersion() for more details.
     */
    RPP_ERROR_INVALID_CONTEXT                = 201,

    /**
     * This indicated that the context being supplied as a parameter to the
     * API call was already the active context.
     * \deprecated
     * This error return is deprecated as of RPP 3.2. It is no longer an
     * error to attempt to push the active context via ::rppCtxPushCurrent().
     */
    RPP_ERROR_CONTEXT_ALREADY_CURRENT        = 202,

    /**
     * This indicates that a map or register operation has failed.
     */
    RPP_ERROR_MAP_FAILED                     = 205,

    /**
     * This indicates that an unmap or unregister operation has failed.
     */
    RPP_ERROR_UNMAP_FAILED                   = 206,

    /**
     * This indicates that the specified array is currently mapped and thus
     * cannot be destroyed.
     */
    RPP_ERROR_ARRAY_IS_MAPPED                = 207,

    /**
     * This indicates that the resource is already mapped.
     */
    RPP_ERROR_ALREADY_MAPPED                 = 208,

    /**
     * This indicates that there is no kernel image available that is suitable
     * for the device. This can occur when a user specifies code generation
     * options for a particular RPP source file that do not include the
     * corresponding device configuration.
     */
    RPP_ERROR_NO_BINARY_FOR_GPU              = 209,

    /**
     * This indicates that a resource has already been acquired.
     */
    RPP_ERROR_ALREADY_ACQUIRED               = 210,

    /**
     * This indicates that a resource is not mapped.
     */
    RPP_ERROR_NOT_MAPPED                     = 211,

    /**
     * This indicates that a mapped resource is not available for access as an
     * array.
     */
    RPP_ERROR_NOT_MAPPED_AS_ARRAY            = 212,

    /**
     * This indicates that a mapped resource is not available for access as a
     * pointer.
     */
    RPP_ERROR_NOT_MAPPED_AS_POINTER          = 213,

    /**
     * This indicates that an uncorrectable ECC error was detected during
     * execution.
     */
    RPP_ERROR_ECC_UNCORRECTABLE              = 214,

    /**
     * This indicates that the ::RPPlimit passed to the API call is not
     * supported by the active device.
     */
    RPP_ERROR_UNSUPPORTED_LIMIT              = 215,

    /**
     * This indicates that the ::RPPcontext passed to the API call can
     * only be bound to a single CPU thread at a time but is already
     * bound to a CPU thread.
     */
    RPP_ERROR_CONTEXT_ALREADY_IN_USE         = 216,

    /**
     * This indicates that peer access is not supported across the given
     * devices.
     */
    RPP_ERROR_PEER_ACCESS_UNSUPPORTED        = 217,

    /**
     * This indicates that the device kernel source is invalid.
     */
    RPP_ERROR_INVALID_SOURCE                 = 300,

    /**
     * This indicates that the file specified was not found.
     */
    RPP_ERROR_FILE_NOT_FOUND                 = 301,

    /**
     * This indicates that a link to a shared object failed to resolve.
     */
    RPP_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND = 302,

    /**
     * This indicates that initialization of a shared object failed.
     */
    RPP_ERROR_SHARED_OBJECT_INIT_FAILED      = 303,

    /**
     * This indicates that an OS call failed.
     */
    RPP_ERROR_OPERATING_SYSTEM               = 304,


    /**
     * This indicates that a resource handle passed to the API call was not
     * valid. Resource handles are opaque types like ::RPPstream and ::RPPevent.
     */
    RPP_ERROR_INVALID_HANDLE                 = 400,


    /**
     * This indicates that a named symbol was not found. Examples of symbols
     * are global/constant variable names, texture names, and surface names.
     */
    RPP_ERROR_NOT_FOUND                      = 500,


    /**
     * This indicates that asynchronous operations issued previously have not
     * completed yet. This result is not actually an error, but must be indicated
     * differently than ::RPP_SUCCESS (which indicates completion). Calls that
     * may return this value include ::rppEventQuery() and ::rppStreamQuery().
     */
    RPP_ERROR_NOT_READY                      = 600,


    /**
     * An exception occurred on the device while executing a kernel. Common
     * causes include dereferencing an invalid device pointer and accessing
     * out of bounds shared memory. The context cannot be used, so it must
     * be destroyed (and a new one should be created). All existing device
     * memory allocations from this context are invalid and must be
     * reconstructed if the program is to continue using RPP.
     */
    RPP_ERROR_ILLEGAL_ADDRESS                  = 700,

    /**
     * This indicates that a launch did not occur because it did not have
     * appropriate resources. This error usually indicates that the user has
     * attempted to pass too many arguments to the device kernel, or the
     * kernel launch specifies too many threads for the kernel's register
     * count. Passing arguments of the wrong size (i.e. a 64-bit pointer
     * when a 32-bit int is expected) is equivalent to passing too many
     * arguments and can also result in this error.
     */
    RPP_ERROR_LAUNCH_OUT_OF_RESOURCES        = 701,

    /**
     * This indicates that the device kernel took too long to execute. The
     * context cannot be used (and must be destroyed similar to
     * ::RPP_ERROR_LAUNCH_FAILED). All existing device memory allocations from
     * this context are invalid and must be reconstructed if the program is to
     * continue using RPP.
     */
    RPP_ERROR_LAUNCH_TIMEOUT                 = 702,

    /**
     * This error indicates a kernel launch that uses an incompatible texturing
     * mode.
     */
    RPP_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING  = 703,

    /**
     * This error indicates that the primary context for the specified device
     * has already been initialized.
     */
    RPP_ERROR_PRIMARY_CONTEXT_ACTIVE = 708,

    /**
     * This error indicates that the context current to the calling thread
     * has been destroyed using ::rppCtxDestroy, or is a primary context which
     * has not yet been initialized.
     */
    RPP_ERROR_CONTEXT_IS_DESTROYED           = 709,

    /**
     * A device-side assert triggered during kernel execution.
     * The context cannot be used anymore, and must be destroyed.
     * All existing device memory allocations from this context are invalid
     * and must be reconstructed if the program is to continue using RPP.
     */
    RPP_ERROR_ASSERT                = 710,

    /**
     * This error indicates that the memory range passed to rppMemHostRegister()
     * has already been registered.
     */
    RPP_ERROR_HOST_MEMORY_ALREADY_REGISTERED    = 712,

    /**
     * This error indicates that the pointer passed to rppMemHostUnregister()
     * does not correspond to any currently registered memory region.
     */
    RPP_ERROR_HOST_MEMORY_NOT_REGISTERED    = 713,

    /**
     * While executing a kernel, the device encountered a stack error.
     * This can be due to stack corruption or exceeding the stack size limit.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_HARDWARE_STACK_ERROR           = 714,

    /**
     * While executing a kernel, the device encountered an illegal instruction.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_ILLEGAL_INSTRUCTION            = 715,

    /**
     * While executing a kernel, the device encountered a load or store instruction
     * on a memory address which is not aligned.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_MISALIGNED_ADDRESS             = 716,

    /**
     * While executing a kernel, the device encountered an instruction
     * which can only operate on memory locations in certain address spaces
     * (global, shared, or local), but was supplied a memory address not
     * belonging to an allowed address space.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_INVALID_ADDRESS_SPACE          = 717,

    /**
     * While executing a kernel, the device program counter wrapped its address space.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_INVALID_PC                     = 718,

    /**
     * An exception occurred on the device while executing a kernel. Common
     * causes include dereferencing an invalid device pointer and accessing
     * out of bounds shared memory.
     * This leaves the process in an inconsistent state and any further RPP work
     * will return the same error. To continue using RPP, the process must be terminated
     * and relaunched.
     */
    RPP_ERROR_LAUNCH_FAILED                  = 719,

    /**
     * This error indicates that the number of blocks launched per grid for a kernel
     * exceeds the maximum number of blocks as allowed.
     */
    RPP_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE   = 720,

    /**
     * This error indicates that the attempted operation is not permitted.
     */
    RPP_ERROR_NOT_PERMITTED                  = 800,

    /**
     * This error indicates that the attempted operation is not supported
     * on the current system or device.
     */
    RPP_ERROR_NOT_SUPPORTED                  = 801,


    /**
     * This indicates that an unknown internal error has occurred.
     */
    RPP_ERROR_UNKNOWN                        = 999
} RPPresult;

typedef RPPresult RPPReturn_t; // store the enum as int

/******************************************************************/

#define IS_VALID(x, y) ((y)[(x) / CHAR_BIT] & (1 << ((x) % CHAR_BIT)))
#define SET_VALID(x, y) ((y)[(x) / CHAR_BIT] |= (1 << ((x) % CHAR_BIT)))
#define RESET_VALID(x, y) ((y)[(x) / CHAR_BIT] &= ~(1 << ((x) % CHAR_BIT)))
#define RESET_ALL(y) memset(y, 0, sizeof(y))

#define SET_VALUE(structPtr, field, value, prefix)                                                                     \
  do {                                                                                                                 \
    (structPtr)->field = (value);                                                                                      \
    SET_VALID(prefix##field##_valid, (structPtr)->valid);                                                              \
  } while (0)
#define INVALIDATE_VALUE(structPtr, field, prefix)                                                                     \
  do {                                                                                                                 \
    RESET_VALID(prefix##field##_valid, (structPtr)->valid);                                                            \
  } while (0)
#define VALUE_IS_VALID(structPtr, field, prefix) IS_VALID(prefix##field##_valid, (structPtr)->valid)

#define SET_SYS_CMD(structPtr, field, value) SET_VALUE(structPtr, field, value, sys_cmd_)
#define RESET_SYS_CMD(structPtr, field) INVALIDATE_VALUE(structPtr, field, sys_cmd_)
#define SYS_CMD_FIELD_VALID(structPtr, field) VALUE_IS_VALID(structPtr, field, sys_cmd_)


#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif
/***********************thermal_ctrl*******************************/
typedef enum Initial_conf_enum {
    INIT_EMPTY = 0,
    INIT_CONF = 1,
} Initial_conf_e;

typedef enum fan_ctrl_state_enum {
    AUTO_DISABLE = 0,
    AUTO_ENABLE = 1,
} fan_ctrl_state_e;

typedef struct p_info_s {
    double pvt_t;
    double pvt_v;
    double pmic_vin;
    double pmic_vout;
    double pmic_iin;
    double pmic_iout;
    double pmic_pin;
    double pmic_pout;
    double pmic_tic;
    double pmic_tloopa;
}p_info;

enum sys_cmd_valid {
    sys_cmd_set_auto_valid = 0,
    sys_cmd_fan_speed_w_valid,
    sys_cmd_set_error_valid,
    sys_cmd_set_warning_valid,
    sys_cmd_working_temperature_valid,
    sys_cmd_throttling_temperature_valid,
    sys_cmd_trip_temperature_valid,
    sys_cmd_save_change_valid,
    sys_cmd_pmic_vol_valid,
    sys_cmd_polling_time_valid,
    sys_cmd_valid_count,
};

/**
 * thermal ctrl related configuration struct:
 */
typedef struct thermal_rw_s{
  uint32_t irq_vector;
  uint32_t fan_speed_r;
  uint32_t fan_speed_w;
  fan_ctrl_state_e set_auto;
  fan_ctrl_state_e set_warning;
  fan_ctrl_state_e set_error;
  p_info pmsg;
  uint32_t pmic_vol;
  uint32_t polling_time;
  uint32_t working_temperature;
  uint32_t throttling_temperature;
  uint32_t trip_temperature;
  Initial_conf_e ini_conf;
  uint8_t valid[(sys_cmd_valid_count + CHAR_BIT - 1) / CHAR_BIT];
} thermal_rw;

/***********************freq_ctrl*******************************/

typedef enum freq_ctrl_module_enum {
    RPP_CORE_MOUDLE = 0,
    PLL1_MOUDLE = 1,
    PLL2_MOUDLE = 2,
    PLL3_MOUDLE = 3,
    VE_MOUDLE = 5,
} freq_ctrl_module_e;

/**
 * freq ctrl related configuration struct:
 */
typedef struct freq_rw_s{
  uint32_t freq_div;
  freq_ctrl_module_e freq_ctrl_module;
  Initial_conf_e ini_conf;
} freq_rw;

/********************************************************************/
typedef enum i2c_mode_enum {
    I2C_UNKNOW = 0,
    I2C_READ = 2,
    I2C_WRITE = 3,
    REBOOT = 4,
} i2c_mode_e;

/**
 * eeprom ctrl related configuration struct:
 */
typedef struct slave_s{
  uint32_t id;
  uint32_t addr;
  uint32_t ddr_addr;
  i2c_mode_e mode;
  uint32_t iic_id; // 0 -- iic_eeprom, 1 - iic_pmic
  uint32_t addr_type; // 0 -- 16-bit addr, 1 -- 8-bit addr, 2 -- 32-bit addr, 3 -- resv
  uint32_t freq; //khz
  uint32_t len;
  uint32_t val; 
  uint8_t *file;
  uint8_t buf[4000];
} i2c_rw_t;

/***********************pcie_ctrl*******************************/

/**
 * pcie related configuration struct:
 */
typedef struct pcie_tool_rw{
    uint32_t bar; 
    uint32_t chan; 
    uint32_t weight; 
    uint64_t addr; 
    uint32_t len; 
    uint32_t val; 
    char *mode;
    char *fname;
    char *tool;
} pcie_rw; 

typedef union
{
    struct
    {
        uint32_t    DFS           :1; /**< bit[0]: (rw)  Read/Write */
        uint32_t    VE            :1; /**< bit[1]: (rw)  Read/Write */
        uint32_t    BOOST_EN      :1; /**< bit[2]: (rw)  Read/Write */
        uint32_t    SPECIFIED_PLL :1; /**< bit[3]: (rw)  Read/Write */
        uint32_t    PLL_TYPE      :3; /**< bit[4:6]: (rw)  Read/Write */
        uint32_t    reserved0     :1; /**< bit[7]: (rw)  Read/Write */
        uint32_t    vol           :8; /**< bit[8:15]: (rw)  Read/Write */
        uint32_t    FREQ          :16; /**< bit[16:31]: (rw)  Read/Write */
    };
    uint32_t    val;
} working_mode_cmd_t;


typedef struct rtop_interface_option_struct {
    int temperature_in_fahrenheit;                   // Switch from celsius to fahrenheit temperature scale
    int use_color;                                   // Name self explanatory
    int update_interval;                              // Interval between interface update in milliseconds
    int show_startup_messages;                       // True to show the startup messages
    char *config_file_location;                       // Location of the config file
} rtop_interface_option;

#endif // RTOP_COMMON_H__
