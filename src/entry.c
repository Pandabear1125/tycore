#include "macros.h"

// TODO remake the register map file
#include "imxrt.h"

CFUNC SECTION(".reset_vector") void reset_vector(void) {
	IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03 = 5;
	IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03 = IOMUXC_PAD_DSE(7);
	IOMUXC_GPR_GPR27 = 0xFFFFFFFF;
	GPIO7_GDIR |= (1<<3);
	GPIO7_DR_SET = (1<<3); // digitalWrite(13, HIGH);
}
