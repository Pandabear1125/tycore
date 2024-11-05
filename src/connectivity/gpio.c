#include "gpio.h"

// GPIO pin to MUX register mapping
// This specifies which MUX register the pin corresponds to
static IOMUXC_SW_MUX_CTL_PAD_t* gpio_pin_mux_map[GPIO_PIN_COUNT] = {
    /*  0  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03,     // GPIO_AD_B0_03    | GPIO1_IO03
    /*  1  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02,     // GPIO_AD_B0_02    | GPIO1_IO02
    /*  2  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04,       // GPIO_EMC_04      | GPIO4_IO04
    /*  3  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05,       // GPIO_EMC_05      | GPIO4_IO05
    /*  4  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06,       // GPIO_EMC_06      | GPIO4_IO06
    /*  5  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08,       // GPIO_EMC_08      | GPIO4_IO08
    /*  6  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10,        // GPIO_B0_10       | GPIO2_IO10
    /*  7  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01,        // GPIO_B1_01       | GPIO2_IO17
    /*  8  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00,        // GPIO_B1_00       | GPIO2_IO16
    /*  9  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11,        // GPIO_B0_11       | GPIO2_IO11
    /* 10  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00,        // GPIO_B0_00       | GPIO2_IO00
    /* 11  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02,        // GPIO_B0_02       | GPIO2_IO02
    /* 12  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01,        // GPIO_B0_01       | GPIO2_IO01
    /* 13  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03,        // GPIO_B0_03       | GPIO2_IO03
    /* 14  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02,     // GPIO_AD_B1_02    | GPIO1_IO18
    /* 15  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03,     // GPIO_AD_B1_03    | GPIO1_IO19
    /* 16  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07,     // GPIO_AD_B1_07    | GPIO1_IO23
    /* 17  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06,     // GPIO_AD_B1_06    | GPIO1_IO22
    /* 18  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01,     // GPIO_AD_B1_01    | GPIO1_IO17
    /* 19  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00,     // GPIO_AD_B1_00    | GPIO1_IO16
    /* 20  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10,     // GPIO_AD_B1_10    | GPIO1_IO26
    /* 21  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11,     // GPIO_AD_B1_11    | GPIO1_IO27
    /* 22  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08,     // GPIO_AD_B1_08    | GPIO1_IO24
    /* 23  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09,     // GPIO_AD_B1_09    | GPIO1_IO25
    /* 24  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12,     // GPIO_AD_B0_12    | GPIO1_IO12
    /* 25  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13,     // GPIO_AD_B0_13    | GPIO1_IO13
    /* 26  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14,     // GPIO_AD_B1_14    | GPIO1_IO30
    /* 27  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15,     // GPIO_AD_B1_15    | GPIO1_IO31
    /* 28  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32,       // GPIO_EMC_32      | GPIO3_IO18
    /* 29  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31,       // GPIO_EMC_31      | GPIO4_IO31
    /* 30  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37,       // GPIO_EMC_37      | GPIO3_IO23
    /* 31  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36,       // GPIO_EMC_36      | GPIO3_IO22
    /* 32  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12,        // GPIO_B0_12       | GPIO2_IO12
    /* 33  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07,       // GPIO_EMC_07      | GPIO4_IO07
    /* 34  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_13,        // GPIO_B1_13       | GPIO2_IO29
    /* 35  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_12,        // GPIO_B1_12       | GPIO2_IO28
    /* 36  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_02,        // GPIO_B1_02       | GPIO2_IO18
    /* 37  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03,        // GPIO_B1_03       | GPIO2_IO19
    /* 38  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_12,     // GPIO_AD_B1_12    | GPIO1_IO28
    /* 39  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_13,     // GPIO_AD_B1_13    | GPIO1_IO29
    /* 40  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04,     // GPIO_AD_B1_04    | GPIO1_IO20
    /* 41  */   IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05      // GPIO_AD_B1_05    | GPIO1_IO21
};

