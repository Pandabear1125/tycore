#include "macros.h"

// TODO remake the register map file
#include "imxrt_regmap.h"

extern uint32_t __ld_flexram_config;
extern uint32_t __ld_stack_start;

extern uint32_t __ld_itcm_start;
extern uint32_t __ld_itcm_load;
extern uint32_t __ld_itcm_size;

extern uint32_t __ld_dtcm_start;
extern uint32_t __ld_dtcm_load;
extern uint32_t __ld_dtcm_size;

extern int main(void);

CFUNC SECTION(".reset_vector") void reset_vector(void) {
	IOMUXC_GPR_GPR16->FLEXRAM_BANK_CFG_SEL = 1;
	IOMUXC_GPR_GPR17->FLEXRAM_BANK_CFG = (uint32_t)&__ld_flexram_config;

	asm volatile (
		"mov sp, %0"
		: 
		: "r" ((uint32_t)&__ld_stack_start)
		: "memory"
	);

	// Copy the ITCM and DTCM sections from flash to RAM
	uint32_t *src = &__ld_itcm_load;
	uint32_t *dst = &__ld_itcm_start;
	uint32_t len = (uint32_t)&__ld_itcm_size;
	while (len--) *dst++ = *src++;

	src = &__ld_dtcm_load;
	dst = &__ld_dtcm_start;
	len = (uint32_t)&__ld_dtcm_size;
	while (len--) *dst++ = *src++;

	main();

	while (1) asm("wfi");

}
