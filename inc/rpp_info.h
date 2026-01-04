#ifndef RPP_INFO_H__
#define RPP_INFO_H__

#define RPP_PRAM_SIZE           (2048*1024)

#if defined(RPP_FPGA)
#define RPP_SRAM_SIZE           (20*1024*1024)
#else
#define RPP_SRAM_SIZE           (24*1024*1024)
#endif

#define RPP_MPU0_SRAM_SIZE      (64*1024)
#define RPP_MPU1_SRAM_SIZE      (64*1024)
#define RPP_FRAM_SIZE           (8*1024)


#define RPP_DMA_BASE         0x1000000000
#ifdef RTL_TB
#define FRAM_BASE            0x1006000000
#define RPP_SRAM_BASE        0x1004000000
#define RPP_PRAM_ADDR        0x1007000000
#else
#define FRAM_BASE              0x6000000
#define RPP_SRAM_BASE        0x4000000
#define RPP_PRAM_ADDR        0x7000000
#endif
// Scheduler, 0x400000 - 0x401000
#define RPP_SCHE_ADDR_VER1                0x400000
#define RPP_SCHE_ADDR_VER2                0x2080000
#define RPP_CORE_REG_BASE               0x1000000000



#define RPP_DMA_SRAM_BASE    (RPP_DMA_BASE + 0x4000000)
#define RPP_DMA_MPU0_SRAM_BASE    (RPP_DMA_BASE + 0x10040000)
#define RPP_DMA_MPU1_SRAM_BASE    (RPP_DMA_BASE + 0x11040000)
#define RPP_DMA_FRAM_BASE    (RPP_DMA_BASE + 0x6000000)
#define RPP_DMA_PRAM_BASE    (RPP_DMA_BASE + 0x7000000)

#ifdef RTL_TB
#define AXI_BAR1_BASE                (RPP_CORE_REG_BASE + 0x3004000)
#define RPP_RESET_REG_ADDR          (RPP_CORE_REG_BASE + 0x3005004)
#define CDMA_BASE                    (RPP_CORE_REG_BASE + 0x3000000)
#define PCIE_DMA_BASE                (RPP_CORE_REG_BASE + 0x7380000)
#else
#define AXI_BAR1_BASE                (0x3004000)
#define RPP_RESET_REG_ADDR          (0x3005004)
#define CDMA_BASE                    (0x3000000)
#define PCIE_DMA_BASE                (0x7380000)
#endif
#define RPP_CORE_BUSY                (AXI_BAR1_BASE + 0x0)
#define RPP_YX_REG_ADDR                (AXI_BAR1_BASE + 0x10)
#define RPP_TZ_REG_ADDR                (AXI_BAR1_BASE + 0x14)
#define RPP_XYZ_FIFO_INFO_ADDR        (AXI_BAR1_BASE + 0x18)
#define RPP_IDLE_MIN_ADDR            (AXI_BAR1_BASE + 0x1c)
#define RPP_PRE_LINE_ADDR            (AXI_BAR1_BASE + 0x20)
#define RPP_ICACHE_MSB                (AXI_BAR1_BASE + 0x24)
#define RPP_ICACHE_LSB                (AXI_BAR1_BASE + 0x28)
#define RPP_FMEM_LEN_ADDR            (AXI_BAR1_BASE + 0x2c)
#define RPP_FMEM_MSB                (AXI_BAR1_BASE + 0x30)
#define RPP_FMEM_LSB                (AXI_BAR1_BASE + 0x34)

#define RPP_START_REG_ADDR            (AXI_BAR1_BASE + 0x40)
#define RPP_FIFO_INFO_ADDR            (AXI_BAR1_BASE + 0x44)

#define RPP_COLUMN_STATUS            (AXI_BAR1_BASE + 0x50)

#define RPP_INT_CLEAR_ADDR            (AXI_BAR1_BASE + 0x60)
#define RPP_INT_MASK_ADDR            (AXI_BAR1_BASE + 0x64)
#define RPP_INT_TIMER_ADDR            (AXI_BAR1_BASE + 0x68)

