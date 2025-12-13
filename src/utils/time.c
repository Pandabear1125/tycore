#include "time.h"

#include <stdint.h>

#include "../boot/nvic.h"
#include "../imxrt_regmap.h"

volatile uint32_t systick_millis = 0;  // milliseconds counter

// Systick interrupt handler
ITCM void systick_isr(void) {
	systick_millis = systick_millis + 1;
}

ITCM void configureSystick(void) {
	//Teensy Doesnt have a external clock source, it will be 1 regardless of writes to this bit
	SCS_SYST_CSR->clksource = 1;

	//enable the systick exception
	SCS_SYST_CSR->tickint = 1;

	//add the IRQ to the IVT
	nvic_add_core_isr(15, systick_isr);

	//reload value to 1ms,
	//TODO CORE_FREQ should be replaced with AHB_FREQUENCY for more accuracy
	SCS_SYST_RVR->reload = (CORE_FREQ / 1000u) - 1u;

	//enable
	SCS_SYST_CSR->enable = 1;
}

ITCM void delay(uint32_t milliseconds) {
	uint32_t initialSystick = systick_millis;

	while (systick_millis <= initialSystick + milliseconds) {
		NOP();
	}
	return;
}
