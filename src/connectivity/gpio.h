#ifndef TYCORE_GPIO_H
#define TYCORE_GPIO_H

#include "../imxrt_regmap.h"

#define GPIO_PIN_COUNT 42

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus extern "C"

/**
 * @brief Initialize the GPIO pins and set them to use fast GPIO. On system startup, the GPIO pins are disabled.
 * @note This function must be called before using any GPIO pins otherwise it is undefined behavior.
 * @return 0 if successful, otherwise an error code.
 */
int gpio_init(void);

// GPIO pin modes
typedef enum {
    INPUT = 0,
    INPUT_PULLUP,
    INPUT_PULLDOWN,
    OUTPUT,
    OUTPUT_OPENDRAIN,
    INPUT_DISABLE
} gpio_pin_mode_t;

/**
 * @brief Set the mode of a GPIO pin.
 * @param pin The GPIO pin number.
 * @param mode The mode to set the pin to.
 * @note Using a pin without setting the mode is undefined behavior.
 */
void pinMode(uint8_t pin, gpio_pin_mode_t mode);

/**
 * @brief Write a value to a GPIO pin.
 * @param pin The GPIO pin number.
 * @param value The value to write to the pin (0/LOW or 1/HIGH).
 * @note The pin must be set to some OUTPUT mode.
 */
void digitalWrite(uint8_t pin, uint8_t value);

/**
 * @brief Read the value of a GPIO pin.
 * @param pin The GPIO pin number.
 * @return The value of the pin (0/LOW or 1/HIGH).
 * @note The pin must be set to some INPUT mode.
 */
uint8_t digitalRead(uint8_t pin);

/**
 * @brief Toggle the value of a GPIO pin.
 * @param pin The GPIO pin number.
 * @note The pin must be set to some OUTPUT mode.
 */
void digitalToggle(uint8_t pin);

/**
 * @brief Set the pin to 0/LOW.
 * @param pin The GPIO pin number.
 * @note The pin must be set to some OUTPUT mode.
 */
void digitalClear(uint8_t pin);

#ifdef __cplusplus
}
#endif  // __cplusplus extern "C"

#endif // TYCORE_GPIO_H