#define RPP_CNTR_LOW_REG_ADDR        (AXI_BAR1_BASE + 0x70)
#define RPP_CNTR_HIGH_REG_ADDR        (AXI_BAR1_BASE + 0x74)
#define RPP_CNTR_CLEAR_REG_ADDR        (AXI_BAR1_BASE + 0x78)
#define RPP_VERSION_REG_ADDR        (AXI_BAR1_BASE + 0x7c)

#define RPP_ICACHE_CLR                (AXI_BAR1_BASE + 0x80)
#define RPP_ICACHE_CLR_START        (AXI_BAR1_BASE + 0x84)
#define RPP_ICACHE_CLR_END            (AXI_BAR1_BASE + 0x88)

/*
 *
 * channel 0 Descriptor Mode/Direct Mode: Core
 * channel 1 Descriptor Mode: APB descriptor
 * channel 1 Direct Mode: Scheduler
 * channel 2 Descriptor Mode/Direct Mode: MPU0
 * channel 3 Descriptor Mode/Direct Mode: MPU1
 *
 */
#define CDMACR                        (CDMA_BASE + 0x0) // CDMA Control
#define CDMASR                        (CDMA_BASE + 0x4) // CDMA Status
#define CH0_DESC_PTR_HI                (CDMA_BASE + 0x8) // CDMA Desc ptr, MSB 32 bits
#define CH0_DESC_PTR                (CDMA_BASE + 0xc) // CDMA Desc ptr
#define CH1_DESC_PTR_HI                (CDMA_BASE + 0x10) // CDMA Desc ptr, MSB 32 bits
#define CH1_DESC_PTR                (CDMA_BASE + 0x14) // CDMA Desc ptr
#define CH0_SA_MSB                    (CDMA_BASE + 0x18) // Source address, MSB 32 bits
#define CH0_SA                        (CDMA_BASE + 0x1c) // Source address
#define CH0_DA_MSB                    (CDMA_BASE + 0x20) // Destination address, MSB 32 bits
#define CH0_DA                        (CDMA_BASE + 0x24) // Destination address
#define CH0_BTT                        (CDMA_BASE + 0x28) // Bytes to Transfer
#define CH1_SA_MSB                    (CDMA_BASE + 0x2c) // Source address, MSB 32 bits
#define CH1_SA                        (CDMA_BASE + 0x30) // Source address
#define CH1_DA_MSB                    (CDMA_BASE + 0x34) // Destination address, MSB 32 bits
#define CH1_DA                        (CDMA_BASE + 0x38) // Destination address
#define CH1_BTT                        (CDMA_BASE + 0x3c) // Bytes to Transfer
#define AXI4_DATA_CFG_0                (CDMA_BASE + 0x40) // data ports
#define AXI4_DATA_CFG_1                (CDMA_BASE + 0x44) // data ports
#define AXI4_DESC_CFG_0                (CDMA_BASE + 0x48) // descriptor ports
//#define AXI4_DESC_CFG_1                (CDMA_BASE + 0x4c) // descriptor ports
#define CH2_DESC_PTR_HI                (CDMA_BASE + 0x50) // CDMA Desc ptr, MSB 32 bits
#define CH2_DESC_PTR                (CDMA_BASE + 0x54) // CDMA Desc ptr
#define CH3_DESC_PTR_HI                (CDMA_BASE + 0x58) // CDMA Desc ptr, MSB 32 bits
#define CH3_DESC_PTR                (CDMA_BASE + 0x5c) // CDMA Desc ptr
#define CH2_SA_MSB                    (CDMA_BASE + 0x60) // Source address, MSB 32 bits
#define CH2_SA                        (CDMA_BASE + 0x64) // Source address
#define CH2_DA_MSB                    (CDMA_BASE + 0x68) // Destination address, MSB 32 bits
#define CH2_DA                        (CDMA_BASE + 0x6c) // Destination address
#define CH2_BTT                        (CDMA_BASE + 0x70) // Bytes to Transfer
#define CH3_SA_MSB                    (CDMA_BASE + 0x74) // Source address, MSB 32 bits
#define CH3_SA                        (CDMA_BASE + 0x78) // Source address
#define CH3_DA_MSB                    (CDMA_BASE + 0x7c) // Destination address, MSB 32 bits
#define CH3_DA                        (CDMA_BASE + 0x80) // Destination address
#define CH3_BTT                        (CDMA_BASE + 0x84) // Bytes to Transfer
#define CDMA_DBG_SEL                 (CDMA_BASE + 0x90) // debug data sel
#define CDMA_DBG_DATA                 (CDMA_BASE + 0x94) // debug data out
#define R_EXTRA_SIZES                (CDMA_BASE + 0x150) // axi can read more extra_sizes data than its internal memory size
#define MAX_AW_CMDS                  (CDMA_BASE + 0x158) // axi aw cmd outstanding

