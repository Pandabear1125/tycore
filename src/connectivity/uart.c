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

	// reset the LPUART module
	config->lpuart_reg->global.rst = 1;
	NOP();
	config->lpuart_reg->global.rst = 0;

	// configure the RX pin
	gpio_pin_to_pad_map[config->rx_pin]->dse	  = 7;
	gpio_pin_to_pad_map[config->rx_pin]->pke	  = 1;
	gpio_pin_to_pad_map[config->rx_pin]->pue	  = 1;
	gpio_pin_to_pad_map[config->rx_pin]->pus	  = 3;
	gpio_pin_to_pad_map[config->rx_pin]->hys	  = 1;
	// set mux to LPUART
	gpio_pin_to_mux_map[config->rx_pin]->mux_mode = config->rx_pin_mux;
	config->rx_input_reg->daisy					  = config->rx_input_daisy;
	// force RX as input
	config->lpuart_reg->pincfg.trgsel			  = 0;

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
	// bothedge per the datasheet
	if (osr <= 8) {
		config->lpuart_reg->baud.bothedge = 1;
	} else {
		config->lpuart_reg->baud.bothedge = 0;
	}

	// configure the interrupts
	config->lpuart_reg->ctrl.tie  = 1;	// enable TDRE interrupts
	config->lpuart_reg->ctrl.tcie = 1;	// enable   TC interrupts
	config->lpuart_reg->ctrl.rie  = 1;	// enable RDRF interrupts
	config->lpuart_reg->ctrl.ilie = 1;	// enable IDLE interrupts
	config->lpuart_reg->ctrl.orie = 1;	// enable   OR interrupts

	// TODO: do we really need the FIFO if its only 4 bytes deep?
	// enable FIFOs
	// TODO: this is always 0b001, do we need the calculation?
	// const uint8_t tx_fifo_depth_reg = config->lpuart_reg->fifo.txfifosize;
	// const uint8_t tx_fifo_depth		= (1u << (tx_fifo_depth_reg + 1u)) >> (tx_fifo_depth_reg == 0u);
	// const uint8_t rx_fifo_depth_reg = config->lpuart_reg->fifo.rxfifosize;
	// const uint8_t rx_fifo_depth		= (1u << (rx_fifo_depth_reg + 1u)) >> (rx_fifo_depth_reg == 0u);

	// config->lpuart_reg->fifo.txfe = 1;	// enable TX FIFO
	// config->lpuart_reg->fifo.rxfe = 1;	// enable RX FIFO

	// set FIFO watermarks
	// config->lpuart_reg->water.txwater = tx_fifo_depth / 2;
	// config->lpuart_reg->water.rxwater = rx_fifo_depth / 2;

	// enable TX and RX
	config->lpuart_reg->ctrl.te = 1;
	config->lpuart_reg->ctrl.re = 1;

	// enable the interrupt in the NVIC and register the ISR
	nvic_add_isr(config->irq_num, config->internal_isr);
	nvic_enable_irq(config->irq_num);

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

ITCM uint32_t lpuart_available(lpuart_config_t* config) {
	DISABLE_INTERRUPTS();
	const uint32_t head = config->rx_buffer_head;
	const uint32_t tail = config->rx_buffer_tail;
	ENABLE_INTERRUPTS();

	if (head >= tail) {
		return head - tail;
	} else {
		return (config->rx_buffer_size - tail) + head;
	}
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

// produces bytes into the RX buffer
ITCM void lpuart_handle_rx_isr(lpuart_config_t* config) {
	DISABLE_INTERRUPTS();

	// handle RDRF
	if (config->lpuart_reg->stat.rdrf) {
		// read the received byte
		const uint8_t byte = config->lpuart_reg->data.data;

		const uint32_t next_head = (config->rx_buffer_head + 1) % config->rx_buffer_size;
		if (next_head != config->rx_buffer_tail) {
			// there is space in the buffer
			config->rx_buffer[config->rx_buffer_head] = byte;
			config->rx_buffer_head					  = next_head;
		} else {
			// TODO: rx overrun?
		}
	}

	// handle IDLE
	if (config->lpuart_reg->stat.idle) {
		// clear IDLE flag (w1c) prevents repeated interrupts
		config->lpuart_reg->stat.idle = 1;
	}

	// TODO: overrun?

	ENABLE_INTERRUPTS();
}

// consumes bytes from the TX buffer
ITCM void lpuart_handle_tx_isr(lpuart_config_t* config) {
	// need to check both TDRE and TC flags
	digitalToggle(13);

	DISABLE_INTERRUPTS();

	// handle TDRE
	if (config->lpuart_reg->stat.tdre) {
		if (config->tx_buffer_head != config->tx_buffer_tail) {
			// there is data in the buffer
			const uint8_t byte	   = config->tx_buffer[config->tx_buffer_tail];
			config->tx_buffer_tail = (config->tx_buffer_tail + 1) % config->tx_buffer_size;

			// send the byte
			config->lpuart_reg->data.data = byte;
		} else {
			// TODO: tx overrun?
			// buffer empty, disable TDRE interrupts
			config->lpuart_reg->ctrl.tie = 0;
		}
	}

	// handle TC
	if (config->lpuart_reg->stat.tc) {
		// if the TX buffer is empty, disable TC interrupts
		if (config->tx_buffer_head == config->tx_buffer_tail) {
			config->lpuart_reg->ctrl.tcie = 0;
		}
	}

	ENABLE_INTERRUPTS();
}

// produces bytes into the TX buffer
ITCM uint32_t lpuart_write_byte(lpuart_config_t* config, uint8_t byte) {
	DISABLE_INTERRUPTS();

	const uint32_t next_head = (config->tx_buffer_head + 1) % config->tx_buffer_size;
	if (next_head != config->tx_buffer_tail) {
		// there is space in the buffer
		config->tx_buffer[config->tx_buffer_head] = byte;
		config->tx_buffer_head					  = next_head;

		// enable TC interrupts to start sending
		config->lpuart_reg->ctrl.tie = 1;
	} else {
		// buffer full
		ENABLE_INTERRUPTS();
		return 0;
	}

	ENABLE_INTERRUPTS();

	return 1;
}

// consumes bytes from the RX buffer
ITCM int32_t lpuart_read_byte(lpuart_config_t* config) {
	uint8_t byte = 0;

	DISABLE_INTERRUPTS();

	if (config->rx_buffer_head != config->rx_buffer_tail) {
		// there is data in the buffer
		byte				   = config->rx_buffer[config->rx_buffer_tail];
		config->rx_buffer_tail = (config->rx_buffer_tail + 1) % config->rx_buffer_size;
	} else {
		// buffer empty
		ENABLE_INTERRUPTS();
		return -1;
	}

	ENABLE_INTERRUPTS();

	return byte;
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

	DSB();
}
