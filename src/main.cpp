#include "connectivity/gpio.h"
// #include "imxrt.h"

extern volatile int x;

class Test {
public:
	Test() {
		gpio_init();
		pinMode(13, OUTPUT);
		x = 50;
		digitalWrite(13, 1);
	}

	void foo() {
		for (int i = 0; i < 100; i++)
			x++;
	}
};

Test test;

// TODO create actual main, this is just to satisfy linker references
int main(void) {
	test.foo();

	return 0;
}