// GPIO pin to PAD register mapping
// This specifies which PAD register the pin corresponds to
static IOMUXC_SW_PAD_CTL_PAD_t* gpio_pin_pad_map[GPIO_PIN_COUNT] = {
    /*  0  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03,     // GPIO_AD_B0_03    | GPIO1_IO03
    /*  1  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02,     // GPIO_AD_B0_02    | GPIO1_IO02
    /*  2  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04,       // GPIO_EMC_04      | GPIO4_IO04
    /*  3  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05,       // GPIO_EMC_05      | GPIO4_IO05
    /*  4  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06,       // GPIO_EMC_06      | GPIO4_IO06
    /*  5  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08,       // GPIO_EMC_08      | GPIO4_IO08
    /*  6  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10,        // GPIO_B0_10       | GPIO2_IO10
    /*  7  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01,        // GPIO_B1_01       | GPIO2_IO17
    /*  8  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00,        // GPIO_B1_00       | GPIO2_IO16
    /*  9  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11,        // GPIO_B0_11       | GPIO2_IO11
    /* 10  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00,        // GPIO_B0_00       | GPIO2_IO00
    /* 11  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02,        // GPIO_B0_02       | GPIO2_IO02
    /* 12  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01,        // GPIO_B0_01       | GPIO2_IO01
    /* 13  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03,        // GPIO_B0_03       | GPIO2_IO03
    /* 14  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02,     // GPIO_AD_B1_02    | GPIO1_IO18
    /* 15  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03,     // GPIO_AD_B1_03    | GPIO1_IO19
    /* 16  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07,     // GPIO_AD_B1_07    | GPIO1_IO23
    /* 17  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06,     // GPIO_AD_B1_06    | GPIO1_IO22
    /* 18  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01,     // GPIO_AD_B1_01    | GPIO1_IO17
    /* 19  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00,     // GPIO_AD_B1_00    | GPIO1_IO16
    /* 20  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10,     // GPIO_AD_B1_10    | GPIO1_IO26
    /* 21  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11,     // GPIO_AD_B1_11    | GPIO1_IO27
    /* 22  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08,     // GPIO_AD_B1_08    | GPIO1_IO24
    /* 23  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09,     // GPIO_AD_B1_09    | GPIO1_IO25
    /* 24  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12,     // GPIO_AD_B0_12    | GPIO1_IO12
    /* 25  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13,     // GPIO_AD_B0_13    | GPIO1_IO13
    /* 26  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14,     // GPIO_AD_B1_14    | GPIO1_IO30
    /* 27  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15,     // GPIO_AD_B1_15    | GPIO1_IO31
    /* 28  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32,       // GPIO_EMC_32      | GPIO3_IO18
    /* 29  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31,       // GPIO_EMC_31      | GPIO4_IO31
    /* 30  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37,       // GPIO_EMC_37      | GPIO3_IO23
    /* 31  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36,       // GPIO_EMC_36      | GPIO3_IO22
    /* 32  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12,        // GPIO_B0_12       | GPIO2_IO12
    /* 33  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07,       // GPIO_EMC_07      | GPIO4_IO07
    /* 34  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13,        // GPIO_B1_13       | GPIO2_IO29
    /* 35  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12,        // GPIO_B1_12       | GPIO2_IO28
    /* 36  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_02,        // GPIO_B1_02       | GPIO2_IO18
    /* 37  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03,        // GPIO_B1_03       | GPIO2_IO19
    /* 38  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_12,     // GPIO_AD_B1_12    | GPIO1_IO28
    /* 39  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_13,     // GPIO_AD_B1_13    | GPIO1_IO29
    /* 40  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04,     // GPIO_AD_B1_04    | GPIO1_IO20
    /* 41  */   IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05      // GPIO_AD_B1_05    | GPIO1_IO21
};

