#include "connectivity/gpio.h"
#include "connectivity/uart.h"

int main(void) {
	pinMode(13, OUTPUT);

	// lpuart_begin(&lpuart1_config);
	// lpuart_begin(&lpuart2_config);
	// lpuart_begin(&lpuart3_config);
	// lpuart_begin(&lpuart4_config);
	lpuart_begin(&lpuart5_config);
	// lpuart_begin(&lpuart6_config);
	// lpuart_begin(&lpuart7_config);
	// lpuart_begin(&lpuart8_config);

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 5000000; i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 5000000; i++);

		// lpuart_write(&lpuart1_config, 'A');
		// lpuart_write(&lpuart2_config, 'A');
		// lpuart_write(&lpuart3_config, 'A');
		// lpuart_write(&lpuart4_config, 'A');
		lpuart_write(&lpuart5_config, 'A');
		// lpuart_write(&lpuart6_config, 'A');
		// lpuart_write(&lpuart7_config, 'A');
		// lpuart_write(&lpuart8_config, 'A');
	}

	return 0;
}