#define FRAM_PARA_OFFSET           (FRAM_BASE)

#define FRAM_PARA_SIZE             (896)
#define FRAM_STATIC_CFG_OFFSET     (FRAM_PARA_OFFSET + FRAM_PARA_SIZE)
#define FRAM_STATIC_CFG_SIZE       (128)
#define FRAM_1K
#define FRAM_DMA_OFFSET				(FRAM_BASE + 4*1024 - 256)
#define FRAM_DMA_SIZE				(256)
#define FRAM_TASK_DESC_OFFSET		(FRAM_BASE + 3*1024)
#define FRAM_TASK_DESC_SIZE			(256)

//FRAM RESERVED PARA
#define FRAM_RSVD_PARA_OFFSET       (FRAM_BASE + 256)
#define PARA_CODE_SIZE_OFFSET        FRAM_RSVD_PARA_OFFSET
#define PARA_GRID_X_OFFSET            (PARA_CODE_SIZE_OFFSET + 2)
#define PARA_GRID_Y_OFFSET            (PARA_GRID_X_OFFSET + 2)
#define PARA_GRID_Z_OFFSET            (PARA_GRID_Y_OFFSET + 2)

#define PARA_BLOCK_X_OFFSET            (PARA_GRID_Z_OFFSET + 2)
#define PARA_BLOCK_Y_OFFSET            (PARA_BLOCK_X_OFFSET + 2)
#define PARA_BLOCK_Z_OFFSET            (PARA_BLOCK_Y_OFFSET + 2)
#define PARA_TID_XYZ                (PARA_BLOCK_Z_OFFSET + 2)

#define PARA_DMA_IN_LO_OFFSET            (PARA_TID_XYZ + 2)
#define PARA_DMA_IN_HI_OFFSET            (PARA_DMA_IN_LO_OFFSET + 4)
#define PARA_DMA_OUT_LO_OFFSET            (PARA_DMA_IN_HI_OFFSET + 4)
#define PARA_DMA_OUT_HI_OFFSET            (PARA_DMA_OUT_LO_OFFSET + 4)
#define PARA_DMA_IN_STRD_OFFSET            (PARA_DMA_OUT_HI_OFFSET + 4)
#define PARA_DMA_OUT_STRD_OFFSET        (PARA_DMA_IN_STRD_OFFSET + 2)

#define PARA_OUT_X_STRD                    (PARA_DMA_OUT_STRD_OFFSET + 2)
#define PARA_OUT_Y_STRD                    (PARA_OUT_X_STRD + 4)
#define PARA_OUT_Z_STRD                    (PARA_OUT_Y_STRD + 4)
#define PARA_IN_Y_STRD                    (PARA_OUT_Z_STRD + 4)
#define PARA_IN_Z_STRD                    (PARA_IN_Y_STRD + 4)

#define PARA_FILTER_X_STRD                (PARA_IN_Z_STRD + 4)
#define PARA_TID_BASE                    (PARA_FILTER_X_STRD + 4)
#define PARA_TID_DEPACK                    (PARA_TID_BASE + 4)

#define PARA_DFT_OUTPUT                    (PARA_TID_DEPACK + 4)
#define PARA_DUMMY_CYCLE                (PARA_DFT_OUTPUT + 4)

