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

// References of the form RM 11.2.3 refer to the reference manual for the IMXRT1062, chapter 11, section 2, subsection 3
// Reference manual can be found in the doc folder: IMXRT1060ReferenceManual.pdf

#include <stdint.h>

typedef volatile uint32_t reg_t;

// IOMUXC Memory Map/Register Definition
// RM 11

#pragma region IOMUXC_MODULE

typedef volatile struct {
	reg_t mux_mode : 4;	 // what ALT mode this pin is set to, determines functionality
	reg_t sion	   : 1;	 // software input on/off, allows software to control input
	reg_t		   : 27;
} IOMUXC_SW_MUX_CTL_PAD_t;

// ALT mode macros for GPIO muxing
#define IOMUXC_ALT1 (0x01u)
#define IOMUXC_ALT2 (0x02u)
#define IOMUXC_ALT3 (0x03u)
#define IOMUXC_ALT4 (0x04u)
#define IOMUXC_ALT5 (0x05u)
#define IOMUXC_ALT6 (0x06u)
#define IOMUXC_ALT7 (0x07u)
#define IOMUXC_ALT8 (0x08u)

typedef volatile struct {
	reg_t sre	: 1;  // slew rate enable
	reg_t		: 2;
	reg_t dse	: 3;  // drive strength
	reg_t speed : 2;  // drive speed
	reg_t		: 3;
	reg_t ode	: 1;  // open drain enable
	reg_t pke	: 1;  // pull / keep enable
	reg_t pue	: 1;  // pull / keep select
	reg_t pus	: 2;  // pull / keep config
	reg_t hys	: 1;  // hysteresis enable
	reg_t		: 15;
} IOMUXC_SW_PAD_CTL_PAD_t;

// IOMUXC GPR Memory Map/Register Definition
// RM 11.3

#pragma region IOMUXC_GPR

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_GPR_GPR0_t;
#define IOMUXC_GPR_GPR0         ((IOMUXC_GPR_GPR0_t*)0x400AC000u)
#define IOMUXC_GPR_GPR0_RAW     ((reg_t*)0x400AC000u)

typedef volatile struct {
	reg_t sai1_mclk1_sel	: 3;
	reg_t sai1_mclk2_sel	: 3;
	reg_t sai1_mclk3_sel	: 2;
	reg_t sai2_mclk3_sel	: 2;
	reg_t sai3_mclk4_sel	: 2;
	reg_t gint				: 1;
	reg_t enet1_clk_sel		: 1;
	reg_t enet2_clk_sel		: 1;
	reg_t					: 2;
	reg_t enet1_tx_clk_dir	: 1;
	reg_t enet2_tx_clk_dir	: 1;
	reg_t sai1_mclk_dir		: 1;
	reg_t sai2_mclk_dir		: 1;
	reg_t sai3_mclk_dir		: 1;
	reg_t exc_mon			: 1;
	reg_t enet_ipg_clk_s_en : 1;
	reg_t					: 7;
	reg_t cm7_force_hclk_en : 1;
} IOMUXC_GPR_GPR1_t;
#define IOMUXC_GPR_GPR1         ((IOMUXC_GPR_GPR1_t*)0x400AC004u)
#define IOMUXC_GPR_GPR1_RAW     ((reg_t*)0x400AC004u)

typedef volatile struct {
	reg_t axbs_l_axbxl_high_priority : 1;
	reg_t axbs_l_dma_high_priority	 : 1;
	reg_t axbs_l_force_round_robin	 : 1;
	reg_t axbs_p_m0_high_priority	 : 1;
	reg_t axbs_p_m1_high_priority	 : 1;
	reg_t axbs_p_force_round_robin	 : 1;
	reg_t canfd_filter_bypass		 : 1;
	reg_t							 : 5;
	reg_t l2_mem_en_powersaving		 : 1;
	reg_t ram_auto_clk_gating_en	 : 1;
	reg_t l2_mem_deepsleep			 : 1;
	reg_t							 : 1;
	reg_t mqs_clk_div				 : 8;
	reg_t mqs_sw_rst				 : 1;
	reg_t mqs_en					 : 1;
	reg_t mqs_oversample			 : 1;
	reg_t							 : 1;
	reg_t qtimer1_tmr_cnts_freeze	 : 1;
	reg_t qtimer2_tmr_cnts_freeze	 : 1;
	reg_t qtimer3_tmr_cnts_freeze	 : 1;
	reg_t qtimer4_tmr_cnts_freeze	 : 1;
} IOMUXC_GPR_GPR2_t;
#define IOMUXC_GPR_GPR2         ((IOMUXC_GPR_GPR2_t*)0x400AC008u)
#define IOMUXC_GPR_GPR2_RAW     ((reg_t*)0x400AC008u)

typedef volatile struct {
	reg_t ocram_ctl		  : 4;
	reg_t dcp_key_sel	  : 1;
	reg_t				  : 3;
	reg_t ocram2_ctl	  : 4;
	reg_t				  : 3;
	reg_t axbs_l_halt_req : 1;
	reg_t ocram_status	  : 4;
	reg_t				  : 4;
	reg_t ocram2_status	  : 4;
	reg_t				  : 3;
	reg_t axbs_l_halted	  : 1;
} IOMUXC_GPR_GPR3_t;
#define IOMUXC_GPR_GPR3         ((IOMUXC_GPR_GPR3_t*)0x400AC00Cu)
#define IOMUXC_GPR_GPR3_RAW     ((reg_t*)0x400AC00Cu)

typedef volatile struct {
	reg_t edma_stop_req	   : 1;
	reg_t can1_stop_req	   : 1;
	reg_t can2_stop_req	   : 1;
	reg_t trng_stop_req	   : 1;
	reg_t enet_stop_req	   : 1;
	reg_t sai1_stop_req	   : 1;
	reg_t sai2_stop_req	   : 1;
	reg_t sai3_stop_req	   : 1;
	reg_t enet2_stop_req   : 1;
	reg_t semc_stop_req	   : 1;
	reg_t pit_stop_req	   : 1;
	reg_t flexspi_stop_req : 1;
	reg_t flexio1_stop_req : 1;
	reg_t flexio2_stop_req : 1;
	reg_t flexio3_stop_req : 1;
	reg_t flexio4_stop_req : 1;
	reg_t edma_stop_ack	   : 1;
	reg_t can1_stop_ack	   : 1;
	reg_t can2_stop_ack	   : 1;
	reg_t trng_stop_ack	   : 1;
	reg_t enet_stop_ack	   : 1;
	reg_t sai1_stop_ack	   : 1;
	reg_t sai2_stop_ack	   : 1;
	reg_t sai3_stop_ack	   : 1;
	reg_t enet2_stop_ack   : 1;
	reg_t semc_stop_ack	   : 1;
	reg_t pit_stop_ack	   : 1;
	reg_t flexspi_stop_ack : 1;
	reg_t flexio1_stop_ack : 1;
	reg_t flexio2_stop_ack : 1;
	reg_t flexio3_stop_ack : 1;
	reg_t flexio4_stop_ack : 1;
} IOMUXC_GPR_GPR4_t;
#define IOMUXC_GPR_GPR4         ((IOMUXC_GPR_GPR4_t*)0x400AC010u)
#define IOMUXC_GPR_GPR4_RAW     ((reg_t*)0x400AC010u)

typedef volatile struct {
	reg_t					 : 6;
	reg_t wdog1_mask		 : 1;
	reg_t wdog2_mask		 : 1;
	reg_t					 : 15;
	reg_t gpt2_capin1_sel	 : 1;
	reg_t gpt2_capin2_sel	 : 1;
	reg_t enet_event3in_sel	 : 1;
	reg_t enet2_event3in_sel : 1;
	reg_t					 : 1;
	reg_t vref_1m_clk_gpt1	 : 1;
	reg_t vref_1m_clk_gpt2	 : 1;
	reg_t					 : 2;
} IOMUXC_GPR_GPR5_t;
#define IOMUXC_GPR_GPR5         ((IOMUXC_GPR_GPR5_t*)0x400AC014u)
#define IOMUXC_GPR_GPR5_RAW     ((reg_t*)0x400AC014u)

typedef volatile struct {
	reg_t qtimer1_trm0_input_sel : 1;
	reg_t qtimer1_trm1_input_sel : 1;
	reg_t qtimer1_trm2_input_sel : 1;
	reg_t qtimer1_trm3_input_sel : 1;
	reg_t qtimer2_trm0_input_sel : 1;
	reg_t qtimer2_trm1_input_sel : 1;
	reg_t qtimer2_trm2_input_sel : 1;
	reg_t qtimer2_trm3_input_sel : 1;
	reg_t qtimer3_trm0_input_sel : 1;
	reg_t qtimer3_trm1_input_sel : 1;
	reg_t qtimer3_trm2_input_sel : 1;
	reg_t qtimer3_trm3_input_sel : 1;
	reg_t qtimer4_trm0_input_sel : 1;
	reg_t qtimer4_trm1_input_sel : 1;
	reg_t qtimer4_trm2_input_sel : 1;
	reg_t qtimer4_trm3_input_sel : 1;
	reg_t iomuxc_xbar_dir_sel_4	 : 1;
	reg_t iomuxc_xbar_dir_sel_5	 : 1;
	reg_t iomuxc_xbar_dir_sel_6	 : 1;
	reg_t iomuxc_xbar_dir_sel_7	 : 1;
	reg_t iomuxc_xbar_dir_sel_8	 : 1;
	reg_t iomuxc_xbar_dir_sel_9	 : 1;
	reg_t iomuxc_xbar_dir_sel_10 : 1;
	reg_t iomuxc_xbar_dir_sel_11 : 1;
	reg_t iomuxc_xbar_dir_sel_12 : 1;
	reg_t iomuxc_xbar_dir_sel_13 : 1;
	reg_t iomuxc_xbar_dir_sel_14 : 1;
	reg_t iomuxc_xbar_dir_sel_15 : 1;
	reg_t iomuxc_xbar_dir_sel_16 : 1;
	reg_t iomuxc_xbar_dir_sel_17 : 1;
	reg_t iomuxc_xbar_dir_sel_18 : 1;
	reg_t iomuxc_xbar_dir_sel_19 : 1;
} IOMUXC_GPR_GPR6_t;
#define IOMUXC_GPR_GPR6         ((IOMUXC_GPR_GPR6_t*)0x400AC018u)
#define IOMUXC_GPR_GPR6_RAW     ((reg_t*)0x400AC018u)

typedef volatile struct {
	reg_t lpi2c1_stop_req  : 1;
	reg_t lpi2c2_stop_req  : 1;
	reg_t lpi2c3_stop_req  : 1;
	reg_t lpi2c4_stop_req  : 1;
	reg_t lpspi1_stop_req  : 1;
	reg_t lpspi2_stop_req  : 1;
	reg_t lpspi3_stop_req  : 1;
	reg_t lpspi4_stop_req  : 1;
	reg_t lpuart1_stop_req : 1;
	reg_t lpuart2_stop_req : 1;
	reg_t lpuart3_stop_req : 1;
	reg_t lpuart4_stop_req : 1;
	reg_t lpuart5_stop_req : 1;
	reg_t lpuart6_stop_req : 1;
	reg_t lpuart7_stop_req : 1;
	reg_t lpuart8_stop_req : 1;
	reg_t lpi2c1_stop_ack  : 1;
	reg_t lpi2c2_stop_ack  : 1;
	reg_t lpi2c3_stop_ack  : 1;
	reg_t lpi2c4_stop_ack  : 1;
	reg_t lpspi1_stop_ack  : 1;
	reg_t lpspi2_stop_ack  : 1;
	reg_t lpspi3_stop_ack  : 1;
	reg_t lpspi4_stop_ack  : 1;
	reg_t lpuart1_stop_ack : 1;
	reg_t lpuart2_stop_ack : 1;
	reg_t lpuart3_stop_ack : 1;
	reg_t lpuart4_stop_ack : 1;
	reg_t lpuart5_stop_ack : 1;
	reg_t lpuart6_stop_ack : 1;
	reg_t lpuart7_stop_ack : 1;
	reg_t lpuart8_stop_ack : 1;
} IOMUXC_GPR_GPR7_t;
#define IOMUXC_GPR_GPR7         ((IOMUXC_GPR_GPR7_t*)0x400AC01Cu)
#define IOMUXC_GPR_GPR7_RAW     ((reg_t*)0x400AC01Cu)

