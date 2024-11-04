#include "connectivity/gpio.h"
// #include "imxrt.h"

// TODO create actual main, this is just to satisfy linker references
int main(void) {
	// set default configuration for GPIO_B0_03
	gpio_pin_mux_map[13]->MUX_MODE = 5;
	// set default configuration for GPIO_B0_03
	gpio_pin_pad_map[13]->DSE = 7;
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