#define PARA_DIMX_SHADOW                (PARA_DUMMY_CYCLE + 4)
#define PARA_DIMY_SHADOW                (PARA_DIMX_SHADOW + 2)
#define PARA_DIMZ_SHADOW                (PARA_DIMY_SHADOW + 2)
#define PARA_XYZCFG_SHADOW              (PARA_DIMZ_SHADOW + 2)

#define FRAM_RSVD_PARA_END              (PARA_XYZCFG_SHADOW + 2)


//spill register offset
#define SPILL_REG_NUM 40
#define SPILL_SCA_REG_NUM 32
#define SRAM_SPILL_OFFSET            (RPP_SRAM_SIZE - 0x40000) // (0x1680000) //fix me here
#define SRAM_AUG_OFFSET              (0x1700000) //fix me here
#define SRAM_PRED_OFFSET             (0x1780000) //fix me here

#define FRAM_SPILL_OFFSET            (256 + 128)
#define FRAM_SCA_SPILL_OFFSET        (FRAM_SPILL_OFFSET + SPILL_REG_NUM * 4)
#define FRAM_SPILL_OFF_END           (FRAM_SCA_SPILL_OFFSET + SPILL_SCA_REG_NUM * 4)

#define PRED_NUM 37
#define FRAM_PRED_BEG            (FRAM_SPILL_OFF_END + 4)
#define FRAM_PRED_END            (FRAM_PRED_BEG + PRED_NUM*4)

#if 0
//FRAM static configuration DEFINE
#define FRAM_BASE_LSB             (FRAM_STATIC_CFG_OFFSET)
#define FRAM_BASE_MSB             (FRAM_STATIC_CFG_OFFSET + 0x4)
#define PRAM_BASE_LSB             (FRAM_STATIC_CFG_OFFSET + 0x8)
#define PRAM_BASE_MSB             (FRAM_STATIC_CFG_OFFSET + 0xc)
#define PARA_MAX_SIZE             (FRAM_STATIC_CFG_OFFSET + 0x10)
#define KERN_FUNC_BASE_LSB      (FRAM_STATIC_CFG_OFFSET + 0x14)
#define KERN_FUNC_BASE_MSB      (FRAM_STATIC_CFG_OFFSET + 0x18)
#define KERN_FUNC_SIZE             (FRAM_STATIC_CFG_OFFSET + 0x1c)
#define KERN_PARA_BASE_LSB      (FRAM_STATIC_CFG_OFFSET + 0x20)
#define KERN_PARA_BASE_MSB      (FRAM_STATIC_CFG_OFFSET + 0x24)
#define KERN_PARA_SIZE             (FRAM_STATIC_CFG_OFFSET + 0x28)

#define FRAM_STATIC_CFG_END    (KERN_PARA_SIZE + 4)
#endif
//FRAM DMA register DEFINE
#define DMA_CONTROL          FRAM_DMA_OFFSET
#define DMA_STATUS           (DMA_CONTROL + 4)
#define DMA_CH0_DESC_HI      (DMA_STATUS + 4)
#define DMA_CH0_DESC_LOW     (DMA_CH0_DESC_HI + 4)
#define DMA_CH1_DESC_HI      (DMA_CH0_DESC_LOW + 4)
#define DMA_CH1_DESC_LOW     (DMA_CH1_DESC_HI + 4)
#define DMA_CH0_MOD1_SRC_HI   (DMA_CH1_DESC_LOW + 4)
#define DMA_CH0_MOD1_SRC_LO   (DMA_CH0_MOD1_SRC_HI + 4)
#define DMA_CH0_MOD1_DST_HI   (DMA_CH0_MOD1_SRC_LO + 4)
#define DMA_CH0_MOD1_DST_LO   (DMA_CH0_MOD1_DST_HI + 4)
#define DMA_CH0_MOD1_LEN      (DMA_CH0_MOD1_DST_LO + 4)

