#ifndef TYCORE_PIN_INFO_H
#define TYCORE_PIN_INFO_H

#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "../utils/memory.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"

#define GPIO_PIN_COUNT 42

// GPIO pin to MUX register mapping
extern IOMUXC_SW_MUX_CTL_PAD_t* const gpio_pin_to_mux_map[GPIO_PIN_COUNT];
// GPIO pin to PAD register mapping
extern IOMUXC_SW_PAD_CTL_PAD_t* const gpio_pin_to_pad_map[GPIO_PIN_COUNT];
// GPIO pin to GPIO register mapping
extern GPIO_t* const				  gpio_pin_to_gpio_map[GPIO_PIN_COUNT];
// GPIO pin to GPIO mask mapping
extern const uint32_t				  gpio_pin_to_gpio_mask_map[GPIO_PIN_COUNT];

/**
 * @brief Get the MUX register for a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The MUX register for the pin.
 * @note This function is not performant, use with one-time initialization.
 */
FLASH_CODE IOMUXC_SW_MUX_CTL_PAD_t* get_pin_mux(uint8_t pin);

/**
 * @brief Get the PAD register for a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The PAD register for the pin.
 * @note This function is not performant, use with one-time initialization.
 */
FLASH_CODE IOMUXC_SW_PAD_CTL_PAD_t* get_pin_pad(uint8_t pin);

/**
 * @brief Get the GPIO register for a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The GPIO register for the pin.
 * @note This function is not performant, use with one-time initialization.
 */
FLASH_CODE GPIO_t* get_pin_gpio(uint8_t pin);

/**
 * @brief Get the GPIO mask for a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The GPIO mask for the pin.
 * @note This function is not performant, use with one-time initialization.
 */
FLASH_CODE uint32_t get_pin_gpio_mask(uint8_t pin);

#ifdef __cplusplus
}
#endif	// __cplusplus extern "C"

#endif	// TYCORE_PIN_INFO_H
