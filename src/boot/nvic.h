#ifndef NVIC_H
#define NVIC_H

#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "../utils/memory.h"

// irq handler type: void function with no parameters
typedef void (*irq_handler_t)(void);

// exposed vector table array
extern volatile irq_handler_t vector_table[NVIC_SUPPORTED_IRQ_NUM + NVIC_SYSTEM_IRQ_NUM] __attribute__((section(".interrupt_vector")));

/**
 * @brief Initialize the NVIC. Sets default handlers and priorities for all supported interrupts.
 * 
 */
ITCM void nvic_init(void);

/**
 * @brief Add a custom handler for a specific external interrupt.
 * 
 * @param irq_num The interrupt number to add the handler for.
 * @param handler The function pointer to the handler.
 */
ITCM void nvic_add_handler(uint8_t irq_num, irq_handler_t handler);

/**
 * @brief Remove a custom handler for a specific external interrupt. Replaces the handler with the default handler.
 * 
 * @param irq_num The interrupt number to remove the handler for.
 */
ITCM void nvic_remove_handler(uint8_t irq_num);

/**
 * @brief Add a custom handler for a specific core interrupt.
 * 
 * @param irq_num The interrupt number to add the handler for.
 * @param handler The function pointer to the handler.
 */
ITCM void nvic_add_core_handler(uint8_t irq_num, irq_handler_t handler);

/**
 * @brief Remove a custom handler for a specific core interrupt. Replaces the handler with the default handler.
 * 
 * @param irq_num The interrupt number to remove the handler for.
 */
ITCM void nvic_remove_core_handler(uint8_t irq_num);

/**
 * @brief Set the priority for a specific interrupt.
 * 
 * @param irq_num The interrupt number to set the priority for.
 * @param priority The priority level to set (0 is highest priority) [0-15].
 */
ITCM void nvic_set_priority(uint8_t irq_num, uint8_t priority);

/**
 * @brief Get the priority for a specific interrupt.
 * 
 * @param irq_num The interrupt number to get the priority for.
 * @return uint8_t The priority level of the interrupt (0 is highest priority) [0-15].
 */
ITCM uint8_t nvic_get_priority(uint8_t irq_num);

/**
 * @brief Default handler for interrupts. This function is called when an interrupt occurs
 *        that does not have a specific handler defined.
 * 
 * This function can be overridden by defining a custom handler in the vector table.
 */
ITCM void default_handler(void);

#endif	// NVIC_H