typedef volatile struct {
	reg_t lpi2c1_ipg_stop_mode	: 1;
	reg_t lp12c1_ipg_doze		: 1;
	reg_t lpi2c2_ipg_stop_mode	: 1;
	reg_t lpi2c2_ipg_doze		: 1;
	reg_t lpi2c3_ipg_stop_mode	: 1;
	reg_t lpi2c3_ipg_doze		: 1;
	reg_t lpi2c4_ipg_stop_mode	: 1;
	reg_t lpi2c4_ipg_doze		: 1;
	reg_t lpspi1_ipg_stop_mode	: 1;
	reg_t lpspi1_ipg_doze		: 1;
	reg_t lpspi2_ipg_stop_mode	: 1;
	reg_t lpspi2_ipg_doze		: 1;
	reg_t lpspi3_ipg_stop_mode	: 1;
	reg_t lpspi3_ipg_doze		: 1;
	reg_t lpspi4_ipg_stop_mode	: 1;
	reg_t lpspi4_ipg_doze		: 1;
	reg_t lpuart1_ipg_stop_mode : 1;
	reg_t lpuart1_ipg_doze		: 1;
	reg_t lpuart2_ipg_stop_mode : 1;
	reg_t lpuart2_ipg_doze		: 1;
	reg_t lpuart3_ipg_stop_mode : 1;
	reg_t lpuart3_ipg_doze		: 1;
	reg_t lpuart4_ipg_stop_mode : 1;
	reg_t lpuart4_ipg_doze		: 1;
	reg_t lpuart5_ipg_stop_mode : 1;
	reg_t lpuart5_ipg_doze		: 1;
	reg_t lpuart6_ipg_stop_mode : 1;
	reg_t lpuart6_ipg_doze		: 1;
	reg_t lpuart7_ipg_stop_mode : 1;
	reg_t lpuart7_ipg_doze		: 1;
	reg_t lpuart8_ipg_stop_mode : 1;
	reg_t lpuart8_ipg_doze		: 1;
} IOMUXC_GPR_GPR8_t;
#define IOMUXC_GPR_GPR8         ((IOMUXC_GPR_GPR8_t*)0x400AC020u)
#define IOMUXC_GPR_GPR8_RAW     ((reg_t*)0x400AC020u)

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_GPR_GPR9_t;
#define IOMUXC_GPR_GPR9         ((IOMUXC_GPR_GPR9_t*)0x400AC024u)
#define IOMUXC_GPR_GPR9_RAW     ((reg_t*)0x400AC024u)

typedef volatile struct {
	reg_t niden						  : 1;
	reg_t dbg_en					  : 1;
	reg_t sec_err_resp				  : 1;
	reg_t							  : 1;
	reg_t dcpkey_ocotp_or_keymux	  : 1;
	reg_t							  : 3;
	reg_t ocram_tz_en				  : 1;
	reg_t ocram_tz_addr				  : 7;
	reg_t lock_niden				  : 1;
	reg_t lock_dbg_en				  : 1;
	reg_t lock_sec_err_resp			  : 1;
	reg_t							  : 1;
	reg_t lock_dcpkey_ocotp_or_keymux : 1;
	reg_t							  : 3;
	reg_t lock_ocram_tz_en			  : 1;
	reg_t lock_ocram_tz_addr		  : 7;
} IOMUXC_GPR_GPR10_t;
#define IOMUXC_GPR_GPR10        ((IOMUXC_GPR_GPR10_t*)0x400AC028u)
#define IOMUXC_GPR_GPR10_RAW    ((reg_t*)0x400AC028u)

typedef volatile struct {
	reg_t m7_apc_ar_r0_ctrl : 2;
	reg_t m7_apc_ar_r1_ctrl : 2;
	reg_t m7_apc_ar_r2_ctrl : 2;
	reg_t m7_apc_ar_r3_ctrl : 2;
	reg_t bee_de_rx_en		: 4;
	reg_t					: 20;
} IOMUXC_GPR_GPR11_t;
#define IOMUXC_GPR_GPR11        ((IOMUXC_GPR_GPR11_t*)0x400AC02Cu)
#define IOMUXC_GPR_GPR11_RAW    ((reg_t*)0x400AC02Cu)

typedef volatile struct {
	reg_t flexio1_ipg_stop_mode : 1;
	reg_t flexio1_ipg_doze		: 1;
	reg_t flexio2_ipg_stop_mode : 1;
	reg_t flexio2_ipg_doze		: 1;
	reg_t acmp_ipg_stop_mode	: 1;
	reg_t flexio3_ipg_stop_mode : 1;
	reg_t flexio3_ipg_doze		: 1;
	reg_t						: 25;
} IOMUXC_GPR_GPR12_t;
#define IOMUXC_GPR_GPR12        ((IOMUXC_GPR_GPR12_t*)0x400AC030u)
#define IOMUXC_GPR_GPR12_RAW    ((reg_t*)0x400AC030u)

typedef volatile struct {
	reg_t arcache_usdhc	 : 1;
	reg_t awcache_usdhc	 : 1;
	reg_t				 : 2;
	reg_t canfd_stop_req : 1;
	reg_t				 : 2;
	reg_t cache_enet	 : 1;
	reg_t				 : 5;
	reg_t cache_usb		 : 1;
	reg_t				 : 6;
	reg_t canfd_stop_ack : 1;
	reg_t				 : 11;
} IOMUXC_GPR_GPR13_t;
#define IOMUXC_GPR_GPR13        ((IOMUXC_GPR_GPR13_t*)0x400AC034u)
#define IOMUXC_GPR_GPR13_RAW    ((reg_t*)0x400AC034u)

typedef volatile struct {
	reg_t acmp1_cmp_igen_trim_dn : 1;
	reg_t acmp2_cmp_igen_trim_dn : 1;
	reg_t acmp3_cmp_igen_trim_dn : 1;
	reg_t acmp4_cmp_igen_trim_dn : 1;
	reg_t acmp1_cmp_igen_trim_up : 1;
	reg_t acmp2_cmp_igen_trim_up : 1;
	reg_t acmp3_cmp_igen_trim_up : 1;
	reg_t acmp4_cmp_igen_trim_up : 1;
	reg_t acmp1_sample_sync_en	 : 1;
	reg_t acmp2_sample_sync_en	 : 1;
	reg_t acmp3_sample_sync_en	 : 1;
	reg_t acmp4_sample_sync_en	 : 1;
	reg_t						 : 20;
} IOMUXC_GPR_GPR14_t;
#define IOMUXC_GPR_GPR14        ((IOMUXC_GPR_GPR14_t*)0x400AC038u)
#define IOMUXC_GPR_GPR14_RAW    ((reg_t*)0x400AC038u)

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_GPR_GPR15_t;
#define IOMUXC_GPR_GPR15        ((IOMUXC_GPR_GPR15_t*)0x400AC03Cu)
#define IOMUXC_GPR_GPR15_RAW    ((reg_t*)0x400AC03Cu)

typedef volatile struct {
	reg_t					   : 2;
	reg_t flexram_bank_cfg_sel : 1;
	reg_t					   : 4;
	reg_t cm7_init_vtor		   : 25;
} IOMUXC_GPR_GPR16_t;
#define IOMUXC_GPR_GPR16        ((IOMUXC_GPR_GPR16_t*)0x400AC040u)
#define IOMUXC_GPR_GPR16_RAW    ((reg_t*)0x400AC040u)

typedef volatile struct {
	reg_t flexram_bank_cfg : 32;
} IOMUXC_GPR_GPR17_t;
#define IOMUXC_GPR_GPR17        ((IOMUXC_GPR_GPR17_t*)0x400AC044u)
#define IOMUXC_GPR_GPR17_RAW    ((reg_t*)0x400AC044u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r0_bot : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r0_bot		: 29;
} IOMUXC_GPR_GPR18_t;
#define IOMUXC_GPR_GPR18        ((IOMUXC_GPR_GPR18_t*)0x400AC048u)
#define IOMUXC_GPR_GPR18_RAW    ((reg_t*)0x400AC048u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r0_top : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r0_top		: 29;
} IOMUXC_GPR_GPR19_t;
#define IOMUXC_GPR_GPR19        ((IOMUXC_GPR_GPR19_t*)0x400AC04Cu)
#define IOMUXC_GPR_GPR19_RAW    ((reg_t*)0x400AC04Cu)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r1_bot : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r1_bot		: 29;
} IOMUXC_GPR_GPR20_t;
#define IOMUXC_GPR_GPR20        ((IOMUXC_GPR_GPR20_t*)0x400AC050u)
#define IOMUXC_GPR_GPR20_RAW    ((reg_t*)0x400AC050u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r1_top : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r1_top		: 29;
} IOMUXC_GPR_GPR21_t;
#define IOMUXC_GPR_GPR21        ((IOMUXC_GPR_GPR21_t*)0x400AC054u)
#define IOMUXC_GPR_GPR21_RAW    ((reg_t*)0x400AC054u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r2_bot : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r2_bot		: 29;
} IOMUXC_GPR_GPR22_t;
#define IOMUXC_GPR_GPR22        ((IOMUXC_GPR_GPR22_t*)0x400AC058u)
#define IOMUXC_GPR_GPR22_RAW    ((reg_t*)0x400AC058u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r2_top : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r2_top		: 29;
} IOMUXC_GPR_GPR23_t;
#define IOMUXC_GPR_GPR23        ((IOMUXC_GPR_GPR23_t*)0x400AC05Cu)
#define IOMUXC_GPR_GPR23_RAW    ((reg_t*)0x400AC05Cu)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r3_bot : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r3_bot		: 29;
} IOMUXC_GPR_GPR24_t;
#define IOMUXC_GPR_GPR24        ((IOMUXC_GPR_GPR24_t*)0x400AC060u)
#define IOMUXC_GPR_GPR24_RAW    ((reg_t*)0x400AC060u)

typedef volatile struct {
	reg_t lock_m7_apc_ac_r3_top : 1;
	reg_t						: 2;
	reg_t m7_apc_ac_r3_top		: 29;
} IOMUXC_GPR_GPR25_t;
#define IOMUXC_GPR_GPR25        ((IOMUXC_GPR_GPR25_t*)0x400AC064u)
#define IOMUXC_GPR_GPR25_RAW    ((reg_t*)0x400AC064u)

typedef volatile struct {
	reg_t gpio_mux1_gpio_sel : 32;
} IOMUXC_GPR_GPR26_t;
#define IOMUXC_GPR_GPR26        ((IOMUXC_GPR_GPR26_t*)0x400AC068u)
#define IOMUXC_GPR_GPR26_RAW    ((reg_t*)0x400AC068u)

typedef volatile struct {
	reg_t gpio_mux2_gpio_sel : 32;
} IOMUXC_GPR_GPR27_t;
#define IOMUXC_GPR_GPR27        ((IOMUXC_GPR_GPR27_t*)0x400AC06Cu)
#define IOMUXC_GPR_GPR27_RAW    ((reg_t*)0x400AC06Cu)

typedef volatile struct {
	reg_t gpio_mux3_gpio_sel : 32;
} IOMUXC_GPR_GPR28_t;
#define IOMUXC_GPR_GPR28        ((IOMUXC_GPR_GPR28_t*)0x400AC070u)
#define IOMUXC_GPR_GPR28_RAW    ((reg_t*)0x400AC070u)

typedef volatile struct {
	reg_t gpio_mux4_gpio_sel : 32;
} IOMUXC_GPR_GPR29_t;
#define IOMUXC_GPR_GPR29        ((IOMUXC_GPR_GPR29_t*)0x400AC074u)
#define IOMUXC_GPR_GPR29_RAW    ((reg_t*)0x400AC074u)

typedef volatile struct {
	reg_t						   : 12;
	reg_t flexspi_remap_addr_start : 20;
} IOMUXC_GPR_GPR30_t;
#define IOMUXC_GPR_GPR30        ((IOMUXC_GPR_GPR30_t*)0x400AC078u)
#define IOMUXC_GPR_GPR30_RAW    ((reg_t*)0x400AC078u)

typedef volatile struct {
	reg_t						 : 12;
	reg_t flexspi_remap_addr_end : 20;
} IOMUXC_GPR_GPR31_t;
#define IOMUXC_GPR_GPR31        ((IOMUXC_GPR_GPR31_t*)0x400AC07Cu)
#define IOMUXC_GPR_GPR31_RAW    ((reg_t*)0x400AC07Cu)

typedef volatile struct {
	reg_t							: 12;
	reg_t flexspi_remap_addr_offset : 20;
} IOMUXC_GPR_GPR32_t;
#define IOMUXC_GPR_GPR32        ((IOMUXC_GPR_GPR32_t*)0x400AC080u)
#define IOMUXC_GPR_GPR32_RAW    ((reg_t*)0x400AC080u)

typedef volatile struct {
	reg_t ocram2_tz_en		  : 1;
	reg_t ocram2_tz_addr	  : 7;
	reg_t					  : 8;
	reg_t lock_ocram2_tz_en	  : 1;
	reg_t lock_ocram2_tz_addr : 7;
	reg_t					  : 8;
} IOMUXC_GPR_GPR33_t;
#define IOMUXC_GPR_GPR33        ((IOMUXC_GPR_GPR33_t*)0x400AC084u)
#define IOMUXC_GPR_GPR33_RAW    ((reg_t*)0x400AC084u)

typedef volatile struct {
	reg_t sip_test_mux_boot_pin_sel : 8;
	reg_t sip_test_mux_qspi_sip_en	: 1;
	reg_t							: 23;
} IOMUXC_GPR_GPR34_t;
#define IOMUXC_GPR_GPR34        ((IOMUXC_GPR_GPR34_t*)0x400AC088u)
#define IOMUXC_GPR_GPR34_RAW    ((reg_t*)0x400AC088u)

#pragma endregion  // IOMUXC_GPR

// IOMUXC SNVS Memory Map/Register Definition
// RM 11.4

#pragma region IOMUXC_SNVS

#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP               ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8000u)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP_RAW           ((reg_t*)0x401F8000u)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ          ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8004u)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ_RAW      ((reg_t*)0x401F8004u)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8008u)
#define IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ_RAW    ((reg_t*)0x401F8008u)

#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE            ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F800Cu)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE_RAW        ((reg_t*)0x401F800Cu)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B                ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8010u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B_RAW            ((reg_t*)0x401F8010u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF                ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8014u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF_RAW            ((reg_t*)0x401F8014u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP               ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8018u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP_RAW           ((reg_t*)0x401F8018u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ          ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F801Cu)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ_RAW      ((reg_t*)0x401F801Cu)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8020u)
#define IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ_RAW    ((reg_t*)0x401F8020u)

