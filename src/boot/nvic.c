#include "nvic.h"

// define the vector table
volatile isr_t vector_table[NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM] __attribute__((section(".interrupt_vector")));

// forward declare the default handler
ITCM void default_handler(void);

FLASH_CODE void nvic_init(void) {
	for (uint8_t i = 0; i < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM; i++) {
		vector_table[i] = default_handler;
	}

	for (uint8_t i = 0; i < NVIC_SUPPORTED_IRQ_NUM; i++) {
		nvic_set_irq_priority(i, 8);
	}

	SCB_VTOR->tbloff = (uint32_t)&vector_table;
}

ITCM void nvic_add_isr(uint8_t irq_num, isr_t handler) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		// normal isr's live after the 16 system isr's
		vector_table[irq_num + NVIC_SYSTEM_IRQ_NUM] = handler;
	}
}

ITCM void nvic_remove_isr(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		// normal isr's live after the 16 system isr's
		vector_table[irq_num + NVIC_SYSTEM_IRQ_NUM] = default_handler;
	}
}

ITCM void nvic_add_core_isr(uint8_t irq_num, isr_t handler) {
	if (irq_num < NVIC_SYSTEM_IRQ_NUM) {
		// core isr's live at the start of the vector table
		vector_table[irq_num] = handler;
	}
}

ITCM void nvic_remove_core_isr(uint8_t irq_num) {
	if (irq_num < NVIC_SYSTEM_IRQ_NUM) {
		// core isr's live at the start of the vector table
		vector_table[irq_num] = default_handler;
	}
}

ITCM void nvic_enable_irq(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		// set the correct ISER block and bit
		SCS_NVIC_ISER(irq_num >> 5u)->setena = (1u << (irq_num & 31u));
	}
}

ITCM void nvic_disable_irq(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		// set the correct ICER block and bit
		SCS_NVIC_ICER(irq_num >> 5u)->clrena = (1u << (irq_num & 31u));
	}
}

ITCM void nvic_set_irq_priority(uint8_t irq_num, uint8_t priority) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		// clear the correct priority bits
		// - get the IPR register (4 priorities per register)
		// - clear the correct 8 bits for this irq_num (irq_num % 4 * 8)
		SCS_NVIC_IPR(irq_num >> 2u)->pri &= ~(0xFFu << ((irq_num & 0x3u) * 8u));
		// set the correct priority bits
		SCS_NVIC_IPR(irq_num >> 2u)->pri |= ((priority & 0xFFu) << ((irq_num & 0x3u) * 8u));
	}
}

ITCM uint8_t nvic_get_irq_priority(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		return (SCS_NVIC_IPR(irq_num >> 2u)->pri >> ((irq_num & 0x3u) * 8u)) & 0xFFu;
	}

	return 0xFFu;  // invalid irq_num
}

/**
 * @brief Default handler for interrupts. This function is called when an interrupt occurs
 *        that does not have a specific handler defined.
 * 
 * This function can be overridden by defining a custom handler in the vector table.
 */
ITCM void default_handler(void) {
	// TODO
}
