#ifndef IMXRT_REGMAP_H
#define IMXRT_REGMAP_H

// This file contains the register definitions and contents for the IMXRT1062

// The register format is as follows:
//      typedef volatile struct {
//          reg_t field1 : a;
//          reg_t field2 : b;
//          ...
//          reg_t fieldN : z;
//      } REGISTER_NAME_t;
// #define REGISTER_NAME ((REGISTER_NAME_t*)0xADDRESS)
// The define is required to keep the compiler from placing these in the DTCM and in memory in general

#include <stdint.h>

typedef volatile uint32_t reg_t;

// IOMUXC GPR Memory Map/Register Definition
// RM 11.3

#pragma region IOMUXC_GPR

typedef volatile struct {
    reg_t : 32; 
} IOMUXC_GPR_GPR0_t;
#define IOMUXC_GPR_GPR0 ((IOMUXC_GPR_GPR0_t*)0x400AC000)

typedef volatile struct {
    reg_t SAI1_MCLK1_SEL : 3;
    reg_t SAI1_MCLK2_SEL : 3;
    reg_t SAI1_MCLK3_SEL : 2;
    reg_t SAI2_MCLK3_SEL : 2;
    reg_t SAI3_MCLK4_SEL : 2;
    reg_t GINT : 1;
    reg_t ENET1_CLK_SEL : 1;
    reg_t ENET2_CLK_SEL : 1;
    reg_t : 2;
    reg_t ENET1_TX_CLK_DIR : 1;
    reg_t ENET2_TX_CLK_DIR : 1;
    reg_t SAI1_MCLK_DIR : 1;
    reg_t SAI2_MCLK_DIR : 1;
    reg_t SAI3_MCLK_DIR : 1;
    reg_t EXC_MON : 1;
    reg_t ENET_IPG_CLK_S_EN : 1;
    reg_t : 7;
    reg_t CM7_FORCE_HCLK_EN : 1;
} IOMUXC_GPR_GPR1_t;
#define IOMUXC_GPR_GPR1 ((IOMUXC_GPR_GPR1_t*)0x400AC004)

typedef volatile struct {
    reg_t AXBS_L_AXBXL_HIGH_PRIORITY : 1;
    reg_t AXBS_L_DMA_HIGH_PRIORITY : 1;
    reg_t AXBS_L_FORCE_ROUND_ROBIN : 1;
    reg_t AXBS_P_M0_HIGH_PRIORITY : 1;
    reg_t AXBS_P_M1_HIGH_PRIORITY : 1;
    reg_t AXBS_P_FORCE_ROUND_ROBIN : 1;
    reg_t CANFD_FILTER_BYPASS : 1;
    reg_t : 5;
    reg_t L2_MEM_EN_POWERSAVING : 1;
    reg_t RAM_AUTO_CLK_GATING_EN : 1;
    reg_t L2_MEM_DEEPSLEEP : 1;
    reg_t : 1;
    reg_t MQS_CLK_DIV : 8;
    reg_t MQS_SW_RST : 1;
    reg_t MQS_EN : 1;
    reg_t MQS_OVERSAMPLE : 1;
    reg_t : 1;
    reg_t QTIMER1_TMR_CNTS_FREEZE : 1;
    reg_t QTIMER2_TMR_CNTS_FREEZE : 1;
    reg_t QTIMER3_TMR_CNTS_FREEZE : 1;
    reg_t QTIMER4_TMR_CNTS_FREEZE : 1;
} IOMUXC_GPR_GPR2_t;
#define IOMUXC_GPR_GPR2 ((IOMUXC_GPR_GPR2_t*)0x400AC008)

typedef volatile struct {
    reg_t OCRAM_CTL : 4;
    reg_t DCP_KEY_SEL : 1;
    reg_t : 3;
    reg_t OCRAM2_CTL : 4;
    reg_t : 3;
    reg_t AXBS_L_HALT_REQ : 1;
    reg_t OCRAM_STATUS : 4;
    reg_t : 4;
    reg_t OCRAM2_STATUS : 4;
    reg_t : 3;
    reg_t AXBS_L_HALTED : 1;
} IOMUXC_GPR_GPR3_t;
#define IOMUXC_GPR_GPR3 ((IOMUXC_GPR_GPR3_t*)0x400AC00C)

