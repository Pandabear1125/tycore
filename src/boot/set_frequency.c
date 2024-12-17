#include <stdint.h>

#include "../imxrt_regmap.h"

#include "../connectivity/gpio.h"

#include "../utils/macros.h"
#include "../utils/memory.h"

// Core CPU frequency
volatile uint32_t AHB_FREQUENCY = 0;
// Main peripheral frequency
volatile uint32_t IPG_FREQUENCY = 0;

// the frequency step per voltage increase
#define FREQ_STEP       (28000000u)

// the maximum voltage that can be set/generated
#define MAX_VOLTAGE     (1575u)

// the minimum frequency PLL1 can be set to
#define PLL1_MIN_FREQ   (648000000u)
// the maximum frequency PLL1 can be set to
#define PLL1_MAX_FREQ   (1296000000u)

// official frequencies
#define FULL_SPEED_FREQ (528000000u)
#define OVERDRIVE_FREQ  (600000000u)
#define LOW_POWER_FREQ  (24000000u)

FLASH_CODE void set_core_frequency(uint32_t frequency) {
    // increase the voltage as required

	// compute required voltage
	// Table 13-1. Low Power Mode Definition page 997
	// full speed (stock clock speed) starts at 1.15V
	uint32_t voltage = 1150;
	// if freq is greater than full speed voltage needs to increase
	if (frequency > FULL_SPEED_FREQ) {
		// overdrive speed (600MHz) starts at 1.25V
		voltage = 1250;

		// if the frequency is more than overdrive, we need to overclock the voltage
		// 600MHz is the max supported frequency by NXP but we can go further
		if (frequency > OVERDRIVE_FREQ) {
			// the voltage setting steps 25mV, we need to figure out how many steps to increase
			voltage += ((frequency - OVERDRIVE_FREQ) / FREQ_STEP) * 25;
			// but we cant increase too much since it has a max voltage
			if (voltage > MAX_VOLTAGE) voltage = MAX_VOLTAGE;
		}
	} 
	// if freq is at or less than low power run
	else if (frequency <= LOW_POWER_FREQ) {
		// low power run starts at 0.95V
		voltage = 950;
	}


    // enable the dcdc clock incase it was disabled
    CCM_CCGR6->dcdc_clk_enable = CGR_ON;

    // set the voltage setting, the value starts at 800mV and steps by 25mV
    DCDC_REG3->trg = (voltage - 800) / 25;
    // wait for the voltage to stabilize
    while (!(DCDC_REG0->sts_dc_ok)) {}

	// if the periph clock is derived from pre_periph_clk_sel (ARM PLL (pll1)) we need to switch to periph
    if (!(CCM_CBCDR->periph_clk_sel)) {
        const uint32_t select = 1;  // select the osc_clk source (24MHz)
        const uint32_t divisor = 0; // divide by 1

        // set the divisor first
        CCM_CBCDR->periph_clk2_podf = divisor;

        // set the source next
        CCM_CBCMR->periph_clk2_sel = select;
        // wait for the switch to complete
        while (CCM_CDHIPR->periph2_clk_sel_busy) {}
    }

    // switch to periph_clk2
    CCM_CBCDR->periph_clk_sel = 1;
    // wait for the switch to complete
    while (CCM_CDHIPR->periph_clk_sel_busy) {}

    // calculate the needed dividers to divide pll1's variable frequency down to the required frequency
	// we need figure out how much to scale pll1 and then later divide it down
	// https://www.cnblogs.com/henjay724/p/15581290.html
    uint32_t div_arm = 1;
	uint32_t div_ahb = 1;
	while (frequency * div_arm * div_ahb < PLL1_MIN_FREQ) {
		// try dividing the first divisor first
		if (div_arm < 8) {
			div_arm = div_arm + 1;
		} else {
			// if we cant divide the first divisor anymore, try the second
			if (div_ahb < 8) {
				div_ahb = div_ahb + 1;
				// reset the first divisor
				div_arm = 1;
			} else {
				break;
			}
		}
	}

	// derrive the div_select (pll1_scaler) from the dividers, the 12MHz is simplified from 24MHz/2
	// this is the scaler required to bring pll1's output to the required frequency prior to division
	uint32_t pll1_scaler = (frequency * div_arm * div_ahb + 6000000) / 12000000;
	// clamp the scaler to the official range
	if (pll1_scaler > 108) pll1_scaler = 108;
	if (pll1_scaler < 54) pll1_scaler = 54;

	// the final frequency is the scaled pll1 frequency divided by the dividers, this effectively rounds to the nearest 12MHz
    // 12MHz comes from the /2 in div_select
	frequency = pll1_scaler * 12000000 / div_arm / div_ahb;

    // power down PLL1 and reconfigure the new scaler (pll1_scaler)
	// div_select is a bad name for this register since its a scaler, not a divider
    CCM_ANALOG_PLL_ARM->powerdown = 1;

    // we need to clear the PPL_ARM register then set enable and the new pll1_scaler
    // normal struct accesses do not work since the register expects an all or nothing access
    // so we need to do a read modify write

    // the address for the register is 0x400D8000
    // the enable bit is the 13th bit
    // the div_select is the 0-6 bits

    // TODO declare "raw" pointers in the regmap
    *(volatile uint32_t*)0x400D8000 = (1 << 13) | (pll1_scaler & 0x7Fu);
        
    // wait while the pll configures
    while (!(CCM_ANALOG_PLL_ARM->lock));
    
    // set the dividers

    // set the arm podf
    CCM_CACRR->arm_podf = div_arm - 1;
    // wait for the divider to stabilize
    while (CCM_CDHIPR->arm_podf_busy) {}

    // set the ahb podf
    CCM_CBCDR->ahb_podf = div_ahb - 1;
    // wait for the divider to stabilize
    while (CCM_CDHIPR->ahb_podf_busy) {}

    // figure our a good divisor for the ipg clock, it cant be more than 4 nor should it be more than 150MHz
    // although it can be more than 150MHz if it is forced to be
    uint32_t div_ipg = (frequency + (150000000 - 1)) / 150000000;
    // divider is 2 bit so it cant be more than 4
    if (div_ipg > 4) div_ipg = 4;
    // set the ipg podf
    CCM_CBCDR->ipg_podf = div_ipg - 1;
    
    // unset the periph_clk_sel to switch back to pll1
    CCM_CBCDR->periph_clk_sel = 0;
    // wait for the switch to complete
    while (CCM_CDHIPR->periph_clk_sel_busy) {}

    // set the global frequency variables
    AHB_FREQUENCY = frequency;
    IPG_FREQUENCY = frequency / div_ipg;
}