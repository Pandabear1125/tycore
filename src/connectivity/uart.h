#ifndef TYCORE_UART_H
#define TYCORE_UART_H

#include <stdint.h>

#include "../imxrt_regmap.h"
#include "../utils/macros.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus extern "C"

// TODO: 80MHz is good for > 2Mbaud, 24MHz is good for < 2Mbaud
// although 80MHz is acceptable for all but 110baud
static const uint32_t UART_CLOCK = 24u * 1000u * 1000u;	 // 80 MHz

// TODO: polling for now, implement interrupts later

// Components required for a specific LPUART configuration
typedef struct {
	reg_t*	  ccm_reg;	   // the raw register for the clock module
	uint32_t  ccm_mask;	   // the mask to enable the clock for the LPUART module
	LPUART_t* lpuart_reg;  // the LPUART register
	uint8_t	  rx_pin;	   // the RX pin
	uint8_t	  rx_pin_mux;  // the RX pin mux (ALT mode)
	uint8_t	  tx_pin;	   // the TX pin
	uint8_t	  tx_pin_mux;  // the TX pin mux (ALT mode)
} lpuart_config_t;

typedef enum {
	LPUART_OK				= 0,
	LPUART_INVALID_BAUDRATE = -1,
} lpuart_status_t;

// Serial 6
DTCM extern lpuart_config_t lpuart1_config;
// Serial 3
DTCM extern lpuart_config_t lpuart2_config;
// Serial 4
DTCM extern lpuart_config_t lpuart3_config;
// Serial 2
DTCM extern lpuart_config_t lpuart4_config;
// Serial 8
DTCM extern lpuart_config_t lpuart5_config;
// Serial 1
DTCM extern lpuart_config_t lpuart6_config;
// Serial 7
DTCM extern lpuart_config_t lpuart7_config;
// Serial 5
DTCM extern lpuart_config_t lpuart8_config;

/**
 * @brief Initialize the LPUART global clock
 */
FLASH_CODE void lpuart_init(void);

/**
 * @brief Begin a specific LPUART module
 * @param config The configuration for the LPUART module
 * @param baudrate The desired baudrate
 *
 * @return 0 on success, -1 on failure
 */
FLASH_CODE lpuart_status_t lpuart_begin(lpuart_config_t* config, uint32_t baudrate);

// TODO: name this better
ITCM void lpuart_write(lpuart_config_t* config, uint8_t c);

#ifdef __cplusplus
}
#endif	// __cplusplus extern "C"

#endif	// TYCORE_UART_H
