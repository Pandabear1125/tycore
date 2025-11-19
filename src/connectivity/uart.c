#include "uart.h"

// TODO: implement alt rx/tx pins

// Serial 6
uint8_t lpuart1_tx_buffer[LPUART1_TX_BUFFER_SIZE] = {0};
uint8_t lpuart1_rx_buffer[LPUART1_RX_BUFFER_SIZE] = {0};
void	lpuart1_isr(void) { lpuart_isr(&lpuart1_config); }

lpuart_config_t lpuart1_config = {
	.ccm_reg		= CCM_CCGR5_RAW,
	.ccm_mask		= CCM_CGn(12),
	.lpuart_reg		= LPUART1,
	.rx_pin			= 25,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart1_rx_buffer,
	.rx_buffer_size = LPUART1_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 24,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart1_tx_buffer,
	.tx_buffer_size = LPUART1_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART1,
	.internal_isr	= lpuart1_isr,
	.user_isr		= 0,
};

// Serial 3
uint8_t lpuart2_tx_buffer[LPUART2_TX_BUFFER_SIZE] = {0};
uint8_t lpuart2_rx_buffer[LPUART2_RX_BUFFER_SIZE] = {0};
void	lpuart2_isr(void) { lpuart_isr(&lpuart2_config); }

lpuart_config_t lpuart2_config = {
	.ccm_reg		= CCM_CCGR0_RAW,
	.ccm_mask		= CCM_CGn(14),
	.lpuart_reg		= LPUART2,
	.rx_pin			= 15,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart2_rx_buffer,
	.rx_buffer_size = LPUART2_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 14,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart2_tx_buffer,
	.tx_buffer_size = LPUART2_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART2,
	.internal_isr	= lpuart2_isr,
	.user_isr		= 0,
};

// Serial 4
uint8_t lpuart3_tx_buffer[LPUART3_TX_BUFFER_SIZE] = {0};
uint8_t lpuart3_rx_buffer[LPUART3_RX_BUFFER_SIZE] = {0};
void	lpuart3_isr(void) { lpuart_isr(&lpuart3_config); }

lpuart_config_t lpuart3_config = {
	.ccm_reg		= CCM_CCGR0_RAW,
	.ccm_mask		= CCM_CGn(6),
	.lpuart_reg		= LPUART3,
	.rx_pin			= 16,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart3_rx_buffer,
	.rx_buffer_size = LPUART3_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 17,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart3_tx_buffer,
	.tx_buffer_size = LPUART3_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART3,
	.internal_isr	= lpuart3_isr,
	.user_isr		= 0,
};

// Serial 2
uint8_t lpuart4_tx_buffer[LPUART4_TX_BUFFER_SIZE] = {0};
uint8_t lpuart4_rx_buffer[LPUART4_RX_BUFFER_SIZE] = {0};
void	lpuart4_isr(void) { lpuart_isr(&lpuart4_config); }

lpuart_config_t lpuart4_config = {
	.ccm_reg		= CCM_CCGR1_RAW,
	.ccm_mask		= CCM_CGn(12),
	.lpuart_reg		= LPUART4,
	.rx_pin			= 7,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart4_rx_buffer,
	.rx_buffer_size = LPUART4_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 8,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart4_tx_buffer,
	.tx_buffer_size = LPUART4_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART4,
	.internal_isr	= lpuart4_isr,
	.user_isr		= 0,
};

// Serial 8
uint8_t lpuart5_tx_buffer[LPUART5_TX_BUFFER_SIZE] = {0};
uint8_t lpuart5_rx_buffer[LPUART5_RX_BUFFER_SIZE] = {0};
void	lpuart5_isr(void) { lpuart_isr(&lpuart5_config); }

lpuart_config_t lpuart5_config = {
	.ccm_reg		= CCM_CCGR3_RAW,
	.ccm_mask		= CCM_CGn(1),
	.lpuart_reg		= LPUART5,
	.rx_pin			= 34,
	.rx_pin_mux		= IOMUXC_ALT1,
	.rx_buffer		= lpuart5_rx_buffer,
	.rx_buffer_size = LPUART5_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 35,
	.tx_pin_mux		= IOMUXC_ALT1,
	.tx_buffer		= lpuart5_tx_buffer,
	.tx_buffer_size = LPUART5_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART5,
	.internal_isr	= lpuart5_isr,
	.user_isr		= 0,
};