#define DMA_CH1_MOD1_SRC_HI   (DMA_CH0_MOD1_LEN + 4)
#define DMA_CH1_MOD1_SRC_LO   (DMA_CH1_MOD1_SRC_HI + 4)
#define DMA_CH1_MOD1_DST_HI   (DMA_CH1_MOD1_SRC_LO + 4)
#define DMA_CH1_MOD1_DST_LO   (DMA_CH1_MOD1_DST_HI + 4)
#define DMA_CH1_MOD1_LEN      (DMA_CH1_MOD1_DST_LO + 4)

#define FRAM_DMA_END          (DMA_CH1_MOD1_LEN + 4)


//FRAM TASK DESCRIPTOR
#define BLOCK_ID_X_OFFSET        (FRAM_TASK_DESC_OFFSET)
#define BLOCK_ID_Y_OFFSET        (BLOCK_ID_X_OFFSET + 2)
#define BLOCK_ID_Z_OFFSET        (BLOCK_ID_Y_OFFSET + 2)
#define BLOCK_ID_RSVD_OFFSET     (BLOCK_ID_Z_OFFSET + 2)
#define STACK_PTR_OFFSET          (BLOCK_ID_RSVD_OFFSET + 2)
#define TASK_PTR_OFFSET           (STACK_PTR_OFFSET + 4)
#define FRAM_TASK_DESC_END        (TASK_PTR_OFFSET + 4)

#ifdef _RPP_WITH_SW_SCHEDULER
//#warning _RPP_WITH_SW_SCHEDULER
#define RPP_SCHE_REG_BASE                RPP_SCHE_ADDR_VER1
#else
#define RPP_SCHE_REG_BASE                RPP_SCHE_ADDR_VER2
#endif

#define RPP_INITIAL_HEAD_Q0                (RPP_SCHE_REG_BASE + 0x00)
#define RPP_CURR_HEAD_Q0                (RPP_SCHE_REG_BASE + 0x30)
#define RPP_CURR_TAIL_Q0                (RPP_SCHE_REG_BASE + 0x60)
#define RPP_RECONFIG_Q0                    (RPP_SCHE_REG_BASE + 0x90)
#define RPP_TAIL_ADDR_REFRESH_Q0        (RPP_SCHE_REG_BASE + 0xc0)

#define RPP_SCHE_REG_CTRL                (RPP_SCHE_REG_BASE + 0xf0)
#define RPP_SCHE_REG_STATUS                (RPP_SCHE_REG_BASE + 0xf4)
#define RPP_CORE_REG_ADDR_MSB            (RPP_SCHE_REG_BASE + 0xf8)
#define RPP_CORE_REG_ADDR_LSB            (RPP_SCHE_REG_BASE + 0xfc)
//#define RPP_CORE_REG_ADDR_OFFS            (RPP_SCHE_REG_BASE + 0x100)
#define RPP_DESC_DDR_ADDR_MSB            (RPP_SCHE_REG_BASE + 0x104)
#define RPP_KERN_FUNC_DDR_ADDR_MSB        (RPP_SCHE_REG_BASE + 0x108)
#define RPP_KERN_PARA_DDR_ADDR_MSB        (RPP_SCHE_REG_BASE + 0x10c)
#define RPP_DEV0_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x110)
#define RPP_DEV1_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x114)
#define RPP_DEV2_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x118)
#define RPP_DEV3_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x11c)
#define RPP_DEV4_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x120)
#define RPP_DEV5_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x124)
#define RPP_DEV6_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x128)
#define RPP_DEV7_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x12c)
#define RPP_DEV8_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x130)
#define RPP_DEV9_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x134)
#define RPP_DEV10_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x138)
#define RPP_DEV11_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x13c)
#define RPP_DEV12_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x140)
#define RPP_DEV13_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x144)
#define RPP_DEV14_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x148)
#define RPP_DEV15_ADDR_MSB                (RPP_SCHE_REG_BASE + 0x14c)

#define RPP_EVENT_RW_MPU0                (RPP_SCHE_REG_BASE + 0x150)
#define RPP_EVENT_RW_MPU1                (RPP_SCHE_REG_BASE + 0x154)
#define RPP_EVENT_RW_HOST                (RPP_SCHE_REG_BASE + 0x158)

