#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	lpuart_begin(&lpuart6_config, 115200);

	const char* buffer = "Hello!\r\n";

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 10000000; i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 10000000; i++);

		lpuart_sync_write_buffer(&lpuart6_config, (uint8_t*)buffer, 9);
	}

	return 0;
}