#pragma endregion  // IOMUXC_SNVS

// IOMUXC SNVS GPR Memory Map/Register Definition
// RM 11.5

#pragma region IOMUXC_SNVS_GPR

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_SNVS_GPR_GPR0_t;
#define IOMUXC_SNVS_GPR_GPR0        ((IOMUXC_SNVS_GPR_GPR0_t*)0x401A4000u)
#define IOMUXC_SNVS_GPR_GPR0_RAW    ((reg_t*)0x401A4000u)

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_SNVS_GPR_GPR1_t;
#define IOMUXC_SNVS_GPR_GPR1       ((IOMUXC_SNVS_GPR_GPR1_t*)0x401A4004u)
#define IOMUXC_SNVS_GPR_GPR1_RAW   ((reg_t*)0x401A4004u)

typedef volatile struct {
	reg_t reserved : 32;
} IOMUXC_SNVS_GPR_GPR2_t;
#define IOMUXC_SNVS_GPR_GPR2        ((IOMUXC_SNVS_GPR_GPR2_t*)0x401A4008u)
#define IOMUXC_SNVS_GPR_GPR2_RAW    ((reg_t*)0x401A4008u)

typedef volatile struct {
	reg_t lpsr_mode_enable	   : 1;
	reg_t dcdc_status_capt_clr : 1;
	reg_t por_pull_type		   : 2;
	reg_t					   : 12;
	reg_t dcdc_in_low_vol	   : 1;
	reg_t dcdc_over_cur		   : 1;
	reg_t dcdc_over_vol		   : 1;
	reg_t dcdc_sts_dc_ok	   : 1;
	reg_t					   : 12;
} IOMUXC_SNVS_GPR_GPR3_t;
#define IOMUXC_SNVS_GPR_GPR3        ((IOMUXC_SNVS_GPR_GPR3_t*)0x401A400Cu)
#define IOMUXC_SNVS_GPR_GPR3_RAW    ((reg_t*)0x401A400Cu)

#pragma endregion

// IOMUXC SW MUX Memory Map/Register Definition
// RM 11.6

#pragma region IOMUXC_SW_MUX

// TODO do these require raw access?

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_00       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8014u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_01       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8018u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_02       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F801Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_03       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8020u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8024u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8028u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F802Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8030u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8034u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_09       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8038u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_10       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F803Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_11       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8040u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_12       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8044u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_13       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8048u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_14       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F804Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_15       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8050u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_16       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8054u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_17       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8058u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_18       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F805Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_19       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8060u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_20       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8064u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_21       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8068u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_22       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F806Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_23       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8070u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_24       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8074u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_25       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8078u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_26       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F807Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_27       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8080u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_28       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8084u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_29       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8088u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_30       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F808Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8090u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8094u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_33       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8098u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_34       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F809Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_35       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80A0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80A4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80A8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_38       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80ACu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_39       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80B0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_40       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80B4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_41       ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80B8u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_00     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80BCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_01     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80C0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80C4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80C8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_04     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80CCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_05     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80D0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_06     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80D4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_07     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80D8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_08     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80DCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_09     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80E0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_10     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80E4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_11     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80E8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80ECu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80F0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_14     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80F4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_15     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80F8u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F80FCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8100u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8104u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8108u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F810Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8110u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8114u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8118u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F811Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8120u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8124u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8128u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_12     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F812Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_13     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8130u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8134u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8138u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F813Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8140u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8144u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8148u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_04        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F814Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_05        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8150u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_06        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8154u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_07        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8158u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_08        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F815Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_09        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8160u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8164u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8168u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F816Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_13        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8170u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_14        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8174u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_15        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8178u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F817Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8180u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_02        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8184u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8188u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_04        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F818Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_05        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8190u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_06        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8194u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_07        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8198u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_08        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F819Cu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_09        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81A0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_10        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81A4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_11        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81A8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_12        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81ACu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_13        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81B0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_14        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81B4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_15        ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81B8u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_00     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81BCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81C0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_02     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81C4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_03     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81C8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81CCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81D0u)

#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81D4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81D8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81DCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81E0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81E4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_05     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81E8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_06     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81ECu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_07     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81F0u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_08     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81F4u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_09     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81F8u)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_10     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F81FCu)
#define IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_11     ((IOMUXC_SW_MUX_CTL_PAD_t*)0x401F8200u)

#pragma endregion  // IOMUXC_SW_MUX

// IOMUXC SW PAD Memory Map/Register Definition
// RM 11.6

#pragma region IOMUXC_SW_PAD

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_00       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8204u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_01       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8208u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_02       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F820Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_03       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8210u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8214u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8218u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F821Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8220u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8224u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_09       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8228u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_10       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F822Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_11       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8230u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_12       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8234u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_13       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8238u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_14       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F823Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_15       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8240u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_16       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8244u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_17       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8248u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_18       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F824Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_19       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8250u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_20       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8254u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_21       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8258u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_22       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F825Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_23       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8260u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_24       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8264u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_25       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8268u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_26       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F826Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_27       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8270u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_28       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8274u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_29       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8278u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_30       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F827Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8280u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8284u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_33       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8288u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_34       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F828Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_35       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8290u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8294u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8298u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_38       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F829Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_39       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82A0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_40       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82A4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_41       ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82A8u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_00     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82ACu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_01     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82B0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82B4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82B8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_04     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82BCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_05     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82C0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_06     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82C4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_07     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82C8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_08     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82CCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_09     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82D0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_10     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82D4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_11     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82D8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82DCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82E0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_14     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82E4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_15     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82E8u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82ECu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82F0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82F4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82F8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F82FCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8300u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8304u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8308u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F830Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8310u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8314u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8318u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_12     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F831Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_13     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8320u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8324u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8328u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F832Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8330u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8334u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8338u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_04        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F833Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_05        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8340u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_06        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8344u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_07        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8348u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_08        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F834Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_09        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8350u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8354u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8358u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F835Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_13        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8360u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_14        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8364u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_15        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8368u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F836Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8370u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_02        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8374u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8378u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_04        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F837Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_05        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8380u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_06        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8384u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_07        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8388u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_08        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F838Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_09        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8390u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_10        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8394u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_11        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F8398u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F839Cu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83A0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_14        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83A4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_15        ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83A8u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83ACu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_01     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83B0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_02     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83B4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_03     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83B8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_04     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83BCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_05     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83C0u)

#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_00     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83C4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83C8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_02     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83CCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_03     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83D0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_04     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83D4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83D8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_06     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83DCu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_07     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83E0u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_08     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83E4u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_09     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83E8u)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_10     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83ECu)
#define IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_11     ((IOMUXC_SW_PAD_CTL_PAD_t*)0x401F83F0u)

#pragma endregion  // IOMUXC_SW_PAD

// IOMUXC SELECT_INPUT DAISY Register Definition
// RM 11.6

#pragma region IOMUXC_SELECT_INPUT_DAISY

typedef volatile struct {
	reg_t daisy : 3;
	reg_t		: 29;
} IOMUXC_SELECT_INPUT_DAISY_t;

