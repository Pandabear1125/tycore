#include "connectivity/gpio.h"
#include "utils/time.h"

int main(void) {
	pinMode(13, OUTPUT);  // onboard LED

	digitalToggle(13);

	while (1) {
		delay(1000);  //1s
		digitalToggle(13);
	}

	return 0;
}