typedef volatile struct {
    reg_t EDMA_STOP_REQ : 1;
    reg_t CAN1_STOP_REQ : 1;
    reg_t CAN2_STOP_REQ : 1;
    reg_t TRNG_STOP_REQ : 1;
    reg_t ENET_STOP_REQ : 1;
    reg_t SAI1_STOP_REQ : 1;
    reg_t SAI2_STOP_REQ : 1;
    reg_t SAI3_STOP_REQ : 1;
    reg_t ENET2_STOP_REQ : 1;
    reg_t SEMC_STOP_REQ : 1;
    reg_t PIT_STOP_REQ : 1;
    reg_t FLEXSPI_STOP_REQ : 1;
    reg_t FLEXIO1_STOP_REQ : 1;
    reg_t FLEXIO2_STOP_REQ : 1;
    reg_t FLEXIO3_STOP_REQ : 1;
    reg_t FLEXIO4_STOP_REQ : 1;
    reg_t EDMA_STOP_ACK : 1;
    reg_t CAN1_STOP_ACK : 1;
    reg_t CAN2_STOP_ACK : 1;
    reg_t TRNG_STOP_ACK : 1;
    reg_t ENET_STOP_ACK : 1;
    reg_t SAI1_STOP_ACK : 1;
    reg_t SAI2_STOP_ACK : 1;
    reg_t SAI3_STOP_ACK : 1;
    reg_t ENET2_STOP_ACK : 1;
    reg_t SEMC_STOP_ACK : 1;
    reg_t PIT_STOP_ACK : 1;
    reg_t FLEXSPI_STOP_ACK : 1;
    reg_t FLEXIO1_STOP_ACK : 1;
    reg_t FLEXIO2_STOP_ACK : 1;
    reg_t FLEXIO3_STOP_ACK : 1;
    reg_t FLEXIO4_STOP_ACK : 1;
} IOMUXC_GPR_GPR4_t;
#define IOMUXC_GPR_GPR4 ((IOMUXC_GPR_GPR4_t*)0x400AC010)

typedef volatile struct {
    reg_t : 6;
    reg_t WDOG1_MASK : 1;
    reg_t WDOG2_MASK : 1;
    reg_t : 15;
    reg_t GPT2_CAPIN1_SEL : 1;
    reg_t GPT2_CAPIN2_SEL : 1;
    reg_t ENET_EVENT3IN_SEL : 1;
    reg_t ENET2_EVENT3IN_SEL : 1;
    reg_t : 1;
    reg_t VREF_1M_CLK_GPT1 : 1;
    reg_t VREF_1M_CLK_GPT2 : 1;
    reg_t : 2;
} IOMUXC_GPR_GPR5_t;
#define IOMUXC_GPR_GPR5 ((IOMUXC_GPR_GPR5_t*)0x400AC014)

typedef volatile struct {
    reg_t QTIMER1_TRM0_INPUT_SEL : 1;
    reg_t QTIMER1_TRM1_INPUT_SEL : 1;
    reg_t QTIMER1_TRM2_INPUT_SEL : 1;
    reg_t QTIMER1_TRM3_INPUT_SEL : 1;
    reg_t QTIMER2_TRM0_INPUT_SEL : 1;
    reg_t QTIMER2_TRM1_INPUT_SEL : 1;
    reg_t QTIMER2_TRM2_INPUT_SEL : 1;
    reg_t QTIMER2_TRM3_INPUT_SEL : 1;
    reg_t QTIMER3_TRM0_INPUT_SEL : 1;
    reg_t QTIMER3_TRM1_INPUT_SEL : 1;
    reg_t QTIMER3_TRM2_INPUT_SEL : 1;
    reg_t QTIMER3_TRM3_INPUT_SEL : 1;
    reg_t QTIMER4_TRM0_INPUT_SEL : 1;
    reg_t QTIMER4_TRM1_INPUT_SEL : 1;
    reg_t QTIMER4_TRM2_INPUT_SEL : 1;
    reg_t QTIMER4_TRM3_INPUT_SEL : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_4 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_5 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_6 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_7 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_8 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_9 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_10 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_11 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_12 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_13 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_14 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_15 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_16 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_17 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_18 : 1;
    reg_t IOMUXC_XBAR_DIR_SEL_19 : 1;    
} IOMUXC_GPR_GPR6_t;
#define IOMUXC_GPR_GPR6 ((IOMUXC_GPR_GPR6_t*)0x400AC018)

