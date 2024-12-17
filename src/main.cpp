#include "connectivity/gpio.h"

int main(void) {
	pinMode(13, OUTPUT);

	while (1) {
		digitalWrite(13, 1);
		for (volatile int i = 0; i < 50000000; i++);
		digitalWrite(13, 0);
		for (volatile int i = 0; i < 50000000; i++);
	}

	return 0;
}