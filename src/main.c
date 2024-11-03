#include "imxrt_regmap.h"
// #include "imxrt.h"

// TODO create actual main, this is just to satisfy linker references
int main(void) {
	// set default configuration for GPIO_B0_03
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03->MUX_MODE = 5;
	// set default configuration for GPIO_B0_03
	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03->DSE = 7;
	// enable output for GPIO_B0_03
	GPIO7->GDIR.GDIR |= (1<<3);
	// toggle GPIO_B0_03
	GPIO7->DR_TOGGLE.DR_TOGGLE = (1<<3);

	for (long i = 0; i < 100000000; i++) {
		if (i % 10000000 == 0) {
			GPIO7->DR_TOGGLE.DR_TOGGLE = (1<<3);
		}
	}
}