// Serial 1
uint8_t lpuart6_tx_buffer[LPUART6_TX_BUFFER_SIZE] = {0};
uint8_t lpuart6_rx_buffer[LPUART6_RX_BUFFER_SIZE] = {0};
void	lpuart6_isr(void) { lpuart_isr(&lpuart6_config); }

lpuart_config_t lpuart6_config = {
	.ccm_reg		= CCM_CCGR3_RAW,
	.ccm_mask		= CCM_CGn(3),
	.lpuart_reg		= LPUART6,
	.rx_pin			= 0,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart6_rx_buffer,
	.rx_buffer_size = LPUART6_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 1,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart6_tx_buffer,
	.tx_buffer_size = LPUART6_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART6,
	.internal_isr	= lpuart6_isr,
	.user_isr		= 0,
};

// Serial 7
uint8_t lpuart7_tx_buffer[LPUART7_TX_BUFFER_SIZE] = {0};
uint8_t lpuart7_rx_buffer[LPUART7_RX_BUFFER_SIZE] = {0};
void	lpuart7_isr(void) { lpuart_isr(&lpuart7_config); }

lpuart_config_t lpuart7_config = {
	.ccm_reg		= CCM_CCGR5_RAW,
	.ccm_mask		= CCM_CGn(13),
	.lpuart_reg		= LPUART7,
	.rx_pin			= 28,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart7_rx_buffer,
	.rx_buffer_size = LPUART7_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 29,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart7_tx_buffer,
	.tx_buffer_size = LPUART7_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART7,
	.internal_isr	= lpuart7_isr,
	.user_isr		= 0,
};

// Serial 5
uint8_t lpuart8_tx_buffer[LPUART8_TX_BUFFER_SIZE] = {0};
uint8_t lpuart8_rx_buffer[LPUART8_RX_BUFFER_SIZE] = {0};
void	lpuart8_isr(void) { lpuart_isr(&lpuart8_config); }

lpuart_config_t lpuart8_config = {
	.ccm_reg		= CCM_CCGR6_RAW,
	.ccm_mask		= CCM_CGn(7),
	.lpuart_reg		= LPUART8,
	.rx_pin			= 21,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart8_rx_buffer,
	.rx_buffer_size = LPUART8_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_pin			= 20,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart8_tx_buffer,
	.tx_buffer_size = LPUART8_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.irq_num		= IRQ_LPUART8,
	.internal_isr	= lpuart8_isr,
	.user_isr		= 0,
};

FLASH_CODE void lpuart_init(void) {
	// enable the main LPUART clock
	// disabling the clock makes signal transfer garbage

	// set the divider to 1
	CCM_CSCDR1->uart_clk_podf = 0;

	// select the 24MHz oscillator
	CCM_CSCDR1->uart_clk_sel = 1;
}

FLASH_CODE lpuart_status_t calculate_baudrate_settings(uint32_t target_baud, uint32_t* osr, uint32_t* sbr) {
	const uint32_t MAX_ERROR	   = 3;	 // percent
	const uint32_t error_threshold = (target_baud * MAX_ERROR) / 100;

	// init worst case values
	uint32_t best_sbr	= 8191;
	uint32_t best_osr	= 31;
	uint32_t best_error = target_baud;

	// try all osr values, find the best sbr for each
	for (uint8_t osr = 3; osr <= 31; osr++) {
		// assumes target_baudrate > 0 and (osr + 1) won't overflow the multiply
		uint32_t denom		 = target_baud * (osr + 1u);
		uint32_t perfect_sbr = (UART_CLOCK + denom / 2u) / denom;  // nearest-integer

		// if the sbr is impossible, this osr is not enough
		if (perfect_sbr < 1 || perfect_sbr > 8191) {
			continue;
		}

		// calculate the baudrate with this sbr and osr
		// and the resulting error
		uint32_t calculated_baud = UART_CLOCK / (perfect_sbr * (osr + 1));
		uint32_t error			 = (calculated_baud > target_baud) ? (calculated_baud - target_baud) : (target_baud - calculated_baud);

		if (error < best_error) {
			// found a new best
			best_error = error;
			best_sbr   = perfect_sbr;
			best_osr   = osr;
		}

		if (calculated_baud == target_baud) {
			// perfect match, early return
			break;
		}
	}

	*osr = best_osr;
	*sbr = best_sbr;

	// do a final check to verify the result is within the error threshold
	uint32_t calculated_baud = UART_CLOCK / (best_sbr * (best_osr + 1));
	uint32_t err			 = (calculated_baud > target_baud) ? (calculated_baud - target_baud) : (target_baud - calculated_baud);

	if (err > error_threshold) {
		return LPUART_INVALID_BAUDRATE;
	} else {
		return LPUART_OK;
	}
}

