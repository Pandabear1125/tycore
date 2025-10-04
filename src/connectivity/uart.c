#include "uart.h"

// TODO: implement alt rx/tx pins

// Serial 6
lpuart_config_t lpuart1_config = {
	.ccm_reg	= CCM_CCGR5_RAW,
	.ccm_mask	= CCM_CGn(12),
	.lpuart_reg = LPUART1,
	.rx_pin		= 25,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 24,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 3
lpuart_config_t lpuart2_config = {
	.ccm_reg	= CCM_CCGR0_RAW,
	.ccm_mask	= CCM_CGn(14),
	.lpuart_reg = LPUART2,
	.rx_pin		= 15,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 14,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 4
lpuart_config_t lpuart3_config = {
	.ccm_reg	= CCM_CCGR0_RAW,
	.ccm_mask	= CCM_CGn(6),
	.lpuart_reg = LPUART3,
	.rx_pin		= 16,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 17,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 2
lpuart_config_t lpuart4_config = {
	.ccm_reg	= CCM_CCGR1_RAW,
	.ccm_mask	= CCM_CGn(12),
	.lpuart_reg = LPUART4,
	.rx_pin		= 7,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 8,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 8
lpuart_config_t lpuart5_config = {
	.ccm_reg	= CCM_CCGR3_RAW,
	.ccm_mask	= CCM_CGn(1),
	.lpuart_reg = LPUART5,
	.rx_pin		= 34,
	.rx_pin_mux = IOMUXC_ALT1,
	.tx_pin		= 35,
	.tx_pin_mux = IOMUXC_ALT1,
};

// Serial 1
lpuart_config_t lpuart6_config = {
	.ccm_reg	= CCM_CCGR3_RAW,
	.ccm_mask	= CCM_CGn(3),
	.lpuart_reg = LPUART6,
	.rx_pin		= 0,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 1,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 7
lpuart_config_t lpuart7_config = {
	.ccm_reg	= CCM_CCGR5_RAW,
	.ccm_mask	= CCM_CGn(13),
	.lpuart_reg = LPUART7,
	.rx_pin		= 28,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 29,
	.tx_pin_mux = IOMUXC_ALT2,
};

// Serial 5
lpuart_config_t lpuart8_config = {
	.ccm_reg	= CCM_CCGR6_RAW,
	.ccm_mask	= CCM_CGn(7),
	.lpuart_reg = LPUART8,
	.rx_pin		= 21,
	.rx_pin_mux = IOMUXC_ALT2,
	.tx_pin		= 20,
	.tx_pin_mux = IOMUXC_ALT2,
};

FLASH_CODE void lpuart_init(void) {
	// enable the main LPUART clock
	// disabling the clock makes signal transfer garbage

	// set the divider to 1
	CCM_CSCDR1->uart_clk_podf = 0;

	// select the 24MHz oscillator
	CCM_CSCDR1->uart_clk_sel = 1;
}

FLASH_CODE void lpuart_begin(lpuart_config_t* config, uint32_t baudrate) {
	(void)baudrate;	 // unused for now
	const uint32_t OSR = 26;
	const uint32_t DIV = 8;

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

	/// if baud is not set correctly, data is uninterpretable
	config->lpuart_reg->baud.osr = (OSR - 1);
	config->lpuart_reg->baud.sbr = DIV;
	/// does not seem to impact data transfer
	// LPUART6->pincfg.trgsel = 0;

	config->lpuart_reg->ctrl.te = 1;
	config->lpuart_reg->ctrl.re = 1;
}

ITCM void lpuart_write(lpuart_config_t* config, uint8_t c) {
	// TODO: determine which register to check to see if writing is available
	config->lpuart_reg->data.data = c;
}

/*
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// TODO: 80MHz is good for > 2Mbaud, 24MHz is good for < 2Mbaud
// although 80MHz is acceptable for all but 110baud
const uint32_t UART_CLOCK = 24u * 1000u * 1000u; // 24 MHz
float MAX_ERROR = 0.05f; // 5%

int main() {
	const uint32_t target_baudrate = 115200;

	uint32_t common_baudrates[] = {
		110, 300, 600, 1200, 2400, 4800, 9600, 14400,
		19200, 38400, 57600, 115200, 128000, 230400,
		256000, 460800, 921600, 1000000, 1500000,
		2000000, 2500000, 3000000, 3500000, 4000000,
		5000000, 6000000, 7000000, 8000000, 9000000,
		10000000, 12000000, 14000000, 16000000, 18000000,
		20000000 
	};

	// baudrate equation from datasheet
	// baudrate = UART_CLOCK / (SBR * (OSR + 1))
	// sbr -> [1, 8191]
	// osr -> [3, 31]
	// find the best combination of sbr and osr to minimize the baudrate error

	for (uint32_t baud : common_baudrates) {
		uint32_t calc_baud = 0;
		float err = 0.0f;

		printf("Trg baud: %-12d", baud);
		const uint32_t target_baudrate = baud;
		// init worst case values
		uint32_t best_sbr = 8191;
		uint32_t best_osr = 31;
		float best_error = 1e20;
		for (uint8_t osr = 3; osr <= 31; osr++) {
			uint32_t perfect_sbr = (float)UART_CLOCK / (float)(target_baudrate * (osr + 1)) + 0.5f;
			// if the sbr is impossible, this osr is not enough
			if (perfect_sbr < 1 || perfect_sbr > 8191) {
				continue;
			}

			uint32_t calculated_baud = UART_CLOCK / (perfect_sbr * (osr + 1));

			// calculate the error
			float error = (calculated_baud > target_baudrate) ? (calculated_baud - target_baudrate) / (float)target_baudrate : (target_baudrate - calculated_baud) / (float)target_baudrate;
			if (error < best_error) {
				// found a new best
				best_error = error;
				best_sbr = perfect_sbr;
				best_osr = osr;
			}

			if (calculated_baud == target_baudrate) {
				// perfect match
				break;
			}
		}

		calc_baud = UART_CLOCK / (best_sbr * (best_osr + 1));
		err = (float)calc_baud / (float)target_baudrate - 1.0f;
		// TODO: handle error too big

		printf("| Calc baud: %-12d | Err: %+0.3f%%", calc_baud, err * 100.0f);
		if (fabsf(err) > MAX_ERROR) {
			printf("  <-- ERROR TOO BIG!\n");
		} else {
			printf("\n");
		}
	}

	return 0;
}
*/