typedef volatile struct {
    reg_t LPI2C1_STOP_REQ : 1;
    reg_t LPI2C2_STOP_REQ : 1;
    reg_t LPI2C3_STOP_REQ : 1;
    reg_t LPI2C4_STOP_REQ : 1;
    reg_t LPSPI1_STOP_REQ : 1;
    reg_t LPSPI2_STOP_REQ : 1;
    reg_t LPSPI3_STOP_REQ : 1;
    reg_t LPSPI4_STOP_REQ : 1;
    reg_t LPUART1_STOP_REQ : 1;
    reg_t LPUART2_STOP_REQ : 1;
    reg_t LPUART3_STOP_REQ : 1;
    reg_t LPUART4_STOP_REQ : 1;
    reg_t LPUART5_STOP_REQ : 1;
    reg_t LPUART6_STOP_REQ : 1;
    reg_t LPUART7_STOP_REQ : 1;
    reg_t LPUART8_STOP_REQ : 1;
    reg_t LPI2C1_STOP_ACK : 1;
    reg_t LPI2C2_STOP_ACK : 1;
    reg_t LPI2C3_STOP_ACK : 1;
    reg_t LPI2C4_STOP_ACK : 1;
    reg_t LPSPI1_STOP_ACK : 1;
    reg_t LPSPI2_STOP_ACK : 1;
    reg_t LPSPI3_STOP_ACK : 1;
    reg_t LPSPI4_STOP_ACK : 1;
    reg_t LPUART1_STOP_ACK : 1;
    reg_t LPUART2_STOP_ACK : 1;
    reg_t LPUART3_STOP_ACK : 1;
    reg_t LPUART4_STOP_ACK : 1;
    reg_t LPUART5_STOP_ACK : 1;
    reg_t LPUART6_STOP_ACK : 1;
    reg_t LPUART7_STOP_ACK : 1;
    reg_t LPUART8_STOP_ACK : 1;
} IOMUXC_GPR_GPR7_t;
#define IOMUXC_GPR_GPR7 ((IOMUXC_GPR_GPR7_t*)0x400AC01C)

typedef volatile struct {
    reg_t LPI2C1_IPG_STOP_MODE : 1;
    reg_t LP12C1_IPG_DOZE : 1;
    reg_t LPI2C2_IPG_STOP_MODE : 1;
    reg_t LPI2C2_IPG_DOZE : 1;
    reg_t LPI2C3_IPG_STOP_MODE : 1;
    reg_t LPI2C3_IPG_DOZE : 1;
    reg_t LPI2C4_IPG_STOP_MODE : 1;
    reg_t LPI2C4_IPG_DOZE : 1;
    reg_t LPSPI1_IPG_STOP_MODE : 1;
    reg_t LPSPI1_IPG_DOZE : 1;
    reg_t LPSPI2_IPG_STOP_MODE : 1;
    reg_t LPSPI2_IPG_DOZE : 1;
    reg_t LPSPI3_IPG_STOP_MODE : 1;
    reg_t LPSPI3_IPG_DOZE : 1;
    reg_t LPSPI4_IPG_STOP_MODE : 1;
    reg_t LPSPI4_IPG_DOZE : 1;
    reg_t LPUART1_IPG_STOP_MODE : 1;
    reg_t LPUART1_IPG_DOZE : 1;
    reg_t LPUART2_IPG_STOP_MODE : 1;
    reg_t LPUART2_IPG_DOZE : 1;
    reg_t LPUART3_IPG_STOP_MODE : 1;
    reg_t LPUART3_IPG_DOZE : 1;
    reg_t LPUART4_IPG_STOP_MODE : 1;
    reg_t LPUART4_IPG_DOZE : 1;
    reg_t LPUART5_IPG_STOP_MODE : 1;
    reg_t LPUART5_IPG_DOZE : 1;
    reg_t LPUART6_IPG_STOP_MODE : 1;
    reg_t LPUART6_IPG_DOZE : 1;
    reg_t LPUART7_IPG_STOP_MODE : 1;
    reg_t LPUART7_IPG_DOZE : 1;
    reg_t LPUART8_IPG_STOP_MODE : 1;
    reg_t LPUART8_IPG_DOZE : 1;
} IOMUXC_GPR_GPR8_t;
#define IOMUXC_GPR_GPR8 ((IOMUXC_GPR_GPR8_t*)0x400AC020)

typedef volatile struct {
    reg_t : 32;
} IOMUXC_GPR_GPR9_t;
#define IOMUXC_GPR_GPR9 ((IOMUXC_GPR_GPR9_t*)0x400AC024)

