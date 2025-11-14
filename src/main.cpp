#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	lpuart_begin(&lpuart1_config, 1500000);

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 10000000; i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 10000000; i++);

		lpuart_write(&lpuart1_config, 'H');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, 'e');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, 'l');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, 'l');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, 'o');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, '\r');
		for (volatile int i = 0; i < 100000; i++);
		lpuart_write(&lpuart1_config, '\n');
	}

	return 0;
}