#define RPP_MPU0_INT_CLEAR                (RPP_SCHE_REG_BASE + 0x160)
#define RPP_MPU1_INT_CLEAR                (RPP_SCHE_REG_BASE + 0x164)
#define RPP_PCIE_INT_CLEAR                (RPP_SCHE_REG_BASE + 0x168)

#define RPP_SCHE_INT_INFO_1                (RPP_SCHE_REG_BASE + 0x16c)
#define RPP_SCHE_INT_INFO_2                (RPP_SCHE_REG_BASE + 0x170)
#define RPP_SCHE_INT_INFO_3                (RPP_SCHE_REG_BASE + 0x174)
#define RPP_HOST_DONE_Q0                (RPP_SCHE_REG_BASE + 0x178)

#define RPP_AXI_CONFIG                     (RPP_SCHE_REG_BASE + 0x180)
#define RPP_SCHE_VERSION                (RPP_SCHE_REG_BASE + 0x184)
#define RPP_SCHE_DBG_SEL                (RPP_SCHE_REG_BASE + 0x188)
#define RPP_SCHE_DBG_INFO                (RPP_SCHE_REG_BASE + 0x18c)
#define RPP_SCHE_SPECIAL_CTRL            (RPP_SCHE_REG_BASE + 0x190)
#define RPP_SCHE_SOFT_RESET                (RPP_SCHE_REG_BASE + 0x194)
#define RPP_PROFILE_TIMEING_HI            (RPP_SCHE_REG_BASE + 0x198)
#define RPP_PROFILE_TIMEING_LO            (RPP_SCHE_REG_BASE + 0x19C)
#define RPP_MPU0_SEMA_WAIT_REQ            (RPP_SCHE_REG_BASE + 0x200)
#define RPP_MPU0_SEMA_WAIT_ACK            (RPP_SCHE_REG_BASE + 0x204)
#define RPP_MPU0_SEMA_POST                (RPP_SCHE_REG_BASE + 0x208)
#define RPP_MPU1_SEMA_WAIT_REQ            (RPP_SCHE_REG_BASE + 0x210)
#define RPP_MPU1_SEMA_WAIT_ACK            (RPP_SCHE_REG_BASE + 0x214)
#define RPP_MPU1_SEMA_POST                (RPP_SCHE_REG_BASE + 0x218)
#define RPP_QUEUE_BYPASS                (RPP_SCHE_REG_BASE + 0x230)
#define RPP_SCH_ADDR_LO_31_12            (RPP_SCHE_REG_BASE + 0x234)

#define RPP_MPU_ADDR_HI                    (RPP_SCHE_REG_BASE + 0x238)
#define RPP_MPU_ADDR_LO_Q0                (RPP_SCHE_REG_BASE + 0x240)
#define RPP_MPU_ADDR_LO_Q1                (RPP_SCHE_REG_BASE + 0x244)
#define RPP_MPU_ADDR_LO_Q2                (RPP_SCHE_REG_BASE + 0x248)
#define RPP_MPU_ADDR_LO_Q3                (RPP_SCHE_REG_BASE + 0x24C)
#define RPP_MPU_ADDR_LO_Q4                (RPP_SCHE_REG_BASE + 0x250)
#define RPP_MPU_ADDR_LO_Q5                (RPP_SCHE_REG_BASE + 0x254)
#define RPP_MPU_ADDR_LO_Q6                (RPP_SCHE_REG_BASE + 0x258)
#define RPP_MPU_ADDR_LO_Q7                (RPP_SCHE_REG_BASE + 0x25C)
#define RPP_MPU_ADDR_LO_Q8                (RPP_SCHE_REG_BASE + 0x260)
#define RPP_MPU_ADDR_LO_Q9                (RPP_SCHE_REG_BASE + 0x264)

