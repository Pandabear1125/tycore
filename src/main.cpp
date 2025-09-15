#include "connectivity/gpio.h"
#include "connectivity/uart.h"

volatile int32_t x = 0;

int main(void) {
	pinMode(13, OUTPUT);

	gpio_attach_isr(29, GPIO_ANY_EDGE, nullptr);

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 50000000 - (x * 10000000); i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 50000000 - (x * 10000000); i++);
	}

	return 0;
}
