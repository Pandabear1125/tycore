#include "gpio.h"

ITCM void gpio_isr(void);

FLASH_CODE int gpio_init(void) {
	// enable use of fast GPIO
	// this switches the normal GPIO1/2/3/4 to use GPIO6/7/8/9

	// swap GPIO1 to GPIO6
	IOMUXC_GPR_GPR26->gpio_mux1_gpio_sel = 0xffffffffu;
	// swap GPIO2 to GPIO7
	IOMUXC_GPR_GPR27->gpio_mux2_gpio_sel = 0xffffffffu;
	// swap GPIO3 to GPIO8
	IOMUXC_GPR_GPR28->gpio_mux3_gpio_sel = 0xffffffffu;
	// swap GPIO4 to GPIO9
	IOMUXC_GPR_GPR29->gpio_mux4_gpio_sel = 0xffffffffu;

	// enable the shared interrupt isr for GPIO6/7/8/9
	nvic_add_isr(IRQ_GPIO6789, gpio_isr);
	nvic_enable_irq(IRQ_GPIO6789);

	return 0;
}

FLASH_CODE void pinMode(uint8_t pin, gpio_pin_mode_t mode) {
	switch (mode) {
	case INPUT:
		// set pin to input
		// disable input keeper in order to read the current value, rather than the last "set" value
		gpio_pin_to_pad_map[pin]->pue = 1;

		// set direction to input
		gpio_pin_to_gpio_map[pin]->gdir.gdir &= ~gpio_pin_to_gpio_mask_map[pin];
		break;
	case INPUT_PULLUP:
		// set pin to input with pullup
		gpio_pin_to_pad_map[pin]->pke = 1;	// enable pullup
		gpio_pin_to_pad_map[pin]->pue = 1;	// enable pullup
		gpio_pin_to_pad_map[pin]->pus = 3;	// select 22kOhm pullup
		gpio_pin_to_pad_map[pin]->hys = 1;	// enable hysteresis

		// set direction to input
		gpio_pin_to_gpio_map[pin]->gdir.gdir &= ~gpio_pin_to_gpio_mask_map[pin];
		break;
	case INPUT_PULLDOWN:
		// set pin to input with pulldown
		gpio_pin_to_pad_map[pin]->pke = 1;	// enable pulldown
		gpio_pin_to_pad_map[pin]->pue = 1;	// enable pulldown
		gpio_pin_to_pad_map[pin]->pus = 0;	// select 100kOhm pulldown
		gpio_pin_to_pad_map[pin]->hys = 1;	// enable hysteresis

		// set direction to input
		gpio_pin_to_gpio_map[pin]->gdir.gdir &= ~gpio_pin_to_gpio_mask_map[pin];
		break;
	case OUTPUT:
		// set direction to output
		gpio_pin_to_gpio_map[pin]->gdir.gdir |= gpio_pin_to_gpio_mask_map[pin];
		break;
	case OUTPUT_OPENDRAIN:
		// set pin to output with open drain
		gpio_pin_to_pad_map[pin]->ode = 1;	// enable open drain

		// set direction to output
		gpio_pin_to_gpio_map[pin]->gdir.gdir |= gpio_pin_to_gpio_mask_map[pin];
		break;
	case INPUT_DISABLE:
		// disable pin
		gpio_pin_to_pad_map[pin]->hys = 1;
		break;
	}

	// set GPIO mode for this pin (ALT5)
	gpio_pin_to_mux_map[pin]->mux_mode = IOMUXC_ALT5;
	// set SION to allow software control of input, allows reading of output value
	gpio_pin_to_mux_map[pin]->sion	   = 1;
	// set GPIO drive strength for this pin (7)
	gpio_pin_to_pad_map[pin]->dse	   = 7;
}

ITCM void digitalWrite(uint8_t pin, uint8_t value) {
	// This assumes the pin is already set to some OUTPUT mode

	// Write value to GPIO data register
	if (value)
		gpio_pin_to_gpio_map[pin]->dr.dr |= gpio_pin_to_gpio_mask_map[pin];
	else
		gpio_pin_to_gpio_map[pin]->dr.dr &= ~gpio_pin_to_gpio_mask_map[pin];
}

ITCM uint8_t digitalRead(uint8_t pin) {
	// This assumes the pin is already set to some INPUT mode

	// Read value from GPIO data register
	return !!(gpio_pin_to_gpio_map[pin]->psr.psr & gpio_pin_to_gpio_mask_map[pin]);
}

