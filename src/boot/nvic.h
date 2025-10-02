#ifndef NVIC_H
#define NVIC_H

#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "../utils/memory.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"

// Helpful definitions
// - ISR: Interrupt Service Routine, the actual function that gets called on interrupt requests
// - IRQ: Interrupt ReQuest, the signal that an interrupt has occurred
// - IDT: Interrupt Descriptor Table, the table that holds the ISR function pointers, indexed by IRQ number
// - NVIC: Nested Vector Interrupt Controller, the hardware that manages interrupts and their priorities
//
// Logical flow:
//   On the event of an IRQ, the CPU looks up the corresponding ISR in the IDT and executes it,
//   provided the IRQ is enabled in the NVIC.

// isr type: void function with no parameters
typedef void (*isr_t)(void);

/**
 * @brief Initialize the NVIC. Sets default handlers and priorities for all supported interrupts.
 * 
 */
FLASH_CODE void nvic_init(void);

/**
 * @brief Add a custom handler for a specific external interrupt.
 * 
 * @param irq_num The interrupt number to add the handler for.
 * @param handler The function pointer to the handler.
 */
ITCM void nvic_add_isr(uint8_t irq_num, isr_t handler);

/**
 * @brief Remove a custom handler for a specific external interrupt. Replaces the handler with the default handler.
 * 
 * @param irq_num The interrupt number to remove the handler for.
 */
ITCM void nvic_remove_isr(uint8_t irq_num);

/**
 * @brief Add a custom handler for a specific core interrupt.
 * 
 * @param irq_num The interrupt number to add the handler for.
 * @param handler The function pointer to the handler.
 */
ITCM void nvic_add_core_isr(uint8_t irq_num, isr_t handler);

/**
 * @brief Remove a custom handler for a specific core interrupt. Replaces the handler with the default handler.
 * 
 * @param irq_num The interrupt number to remove the handler for.
 */
ITCM void nvic_remove_core_isr(uint8_t irq_num);

/**
 * @brief Enable a specific interrupt.
 * 
 * @param irq_num The interrupt number to enable.
 */
ITCM void nvic_enable_irq(uint8_t irq_num);

/**
 * @brief Disable a specific interrupt.
 * 
 * @param irq_num The interrupt number to disable.
 */
ITCM void nvic_disable_irq(uint8_t irq_num);

/**
 * @brief Set the priority for a specific interrupt.
 * 
 * @param irq_num The interrupt number to set the priority for.
 * @param priority The priority level to set (0 is highest priority) [0-15].
 */
ITCM void nvic_set_irq_priority(uint8_t irq_num, uint8_t priority);

/**
 * @brief Get the priority for a specific interrupt.
 * 
 * @param irq_num The interrupt number to get the priority for.
 * @return uint8_t The priority level of the interrupt (0 is highest priority) [0-15].
 */
ITCM uint8_t nvic_get_irq_priority(uint8_t irq_num);

#ifdef __cplusplus
}
#endif	// __cplusplus extern "C"

#endif	// NVIC_H