#define IOMUXC_ANATOP_USB_OTG1_ID_SELECT_INPUT          ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F83F4u)
#define IOMUXC_ANATOP_USB_OTG2_ID_SELECT_INPUT          ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F83F8u)
#define IOMUXC_CCM_PMIC_READY_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F83FCu)
#define IOMUXC_CSI_DATA02_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8400u)
#define IOMUXC_CSI_DATA03_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8404u)
#define IOMUXC_CSI_DATA04_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8408u)
#define IOMUXC_CSI_DATA05_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F840Cu)
#define IOMUXC_CSI_DATA06_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8410u)
#define IOMUXC_CSI_DATA07_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8414u)
#define IOMUXC_CSI_DATA08_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8418u)
#define IOMUXC_CSI_DATA09_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F841Cu)
#define IOMUXC_CSI_HSYNC_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8420u)
#define IOMUXC_CSI_PIXCLK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8424u)
#define IOMUXC_CSI_VSYNC_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8428u)
#define IOMUXC_ENET_IPG_CLK_RMII_SELECT_INPUT           ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F842Cu)
#define IOMUXC_ENET_MDIO_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8430u)
#define IOMUXC_ENET0_RXDATA_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8434u)
#define IOMUXC_ENET1_RXDATA_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8438u)
#define IOMUXC_ENET_RXEN_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F843Cu)
#define IOMUXC_ENET_RXERR_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8440u)
#define IOMUXC_ENET0_TIMER_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8444u)
#define IOMUXC_ENET_TXCLK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8448u)
#define IOMUXC_FLEXCAN1_RX_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F844Cu)
#define IOMUXC_FLEXCAN2_RX_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8450u)
#define IOMUXC_FLEXPWM1_PWMA3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8454u)
#define IOMUXC_FLEXPWM1_PWMA0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8458u)
#define IOMUXC_FLEXPWM1_PWMA1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F845Cu)
#define IOMUXC_FLEXPWM1_PWMA2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8460u)
#define IOMUXC_FLEXPWM1_PWMB3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8464u)
#define IOMUXC_FLEXPWM1_PWMB0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8468u)
#define IOMUXC_FLEXPWM1_PWMB1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F846Cu)
#define IOMUXC_FLEXPWM1_PWMB2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8470u)
#define IOMUXC_FLEXPWM2_PWMA3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8474u)
#define IOMUXC_FLEXPWM2_PWMA0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8478u)
#define IOMUXC_FLEXPWM2_PWMA1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F847Cu)
#define IOMUXC_FLEXPWM2_PWMA2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8480u)
#define IOMUXC_FLEXPWM2_PWMB3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8484u)
#define IOMUXC_FLEXPWM2_PWMB0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8488u)
#define IOMUXC_FLEXPWM2_PWMB1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F848Cu)
#define IOMUXC_FLEXPWM2_PWMB2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8490u)
#define IOMUXC_FLEXPWM4_PWMA0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8494u)
#define IOMUXC_FLEXPWM4_PWMA1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8498u)
#define IOMUXC_FLEXPWM4_PWMA2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F849Cu)
#define IOMUXC_FLEXPWM4_PWMA3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84A0u)
#define IOMUXC_FLEXSPIA_DQS_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84A4u)
#define IOMUXC_FLEXSPIA_DATA0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84A8u)
#define IOMUXC_FLEXSPIA_DATA1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84ACu)
#define IOMUXC_FLEXSPIA_DATA2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84B0u)
#define IOMUXC_FLEXSPIA_DATA3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84B4u)
#define IOMUXC_FLEXSPIB_DATA0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84B8u)
#define IOMUXC_FLEXSPIB_DATA1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84BCu)
#define IOMUXC_FLEXSPIB_DATA2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84C0u)
#define IOMUXC_FLEXSPIB_DATA3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84C4u)
#define IOMUXC_FLEXSPIA_SCK_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84C8u)
#define IOMUXC_LPI2C1_SCL_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84CCu)
#define IOMUXC_LPI2C1_SDA_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84D0u)
#define IOMUXC_LPI2C2_SCL_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84D4u)
#define IOMUXC_LPI2C2_SDA_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84D8u)
#define IOMUXC_LPI2C3_SCL_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84DCu)
#define IOMUXC_LPI2C3_SDA_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84E0u)
#define IOMUXC_LPI2C4_SCL_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84E4u)
#define IOMUXC_LPI2C4_SDA_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84E8u)
#define IOMUXC_LPSPI1_PCS0_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84ECu)
#define IOMUXC_LPSPI1_SCK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84F0u)
#define IOMUXC_LPSPI1_SDI_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84F4u)
#define IOMUXC_LPSPI1_SDO_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84F8u)
#define IOMUXC_LPSPI2_PCS0_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F84FCu)
#define IOMUXC_LPSPI2_SCK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8500u)
#define IOMUXC_LPSPI2_SDI_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8504u)
#define IOMUXC_LPSPI2_SDO_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8508u)
#define IOMUXC_LPSPI3_PCS0_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F850Cu)
#define IOMUXC_LPSPI3_SCK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8510u)
#define IOMUXC_LPSPI3_SDI_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8514u)
#define IOMUXC_LPSPI3_SDO_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8518u)
#define IOMUXC_LPSPI4_PCS0_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F851Cu)
#define IOMUXC_LPSPI4_SCK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8520u)
#define IOMUXC_LPSPI4_SDI_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8524u)
#define IOMUXC_LPSPI4_SDO_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8528u)
#define IOMUXC_LPUART2_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F852Cu)
#define IOMUXC_LPUART2_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8530u)
#define IOMUXC_LPUART3_CTS_B_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8534u)
#define IOMUXC_LPUART3_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8538u)
#define IOMUXC_LPUART3_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F853Cu)
#define IOMUXC_LPUART4_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8540u)
#define IOMUXC_LPUART4_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8544u)
#define IOMUXC_LPUART5_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8548u)
#define IOMUXC_LPUART5_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F854Cu)
#define IOMUXC_LPUART6_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8550u)
#define IOMUXC_LPUART6_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8554u)
#define IOMUXC_LPUART7_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8558u)
#define IOMUXC_LPUART7_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F855Cu)
#define IOMUXC_LPUART8_RX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8560u)
#define IOMUXC_LPUART8_TX_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8564u)
#define IOMUXC_NMI_SELECT_INPUT                         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8568u)
#define IOMUXC_QTIMER2_TIMER0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F856Cu)
#define IOMUXC_QTIMER2_TIMER1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8570u)
#define IOMUXC_QTIMER2_TIMER2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8574u)
#define IOMUXC_QTIMER2_TIMER3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8578u)
#define IOMUXC_QTIMER3_TIMER0_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F857Cu)
#define IOMUXC_QTIMER3_TIMER1_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8580u)
#define IOMUXC_QTIMER3_TIMER2_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8584u)
#define IOMUXC_QTIMER3_TIMER3_SELECT_INPUT              ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8588u)
#define IOMUXC_SAI1_MCLK2_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F858Cu)
#define IOMUXC_SAI1_RX_BCLK_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8590u)
#define IOMUXC_SAI1_RX_DATA0_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8594u)
#define IOMUXC_SAI1_RX_DATA1_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8598u)
#define IOMUXC_SAI1_RX_DATA2_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F859Cu)
#define IOMUXC_SAI1_RX_DATA3_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85A0u)
#define IOMUXC_SAI1_RX_SYNC_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85A4u)
#define IOMUXC_SAI1_TX_BCLK_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85A8u)
#define IOMUXC_SAI1_TX_SYNC_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85ACu)
#define IOMUXC_SAI2_MCLK2_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85B0u)
#define IOMUXC_SAI2_RX_BCLK_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85B4u)
#define IOMUXC_SAI2_RX_DATA0_SELECT_INPUT               ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85B8u)
#define IOMUXC_SAI2_RX_SYNC_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85BCu)
#define IOMUXC_SAI2_TX_BCLK_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85C0u)
#define IOMUXC_SAI2_TX_SYNC_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85C4u)
#define IOMUXC_SPDIF_IN_SELECT_INPUT                    ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85C8u)
#define IOMUXC_USB_OTG2_OC_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85CCu)
#define IOMUXC_USB_OTG1_OC_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85D0u)
#define IOMUXC_USDHC1_CD_B_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85D4u)
#define IOMUXC_USDHC1_WP_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85D8u)
#define IOMUXC_USDHC2_CLK_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85DCu)
#define IOMUXC_USDHC2_CD_B_SELECT_INPUT                 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85E0u)
#define IOMUXC_USDHC2_CMD_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85E4u)
#define IOMUXC_USDHC2_DATA0_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85E8u)
#define IOMUXC_USDHC2_DATA1_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85ECu)
#define IOMUXC_USDHC2_DATA2_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85F0u)
#define IOMUXC_USDHC2_DATA3_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85F4u)
#define IOMUXC_USDHC2_DATA4_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85F8u)
#define IOMUXC_USDHC2_DATA5_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F85FCu)
#define IOMUXC_USDHC2_DATA6_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8600u)
#define IOMUXC_USDHC2_DATA7_SELECT_INPUT                ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8604u)
#define IOMUXC_USDHC2_WP_SELECT_INPUT                   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8608u)
#define IOMUXC_XBAR1_IN02_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F860Cu)
#define IOMUXC_XBAR1_IN03_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8610u)
#define IOMUXC_XBAR1_IN04_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8614u)
#define IOMUXC_XBAR1_IN05_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8618u)
#define IOMUXC_XBAR1_IN06_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F861Cu)
#define IOMUXC_XBAR1_IN07_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8620u)
#define IOMUXC_XBAR1_IN08_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8624u)
#define IOMUXC_XBAR1_IN09_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8628u)
#define IOMUXC_XBAR1_IN17_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F862Cu)
#define IOMUXC_XBAR1_IN18_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8630u)
#define IOMUXC_XBAR1_IN20_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8634u)
#define IOMUXC_XBAR1_IN22_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8638u)
#define IOMUXC_XBAR1_IN23_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F863Cu)
#define IOMUXC_XBAR1_IN24_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8640u)
#define IOMUXC_XBAR1_IN14_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8644u)
#define IOMUXC_XBAR1_IN15_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8648u)
#define IOMUXC_XBAR1_IN16_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F864Cu)
#define IOMUXC_XBAR1_IN25_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8650u)
#define IOMUXC_XBAR1_IN19_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8654u)
#define IOMUXC_XBAR1_IN21_SELECT_INPUT                  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8658u)
#define IOMUXC_ENET2_IPG_CLK_RMII_SELECT_INPUT          ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F870Cu)
#define IOMUXC_ENET2_IPP_IND_MAC0_MDIO_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8710u)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_0 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8714u)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_1 ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8718u)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXEN_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F871Cu)
#define IOMUXC_ENET2_IPP_IND_MAC0_RXERR_SELECT_INPUT    ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8720u)
#define IOMUXC_ENET2_IPP_IND_MAC0_TIMER_SELECT_INPUT_0  ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8724u)
#define IOMUXC_ENET2_IPP_IND_MAC0_TXCLK_SELECT_INPUT    ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8728u)
#define IOMUXC_FLEXSPI2_IPP_IND_DQS_FA_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F872Cu)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT0_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8730u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT1_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8734u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT2_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8738u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT3_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F873Cu)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT0_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8740u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT1_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8744u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT2_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8748u)
#define IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT3_SELECT_INPUT ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F874Cu)
#define IOMUXC_FLEXSPI2_IPP_IND_SCK_FA_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8750u)
#define IOMUXC_FLEXSPI2_IPP_IND_SCK_FB_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8754u)
#define IOMUXC_GPT1_IPP_IND_CAPIN1_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8758u)
#define IOMUXC_GPT1_IPP_IND_CAPIN2_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F875Cu)
#define IOMUXC_GPT1_IPP_IND_CLKIN_SELECT_INPUT          ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8760u)
#define IOMUXC_GPT2_IPP_IND_CAPIN1_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8764u)
#define IOMUXC_GPT2_IPP_IND_CAPIN2_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8768u)
#define IOMUXC_GPT2_IPP_IND_CLKIN_SELECT_INPUT          ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F876Cu)
#define IOMUXC_SAI3_IPG_CLK_SAI_MCLK_SELECT_INPUT_2     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8770u)
#define IOMUXC_SAI3_IPP_IND_SAI_RXBCLK_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8774u)
#define IOMUXC_SAI3_IPP_IND_SAI_RXDATA_SELECT_INPUT_0   ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8778u)
#define IOMUXC_SAI3_IPP_IND_SAI_RXSYNC_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F877Cu)
#define IOMUXC_SAI3_IPP_IND_SAI_TXBCLK_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8780u)
#define IOMUXC_SAI3_IPP_IND_SAI_TXSYNC_SELECT_INPUT     ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8784u)
#define IOMUXC_SEMC_I_IPP_IND_DQS4_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F8788u)
#define IOMUXC_CANFD_IPP_IND_CANRX_SELECT_INPUT         ((IOMUXC_SELECT_INPUT_DAISY_t*)0x401F878Cu)

#pragma endregion  // IOMUXC_SELECT_INPUT_DAISY

// General Purpose Input/Output (GPIO) Register Definition
// RM 12.1

#pragma region GPIO

typedef volatile struct {
	reg_t dr : 32;
} GPIO_DR_t;

typedef volatile struct {
	reg_t gdir : 32;
} GPIO_GDIR_t;

typedef volatile struct {
	reg_t psr : 32;
} GPIO_PSR_t;

typedef volatile struct {
	reg_t icr0	: 2;
	reg_t icr1	: 2;
	reg_t icr2	: 2;
	reg_t icr3	: 2;
	reg_t icr4	: 2;
	reg_t icr5	: 2;
	reg_t icr6	: 2;
	reg_t icr7	: 2;
	reg_t icr8	: 2;
	reg_t icr9	: 2;
	reg_t icr10 : 2;
	reg_t icr11 : 2;
	reg_t icr12 : 2;
	reg_t icr13 : 2;
	reg_t icr14 : 2;
	reg_t icr15 : 2;
} GPIO_ICR1_t;

typedef volatile struct {
	reg_t icr16 : 2;
	reg_t icr17 : 2;
	reg_t icr18 : 2;
	reg_t icr19 : 2;
	reg_t icr20 : 2;
	reg_t icr21 : 2;
	reg_t icr22 : 2;
	reg_t icr23 : 2;
	reg_t icr24 : 2;
	reg_t icr25 : 2;
	reg_t icr26 : 2;
	reg_t icr27 : 2;
	reg_t icr28 : 2;
	reg_t icr29 : 2;
	reg_t icr30 : 2;
	reg_t icr31 : 2;
} GPIO_ICR2_t;

typedef volatile struct {
	reg_t imr : 32;
} GPIO_IMR_t;

typedef volatile struct {
	reg_t isr : 32;
} GPIO_ISR_t;

typedef volatile struct {
	reg_t edge_sel : 32;
} GPIO_EDGE_SEL_t;

typedef volatile struct {
	reg_t dr_set : 32;
} GPIO_DR_SET_t;

typedef volatile struct {
	reg_t dr_clear : 32;
} GPIO_DR_CLEAR_t;

typedef volatile struct {
	reg_t dr_toggle : 32;
} GPIO_DR_TOGGLE_t;

typedef volatile struct {
	/* 0x0  */ GPIO_DR_t		dr;
	/* 0x4  */ GPIO_GDIR_t		gdir;
	/* 0x8  */ GPIO_PSR_t		psr;
	/* 0xC  */ GPIO_ICR1_t		icr1;
	/* 0x10 */ GPIO_ICR2_t		icr2;
	/* 0x14 */ GPIO_IMR_t		imr;
	/* 0x18 */ GPIO_ISR_t		isr;
	/* 0x1C */ GPIO_EDGE_SEL_t	edge_sel;
	/*      */ uint32_t			reserved[25];
	/* 0x84 */ GPIO_DR_SET_t	dr_set;
	/* 0x88 */ GPIO_DR_CLEAR_t	dr_clear;
	/* 0x8C */ GPIO_DR_TOGGLE_t dr_toggle;
} GPIO_t;

#define GPIO1 ((GPIO_t*)0x401B8000u)  // not used, set to gpio 6-9
#define GPIO2 ((GPIO_t*)0x401BC000u)  // not used, set to gpio 6-9
#define GPIO3 ((GPIO_t*)0x401C0000u)  // not used, set to gpio 6-9
#define GPIO4 ((GPIO_t*)0x401C4000u)  // not used, set to gpio 6-9
#define GPIO5 ((GPIO_t*)0x400C0000u)
#define GPIO6 ((GPIO_t*)0x42000000u)
#define GPIO7 ((GPIO_t*)0x42004000u)
#define GPIO8 ((GPIO_t*)0x42008000u)
#define GPIO9 ((GPIO_t*)0x4200C000u)

#pragma endregion  // GPIO

#pragma endregion  // IOMUXC_MODULE

// Clock Controller Module (CCM)
// RM 14

#pragma region CCM_MODULE

// Clock Controller Module (CCM) Memory Map/Register Definition
// RM 14.7

#pragma region CCM

typedef volatile struct {
	reg_t oscnt			   : 8;
	reg_t				   : 4;
	reg_t cosc_en		   : 1;
	reg_t				   : 8;
	reg_t reg_bypass_count : 6;
	reg_t rbc_en		   : 1;
	reg_t				   : 4;
} CCM_CCR_t;
#define CCM_CCR         ((CCM_CCR_t*)0x400FC000u)
#define CCM_CCR_RAW     ((reg_t*)0x400FC000u)

typedef volatile struct {
	reg_t ref_en_b	  : 1;
	reg_t			  : 2;
	reg_t camp2_ready : 1;
	reg_t			  : 1;
	reg_t cosc_ready  : 1;
	reg_t			  : 26;
} CCM_CSR_t;
#define CCM_CSR         ((CCM_CSR_t*)0x400FC008u)
#define CCM_CSR_RAW     ((reg_t*)0x400FC008u)

typedef volatile struct {
	reg_t pll3_sw_clk_sel : 1;
	reg_t				  : 31;
} CCM_CCSR_t;
#define CCM_CCSR        ((CCM_CCSR_t*)0x400FC00Cu)
#define CCM_CCSR_RAW    ((reg_t*)0x400FC00Cu)

typedef volatile struct {
	reg_t arm_podf : 3;
	reg_t		   : 29;
} CCM_CACRR_t;
#define CCM_CACRR       ((CCM_CACRR_t*)0x400FC010u)
#define CCM_CACRR_RAW   ((reg_t*)0x400FC010u)

typedef volatile struct {
	reg_t				   : 6;
	reg_t semc_clk_sel	   : 1;
	reg_t semc_alt_clk_sel : 1;
	reg_t ipg_podf		   : 2;
	reg_t ahb_podf		   : 3;
	reg_t				   : 3;
	reg_t semc_podf		   : 3;
	reg_t				   : 6;
	reg_t periph_clk_sel   : 1;
	reg_t				   : 1;
	reg_t periph_clk2_podf : 3;
	reg_t				   : 2;
} CCM_CBCDR_t;
#define CCM_CBCDR       ((CCM_CBCDR_t*)0x400FC014u)
#define CCM_CBCDR_RAW   ((reg_t*)0x400FC014u)

typedef volatile struct {
	reg_t					 : 4;
	reg_t lpspi_clk_sel		 : 2;
	reg_t					 : 2;
	reg_t flexspi2_clk_sel	 : 2;
	reg_t					 : 2;
	reg_t periph_clk2_sel	 : 2;
	reg_t trace_clk_sel		 : 2;
	reg_t					 : 2;
	reg_t pre_periph_clk_sel : 2;
	reg_t					 : 2;
	reg_t lcdif_podf		 : 3;
	reg_t lpspi_podf		 : 3;
	reg_t flexspi2_podf		 : 3;
} CCM_CBCMR_t;
#define CCM_CBCMR       ((CCM_CBCMR_t*)0x400FC018u)
#define CCM_CBCMR_RAW   ((reg_t*)0x400FC018u)

