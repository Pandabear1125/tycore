#include "connectivity/gpio.h"
// #include "imxrt.h"

// TODO create actual main, this is just to satisfy linker references
int main(void) {
	pinMode(13, OUTPUT);

	for (int i = 0; i < 25; i++) {
		digitalWrite(13, 1);
		for (int j = 0; j < 10000000; j++) asm("nop");
		digitalWrite(13, 0);
		for (int j = 0; j < 10000000; j++) asm("nop");
	}

	return 0;
}