ITCM void digitalToggle(uint8_t pin) {
	// This assumes the pin is already set to some OUTPUT mode

	// Toggle value in GPIO data register
	gpio_pin_to_gpio_map[pin]->dr_toggle.dr_toggle = gpio_pin_to_gpio_mask_map[pin];
}

ITCM void digitalClear(uint8_t pin) {
	// This assumes the pin is already set to some OUTPUT mode

	// Clear value in GPIO data register
	gpio_pin_to_gpio_map[pin]->dr_clear.dr_clear = gpio_pin_to_gpio_mask_map[pin];
}

// Interrupt Descriptor Table for GPIO pins
// 4 GPIO blocks (GPIO6, GPIO7, GPIO8, GPIO9) with 32 pins each
DTCM isr_t gpio_idt[4][32] = {{0}};

FLASH_CODE void gpio_enable_irq(uint8_t pin, gpio_irq_mode_t mode, isr_t handler) {
	const uint32_t mask = gpio_pin_to_gpio_mask_map[pin];

	gpio_pin_to_gpio_map[pin]->imr.imr	 &= ~mask;		  // disable interrupt
	gpio_pin_to_mux_map[pin]->mux_mode	  = IOMUXC_ALT5;  // set GPIO mode
	gpio_pin_to_pad_map[pin]->hys		  = 1;			  // enable hysteresis
	gpio_pin_to_gpio_map[pin]->gdir.gdir &= ~mask;		  // set as input

	// figure out the correct icr position
	const uint32_t mask_index = __builtin_ctz(mask);
	if (mask_index < 16) {
		gpio_pin_to_gpio_map[pin]->icr1.icr &= ~(0x3 << (mask_index * 2));
		gpio_pin_to_gpio_map[pin]->icr1.icr |= ((mode & 0x3) << (mask_index * 2));
	} else {
		gpio_pin_to_gpio_map[pin]->icr2.icr &= ~(0x3 << ((mask_index - 16) * 2));
		gpio_pin_to_gpio_map[pin]->icr2.icr |= ((mode & 0x3) << ((mask_index - 16) * 2));
	}

	// enabling the edge_select will override the icr setting
	if (mode == GPIO_ANY_EDGE) {
		gpio_pin_to_gpio_map[pin]->edge_sel.edge_sel |= mask;	// enable edge select
	} else {
		gpio_pin_to_gpio_map[pin]->edge_sel.edge_sel &= ~mask;	// disable edge select
	}

	// figure out which GPIO block this pin belongs to
	uint8_t gpio_block = 0;
	if (gpio_pin_to_gpio_map[pin] == GPIO6) {
		gpio_block = 0;
	} else if (gpio_pin_to_gpio_map[pin] == GPIO7) {
		gpio_block = 1;
	} else if (gpio_pin_to_gpio_map[pin] == GPIO8) {
		gpio_block = 2;
	} else if (gpio_pin_to_gpio_map[pin] == GPIO9) {
		gpio_block = 3;
	}

	gpio_idt[gpio_block][mask_index] = handler;	 // set the handler

	gpio_pin_to_gpio_map[pin]->isr.isr	= mask;	 // clear any pending interrupt
	gpio_pin_to_gpio_map[pin]->imr.imr |= mask;	 // enable interrupt
}

FLASH_CODE void gpio_detach_isr(uint8_t pin) {
	const uint32_t mask = gpio_pin_to_gpio_mask_map[pin];

	gpio_pin_to_gpio_map[pin]->imr.imr &= ~mask;  // disable interrupt
}

ITCM void gpio_isr(void) {
	// check each GPIO block for pending interrupts
	for (uint8_t block = 0; block < 4; block++) {
		GPIO_t* gpio = GPIO6;
		switch (block) {
		case 0:
			gpio = GPIO6;
			break;
		case 1:
			gpio = GPIO7;
			break;
		case 2:
			gpio = GPIO8;
			break;
		case 3:
			gpio = GPIO9;
			break;
		}

		uint32_t pending = gpio->isr.isr & gpio->imr.imr;
		// clear the pending bits
		gpio->isr.isr	 = pending;

		// handle each pending interrupt
		while (pending) {
			uint32_t bit = __builtin_ctz(pending);

			// the handler should never be null
			gpio_idt[block][bit]();
			// clear the interrupt
			pending &= ~(1u << bit);
		}
	}

	DSB();
}