FLASH_CODE lpuart_status_t lpuart_begin(lpuart_config_t* config, uint32_t baudrate) {
	// enable the specific LPUART clock
	*(config->ccm_reg) |= config->ccm_mask;

	// configure the RX pin
	gpio_pin_to_pad_map[config->rx_pin]->dse	  = 7;
	gpio_pin_to_pad_map[config->rx_pin]->pke	  = 1;
	gpio_pin_to_pad_map[config->rx_pin]->pue	  = 1;
	gpio_pin_to_pad_map[config->rx_pin]->pus	  = 3;
	gpio_pin_to_pad_map[config->rx_pin]->hys	  = 1;
	// set mux to LPUART
	gpio_pin_to_mux_map[config->rx_pin]->mux_mode = config->rx_pin_mux;

	// configure the TX pin
	gpio_pin_to_pad_map[config->tx_pin]->sre	  = 1;
	gpio_pin_to_pad_map[config->tx_pin]->sre	  = 1;
	gpio_pin_to_pad_map[config->tx_pin]->speed	  = 3;
	// set mux to LPUART
	gpio_pin_to_mux_map[config->tx_pin]->mux_mode = config->tx_pin_mux;

	// calculate the baudrate settings
	uint32_t		osr	   = 0;
	uint32_t		sbr	   = 0;
	lpuart_status_t status = calculate_baudrate_settings(baudrate, &osr, &sbr);

	// if baud is not set correctly, data is uninterpretable
	config->lpuart_reg->baud.osr = osr;
	config->lpuart_reg->baud.sbr = sbr;
	// TODO: bothedge?

	// does not seem to impact data transfer
	// LPUART6->pincfg.trgsel = 0;

	// TODO:
	// read what the PARAM.RXFIFO and PARAM.TXFIFO are
	// DMA?

	config->lpuart_reg->ctrl.te = 1;
	config->lpuart_reg->ctrl.re = 1;

	// TODO: available interrupts:
	// - Overrun (ORIE)
	// - Noise flag (NEIE)
	// - Framing error (FEIE)
	// - Parity error (PEIE)
	// - Tx (TIE)
	// - Tx complete (TCIE)
	// - Rx (RIE)
	// - Idle (ILIE)
	// - Match 1/2 (MA1IE/MA2IE)

	// even if the baudrate calculation failed, we still keep the LPUART enabled, the baudrate error may be acceptable
	return status;
}

ITCM void lpuart_write(lpuart_config_t* config, const uint8_t c) {
	while (!config->lpuart_reg->stat.tdre);

	config->lpuart_reg->data.data = c;
}

ITCM void lpuart_write_buffer(lpuart_config_t* config, const uint8_t* buffer, const uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		lpuart_write(config, buffer[i]);
	}
}

ITCM int32_t lpuart_read(lpuart_config_t* config) {
	// TODO
	(void)config;
	return -1;
}

ITCM void lpuart_handle_rx_isr(lpuart_config_t* config) {
	// check if data is available
	// check IDLE flag too, this can indicate data in FIFO even if RDRF did not trigger (for example if no new data arrived and the FIFO is not full)
	if (config->lpuart_reg->stat.rdrf || config->lpuart_reg->stat.idle) {
		// get number of bytes in FIFO
		uint32_t rx_count = config->lpuart_reg->water.rxcount;

		for (uint32_t i = 0; i < rx_count; i++) {
			// read byte from DATA register
			uint8_t data = (uint8_t)(config->lpuart_reg->data.data & 0xFF);

			// store in RX buffer
			config->rx_buffer[config->rx_buffer_head] = data;
			config->rx_buffer_head					  = (config->rx_buffer_head + 1) % config->rx_buffer_size;
		}

		// clear IDLE flag
		config->lpuart_reg->stat.idle = 0;
	}
}

ITCM void lpuart_handle_tx_isr(lpuart_config_t* config) {
	// TODO
	(void)config;
}

ITCM void lpuart_isr(lpuart_config_t* config) {
	// handle RX
	lpuart_handle_rx_isr(config);

	// handle TX
	lpuart_handle_tx_isr(config);

	// call user ISR if set
	if (config->user_isr) {
		config->user_isr();
	}
}
