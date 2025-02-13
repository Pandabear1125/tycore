#ifndef TYCORE_UART_H
#define TYCORE_UART_H

#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus extern "C"



// test OSR: 26
// test DIV: 8

// TODO: polling for now, implement interrupts later

// Components required for a specific LPUART configuration
typedef struct {
    reg_t*    ccm_reg;
    uint32_t  ccm_mask;
    LPUART_t* lpuart_reg;
    uint8_t   rx_pin;
    uint8_t   tx_pin;
} lpuart_config_t;

// Serial 6
extern lpuart_config_t lpuart1_config;
// Serial 3
extern lpuart_config_t lpuart2_config;
// Serial 4
extern lpuart_config_t lpuart3_config;
// Serial 2
extern lpuart_config_t lpuart4_config;
// Serial 8
extern lpuart_config_t lpuart5_config;
// Serial 1
extern lpuart_config_t lpuart6_config;
// Serial 7
extern lpuart_config_t lpuart7_config;
// Serial 5
extern lpuart_config_t lpuart8_config;

/**
 * @brief Initialize the LPUART global clock
 */
void lpuart_init(void);

/**
 * @brief Begin a specific LPUART module
 * @param config The configuration for the LPUART module
 */
// TODO: take in baud rate
void lpuart_begin(lpuart_config_t* config);

// TODO: name this better
void lpuart_write(lpuart_config_t* config, uint8_t c);



#ifdef __cplusplus
}
#endif  // __cplusplus extern "C"

#endif  // TYCORE_UART_H