typedef volatile struct {
    reg_t NIDEN : 1;
    reg_t DBG_EN : 1;
    reg_t SEC_ERR_RESP : 1;
    reg_t : 1;
    reg_t DCPKEY_OCOTP_OR_KEYMUX : 1;
    reg_t : 3;
    reg_t OCRAM_TZ_EN : 1;
    reg_t OCRAM_TZ_ADDR : 7;
    reg_t LOCK_NIDEN : 1;
    reg_t LOCK_DBG_EN : 1;
    reg_t LOCK_SEC_ERR_RESP : 1;
    reg_t : 1;
    reg_t LOCK_DCPKEY_OCOTP_OR_KEYMUX : 1;
    reg_t : 3;
    reg_t LOCK_OCRAM_TZ_EN : 1;
    reg_t LOCK_OCRAM_TZ_ADDR : 7;
} IOMUXC_GPR_GPR10_t;
#define IOMUXC_GPR_GPR10 ((IOMUXC_GPR_GPR10_t*)0x400AC028)

typedef volatile struct {
    reg_t M7_APC_AR_R0_CTRL : 2;
    reg_t M7_APC_AR_R1_CTRL : 2;
    reg_t M7_APC_AR_R2_CTRL : 2;
    reg_t M7_APC_AR_R3_CTRL : 2;
    reg_t BEE_DE_RX_EN : 4;
    reg_t : 20;
} IOMUXC_GPR_GPR11_t;
#define IOMUXC_GPR_GPR11 ((IOMUXC_GPR_GPR11_t*)0x400AC02C)

typedef volatile struct {
    reg_t FLEXIO1_IPG_STOP_MODE : 1;
    reg_t FLEXIO1_IPG_DOZE : 1;
    reg_t FLEXIO2_IPG_STOP_MODE : 1;
    reg_t FLEXIO2_IPG_DOZE : 1;
    reg_t ACMP_IPG_STOP_MODE : 1;
    reg_t FLEXIO3_IPG_STOP_MODE : 1;
    reg_t FLEXIO3_IPG_DOZE : 1;
    reg_t : 25;
} IOMUXC_GPR_GPR12_t;
#define IOMUXC_GPR_GPR12 ((IOMUXC_GPR_GPR12_t*)0x400AC030)

typedef volatile struct {
    reg_t ARCACHE_USDHC : 1;
    reg_t AWCACHE_USDHC : 1;
    reg_t : 2;
    reg_t CANFD_STOP_REQ : 1;
    reg_t : 2;
    reg_t CACHE_ENET : 1;
    reg_t : 5;
    reg_t CACHE_USB : 1;
    reg_t : 6;
    reg_t CANFD_STOP_ACK : 1;
    reg_t : 11;
} IOMUXC_GPR_GPR13_t;
#define IOMUXC_GPR_GPR13 ((IOMUXC_GPR_GPR13_t*)0x400AC034)

typedef volatile struct {
    reg_t ACMP1_CMP_IGEN_TRIM_DN : 1;
    reg_t ACMP2_CMP_IGEN_TRIM_DN : 1;
    reg_t ACMP3_CMP_IGEN_TRIM_DN : 1;
    reg_t ACMP4_CMP_IGEN_TRIM_DN : 1;
    reg_t ACMP1_CMP_IGEN_TRIM_UP : 1;
    reg_t ACMP2_CMP_IGEN_TRIM_UP : 1;
    reg_t ACMP3_CMP_IGEN_TRIM_UP : 1;
    reg_t ACMP4_CMP_IGEN_TRIM_UP : 1;
    reg_t ACMP1_SAMPLE_SYNC_EN : 1;
    reg_t ACMP2_SAMPLE_SYNC_EN : 1;
    reg_t ACMP3_SAMPLE_SYNC_EN : 1;
    reg_t ACMP4_SAMPLE_SYNC_EN : 1;
    reg_t : 20;
} IOMUXC_GPR_GPR14_t;
#define IOMUXC_GPR_GPR14 ((IOMUXC_GPR_GPR14_t*)0x400AC038)

typedef volatile struct {
    reg_t : 32;
} IOMUXC_GPR_GPR15_t;
#define IOMUXC_GPR_GPR15 ((IOMUXC_GPR_GPR15_t*)0x400AC03C)

typedef volatile struct {
    reg_t : 2;
    reg_t FLEXRAM_BANK_CFG_SEL : 1;
    reg_t : 4;
    reg_t CM7_INIT_VTOR : 25;
} IOMUXC_GPR_GPR16_t;
#define IOMUXC_GPR_GPR16 ((IOMUXC_GPR_GPR16_t*)0x400AC040)