// GPIO pin to GPIO register mapping
// This specifies which GPIO register the pin is in
static GPIO_t* gpio_pin_gpio_map[GPIO_PIN_COUNT] = {
    /*  0  */   GPIO6,  // GPIO1_IO03 -> GPIO6
    /*  1  */   GPIO6,  // GPIO1_IO02 -> GPIO6
    /*  2  */   GPIO9,  // GPIO4_IO04 -> GPIO9
    /*  3  */   GPIO9,  // GPIO4_IO05 -> GPIO9
    /*  4  */   GPIO9,  // GPIO4_IO06 -> GPIO9
    /*  5  */   GPIO9,  // GPIO4_IO08 -> GPIO9
    /*  6  */   GPIO7,  // GPIO2_IO10 -> GPIO7
    /*  7  */   GPIO7,  // GPIO2_IO17 -> GPIO7
    /*  8  */   GPIO7,  // GPIO2_IO16 -> GPIO7
    /*  9  */   GPIO7,  // GPIO2_IO11 -> GPIO7
    /* 10  */   GPIO7,  // GPIO2_IO00 -> GPIO7
    /* 11  */   GPIO7,  // GPIO2_IO02 -> GPIO7
    /* 12  */   GPIO7,  // GPIO2_IO01 -> GPIO7
    /* 13  */   GPIO7,  // GPIO2_IO03 -> GPIO7
    /* 14  */   GPIO6,  // GPIO1_IO18 -> GPIO6
    /* 15  */   GPIO6,  // GPIO1_IO19 -> GPIO6
    /* 16  */   GPIO6,  // GPIO1_IO23 -> GPIO6
    /* 17  */   GPIO6,  // GPIO1_IO22 -> GPIO6
    /* 18  */   GPIO6,  // GPIO1_IO17 -> GPIO6
    /* 19  */   GPIO6,  // GPIO1_IO16 -> GPIO6
    /* 20  */   GPIO6,  // GPIO1_IO26 -> GPIO6
    /* 21  */   GPIO6,  // GPIO1_IO27 -> GPIO6
    /* 22  */   GPIO6,  // GPIO1_IO24 -> GPIO6
    /* 23  */   GPIO6,  // GPIO1_IO25 -> GPIO6
    /* 24  */   GPIO6,  // GPIO1_IO12 -> GPIO6
    /* 25  */   GPIO6,  // GPIO1_IO13 -> GPIO6
    /* 26  */   GPIO6,  // GPIO1_IO30 -> GPIO6
    /* 27  */   GPIO6,  // GPIO1_IO31 -> GPIO6
    /* 28  */   GPIO8,  // GPIO3_IO18 -> GPIO8
    /* 29  */   GPIO9,  // GPIO4_IO31 -> GPIO9
    /* 30  */   GPIO8,  // GPIO3_IO23 -> GPIO8
    /* 31  */   GPIO8,  // GPIO3_IO22 -> GPIO8
    /* 32  */   GPIO7,  // GPIO2_IO12 -> GPIO7
    /* 33  */   GPIO9,  // GPIO4_IO07 -> GPIO9
    /* 34  */   GPIO7,  // GPIO2_IO29 -> GPIO7
    /* 35  */   GPIO7,  // GPIO2_IO28 -> GPIO7
    /* 36  */   GPIO7,  // GPIO2_IO18 -> GPIO7
    /* 37  */   GPIO7,  // GPIO2_IO19 -> GPIO7
    /* 38  */   GPIO6,  // GPIO1_IO28 -> GPIO6
    /* 39  */   GPIO6,  // GPIO1_IO29 -> GPIO6
    /* 40  */   GPIO6,  // GPIO1_IO20 -> GPIO6
    /* 41  */   GPIO6   // GPIO1_IO21 -> GPIO6
};

