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
	reg_t*		   ccm_reg;			// the raw register for the clock module
	uint32_t	   ccm_mask;		// the mask to enable the clock for the LPUART module
	LPUART_t*	   lpuart_reg;		// the LPUART register
	uint8_t		   rx_pin;			// the RX pin
	uint8_t		   rx_pin_mux;		// the RX pin mux (ALT mode)
	uint8_t*	   rx_buffer;		// the RX buffer
	const uint32_t rx_buffer_size;	// size of the RX buffer
	uint32_t	   rx_buffer_head;	// head index for RX buffer
	uint8_t		   tx_pin;			// the TX pin
	uint8_t		   tx_pin_mux;		// the TX pin mux (ALT mode)
	uint8_t*	   tx_buffer;		// the TX buffer
	const uint32_t tx_buffer_size;	// size of the TX buffer
	uint32_t	   tx_buffer_head;	// head index for TX buffer
	uint8_t		   irq_num;			// the IRQ number for this LPUART
} lpuart_config_t;

typedef enum {
	LPUART_OK				= 0,
	LPUART_INVALID_BAUDRATE = -1,
} lpuart_status_t;

// Serial 6
#define LPUART1_TX_BUFFER_SIZE 64
#define LPUART1_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart1_config;
// Serial 3
#define LPUART2_TX_BUFFER_SIZE 64
#define LPUART2_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart2_config;
// Serial 4
#define LPUART3_TX_BUFFER_SIZE 64
#define LPUART3_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart3_config;
// Serial 2
#define LPUART4_TX_BUFFER_SIZE 64
#define LPUART4_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart4_config;
// Serial 8
#define LPUART5_TX_BUFFER_SIZE 64
#define LPUART5_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart5_config;
// Serial 1
#define LPUART6_TX_BUFFER_SIZE 64
#define LPUART6_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart6_config;
// Serial 7
#define LPUART7_TX_BUFFER_SIZE 64
#define LPUART7_RX_BUFFER_SIZE 64
DTCM extern lpuart_config_t lpuart7_config;
// Serial 5
#define LPUART8_TX_BUFFER_SIZE 64
#define LPUART8_RX_BUFFER_SIZE 64
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
