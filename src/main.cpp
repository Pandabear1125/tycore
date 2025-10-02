#include "connectivity/gpio.h"

void isr(void) {
	digitalToggle(13);
}

int main(void) {
	pinMode(13, OUTPUT);					  // onboard LED

	gpio_enable_irq(37, GPIO_ANY_EDGE, isr);  // GPIO1_IO21

	return 0;
}