// GPIO pin to GPIO register bitmask mapping
// This specifies which bit corresponds to the pin in the GPIO register
static uint32_t gpio_pin_gpio_mask_map[GPIO_PIN_COUNT] = {
    /*  0  */   1u << 3u,  // GPIO1_IO03
    /*  1  */   1u << 2u,  // GPIO1_IO02
    /*  2  */   1u << 4u,  // GPIO4_IO04
    /*  3  */   1u << 5u,  // GPIO4_IO05
    /*  4  */   1u << 6u,  // GPIO4_IO06
    /*  5  */   1u << 8u,  // GPIO4_IO08
    /*  6  */   1u << 10u, // GPIO2_IO10
    /*  7  */   1u << 17u, // GPIO2_IO17
    /*  8  */   1u << 16u, // GPIO2_IO16
    /*  9  */   1u << 11u, // GPIO2_IO11
    /* 10  */   1u << 0u,  // GPIO2_IO00
    /* 11  */   1u << 2u,  // GPIO2_IO02
    /* 12  */   1u << 1u,  // GPIO2_IO01
    /* 13  */   1u << 3u,  // GPIO2_IO03
    /* 14  */   1u << 18u, // GPIO1_IO18
    /* 15  */   1u << 19u, // GPIO1_IO19
    /* 16  */   1u << 23u, // GPIO1_IO23
    /* 17  */   1u << 22u, // GPIO1_IO22
    /* 18  */   1u << 17u, // GPIO1_IO17
    /* 19  */   1u << 16u, // GPIO1_IO16
    /* 20  */   1u << 26u, // GPIO1_IO26
    /* 21  */   1u << 27u, // GPIO1_IO27
    /* 22  */   1u << 24u, // GPIO1_IO24
    /* 23  */   1u << 25u, // GPIO1_IO25
    /* 24  */   1u << 12u, // GPIO1_IO12
    /* 25  */   1u << 13u, // GPIO1_IO13
    /* 26  */   1u << 30u, // GPIO1_IO30
    /* 27  */   1u << 31u, // GPIO1_IO31
    /* 28  */   1u << 18u, // GPIO3_IO18
    /* 29  */   1u << 31u, // GPIO4_IO31
    /* 30  */   1u << 23u, // GPIO3_IO23
    /* 31  */   1u << 22u, // GPIO3_IO22
    /* 32  */   1u << 12u, // GPIO2_IO12
    /* 33  */   1u << 7u,  // GPIO4_IO07
    /* 34  */   1u << 29u, // GPIO2_IO29
    /* 35  */   1u << 28u, // GPIO2_IO28
    /* 36  */   1u << 18u, // GPIO2_IO18
    /* 37  */   1u << 19u, // GPIO2_IO19
    /* 38  */   1u << 28u, // GPIO1_IO28
    /* 39  */   1u << 29u, // GPIO1_IO29
    /* 40  */   1u << 20u, // GPIO1_IO20
    /* 41  */   1u << 21u  // GPIO1_IO21
};

int gpio_init(void) {
    // enable use of fast GPIO
    // this switches the normal GPIO1/2/3/4 to use GPIO6/7/8/9

    // swap GPIO1 to GPIO6
    IOMUXC_GPR_GPR26->GPIO_MUX1_GPIO_SEL = 0xffffffff;
    // swap GPIO2 to GPIO7
    IOMUXC_GPR_GPR27->GPIO_MUX2_GPIO_SEL = 0xffffffff;
    // swap GPIO3 to GPIO8
    IOMUXC_GPR_GPR28->GPIO_MUX3_GPIO_SEL = 0xffffffff;
    // swap GPIO4 to GPIO9
    IOMUXC_GPR_GPR29->GPIO_MUX4_GPIO_SEL = 0xffffffff;

    return 0;
}

void pinMode(uint8_t pin, gpio_pin_mode_t mode) {
    switch (mode) {
    case INPUT:
        // set pin to input
        break;
    case INPUT_PULLUP:
        // set pin to input with pullup
        break;
    case INPUT_PULLDOWN:
        // set pin to input with pulldown
        break;
    case OUTPUT:
        // set GPIO mode for this pin (ALT5)
        gpio_pin_mux_map[pin]->MUX_MODE = 5;
        // set GPIO drive strength for this pin (7)
        gpio_pin_pad_map[pin]->DSE = 7;     

        break;
    case OUTPUT_OPENDRAIN:
        // set pin to output with open drain
        break;
    case INPUT_DISABLE:
        // disable pin
        break;
    }
}

void digitalWrite(uint8_t pin, uint8_t value) {
    // Configure GPIO direction register to output (GDIR[GDIR] = 1b) 
    gpio_pin_gpio_map[pin]->GDIR.GDIR |= gpio_pin_gpio_mask_map[pin];
    
    // Write value to GPIO data register
    if (value) 
        gpio_pin_gpio_map[pin]->DR.DR |= gpio_pin_gpio_mask_map[pin];
    else 
        gpio_pin_gpio_map[pin]->DR.DR &= ~gpio_pin_gpio_mask_map[pin];
}

uint8_t digitalRead(uint8_t pin) {
    // Configure GPIO direction register to input (GDIR[GDIR] = 0b)
    gpio_pin_gpio_map[pin]->GDIR.GDIR &= ~gpio_pin_gpio_mask_map[pin];
    
    // Read value from data register/pad status register
    return !!(gpio_pin_gpio_map[pin]->PSR.PSR & gpio_pin_gpio_mask_map[pin]);
}

void digitalToggle(uint8_t pin);

void digitalClear(uint8_t pin);