typedef volatile struct {
	reg_t perclk_podf	  : 6;
	reg_t perclk_clk_sel  : 1;
	reg_t				  : 3;
	reg_t sai1_clk_sel	  : 2;
	reg_t sai2_clk_sel	  : 2;
	reg_t sai3_clk_sel	  : 2;
	reg_t usdhc1_clk_sel  : 1;
	reg_t usdhc2_clk_sel  : 1;
	reg_t				  : 5;
	reg_t flexspi_podf	  : 3;
	reg_t				  : 3;
	reg_t flexspi_clk_sel : 2;
	reg_t				  : 1;
} CCM_CSCMR1_t;
#define CCM_CSCMR1      ((CCM_CSCMR1_t*)0x400FC01Cu)
#define CCM_CSCMR1_RAW  ((reg_t*)0x400FC01Cu)

typedef volatile struct {
	reg_t				  : 2;
	reg_t can_clk_podf	  : 6;
	reg_t can_clk_sel	  : 2;
	reg_t				  : 9;
	reg_t flexio2_clk_sel : 2;
	reg_t				  : 11;
} CCM_CSCMR2_t;
#define CCM_CSCMR2      ((CCM_CSCMR2_t*)0x400FC020u)
#define CCM_CSCMR2_RAW  ((reg_t*)0x400FC020u)

typedef volatile struct {
	reg_t uart_clk_podf : 6;
	reg_t uart_clk_sel	: 2;
	reg_t				: 4;
	reg_t usdhc1_podf	: 3;
	reg_t				: 2;
	reg_t usdhc2_podf	: 3;
	reg_t				: 6;
	reg_t trace_podf	: 16;
	reg_t				: 1;
} CCM_CSCDR1_t;
#define CCM_CSCDR1      ((CCM_CSCDR1_t*)0x400FC024u)
#define CCM_CSCDR1_RAW  ((reg_t*)0x400FC024u)

typedef volatile struct {
	reg_t sai1_clk_podf	   : 6;
	reg_t sai1_clk_pred	   : 3;
	reg_t flexio2_clk_pred : 3;
	reg_t				   : 4;
	reg_t sai3_clk_podf	   : 6;
	reg_t sai3_clk_pred	   : 3;
	reg_t flexio2_clk_podf : 3;
	reg_t				   : 4;
} CCM_CS1CDR_t;
#define CCM_CS1CDR      ((CCM_CS1CDR_t*)0x400FC028u)
#define CCM_CS1CDR_RAW  ((reg_t*)0x400FC028u)

typedef volatile struct {
	reg_t sai2_clk_podf : 6;
	reg_t sai2_clk_pred : 3;
	reg_t				: 23;
} CCM_CS2CDR_t;
#define CCM_CS2CDR      ((CCM_CS2CDR_t*)0x400FC02Cu)
#define CCM_CS2CDR_RAW  ((reg_t*)0x400FC02Cu)

typedef volatile struct {
	reg_t				   : 7;
	reg_t flexio1_clk_sel  : 2;
	reg_t flexio1_clk_podf : 3;
	reg_t flexio1_clk_pred : 3;
	reg_t				   : 5;
	reg_t spdif0_clk_sel   : 2;
	reg_t spdif0_clk_podf  : 3;
	reg_t spdif0_clk_pred  : 3;
	reg_t				   : 4;
} CCM_CDCDR_t;
#define CCM_CDCDR       ((CCM_CDCDR_t*)0x400FC030u)
#define CCM_CDCDR_RAW   ((reg_t*)0x400FC030u)

typedef volatile struct {
	reg_t					: 12;
	reg_t lcdif_pred		: 3;
	reg_t lcdif_pre_clk_sel : 3;
	reg_t lpi2c_clk_sel		: 1;
	reg_t lpi2c_clk_podf	: 6;
	reg_t					: 7;
} CCM_CSCDR2_t;
#define CCM_CSCDR2      ((CCM_CSCDR2_t*)0x400FC038u)
#define CCM_CSCDR2_RAW  ((reg_t*)0x400FC038u)

typedef volatile struct {
	reg_t			  : 9;
	reg_t csi_clk_sel : 2;
	reg_t csi_podf	  : 3;
	reg_t			  : 18;
} CCM_CSCDR3_t;
#define CCM_CSCDR3      ((CCM_CSCDR3_t*)0x400FC03Cu)
#define CCM_CSCDR3_RAW  ((reg_t*)0x400FC03Cu)

typedef volatile struct {
	reg_t semc_podf_busy	   : 1;
	reg_t ahb_podf_busy		   : 1;
	reg_t					   : 1;
	reg_t periph2_clk_sel_busy : 1;
	reg_t					   : 1;
	reg_t periph_clk_sel_busy  : 1;
	reg_t					   : 10;
	reg_t arm_podf_busy		   : 1;
	reg_t					   : 15;
} CCM_CDHIPR_t;
#define CCM_CDHIPR      ((CCM_CDHIPR_t*)0x400FC048u)
#define CCM_CDHIPR_RAW  ((reg_t*)0x400FC048u)

typedef volatile struct {
	reg_t lpm				 : 2;
	reg_t					 : 3;
	reg_t arm_clk_dis_on_lpm : 1;
	reg_t sbyos				 : 1;
	reg_t dis_ref_osc		 : 1;
	reg_t vstby				 : 1;
	reg_t stby_count		 : 2;
	reg_t cosc_pwrdown		 : 1;
	reg_t					 : 7;
	reg_t bypass_lpm_hs1	 : 1;
	reg_t					 : 1;
	reg_t bypass_lpm_hs0	 : 1;
	reg_t mask_core0_wfi	 : 1;
	reg_t					 : 3;
	reg_t mask_scu_idle		 : 1;
	reg_t mask_l2cc_idle	 : 1;
	reg_t					 : 4;
} CCM_CLPCR_t;
#define CCM_CLPCR       ((CCM_CLPCR_t*)0x400FC054u)
#define CCM_CLPCR_RAW   ((reg_t*)0x400FC054u)

typedef volatile struct {
	reg_t lrf_pll				 : 1;
	reg_t						 : 5;
	reg_t cosc_ready			 : 1;
	reg_t						 : 10;
	reg_t semc_podf_loaded		 : 1;
	reg_t						 : 1;
	reg_t periph2_clk_sel_loaded : 1;
	reg_t ahb_podf_loaded		 : 1;
	reg_t						 : 1;
	reg_t periph_clk_sel_loaded	 : 1;
	reg_t						 : 3;
	reg_t arm_podf_loaded		 : 1;
	reg_t						 : 5;
} CCM_CISR_t;
#define CCM_CISR        ((CCM_CISR_t*)0x400FC058u)
#define CCM_CISR_RAW    ((reg_t*)0x400FC058u)

typedef volatile struct {
	reg_t mask_lrf_pll				  : 1;
	reg_t							  : 5;
	reg_t mask_cosc_ready			  : 1;
	reg_t							  : 10;
	reg_t mask_semc_podf_loaded		  : 1;
	reg_t							  : 1;
	reg_t mask_periph2_clk_sel_loaded : 1;
	reg_t mask_ahb_podf_loaded		  : 1;
	reg_t							  : 1;
	reg_t mask_periph_clk_sel_loaded  : 1;
	reg_t							  : 3;
	reg_t arm_podf_loaded			  : 1;
	reg_t							  : 5;
} CCM_CIMR_t;
#define CCM_CIMR        ((CCM_CIMR_t*)0x400FC05Cu)
#define CCM_CIMR_RAW    ((reg_t*)0x400FC05Cu)

typedef volatile struct {
	reg_t clko1_sel : 4;
	reg_t clko1_div : 4;
	reg_t clko1_en	: 1;
	reg_t			: 7;
	reg_t clko2_sel : 5;
	reg_t clko2_div : 3;
	reg_t clko2_en	: 1;
	reg_t			: 7;
} CCM_CCOSR_t;
#define CCM_CCOSR       ((CCM_CCOSR_t*)0x400FC060u)
#define CCM_CCOSR_RAW   ((reg_t*)0x400FC060u)

typedef volatile struct {
	reg_t pmic_delay_scalar		 : 1;
	reg_t						 : 3;
	reg_t efuse_prog_supply_gate : 1;
	reg_t						 : 9;
	reg_t sys_mem_ds_ctrl		 : 2;
	reg_t fpl					 : 1;
	reg_t int_mem_clk_lpm		 : 1;
	reg_t						 : 14;
} CCM_CGPR_t;
#define CCM_CGPR        ((CCM_CGPR_t*)0x400FC064u)
#define CCM_CGPR_RAW    ((reg_t*)0x400FC064u)

// Clock is off during all modes. Stop enter hardware handshake is disabled.
#define CGR_OFF (0x0u)
// Clock is on during run mode, but off in WAIT and STOP modes.
#define CGR_RUN (0x1u)
// 0x2 is reserved.
// Clock is on during all modes, except STOP mode.
#define CGR_ON  (0x3u)

// Clock Gating Register (CCGR) Bit Masks
#define CCM_CGn(n)  (0x3 << (n * 2))

typedef volatile struct {
	reg_t aips_tz1_clk_enable	 : 2;
	reg_t aips_tz2_clk_enable	 : 2;
	reg_t mqs_hmclk_clock_enable : 2;
	reg_t						 : 2;
	reg_t sim_m_mainclk_r_enable : 2;
	reg_t dcp_clk_enable		 : 2;
	reg_t lpuart3_clk_enable	 : 2;
	reg_t can1_clk_enable		 : 2;
	reg_t can1_serial_clk_enable : 2;
	reg_t can2_clk_enable		 : 2;
	reg_t can2_serial_clk_enable : 2;
	reg_t trace_clk_enable		 : 2;
	reg_t gpt2_bus_clk_enable	 : 2;
	reg_t gpt2_serial_clk_enable : 2;
	reg_t lpuart2_clk_enable	 : 2;
	reg_t gpio2_clk_enable		 : 2;
} CCM_CCGR0_t;
#define CCM_CCGR0       ((CCM_CCGR0_t*)0x400FC068u)
#define CCM_CCGR0_RAW   ((reg_t*)0x400FC068u)

typedef volatile struct {
	reg_t lpspi1_clk_enable		: 2;
	reg_t lpspi2_clk_enable		: 2;
	reg_t lpspi3_clk_enable		: 2;
	reg_t lpspi4_clk_enable		: 2;
	reg_t adc2_clk_enable		: 2;
	reg_t enet_clk_enable		: 2;
	reg_t pit_clk_enable		: 2;
	reg_t aoi2_clk_enable		: 2;
	reg_t adc1_clk_enable		: 2;
	reg_t semc_exsc_clk_enable	: 2;
	reg_t gpt_clk_enable		: 2;
	reg_t gpt_serial_clk_enable : 2;
	reg_t lpuart4_clk_enable	: 2;
	reg_t gpio1_clk_enable		: 2;
	reg_t csu_clk_enable		: 2;
	reg_t gpio5_clk_enable		: 2;
} CCM_CCGR1_t;
#define CCM_CCGR1       ((CCM_CCGR1_t*)0x400FC06Cu)
#define CCM_CCGR1_RAW   ((reg_t*)0x400FC06Cu)

typedef volatile struct {
	reg_t ocram_exsc_clk_enable	 : 2;
	reg_t csi_clk_enable		 : 2;
	reg_t iomuxc_snvs_clk_enable : 2;
	reg_t lpi2c1_clk_enable		 : 2;
	reg_t lpi2c2_clk_enable		 : 2;
	reg_t lpi2c3_clk_enable		 : 2;
	reg_t ocotp_clk_enable		 : 2;
	reg_t xbar3_clk_enable		 : 2;
	reg_t ipmux1_clk_enable		 : 2;
	reg_t ipmux2_clk_enable		 : 2;
	reg_t ipmux3_clk_enable		 : 2;
	reg_t xbar1_clk_enable		 : 2;
	reg_t xbar2_clk_enable		 : 2;
	reg_t gpio3_clk_enable		 : 2;
	reg_t lcd_clk_enable		 : 2;
	reg_t pxp_clk_enable		 : 2;
} CCM_CCGR2_t;
#define CCM_CCGR2       ((CCM_CCGR2_t*)0x400FC070u)
#define CCM_CCGR2_RAW   ((reg_t*)0x400FC070u)

typedef volatile struct {
	reg_t flexio2_clk_enable		 : 2;
	reg_t lpuart5_clk_enable		 : 2;
	reg_t semc_clk_enable			 : 2;
	reg_t lpuart6_clk_enable		 : 2;
	reg_t aoi1_clk_enable			 : 2;
	reg_t lcdif_pix_clk_enable		 : 2;
	reg_t gpio4_clk_enable			 : 2;
	reg_t ewm_clk_enable			 : 2;
	reg_t wdog1_clk_enable			 : 2;
	reg_t flexram_clk_enable		 : 2;
	reg_t acmp1_clk_enable			 : 2;
	reg_t acmp2_clk_enable			 : 2;
	reg_t acmp3_clk_enable			 : 2;
	reg_t acmp4_clk_enable			 : 2;
	reg_t ocram_clk_enable			 : 2;
	reg_t iomuxc_snvs_gpr_clk_enable : 2;
} CCM_CCGR3_t;
#define CCM_CCGR3       ((CCM_CCGR3_t*)0x400FC074u)
#define CCM_CCGR3_RAW   ((reg_t*)0x400FC074u)

