#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <termios.h>

#define BUFFER_SIZE 512

int print_usage(const char *msg) {
	if (msg) {
		fprintf(stderr, "Error: %s\n", msg);
	}
	fprintf(stderr, "Usage: monitor <-b baudrate> <device>\n");
	return EXIT_FAILURE;
}

// usage: monitor <-b baudrate> <device>
int main(int argc, char **argv) {
	if (argc < 2) {
		return print_usage("Not enough arguments");
	}

	uint32_t baudrate = 115200u; // default baudrate

	if (argc == 4) {
		if (strcmp(argv[1], "-b") != 0) {
			return print_usage("Invalid option");
		}
		baudrate = strtoul(argv[2], NULL, 10);
		if (baudrate == 0) {
			return print_usage("Invalid baudrate");
		}
	}

	const char *device = argv[argc - 1];
	int fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0) {
		perror("Failed to open device");
		return EXIT_FAILURE;
	}

	// Configure serial port settings
	struct termios options;
	tcgetattr(fd, &options);
	cfsetispeed(&options, baudrate);
	cfsetospeed(&options, baudrate);
	options.c_cflag |= (CLOCAL | CREAD); // Enable receiver, ignore modem control lines
	options.c_cflag &= ~PARENB;          // No parity
	options.c_cflag &= ~CSTOPB;          // 1 stop bit
	options.c_cflag &= ~CSIZE;           // Clear data bits setting
	options.c_cflag |= CS8;              // 8 data bits
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input
	options.c_oflag &= ~OPOST;           // Raw output
	tcsetattr(fd, TCSANOW, &options);

	uint8_t rx_buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	uint8_t tx_buffer[BUFFER_SIZE];
	ssize_t bytes_written;

	while (1) {
		// Read from serial port
		bytes_read = read(fd, rx_buffer, sizeof(rx_buffer) - 1);
		if (bytes_read > 0) {
			rx_buffer[bytes_read] = '\0'; // Null-terminate the string
			printf("RX: ");
			for (ssize_t i = 0; i < bytes_read; i++) {
				printf("%.02x ", rx_buffer[i]);
			}
			printf("\n");
			fflush(stdout);
		}

		// Check for user input
		int input = getc(stdin);
		if (input != EOF) {
			tx_buffer[0] = (uint8_t)input;
			bytes_written = write(fd, tx_buffer, 1);
			if (bytes_written < 0) {
				perror("Failed to write to device");
				close(fd);
				return EXIT_FAILURE;
			}
		}
	}

	close(fd);

	return EXIT_SUCCESS;
}
