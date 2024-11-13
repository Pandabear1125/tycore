#include "connectivity/gpio.h"

int main(void) {
	pinMode(13, OUTPUT);
	pinMode(15, INPUT);

	while (1) {
		uint8_t value = digitalRead(15);

		digitalWrite(13, value);
	}

	return 0;
}