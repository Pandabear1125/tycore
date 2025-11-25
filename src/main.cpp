#include "connectivity/gpio.h"
#include "utils/time.h"


int main(void) {
	pinMode(13, OUTPUT);					  // onboard LED

	digitalToggle(13);


	configureSystick();

	while(1) {
		if(systick_millis % 1000 == 0) { // every second perchance
			digitalToggle(13);
		}
	}

	return 0;
}
