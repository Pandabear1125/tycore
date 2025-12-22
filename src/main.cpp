#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	lpuart_begin(&lpuart6_config, 115200);

	// const char* buffer = "Hello!\r\n";

	while (1) {
		// read
		int32_t byte = lpuart_sync_read_byte(&lpuart6_config);
		if (byte >= 0) {
			// echo back
			lpuart_sync_write_byte(&lpuart6_config, (uint8_t)byte);
			digitalToggle(13);	// toggle LED on each received byte
		}
	}

	return 0;
}
