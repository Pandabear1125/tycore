#include "utils/macros.h"

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

extern int main(void);					// main function
extern void __libc_init_array(void);	// c++ initialization

CFUNC SECTION(".reset_vector") void reset_vector(void) {
	// enable ITCM/DTCM/OCRAM config
	IOMUXC_GPR_GPR16->flexram_bank_cfg_sel = 1;
	// set the ITCM/DTCM/OCRAM config
	IOMUXC_GPR_GPR17->flexram_bank_cfg = (uint32_t)&__ld_flexram_config;

	// set the stack pointer to enable function calling
	__asm__ volatile (
		"mov sp, %0"
		: 
		: "r" ((uint32_t)&__ld_stack_start)
		: "memory"
	);

	// copy ITCM section into ITCM memory
	uint32_t *src = &__ld_itcm_load;
	uint32_t *dst = &__ld_itcm_start;
	uint32_t len = (uint32_t)&__ld_itcm_size;
	while (len--) *dst++ = *src++;

	// copy DTCM section into DTCM memory
	src = &__ld_dtcm_load;
	dst = &__ld_dtcm_start;
	len = (uint32_t)&__ld_dtcm_size;
	while (len--) *dst++ = *src++;

	// initialize c++ statics and global constructors
	__libc_init_array();

	// call main
	main();

	// if main returns, enter infinite loop maintaining interrupts
	while (1) __asm__("wfi");
}
