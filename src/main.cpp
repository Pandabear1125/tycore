#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	lpuart_begin(&lpuart6_config, 921600);

	while (1) {
		if (lpuart_available(&lpuart6_config)) {
			lpuart_write_byte(&lpuart6_config, lpuart_read_byte(&lpuart6_config));
			digitalToggle(13);	// toggle LED on data received
		}

		NOP();
	}

	return 0;
}
