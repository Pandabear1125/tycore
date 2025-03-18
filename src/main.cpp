#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);

	lpuart_begin(&lpuart6_config);

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 5000000; i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 5000000; i++);

		lpuart_write(&lpuart6_config, 'A');
	}

	return 0;
}
