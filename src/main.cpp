#include "connectivity/gpio.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	gpio_enable_irq(37, GPIO_ANY_EDGE);

	return 0;
}
