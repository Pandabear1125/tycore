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

	~Test() {
		digitalWrite(13, 0);
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

	// wait for some time
	for (int i = 0; i < 100000; i++)
		asm("nop");

	return 0;
}