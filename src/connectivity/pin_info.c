#include "pin_info.h"

FLASH_CODE IOMUXC_SW_MUX_CTL_PAD_t* get_pin_mux(uint8_t pin) {
    return gpio_pin_to_mux_map[pin];
}

FLASH_CODE IOMUXC_SW_PAD_CTL_PAD_t* get_pin_pad(uint8_t pin) {
    return gpio_pin_to_pad_map[pin];
}

FLASH_CODE GPIO_t* get_pin_gpio(uint8_t pin) {
    return gpio_pin_to_gpio_map[pin];
}

FLASH_CODE uint32_t get_pin_gpio_mask(uint8_t pin) {
    return gpio_pin_to_gpio_mask_map[pin];
}