typedef volatile struct {
	reg_t sim_m7_mainclk_r_enable : 2;
	reg_t iomuxc_clk_enable		  : 2;
	reg_t iomuxc_gpr_clk_enable	  : 2;
	reg_t bee_clk_enable		  : 2;
	reg_t sim_m7_clk_enable		  : 2;
	reg_t tsc_clk_enable		  : 2;
	reg_t sim_m_clk_enable		  : 2;
	reg_t sim_ems_clk_enable	  : 2;
	reg_t pwm1_clk_enable		  : 2;
	reg_t pwm2_clk_enable		  : 2;
	reg_t pwm3_clk_enable		  : 2;
	reg_t pwm4_clk_enable		  : 2;
	reg_t qdc1_clk_enable		  : 2;
	reg_t qdc2_clk_enable		  : 2;
	reg_t qdc3_clk_enable		  : 2;
	reg_t qdc4_clk_enable		  : 2;
} CCM_CCGR4_t;
#define CCM_CCGR4       ((CCM_CCGR4_t*)0x400FC078u)
#define CCM_CCGR4_RAW   ((reg_t*)0x400FC078u)

typedef volatile struct {
	reg_t rom_clk_enable	  : 2;
	reg_t flexio1_clk_enable  : 2;
	reg_t wdog3_clk_enable	  : 2;
	reg_t dma_clk_enable	  : 2;
	reg_t kpp_clk_enable	  : 2;
	reg_t wdog2_clk_enable	  : 2;
	reg_t aips_tz4_clk_enable : 2;
	reg_t spdif_clk_enable	  : 2;
	reg_t sim_main_clk_enable : 2;
	reg_t sai1_clk_enable	  : 2;
	reg_t sai2_clk_enable	  : 2;
	reg_t sai3_clk_enable	  : 2;
	reg_t lpuart1_clk_enable  : 2;
	reg_t lpuart7_clk_enable  : 2;
	reg_t snvs_hp_clk_enable  : 2;
	reg_t snvs_lp_clk_enable  : 2;
} CCM_CCGR5_t;
#define CCM_CCGR5       ((CCM_CCGR5_t*)0x400FC07Cu)
#define CCM_CCGR5_RAW   ((reg_t*)0x400FC07Cu)

typedef volatile struct {
	reg_t usboh3_clk_enable	  : 2;
	reg_t usdhc1_clk_enable	  : 2;
	reg_t usdhc2_clk_enable	  : 2;
	reg_t dcdc_clk_enable	  : 2;
	reg_t ipmux4_clk_enable	  : 2;
	reg_t flexspi_clk_enable  : 2;
	reg_t trng_clk_enable	  : 2;
	reg_t lpuart8_clk_enable  : 2;
	reg_t timer4_clk_enable	  : 2;
	reg_t aips_tz3_clk_enable : 2;
	reg_t sim_per_clk_enable  : 2;
	reg_t anadig_clk_enable	  : 2;
	reg_t lpi2c4_clk_enable	  : 2;
	reg_t timer1_clk_enable	  : 2;
	reg_t timer2_clk_enable	  : 2;
	reg_t timer3_clk_enable	  : 2;
} CCM_CCGR6_t;
#define CCM_CCGR6       ((CCM_CCGR6_t*)0x400FC080u)
#define CCM_CCGR6_RAW   ((reg_t*)0x400FC080u)

typedef volatile struct {
	reg_t enet2_clk_enable		 : 2;
	reg_t flexspi2_clk_enable	 : 2;
	reg_t axbs_l_clk_enable		 : 2;
	reg_t can3_clk_enable		 : 2;
	reg_t can3_serial_clk_enable : 2;
	reg_t apis_lite_clk_enable	 : 2;
	reg_t flexio3_clk_enable	 : 2;
	reg_t						 : 18;
} CCM_CCGR7_t;
#define CCM_CCGR7       ((CCM_CCGR7_t*)0x400FC084u)
#define CCM_CCGR7_RAW   ((reg_t*)0x400FC084u)

typedef volatile struct {
	reg_t					  : 5;
	reg_t mod_en_ov_gpt		  : 1;
	reg_t mod_em_ov_pit		  : 1;
	reg_t mod_en_usdhc		  : 1;
	reg_t					  : 1;
	reg_t mod_en_ov_trng	  : 1;
	reg_t mod_en_ov_canfd_cpi : 1;
	reg_t					  : 17;
	reg_t mod_en_ov_can2_cpi  : 1;
	reg_t					  : 1;
	reg_t mod_en_ov_can1_cpi  : 1;
	reg_t					  : 1;
} CCM_CMEOR_t;
#define CCM_CMEOR       ((CCM_CMEOR_t*)0x400FC088u)
#define CCM_CMEOR_RAW   ((reg_t*)0x400FC088u)

#pragma endregion  // CCM

// CCM Analog Memory Map/Register Definition
// RM 14.8

#pragma region CCM_ANALOG

typedef volatile struct {
	reg_t div_select	 : 7;
	reg_t				 : 5;
	reg_t powerdown		 : 1;
	reg_t enable		 : 1;
	reg_t bypass_clk_src : 2;
	reg_t bypass		 : 1;
	reg_t				 : 2;
	reg_t pll_sel		 : 1;
	reg_t				 : 11;
	reg_t lock			 : 1;
} CCM_ANALOG_PLL_ARM_t;
#define CCM_ANALOG_PLL_ARM          ((CCM_ANALOG_PLL_ARM_t*)0x400D8000u)
#define CCM_ANALOG_PLL_ARM_SET      ((CCM_ANALOG_PLL_ARM_t*)0x400D8004u)
#define CCM_ANALOG_PLL_ARM_CLR      ((CCM_ANALOG_PLL_ARM_t*)0x400D8008u)
#define CCM_ANALOG_PLL_ARM_TOG      ((CCM_ANALOG_PLL_ARM_t*)0x400D800Cu)
#define CCM_ANALOG_PLL_ARM_RAW      ((reg_t*)0x400D8000u)

typedef volatile struct {
	reg_t				 : 1;
	reg_t div_select	 : 1;
	reg_t				 : 4;
	reg_t en_usb_clks	 : 1;
	reg_t				 : 5;
	reg_t power			 : 1;
	reg_t enable		 : 1;
	reg_t bypass_clk_src : 2;
	reg_t bypass		 : 1;
	reg_t				 : 14;
	reg_t lock			 : 1;
} CCM_ANALOG_PLL_USB1_t;
#define CCM_ANALOG_PLL_USB1         ((CCM_ANALOG_PLL_USB1_t*)0x400D8010u)
#define CCM_ANALOG_PLL_USB1_SET     ((CCM_ANALOG_PLL_USB1_t*)0x400D8014u)
#define CCM_ANALOG_PLL_USB1_CLR     ((CCM_ANALOG_PLL_USB1_t*)0x400D8018u)
#define CCM_ANALOG_PLL_USB1_TOG     ((CCM_ANALOG_PLL_USB1_t*)0x400D801Cu)
#define CCM_ANALOG_PLL_USB1_RAW     ((reg_t*)0x400D8010u)

typedef volatile struct {
	reg_t				 : 1;
	reg_t div_select	 : 1;
	reg_t				 : 4;
	reg_t en_usb_clks	 : 1;
	reg_t				 : 5;
	reg_t power			 : 1;
	reg_t enable		 : 1;
	reg_t bypass_clk_src : 2;
	reg_t bypass		 : 1;
	reg_t				 : 14;
	reg_t lock			 : 1;
} CCM_ANALOG_PLL_USB2_t;
#define CCM_ANALOG_PLL_USB2         ((CCM_ANALOG_PLL_USB2_t*)0x400D8020u)
#define CCM_ANALOG_PLL_USB2_SET     ((CCM_ANALOG_PLL_USB2_t*)0x400D8024u)
#define CCM_ANALOG_PLL_USB2_CLR     ((CCM_ANALOG_PLL_USB2_t*)0x400D8028u)
#define CCM_ANALOG_PLL_USB2_TOG     ((CCM_ANALOG_PLL_USB2_t*)0x400D802Cu)
#define CCM_ANALOG_PLL_USB2_RAW     ((reg_t*)0x400D8020u)

typedef volatile struct {
	reg_t div_select	 : 1;
	reg_t				 : 11;
	reg_t powerdown		 : 1;
	reg_t enable		 : 1;
	reg_t bypass_clk_src : 2;
	reg_t bypass		 : 1;
	reg_t				 : 14;
	reg_t lock			 : 1;
} CCM_ANALOG_PLL_SYS_t;
#define CCM_ANALOG_PLL_SYS          ((CCM_ANALOG_PLL_SYS_t*)0x400D8030u)
#define CCM_ANALOG_PLL_SYS_SET      ((CCM_ANALOG_PLL_SYS_t*)0x400D8034u)
#define CCM_ANALOG_PLL_SYS_CLR      ((CCM_ANALOG_PLL_SYS_t*)0x400D8038u)
#define CCM_ANALOG_PLL_SYS_TOG      ((CCM_ANALOG_PLL_SYS_t*)0x400D803Cu)
#define CCM_ANALOG_PLL_SYS_RAW      ((reg_t*)0x400D8030u)

typedef volatile struct {
	reg_t step	 : 15;
	reg_t enable : 1;
	reg_t stop	 : 16;
} CCM_ANALOG_PLL_SYS_SS_t;
#define CCM_ANALOG_PLL_SYS_SS       ((CCM_ANALOG_PLL_SYS_SS_t*)0x400D8040u)
#define CCM_ANALOG_PLL_SYS_SS_RAW   ((reg_t*)0x400D8040u)

typedef volatile struct {
	reg_t numerator : 30;  // signed
	reg_t			: 2;
} CCM_ANALOG_PLL_SYS_NUM_t;
#define CCM_ANALOG_PLL_SYS_NUM      ((CCM_ANALOG_PLL_SYS_NUM_t*)0x400D8050u)
#define CCM_ANALOG_PLL_SYS_NUM_RAW  ((reg_t*)0x400D8050u)

typedef volatile struct {
	reg_t denominator : 30;	 // signed
	reg_t			  : 2;
} CCM_ANALOG_PLL_SYS_DENOM_t;
#define CCM_ANALOG_PLL_SYS_DENOM    ((CCM_ANALOG_PLL_SYS_DENOM_t*)0x400D8060u)
#define CCM_ANALOG_PLL_SYS_DENOM_RAW ((reg_t*)0x400D8060u)

typedef volatile struct {
	reg_t div_select	  : 7;
	reg_t				  : 5;
	reg_t powerdown		  : 1;
	reg_t enable		  : 1;
	reg_t bypass_clk_src  : 2;
	reg_t bypass		  : 1;
	reg_t				  : 2;
	reg_t post_div_select : 2;
	reg_t				  : 10;
	reg_t lock			  : 1;
} CCM_ANALOG_PLL_AUDIO_t;
#define CCM_ANALOG_PLL_AUDIO        ((CCM_ANALOG_PLL_AUDIO_t*)0x400D8070u)
#define CCM_ANALOG_PLL_AUDIO_SET    ((CCM_ANALOG_PLL_AUDIO_t*)0x400D8074u)
#define CCM_ANALOG_PLL_AUDIO_CLR    ((CCM_ANALOG_PLL_AUDIO_t*)0x400D8078u)
#define CCM_ANALOG_PLL_AUDIO_TOG    ((CCM_ANALOG_PLL_AUDIO_t*)0x400D807Cu)
#define CCM_ANALOG_PLL_AUDIO_RAW    ((reg_t*)0x400D8070u)

typedef volatile struct {
	reg_t numerator : 30;  // signed
	reg_t			: 2;
} CCM_ANALOG_PLL_AUDIO_NUM_t;
#define CCM_ANALOG_PLL_AUDIO_NUM    ((CCM_ANALOG_PLL_AUDIO_NUM_t*)0x400D8080u)
#define CCM_ANALOG_PLL_AUDIO_NUM_RAW ((reg_t*)0x400D8080u)

typedef volatile struct {
	reg_t denominator : 30;	 // signed
	reg_t			  : 2;
} CCM_ANALOG_PLL_AUDIO_DENOM_t;
#define CCM_ANALOG_PLL_AUDIO_DENOM  ((CCM_ANALOG_PLL_AUDIO_DENOM_t*)0x400D8090u)
#define CCM_ANALOG_PLL_AUDIO_DENOM_RAW ((reg_t*)0x400D8090u)

typedef volatile struct {
	reg_t div_select	  : 7;
	reg_t				  : 5;
	reg_t powerdown		  : 1;
	reg_t enable		  : 1;
	reg_t bypass_clk_src  : 2;
	reg_t bypass		  : 1;
	reg_t				  : 2;
	reg_t post_div_select : 2;
	reg_t				  : 10;
	reg_t lock			  : 1;
} CCM_ANALOG_PLL_VIDEO_t;
#define CCM_ANALOG_PLL_VIDEO        ((CCM_ANALOG_PLL_VIDEO_t*)0x400D80A0u)
#define CCM_ANALOG_PLL_VIDEO_SET    ((CCM_ANALOG_PLL_VIDEO_t*)0x400D80A4u)
#define CCM_ANALOG_PLL_VIDEO_CLR    ((CCM_ANALOG_PLL_VIDEO_t*)0x400D80A8u)
#define CCM_ANALOG_PLL_VIDEO_TOG    ((CCM_ANALOG_PLL_VIDEO_t*)0x400D80ACu)
#define CCM_ANALOG_PLL_VIDEO_RAW    ((reg_t*)0x400D80A0u)

