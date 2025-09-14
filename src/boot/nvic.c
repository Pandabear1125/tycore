#include "nvic.h"

// define the vector table
volatile irq_handler_t vector_table[NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM] __attribute__((section(".interrupt_vector")));

ITCM void nvic_init(void) {
	for (uint8_t i = 0; i < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM; i++) {
		vector_table[i] = default_handler;
	}

	for (uint8_t i = 0; i < NVIC_SUPPORTED_IRQ_NUM; i++) {
		nvic_set_priority(i, 128);
	}

	SCB_VTOR->tbloff = (uint32_t)&vector_table;
}

ITCM void nvic_add_handler(uint8_t irq_num, irq_handler_t handler) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		vector_table[irq_num + NVIC_SYSTEM_IRQ_NUM] = handler;
	}
}

ITCM void nvic_remove_handler(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		vector_table[irq_num + NVIC_SYSTEM_IRQ_NUM] = default_handler;
	}
}

ITCM void nvic_add_core_handler(uint8_t irq_num, irq_handler_t handler) {
	if (irq_num < NVIC_SYSTEM_IRQ_NUM) {
		vector_table[irq_num] = handler;
	}
}

ITCM void nvic_remove_core_handler(uint8_t irq_num) {
	if (irq_num < NVIC_SYSTEM_IRQ_NUM) {
		vector_table[irq_num] = default_handler;
	}
}

ITCM void nvic_set_priority(uint8_t irq_num, uint8_t priority) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		switch (irq_num % 4) {
		case 0:
			SCS_NVIC_IPR(irq_num / 4)->pri0 = priority;
			break;
		case 1:
			SCS_NVIC_IPR(irq_num / 4)->pri1 = priority;
			break;
		case 2:
			SCS_NVIC_IPR(irq_num / 4)->pri2 = priority;
			break;
		case 3:
			SCS_NVIC_IPR(irq_num / 4)->pri3 = priority;
			break;
		}
	}
}

ITCM uint8_t nvic_get_priority(uint8_t irq_num) {
	if (irq_num < NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM) {
		switch (irq_num % 4) {
		case 0:
			return SCS_NVIC_IPR(irq_num / 4)->pri0;
		case 1:
			return SCS_NVIC_IPR(irq_num / 4)->pri1;
		case 2:
			return SCS_NVIC_IPR(irq_num / 4)->pri2;
		case 3:
			return SCS_NVIC_IPR(irq_num / 4)->pri3;
		}
	}

	return 0xFF;  // Invalid priority
}

ITCM void default_handler(void) {
	// TODO
}
