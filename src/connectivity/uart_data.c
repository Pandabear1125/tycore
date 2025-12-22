#include "uart.h"

// TODO: implement alt rx/tx pins

// Serial 6
DTCM uint8_t lpuart1_tx_buffer[LPUART1_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart1_rx_buffer[LPUART1_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart1_config = {
	.ccm_reg		= CCM_CCGR5_RAW,
	.ccm_mask		= CCM_CGn(12),
	.lpuart_reg		= LPUART1,
	.rx_input_reg	= 0,
	.rx_input_daisy = 0,
	.rx_pin			= 25,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart1_rx_buffer,
	.rx_buffer_size = LPUART1_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= 0,
	.tx_input_daisy = 0,
	.tx_pin			= 24,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart1_tx_buffer,
	.tx_buffer_size = LPUART1_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART1,
};

// Serial 3
DTCM uint8_t lpuart2_tx_buffer[LPUART2_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart2_rx_buffer[LPUART2_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart2_config = {
	.ccm_reg		= CCM_CCGR0_RAW,
	.ccm_mask		= CCM_CGn(14),
	.lpuart_reg		= LPUART2,
	.rx_input_reg	= IOMUXC_LPUART2_RX_SELECT_INPUT,
	.rx_input_daisy = 1,
	.rx_pin			= 15,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart2_rx_buffer,
	.rx_buffer_size = LPUART2_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= IOMUXC_LPUART2_TX_SELECT_INPUT,
	.tx_input_daisy = 1,
	.tx_pin			= 14,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart2_tx_buffer,
	.tx_buffer_size = LPUART2_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART2,
};

// Serial 4
DTCM uint8_t lpuart3_tx_buffer[LPUART3_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart3_rx_buffer[LPUART3_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart3_config = {
	.ccm_reg		= CCM_CCGR0_RAW,
	.ccm_mask		= CCM_CGn(6),
	.lpuart_reg		= LPUART3,
	.rx_input_reg	= IOMUXC_LPUART3_RX_SELECT_INPUT,
	.rx_input_daisy = 0,
	.rx_pin			= 16,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart3_rx_buffer,
	.rx_buffer_size = LPUART3_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_input_reg	= IOMUXC_LPUART3_TX_SELECT_INPUT,
	.tx_input_daisy = 0,
	.tx_pin			= 17,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart3_tx_buffer,
	.tx_buffer_size = LPUART3_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART3,
};

// Serial 2
DTCM uint8_t lpuart4_tx_buffer[LPUART4_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart4_rx_buffer[LPUART4_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart4_config = {
	.ccm_reg		= CCM_CCGR1_RAW,
	.ccm_mask		= CCM_CGn(12),
	.lpuart_reg		= LPUART4,
	.rx_input_reg	= IOMUXC_LPUART4_RX_SELECT_INPUT,
	.rx_input_daisy = 2,
	.rx_pin			= 7,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart4_rx_buffer,
	.rx_buffer_size = LPUART4_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.tx_input_reg	= IOMUXC_LPUART4_TX_SELECT_INPUT,
	.tx_input_daisy = 2,
	.tx_pin			= 8,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart4_tx_buffer,
	.tx_buffer_size = LPUART4_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART4,
};

// Serial 8
DTCM uint8_t lpuart5_tx_buffer[LPUART5_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart5_rx_buffer[LPUART5_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart5_config = {
	.ccm_reg		= CCM_CCGR3_RAW,
	.ccm_mask		= CCM_CGn(1),
	.lpuart_reg		= LPUART5,
	.rx_input_reg	= IOMUXC_LPUART5_RX_SELECT_INPUT,
	.rx_input_daisy = 1,
	.rx_pin			= 34,
	.rx_pin_mux		= IOMUXC_ALT1,
	.rx_buffer		= lpuart5_rx_buffer,
	.rx_buffer_size = LPUART5_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= IOMUXC_LPUART5_TX_SELECT_INPUT,
	.tx_input_daisy = 1,
	.tx_pin			= 35,
	.tx_pin_mux		= IOMUXC_ALT1,
	.tx_buffer		= lpuart5_tx_buffer,
	.tx_buffer_size = LPUART5_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART5,
};

// Serial 1
DTCM uint8_t lpuart6_tx_buffer[LPUART6_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart6_rx_buffer[LPUART6_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart6_config = {
	.ccm_reg		= CCM_CCGR3_RAW,
	.ccm_mask		= CCM_CGn(3),
	.lpuart_reg		= LPUART6,
	.rx_input_reg	= IOMUXC_LPUART6_RX_SELECT_INPUT,
	.rx_input_daisy = 1,
	.rx_pin			= 0,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart6_rx_buffer,
	.rx_buffer_size = LPUART6_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= IOMUXC_LPUART6_TX_SELECT_INPUT,
	.tx_input_daisy = 1,
	.tx_pin			= 1,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart6_tx_buffer,
	.tx_buffer_size = LPUART6_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART6,
};

// Serial 7
DTCM uint8_t lpuart7_tx_buffer[LPUART7_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart7_rx_buffer[LPUART7_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart7_config = {
	.ccm_reg		= CCM_CCGR5_RAW,
	.ccm_mask		= CCM_CGn(13),
	.lpuart_reg		= LPUART7,
	.rx_input_reg	= IOMUXC_LPUART7_RX_SELECT_INPUT,
	.rx_input_daisy = 1,
	.rx_pin			= 28,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart7_rx_buffer,
	.rx_buffer_size = LPUART7_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= IOMUXC_LPUART7_TX_SELECT_INPUT,
	.tx_input_daisy = 1,
	.tx_pin			= 29,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart7_tx_buffer,
	.tx_buffer_size = LPUART7_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART7,
};

// Serial 5
DTCM uint8_t lpuart8_tx_buffer[LPUART8_TX_BUFFER_SIZE] = {0};
DTCM uint8_t lpuart8_rx_buffer[LPUART8_RX_BUFFER_SIZE] = {0};

lpuart_config_t lpuart8_config = {
	.ccm_reg		= CCM_CCGR6_RAW,
	.ccm_mask		= CCM_CGn(7),
	.lpuart_reg		= LPUART8,
	.rx_input_reg	= IOMUXC_LPUART8_RX_SELECT_INPUT,
	.rx_input_daisy = 1,
	.rx_pin			= 21,
	.rx_pin_mux		= IOMUXC_ALT2,
	.rx_buffer		= lpuart8_rx_buffer,
	.rx_buffer_size = LPUART8_RX_BUFFER_SIZE,
	.rx_buffer_head = 0,
	.rx_buffer_tail = 0,
	.tx_input_reg	= IOMUXC_LPUART8_TX_SELECT_INPUT,
	.tx_input_daisy = 1,
	.tx_pin			= 20,
	.tx_pin_mux		= IOMUXC_ALT2,
	.tx_buffer		= lpuart8_tx_buffer,
	.tx_buffer_size = LPUART8_TX_BUFFER_SIZE,
	.tx_buffer_head = 0,
	.tx_buffer_tail = 0,
	.irq_num		= IRQ_LPUART8,
};
