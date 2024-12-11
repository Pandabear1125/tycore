#include "connectivity/gpio.h"

int main(void) {
	pinMode(33, OUTPUT);
	
	while (1) {
		GPIO9->dr_toggle.dr_toggle |= 1u << 7u;
	}

	return 0;
}