typedef volatile struct {
	reg_t numerator : 30;  // signed
	reg_t			: 2;
} CCM_ANALOG_PLL_VIDEO_NUM_t;
#define CCM_ANALOG_PLL_VIDEO_NUM    ((CCM_ANALOG_PLL_VIDEO_NUM_t*)0x400D80B0u)
#define CCM_ANALOG_PLL_VIDEO_NUM_RAW ((reg_t*)0x400D80B0u)

typedef volatile struct {
	reg_t denominator : 30;	 // signed
	reg_t			  : 2;
} CCM_ANALOG_PLL_VIDEO_DENOM_t;
#define CCM_ANALOG_PLL_VIDEO_DENOM  ((CCM_ANALOG_PLL_VIDEO_DENOM_t*)0x400D80C0u)
#define CCM_ANALOG_PLL_VIDEO_DENOM_RAW ((reg_t*)0x400D80C0u)

typedef volatile struct {
	reg_t div_select	   : 2;
	reg_t enet2_div_select : 2;
	reg_t				   : 8;
	reg_t powerdown		   : 1;
	reg_t enable		   : 1;
	reg_t bypass_clk_src   : 2;
	reg_t bypass		   : 1;
	reg_t				   : 3;
	reg_t enet2_ref_en	   : 1;
	reg_t enet_25m_ref_en  : 1;
	reg_t				   : 9;
	reg_t lock			   : 1;
} CCM_ANALOG_PLL_ENET_t;
#define CCM_ANALOG_PLL_ENET         ((CCM_ANALOG_PLL_ENET_t*)0x400D80E0u)
#define CCM_ANALOG_PLL_ENET_SET     ((CCM_ANALOG_PLL_ENET_t*)0x400D80E4u)
#define CCM_ANALOG_PLL_ENET_CLR     ((CCM_ANALOG_PLL_ENET_t*)0x400D80E8u)
#define CCM_ANALOG_PLL_ENET_TOG     ((CCM_ANALOG_PLL_ENET_t*)0x400D80ECu)
#define CCM_ANALOG_PLL_ENET_RAW     ((reg_t*)0x400D80E0u)

typedef volatile struct {
	reg_t pfd0_frac	   : 6;
	reg_t pfd0_stable  : 1;
	reg_t pfd0_clkgate : 1;
	reg_t pfd1_frac	   : 6;
	reg_t pfd1_stable  : 1;
	reg_t pfd1_clkgate : 1;
	reg_t pfd2_frac	   : 6;
	reg_t pfd2_stable  : 1;
	reg_t pfd2_clkgate : 1;
	reg_t pfd3_frac	   : 6;
	reg_t pfd3_stable  : 1;
	reg_t pfd3_clkgate : 1;
} CCM_ANALOG_PFD_480_t;
#define CCM_ANALOG_PFD_480          ((CCM_ANALOG_PFD_480_t*)0x400D80F0u)
#define CCM_ANALOG_PFD_480_SET      ((CCM_ANALOG_PFD_480_t*)0x400D80F4u)
#define CCM_ANALOG_PFD_480_CLR      ((CCM_ANALOG_PFD_480_t*)0x400D80F8u)
#define CCM_ANALOG_PFD_480_TOG      ((CCM_ANALOG_PFD_480_t*)0x400D80FCu)
#define CCM_ANALOG_PFD_480_RAW      ((reg_t*)0x400D80F0u)

typedef volatile struct {
	reg_t pfd0_frac	   : 6;
	reg_t pfd0_stable  : 1;
	reg_t pfd0_clkgate : 1;
	reg_t pfd1_frac	   : 6;
	reg_t pfd1_stable  : 1;
	reg_t pfd1_clkgate : 1;
	reg_t pfd2_frac	   : 6;
	reg_t pfd2_stable  : 1;
	reg_t pfd2_clkgate : 1;
	reg_t pfd3_frac	   : 6;
	reg_t pfd3_stable  : 1;
	reg_t pfd3_clkgate : 1;
} CCM_ANALOG_PFD_528_t;
#define CCM_ANALOG_PFD_528          ((CCM_ANALOG_PFD_528_t*)0x400D8100u)
#define CCM_ANALOG_PFD_528_SET      ((CCM_ANALOG_PFD_528_t*)0x400D8104u)
#define CCM_ANALOG_PFD_528_CLR      ((CCM_ANALOG_PFD_528_t*)0x400D8108u)
#define CCM_ANALOG_PFD_528_TOG      ((CCM_ANALOG_PFD_528_t*)0x400D810Cu)
#define CCM_ANALOG_PFD_528_RAW      ((reg_t*)0x400D8100u)

typedef volatile struct {
	reg_t reftop_pwd		 : 1;
	reg_t					 : 2;
	reg_t reftop_selfbiasoff : 1;
	reg_t reftop_vbgadj		 : 3;
	reg_t reftop_vbgup		 : 1;
	reg_t					 : 2;
	reg_t stop_mod_config	 : 2;
	reg_t discon_high_snvs	 : 1;
	reg_t osc_i				 : 2;
	reg_t osc_xtalok		 : 1;
	reg_t osc_xtalox_en		 : 1;
	reg_t					 : 8;
	reg_t clkgate_ctrl		 : 1;
	reg_t clkgate_delay		 : 3;
	reg_t rtc_xtal_source	 : 1;
	reg_t xtal_24m_pwd		 : 1;
	reg_t					 : 1;
} CCM_ANALOG_MISC0_t;
#define CCM_ANALOG_MISC0            ((CCM_ANALOG_MISC0_t*)0x400D8150u)
#define CCM_ANALOG_MISC0_SET        ((CCM_ANALOG_MISC0_t*)0x400D8154u)
#define CCM_ANALOG_MISC0_CLR        ((CCM_ANALOG_MISC0_t*)0x400D8158u)
#define CCM_ANALOG_MISC0_TOG        ((CCM_ANALOG_MISC0_t*)0x400D815Cu)
#define CCM_ANALOG_MISC0_RAW        ((reg_t*)0x400D8150u)

typedef volatile struct {
	reg_t lvds1_clk_sel		  : 5;
	reg_t					  : 5;
	reg_t lvdsclk1_oben		  : 1;
	reg_t					  : 1;
	reg_t lvdsclk1_iben		  : 1;
	reg_t					  : 3;
	reg_t pfd_480_autogate_en : 1;
	reg_t pfd_528_autogate_en : 1;
	reg_t					  : 9;
	reg_t irq_temppanic		  : 1;
	reg_t irq_templow		  : 1;
	reg_t irq_temphigh		  : 1;
	reg_t irq_ana_bo		  : 1;
	reg_t irq_dig_bo		  : 1;
} CCM_ANALOG_MISC1_t;
#define CCM_ANALOG_MISC1            ((CCM_ANALOG_MISC1_t*)0x400D8160u)
#define CCM_ANALOG_MISC1_SET        ((CCM_ANALOG_MISC1_t*)0x400D8164u)
#define CCM_ANALOG_MISC1_CLR        ((CCM_ANALOG_MISC1_t*)0x400D8168u)
#define CCM_ANALOG_MISC1_TOG        ((CCM_ANALOG_MISC1_t*)0x400D816Cu)
#define CCM_ANALOG_MISC1_RAW        ((reg_t*)0x400D8160u)

typedef volatile struct {
	reg_t reg0_bo_offset : 3;
	reg_t reg0_bo_status : 1;
	reg_t				 : 1;
	reg_t reg0_enable_bo : 1;
	reg_t reg0_ok		 : 1;
	reg_t pll3_disable	 : 1;
	reg_t reg1_bo_offset : 3;
	reg_t reg1_bo_status : 1;
	reg_t				 : 1;
	reg_t reg1_enable_bo : 1;
	reg_t reg1_ok		 : 1;
	reg_t audio_div_lsb	 : 1;
	reg_t reg2_bo_offset : 3;
	reg_t reg2_bo_status : 1;
	reg_t				 : 1;
	reg_t reg2_enable_bo : 1;
	reg_t reg2_ok		 : 1;
	reg_t audio_div_msb	 : 1;
	reg_t reg0_step_time : 2;
	reg_t reg1_step_time : 2;
	reg_t reg2_step_time : 2;
	reg_t video_div		 : 2;
} CCM_ANALOG_MISC2_t;
#define CCM_ANALOG_MISC2            ((CCM_ANALOG_MISC2_t*)0x400D8170u)
#define CCM_ANALOG_MISC2_SET        ((CCM_ANALOG_MISC2_t*)0x400D8174u)
#define CCM_ANALOG_MISC2_CLR        ((CCM_ANALOG_MISC2_t*)0x400D8178u)
#define CCM_ANALOG_MISC2_TOG        ((CCM_ANALOG_MISC2_t*)0x400D817Cu)
#define CCM_ANALOG_MISC2_RAW        ((reg_t*)0x400D8170u)

#pragma endregion  // CCM_ANALOG

#pragma endregion  // CCM_MODULE

// Power Management Unit (PMU) Module
// RM 16

#pragma region PMU_MODULE

typedef volatile struct {
	reg_t enable_linreg		 : 1;
	reg_t enable_bo			 : 1;
	reg_t enable_ilimit		 : 1;
	reg_t enable_pulldown	 : 1;
	reg_t bo_offset			 : 3;
	reg_t					 : 1;
	reg_t output_trg		 : 5;
	reg_t					 : 3;
	reg_t bo_vdd1p1			 : 1;
	reg_t ok_vdd1p1			 : 1;
	reg_t enable_weak_linreg : 1;
	reg_t selref_weak_linreg : 1;
	reg_t					 : 12;
} PMU_REG_1P1_t;
#define PMU_REG_1P1         ((PMU_REG_1P1_t*)0x400D8110u)
#define PMU_REG_1P1_SET     ((PMU_REG_1P1_t*)0x400D8114u)
#define PMU_REG_1P1_CLR     ((PMU_REG_1P1_t*)0x400D8118u)
#define PMU_REG_1P1_TOG     ((PMU_REG_1P1_t*)0x400D811Cu)
#define PMU_REG_1P1_RAW     ((reg_t*)0x400D8110u)

typedef volatile struct {
	reg_t enable_linreg : 1;
	reg_t enable_bo		: 1;
	reg_t enable_ilimit : 1;
	reg_t				: 1;
	reg_t bo_offset		: 3;
	reg_t vbus_sel		: 1;
	reg_t output_trg	: 5;
	reg_t				: 3;
	reg_t bo_vdd3p0		: 1;
	reg_t ok_vdd3p0		: 1;
	reg_t				: 14;
} PMU_REG_3P0_t;
#define PMU_REG_3P0         ((PMU_REG_3P0_t*)0x400D8120u)
#define PMU_REG_3P0_SET     ((PMU_REG_3P0_t*)0x400D8124u)
#define PMU_REG_3P0_CLR     ((PMU_REG_3P0_t*)0x400D8128u)
#define PMU_REG_3P0_TOG     ((PMU_REG_3P0_t*)0x400D812Cu)
#define PMU_REG_3P0_RAW     ((reg_t*)0x400D8120u)

typedef volatile struct {
	reg_t enable_linreg		 : 1;
	reg_t enable_bo			 : 1;
	reg_t enable_ilimit		 : 1;
	reg_t enable_pulldown	 : 1;
	reg_t bo_offset			 : 3;
	reg_t					 : 1;
	reg_t output_trg		 : 5;
	reg_t					 : 3;
	reg_t bo_vdd2p5			 : 1;
	reg_t ok_vdd2p5			 : 1;
	reg_t enable_weak_linreg : 1;
	reg_t					 : 13;
} PMU_REG_2P5_t;
#define PMU_REG_2P5         ((PMU_REG_2P5_t*)0x400D8130u)
#define PMU_REG_2P5_SET     ((PMU_REG_2P5_t*)0x400D8134u)
#define PMU_REG_2P5_CLR     ((PMU_REG_2P5_t*)0x400D8138u)
#define PMU_REG_2P5_TOG     ((PMU_REG_2P5_t*)0x400D813Cu)
#define PMU_REG_2P5_RAW     ((reg_t*)0x400D8130u)

typedef volatile struct {
	reg_t reg0_targ	 : 5;
	reg_t reg0_adj	 : 4;
	reg_t reg1_targ	 : 5;
	reg_t reg1_adj	 : 4;
	reg_t reg2_targ	 : 5;
	reg_t reg2_adj	 : 4;
	reg_t ramp_rate	 : 2;
	reg_t fet_odrive : 1;
	reg_t			 : 2;
} PMU_REG_CORE_t;
#define PMU_REG_CORE        ((PMU_REG_CORE_t*)0x400D8140u)
#define PMU_REG_CORE_SET    ((PMU_REG_CORE_t*)0x400D8144u)
#define PMU_REG_CORE_CLR    ((PMU_REG_CORE_t*)0x400D8148u)
#define PMU_REG_CORE_TOG    ((PMU_REG_CORE_t*)0x400D814Cu)
#define PMU_REG_CORE_RAW    ((reg_t*)0x400D8140u)

