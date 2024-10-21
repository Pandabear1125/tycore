#include "imxrt.h"

// TODO create actual main, this is just to satisfy linker references
int main(void) {
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
	GPIO7_GDIR |= (1<<3);
	GPIO7_DR_SET = (1<<3); // digitalWrite(13, HIGH);
}