#define RPP_MPU_HEAD_ADDR0                (RPP_SCHE_REG_BASE + 0x270)
#define RPP_MPU_HEAD_ADDR1                (RPP_SCHE_REG_BASE + 0x274)
#define RPP_MPU_HEAD_ADDR2                (RPP_SCHE_REG_BASE + 0x278)
#define RPP_MPU_HEAD_ADDR3                (RPP_SCHE_REG_BASE + 0x27C)
#define RPP_MPU_HEAD_ADDR4                (RPP_SCHE_REG_BASE + 0x280)
#define RPP_MPU_HEAD_ADDR5                (RPP_SCHE_REG_BASE + 0x284)
#define RPP_MPU_HEAD_ADDR6                (RPP_SCHE_REG_BASE + 0x288)
#define RPP_MPU_HEAD_ADDR7                (RPP_SCHE_REG_BASE + 0x28C)
#define RPP_MPU_HEAD_ADDR8                (RPP_SCHE_REG_BASE + 0x290)
#define RPP_MPU_HEAD_ADDR9                (RPP_SCHE_REG_BASE + 0x294)

#define RPP_DUMMY_REG_0                    (RPP_SCHE_REG_BASE + 0x300)
#define RPP_DUMMY_REG_1                    (RPP_SCHE_REG_BASE + 0x304)

#define RPP_SCHE_ERROR_INFO                (RPP_SCHE_REG_BASE + 0x310)
#define RPP_DISPATCH_HEAD_Q0            (RPP_SCHE_REG_BASE + 0x320)

//scheduler special ctrl register value
#define MPU0_INT_EN                        (1<<5)
#define MPU1_INT_EN                        (1<<6)
#define PROFILE_TIMING_EN                (1<<4)
#define Q0_PRIORITY_HIGH                (1)
#define ICACHE_PRE_LINE_NUM                (6)  //3 <<1, defualt value

// End of Scheduler

#define RPP_CDMA_1D_MODE_EN            1
#define RPP_CDMA_2D_MODE_EN            2
#define RPP_CDMA_3D_MODE_EN            4
#define RPP_CDMA_4D_MODE_EN            8
#define RPP_CDMA_INT_MODE_EN        16
#define RPP_CDMA_DEINT_MODE_EN        17

#define RPP_CDMA_SUSPEND_EN           1
#define RPP_CDMA_INT_EN               2
#define RPP_CDMA_INBOUND           4
#define RPP_CDMA_OUTBOUND           8
#define RPP_CDMA_D2D               16
#define RPP_CDMA_C2C               32

#define RPP_DDR_BAR                          0x0
#define RPP_CFG_BAR                          0x2
#define RPP_MPU_BAR                          0x4

#define OLDARCH 0
#define ARCHV2  2
#define ARCHV3  3
#define ARCHV4  4

#define FW_V3                               0x3
#define FW_V4                               0x4

#define PCIE_LINK_CAP_NOMAL                  0x700007c
#define PCIE_LINK_STA_NOMAL                  0x7000080
#define DDR_CLOCK_GATE_EN                    0x20000
#define VE_CLOCK_GATE_EN                     0x20004
#define VCPU_SCH_PCIE_RPPTOP_CG              0x20008
#define RPP_TOP_CLK_REGS                     0x2000c
#define VE_BPU_CLK_REGS                      0x20010
#define VE_APB_CLK_REGS                      0x20014
#define DDR_APB_CLK_REGS                     0x20018
#define PCI_SCH_CLK_REGS                     0x2001c
#define VE_MAIN_CLK_REGS                     0x20020
#define CNT_EN                               0x20030
#define GLITCH_FREE_MUX_CLK_SEL              0x20034
#define RPP_TOP_APB_CLK_REGS                 0x20038
#define VCPU_PER_CLK_REGS                    0x2003c
#define PLL1_DIV_REGS_NOMAL                  0x20040
#define PLL2_DIV_REGS_NOMAL                  0x2004c
#define PLL3_DIV_REGS_NOMAL                  0x20058
#define PLL4_DIV_REGS_NOMAL                  0x20064
#define PLL5_DIV_REGS_NOMAL                  0x20070