typedef volatile struct {
	reg_t reftop_pwd		 : 1;
	reg_t reftop_pwdvbgup	 : 1;
	reg_t reftop_lowpower	 : 1;
	reg_t reftop_selfbiasoff : 1;
	reg_t reftop_vbgadj		 : 3;
	reg_t reftop_vbgup		 : 1;
	reg_t					 : 2;
	reg_t stop_mode_config	 : 2;
	reg_t discon_high_snvs	 : 1;
	reg_t osc_i				 : 2;
	reg_t osc_xtalok		 : 1;
	reg_t osc_xtalok_en		 : 1;
	reg_t					 : 8;
	reg_t clkgate_ctrl		 : 1;
	reg_t clkgate_delay		 : 3;
	reg_t rtc_xtal_source	 : 1;
	reg_t xtal_24m_pwd		 : 1;
	reg_t vid_pll_prediv	 : 1;
} PMU_MISC0_t;
#define PMU_MISC0           ((PMU_MISC0_t*)0x400D8150u)
#define PMU_MISC0_SET       ((PMU_MISC0_t*)0x400D8154u)
#define PMU_MISC0_CLR       ((PMU_MISC0_t*)0x400D8158u)
#define PMU_MISC0_TOG       ((PMU_MISC0_t*)0x400D815Cu)
#define PMU_MISC0_RAW       ((reg_t*)0x400D8150u)

typedef volatile struct {
	reg_t lvds1_clk_sel		  : 5;
	reg_t lvds2_clk_sel		  : 5;
	reg_t lvdsclk1_oben		  : 1;
	reg_t lvdsclk2_oben		  : 1;
	reg_t lvdsclk1_iben		  : 1;
	reg_t lvdsclk2_iben		  : 1;
	reg_t					  : 2;
	reg_t pfd_480_autogate_en : 1;
	reg_t pfd_528_autogate_en : 1;
	reg_t					  : 9;
	reg_t irq_temppanic		  : 1;
	reg_t irq_templow		  : 1;
	reg_t irq_temphigh		  : 1;
	reg_t irq_ana_bo		  : 1;
	reg_t irq_dig_bo		  : 1;
} PMU_MISC1_t;
#define PMU_MISC1           ((PMU_MISC1_t*)0x400D8160u)
#define PMU_MISC1_SET       ((PMU_MISC1_t*)0x400D8164u)
#define PMU_MISC1_CLR       ((PMU_MISC1_t*)0x400D8168u)
#define PMU_MISC1_TOG       ((PMU_MISC1_t*)0x400D816Cu)
#define PMU_MISC1_RAW       ((reg_t*)0x400D8160u)

typedef volatile struct {
	reg_t reg0_bo_offset : 3;
	reg_t reg0_bo_status : 1;
	reg_t				 : 1;
	reg_t reg0_enable_bo : 1;
	reg_t				 : 1;
	reg_t pll3_disable	 : 1;
	reg_t reg1_bo_offset : 3;
	reg_t reg1_bo_status : 1;
	reg_t				 : 1;
	reg_t reg1_enable_bo : 1;
	reg_t				 : 1;
	reg_t audio_div_lsb	 : 1;
	reg_t reg2_bo_offset : 3;
	reg_t reg2_bo_status : 1;
	reg_t				 : 1;
	reg_t reg2_enable_bo : 1;
	reg_t reg2_ok		 : 1;
	reg_t audio_div_msb	 : 1;
	reg_t reg0_step_time : 2;
	reg_t reg1_step_time : 2;
	reg_t reg2_step_time : 2;
	reg_t video_div		 : 2;
} PMU_MISC2_t;
#define PMU_MISC2           ((PMU_MISC2_t*)0x400D8170u)
#define PMU_MISC2_SET       ((PMU_MISC2_t*)0x400D8174u)
#define PMU_MISC2_CLR       ((PMU_MISC2_t*)0x400D8178u)
#define PMU_MISC2_TOG       ((PMU_MISC2_t*)0x400D817Cu)
#define PMU_MISC2_RAW       ((reg_t*)0x400D8170u)

#pragma endregion  // PMU_MODULE

// DCDC Converter Module
// RM 18

#pragma region DCDC_MODULE

// DCDC Memory Map/Register Descriptions
// RM 18.5.1

typedef volatile struct {
	reg_t pwd_zcd				  : 1;
	reg_t disable_auto_clk_switch : 1;
	reg_t sel_clk				  : 1;
	reg_t pwd_osc_int			  : 1;
	reg_t pwd_cur_sns_cmp		  : 1;
	reg_t cur_sns_thrsh			  : 3;
	reg_t pwd_overcur_det		  : 1;
	reg_t overcur_trig_adj		  : 2;
	reg_t pwd_cmp_batt_det		  : 1;
	reg_t						  : 4;
	reg_t en_lp_overload_sns	  : 1;
	reg_t pwd_high_volt_det		  : 1;
	reg_t lp_overload_thrsh		  : 2;
	reg_t lp_overload_freq_sel	  : 1;
	reg_t lp_high_hys			  : 1;
	reg_t						  : 4;
	reg_t pwd_cmp_offset		  : 1;
	reg_t xtalok_disable		  : 1;
	reg_t current_alert_reset	  : 1;
	reg_t xtal_24m_ok			  : 1;
	reg_t						  : 1;
	reg_t sts_dc_ok				  : 1;
} DCDC_REG0_t;
#define DCDC_REG0       ((DCDC_REG0_t*)0x40080000u)
#define DCDC_REG0_RAW   ((reg_t*)0x40080000u)

typedef volatile struct {
	reg_t					  : 7;
	reg_t reg_fbk_sel		  : 2;
	reg_t reg_rload_sw		  : 1;
	reg_t					  : 2;
	reg_t lp_cmp_isrc_sel	  : 2;
	reg_t					  : 7;
	reg_t loopctrl_hst_thresh : 1;
	reg_t					  : 1;
	reg_t loopctrl_en_hyst	  : 1;
	reg_t vbg_trim			  : 5;
	reg_t					  : 3;
} DCDC_REG1_t;
#define DCDC_REG1       ((DCDC_REG1_t*)0x40080004u)
#define DCDC_REG1_RAW   ((reg_t*)0x40080004u)

typedef volatile struct {
	reg_t						: 6;
	reg_t loopctrl_dc_ff		: 3;
	reg_t loopctrl_en_rcscale	: 3;
	reg_t loopctrl_rscale_thrsh : 1;
	reg_t loopctrl_hyst_sign	: 1;
	reg_t						: 13;
	reg_t disable_pulse_skip	: 1;
	reg_t dcm_set_ctrl			: 1;
	reg_t						: 3;
} DCDC_REG2_t;
#define DCDC_REG2       ((DCDC_REG2_t*)0x40080008u)
#define DCDC_REG2_RAW   ((reg_t*)0x40080008u)

typedef volatile struct {
	reg_t trg				: 5;
	reg_t					: 3;
	reg_t target_lp			: 3;
	reg_t					: 13;
	reg_t minpwr_dc_halfclk : 1;
	reg_t					: 5;
	reg_t disable_step		: 1;
	reg_t					: 1;
} DCDC_REG3_t;
#define DCDC_REG3       ((DCDC_REG3_t*)0x4008000Cu)
#define DCDC_REG3_RAW   ((reg_t*)0x4008000Cu)

#pragma endregion  // DCDC_MODULE

// Low Power UART (LPUART) Module
// RM 49

#pragma region LPUART_MODULE

typedef volatile struct {
	reg_t feature : 16;
	reg_t minor	  : 8;
	reg_t major	  : 8;
} LPUART_VERID_t;

typedef volatile struct {
	reg_t txfifo : 8;
	reg_t rxfifo : 8;
	reg_t		 : 16;
} LPUART_PARAM_t;

typedef volatile struct {
	reg_t	  : 1;
	reg_t rst : 1;
	reg_t	  : 30;
} LPUART_GLOBAL_t;

typedef volatile struct {
	reg_t trgsel : 2;
	reg_t		 : 30;
} LPUART_PINCFG_t;

typedef volatile struct {
	reg_t sbr		: 13;
	reg_t sbns		: 1;
	reg_t rxedgie	: 1;
	reg_t lbkdie	: 1;
	reg_t resyncdis : 1;
	reg_t bothedge	: 1;
	reg_t matcfg	: 2;
	reg_t			: 1;
	reg_t rdmae		: 1;
	reg_t			: 1;
	reg_t tdmae		: 1;
	reg_t osr		: 5;
	reg_t m10		: 1;
	reg_t maen2		: 1;
	reg_t maen1		: 1;
} LPUART_BAUD_t;

typedef volatile struct {
	reg_t		  : 14;
	reg_t ma2f	  : 1;
	reg_t ma1f	  : 1;
	reg_t pf	  : 1;
	reg_t fe	  : 1;
	reg_t nf	  : 1;
	reg_t OR	  : 1;	// C/C++ moment, cant be 'or' since thats a keyword
	reg_t idle	  : 1;
	reg_t rdrf	  : 1;
	reg_t tc	  : 1;
	reg_t tdre	  : 1;
	reg_t raf	  : 1;
	reg_t lbkde	  : 1;
	reg_t brk13	  : 1;
	reg_t rwuid	  : 1;
	reg_t rxinv	  : 1;
	reg_t msbf	  : 1;
	reg_t rxedgif : 1;
	reg_t lbkdif  : 1;
} LPUART_STAT_t;

typedef volatile struct {
	reg_t pt	  : 1;
	reg_t pe	  : 1;
	reg_t ilt	  : 1;
	reg_t wake	  : 1;
	reg_t m		  : 1;
	reg_t rsrc	  : 1;
	reg_t dozeen  : 1;
	reg_t loops	  : 1;
	reg_t idlecfg : 3;
	reg_t m7	  : 1;
	reg_t		  : 2;
	reg_t ma2ie	  : 1;
	reg_t ma1ie	  : 1;
	reg_t sbk	  : 1;
	reg_t rwu	  : 1;
	reg_t re	  : 1;
	reg_t te	  : 1;
	reg_t ilie	  : 1;
	reg_t rie	  : 1;
	reg_t tcie	  : 1;
	reg_t tie	  : 1;
	reg_t peie	  : 1;
	reg_t feie	  : 1;
	reg_t neie	  : 1;
	reg_t orie	  : 1;
	reg_t txinv	  : 1;
	reg_t txdir	  : 1;
	reg_t r9t8	  : 1;
	reg_t r8t9	  : 1;
} LPUART_CTRL_t;

typedef volatile struct {
	reg_t data	  : 10;
	reg_t		  : 1;
	reg_t idline  : 1;
	reg_t rxempt  : 1;
	reg_t fretsc  : 1;
	reg_t paritye : 1;
	reg_t noisy	  : 1;
	reg_t		  : 16;
} LPUART_DATA_t;

typedef volatile struct {
	reg_t ma1 : 10;
	reg_t	  : 6;
	reg_t ma2 : 10;
	reg_t	  : 6;
} LPUART_MATCH_t;

typedef volatile struct {
	reg_t txctse   : 1;
	reg_t txrtse   : 1;
	reg_t txrtspol : 1;
	reg_t rxrtse   : 1;
	reg_t txctsc   : 1;
	reg_t txctssrc : 1;
	reg_t		   : 2;
	reg_t rtswater : 2;
	reg_t		   : 6;
	reg_t tnp	   : 2;
	reg_t iren	   : 1;
	reg_t		   : 13;
} LPUART_MODIR_t;

typedef volatile struct {
	reg_t rxfifosize : 3;
	reg_t rxfe		 : 1;
	reg_t txfifosize : 3;
	reg_t txfe		 : 1;
	reg_t rxufe		 : 1;
	reg_t txofe		 : 1;
	reg_t rxiden	 : 3;
	reg_t			 : 1;
	reg_t rxflush	 : 1;
	reg_t txflush	 : 1;
	reg_t rxuf		 : 1;
	reg_t txof		 : 1;
	reg_t			 : 4;
	reg_t rxempt	 : 1;
	reg_t txempt	 : 1;
	reg_t			 : 8;
} LPUART_FIFO_t;

typedef volatile struct {
	reg_t txwater : 2;
	reg_t		  : 6;
	reg_t txcount : 3;
	reg_t		  : 5;
	reg_t rxwater : 2;
	reg_t		  : 6;
	reg_t rxcount : 3;
	reg_t		  : 5;
} LPUART_WATER_t;

typedef volatile struct {
	LPUART_VERID_t	verid;
	LPUART_PARAM_t	param;
	LPUART_GLOBAL_t global;
	LPUART_PINCFG_t pincfg;
	LPUART_BAUD_t	baud;
	LPUART_STAT_t	stat;
	LPUART_CTRL_t	ctrl;
	LPUART_DATA_t	data;
	LPUART_MATCH_t	match;
	LPUART_MODIR_t	modir;
	LPUART_FIFO_t	fifo;
	LPUART_WATER_t	water;
} LPUART_t;

#define LPUART1     ((LPUART_t*)0x40184000u)
#define LPUART2     ((LPUART_t*)0x40188000u)
#define LPUART3     ((LPUART_t*)0x4018C000u)
#define LPUART4     ((LPUART_t*)0x40190000u)
#define LPUART5     ((LPUART_t*)0x40194000u)
#define LPUART6     ((LPUART_t*)0x40198000u)
#define LPUART7     ((LPUART_t*)0x4019C000u)
#define LPUART8     ((LPUART_t*)0x401A0000u)

#pragma endregion  // LPUART_MODULE

#endif			   // IMXRT_REGMAP_H
