#include "uart.h"

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
	config->rx_input_reg->daisy					  = config->rx_input_daisy;

	// configure the TX pin
	gpio_pin_to_pad_map[config->tx_pin]->sre	  = 1;
	gpio_pin_to_pad_map[config->tx_pin]->sre	  = 1;
	gpio_pin_to_pad_map[config->tx_pin]->speed	  = 3;
	// set mux to LPUART
	gpio_pin_to_mux_map[config->tx_pin]->mux_mode = config->tx_pin_mux;
	config->tx_input_reg->daisy					  = config->tx_input_daisy;

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

ITCM uint32_t lpuart_sync_write_byte(lpuart_config_t* config, uint8_t byte) {
	// wait until STAT[TDRE] (transmit data register empty) is set
	while (!config->lpuart_reg->stat.tdre);	 // TODO: timeout?

	config->lpuart_reg->data.data = byte;

	return 1;
}

ITCM uint32_t lpuart_sync_write_buffer(lpuart_config_t* config, const uint8_t* buffer, uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		while (!config->lpuart_reg->stat.tdre);	 // TODO: timeout?

		config->lpuart_reg->data.data = buffer[i];
	}

	return length;
}

ITCM int32_t lpuart_sync_read_byte(lpuart_config_t* config) {
	// wait until STAT[RDRF] (receive data register full) is set
	while (!config->lpuart_reg->stat.rdrf);	 // TODO: timeout?

	return config->lpuart_reg->data.data;
}

ITCM int32_t lpuart_sync_read_buffer(lpuart_config_t* config, uint8_t* buffer, uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		while (!config->lpuart_reg->stat.rdrf);	 // TODO: timeout?

		buffer[i] = config->lpuart_reg->data.data;
	}

	return length;
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