typedef volatile struct {
    reg_t FLEXRAM_BANK_CFG : 32;
} IOMUXC_GPR_GPR17_t;
#define IOMUXC_GPR_GPR17 ((IOMUXC_GPR_GPR17_t*)0x400AC044)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R0_BOT : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R0_BOT : 29;
} IOMUXC_GPR_GPR18_t;
#define IOMUXC_GPR_GPR18 ((IOMUXC_GPR_GPR18_t*)0x400AC048)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R0_TOP : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R0_TOP : 29;
} IOMUXC_GPR_GPR19_t;
#define IOMUXC_GPR_GPR19 ((IOMUXC_GPR_GPR19_t*)0x400AC04C)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R1_BOT : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R1_BOT : 29;
} IOMUXC_GPR_GPR20_t;
#define IOMUXC_GPR_GPR20 ((IOMUXC_GPR_GPR20_t*)0x400AC050)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R1_TOP : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R1_TOP : 29;
} IOMUXC_GPR_GPR21_t;
#define IOMUXC_GPR_GPR21 ((IOMUXC_GPR_GPR21_t*)0x400AC054)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R2_BOT : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R2_BOT : 29;
} IOMUXC_GPR_GPR22_t;
#define IOMUXC_GPR_GPR22 ((IOMUXC_GPR_GPR22_t*)0x400AC058)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R2_TOP : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R2_TOP : 29;
} IOMUXC_GPR_GPR23_t;
#define IOMUXC_GPR_GPR23 ((IOMUXC_GPR_GPR23_t*)0x400AC05C)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R3_BOT : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R3_BOT : 29;
} IOMUXC_GPR_GPR24_t;
#define IOMUXC_GPR_GPR24 ((IOMUXC_GPR_GPR24_t*)0x400AC060)

typedef volatile struct {
    reg_t LOCK_M7_APC_AC_R3_TOP : 1;
    reg_t : 2;
    reg_t M7_APC_AC_R3_TOP : 29;
} IOMUXC_GPR_GPR25_t;
#define IOMUXC_GPR_GPR25 ((IOMUXC_GPR_GPR25_t*)0x400AC064)

typedef volatile struct {
    reg_t GPIO_MUX1_GPIO_SEL : 32;
} IOMUXC_GPR_GPR26_t;
#define IOMUXC_GPR_GPR26 ((IOMUXC_GPR_GPR26_t*)0x400AC068)

typedef volatile struct {
    reg_t GPIO_MUX2_GPIO_SEL : 32;
} IOMUXC_GPR_GPR27_t;
#define IOMUXC_GPR_GPR27 ((IOMUXC_GPR_GPR27_t*)0x400AC06C)

typedef volatile struct {
    reg_t GPIO_MUX3_GPIO_SEL : 32;
} IOMUXC_GPR_GPR28_t;
#define IOMUXC_GPR_GPR28 ((IOMUXC_GPR_GPR28_t*)0x400AC070)

typedef volatile struct {
    reg_t GPIO_MUX4_GPIO_SEL : 32;
} IOMUXC_GPR_GPR29_t;
#define IOMUXC_GPR_GPR29 ((IOMUXC_GPR_GPR29_t*)0x400AC074)

typedef volatile struct {
    reg_t : 12;
    reg_t FLEXSPI_REMAP_ADDR_START : 20;
} IOMUXC_GPR_GPR30_t;
#define IOMUXC_GPR_GPR30 ((IOMUXC_GPR_GPR30_t*)0x400AC078)

typedef volatile struct {
    reg_t : 12;
    reg_t FLEXSPI_REMAP_ADDR_END : 20;
} IOMUXC_GPR_GPR31_t;
#define IOMUXC_GPR_GPR31 ((IOMUXC_GPR_GPR31_t*)0x400AC07C)

typedef volatile struct {
    reg_t : 12;
    reg_t FLEXSPI_REMAP_ADDR_OFFSET : 20;
} IOMUXC_GPR_GPR32_t;
#define IOMUXC_GPR_GPR32 ((IOMUXC_GPR_GPR32_t*)0x400AC080)

typedef volatile struct {
    reg_t OCRAM2_TZ_EN : 1;
    reg_t OCRAM2_TZ_ADDR : 7;
    reg_t : 8;
    reg_t LOCK_OCRAM2_TZ_EN : 1;
    reg_t LOCK_OCRAM2_TZ_ADDR : 7;
    reg_t : 8;
} IOMUXC_GPR_GPR33_t;
#define IOMUXC_GPR_GPR33 ((IOMUXC_GPR_GPR33_t*)0x400AC084)

typedef volatile struct {
    reg_t SIP_TEST_MUX_BOOT_PIN_SEL : 8;
    reg_t SIP_TEST_MUX_QSPI_SIP_EN : 1;
    reg_t : 23;
} IOMUXC_GPR_GPR34_t;
#define IOMUXC_GPR_GPR34 ((IOMUXC_GPR_GPR34_t*)0x400AC088)
#pragma endregion

#endif // IMXRT_REGMAP_H