typedef enum  {
  INFO_DEVICE_NAME,
  INFO_SN,
  INFO_BOARD_VERSION,
  INFO_FIRMWARE,
  INFO_BOOT_MODE,
  INFO_PCI_ID,
  INFO_PCIE_LINK_CAP_SPEEND,
  INFO_PCIE_LINK_CAP_WIDTH,
  INFO_PCIE_LINK_STA_SPEEND,
  INFO_PCIE_LINK_STA_WIDTH,
  INFO_RPP_CORE_CLK,
  INFO_VE_CLK,
  INFO_DDR0_CLK,
  INFO_DDR1_CLK,
  INFO_FAN_WORKING_TEMP,
  INFO_CLOCK_THROTTLING_TEMP,
  INFO_TRIP_TEMP,
  INFO_FAN_SPEED,
  INFO_DDR_NUM,
  INFO_DDR_SIZE,
  INFO_TEMP,
  INFO_POW,
  INFO_POW_IN,
  INFO_GPU_LOADING,
  INFO_BL_CONFIG_VERSION,
  INFO_FW_CONFIG_VERSION,
  INFO_BOOTLOADER_VERSION,
  INFO_VOL,
  INFO_PWRMODE,
  INFO_WORKMODE,
  INFO_MFG_ID,
  INFO_BRAND,
  INFO_PN,
} info_name;

typedef enum  {
  INFO_RETURN_INT,
  INFO_RETURN_UNSIGNED_INT,
  INFO_RETURN_CHAR,
  INFO_RETURN_FLOAT,
  INFO_RETURN_DOUBLE,
  INFO_RETURN_STRING,
  INFO_RETURN_SHORT,
  INFO_RETURN_LONG,
} info_type;

typedef enum  {
    SUBCMD_SET_CTRL_HEADER = 0x0,
    SUBCMD_SET_THERMAL_CTRL = 0x1,
    SUBCMD_SET_PMIC_VOL = 0x2,
    SUBCMD_SET_DDR_CTRL = 0x3,
    SUBCMD_SET_PLL1 = 0x4,
    SUBCMD_SET_PLL2 = 0x5,
    SUBCMD_SET_PLL3 = 0x6,
    SUBCMD_SET_RPP_CORE_FREQ = 0x7,
    SUBCMD_SET_VE_FREQ = 0x8,
    SUBCMD_SET_PMIC_ONOFF = 0x9,
    SUBCMD_SET_POLLING_TIME = 0xa,
    SUBCMD_GET_CTRL_HEADER = 0x10,
    SUBCMD_GET_THERMAL_CTRL = 0x11,
    SUBCMD_GET_PMIC_VOL = 0x12,
    SUBCMD_GET_DDR_CTRL = 0x13,
    SUBCMD_GET_PLL1 = 0x14,
    SUBCMD_GET_PLL2 = 0x15,
    SUBCMD_GET_PLL3 = 0x16,
    SUBCMD_GET_RPP_CORE_FREQ = 0x17,
    SUBCMD_GET_VE_FREQ = 0x18,
} ctrl_cmd_e;

typedef enum  {
    SUBCMD_SET_PWRMODE_WORKING = 0x0,
    SUBCMD_SET_PWRMODE_LOWER_POWER = 0x1,
    SUBCMD_SET_PWRMODE_STANDBY = 0x2,
    SUBCMD_PWRMODE_MAX,
} power_mode_cmd_e;

typedef enum {
    AE_SMI_STATUS_MS_NULL = 0,
    AE_SMI_STATUS_MS_SLEEP_IN = 11,
    AE_SMI_STATUS_MS_SLEEP_ACK = 12,
    AE_SMI_STATUS_MS_WAKED_IN = 13,
    AE_SMI_STATUS_MS_WAKED_ACK = 14,
    AE_SMI_STATUS_MS_WAKING_IN = 15,
    AE_SMI_STATUS_MS_WAKING_ACK = 16,
    AE_SMI_STATUS_MS_EXIT = 200,
    AE_SMI_STATUS_MS_FAIL = 255,
} AE_SMI_STAUS_ENUM;

#endif
