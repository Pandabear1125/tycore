#ifndef TYCORE_GPIO_H
#define TYCORE_GPIO_H

#include "../connectivity/pin_info.h"
#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "../utils/memory.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"

// TODO: make fast GPIO

/**
 * @brief Initialize the GPIO pins and set them to use fast GPIO. On system startup, the GPIO pins are disabled.
 * @note This function must be called before using any GPIO pins otherwise it is undefined behavior.
 * @return 0 if successful, otherwise -1
 */
FLASH_CODE int gpio_init(void);

// GPIO pin modes
typedef enum {
	INPUT = 0,
	INPUT_PULLUP,
	INPUT_PULLDOWN,
	OUTPUT,
	OUTPUT_OPENDRAIN,
	INPUT_DISABLE,
} gpio_pin_mode_t;

/**
 * @brief Set the mode of a GPIO pin.
 * @param pin The GPIO pin number.
 * @param mode The mode to set the pin to.
 * @note Using a pin without setting the mode is undefined behavior.
 */
FLASH_CODE void pinMode(uint8_t pin, gpio_pin_mode_t mode);

/**
 * @brief Write a value to a GPIO pin.
 * @param pin The GPIO pin number.
 * @param value The value to write to the pin (0/LOW or 1/HIGH).
 * @note The pin must be set to some OUTPUT mode.
 */
ITCM void digitalWrite(uint8_t pin, uint8_t value);

/**
 * @brief Read the value of a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The value of the pin (0/LOW or 1/HIGH).
 * @note The pin must be set to some INPUT mode.
 */
ITCM uint8_t digitalRead(uint8_t pin);

/**
 * @brief Toggle the value of a GPIO pin.
 * @param pin The GPIO pin number.
 * @note The pin must be set to some OUTPUT mode.
 */
ITCM void digitalToggle(uint8_t pin);

/**
 * @brief Set the pin to 0/LOW.
 * @param pin The GPIO pin number.
 * @note The pin must be set to some OUTPUT mode.
 */
ITCM void digitalClear(uint8_t pin);

#ifdef __cplusplus
}
#endif	// __cplusplus extern "C"

#endif	// TYCORE_GPIO_H
