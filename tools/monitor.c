#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <termios.h>
#include <signal.h>

#define BUFFER_SIZE 512

void print_bits(uint8_t byte) {
	for (int i = 7; i >= 0; i--) {
		printf("%c", (byte & (1 << i)) ? '1' : '0');
	}
	printf(" '%c'", (byte >= 32 && byte <= 126) ? byte : '`');
}

int print_usage(const char *msg) {
	if (msg) {
		fprintf(stderr, "Error: %s\n", msg);
	}
	fprintf(stderr, "Usage: monitor <-b baudrate> <device>\n");
	return EXIT_FAILURE;
}

void simple_echo();
void ascii_check();

static struct termios g_orig_termios;
static int g_orig_fl = -1;
static int g_raw_enabled = 0;

int enable_raw_mode(void)
{
    if (g_raw_enabled)
        return 0;

    // Save original termios
    if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
        return -1;

    // Save original fd flags
    g_orig_fl = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (g_orig_fl == -1)
        return -1;

    // Put stdin in non-blocking mode (works for TTYs, pipes, sockets)
    if (fcntl(STDIN_FILENO, F_SETFL, g_orig_fl | O_NONBLOCK) == -1)
        return -1;

    // If stdin is not a TTY (pipe/file), termios does not apply; we're done.
    if (!isatty(STDIN_FILENO)) {
        g_raw_enabled = 1;
        return 0;
    }

    struct termios raw = g_orig_termios;

    // Non-canonical mode: deliver input immediately, not line-buffered
    raw.c_lflag &= ~(ICANON | ECHO);

    // Optional: disable signal generation from Ctrl-C/Ctrl-Z/Ctrl-\.
    // If you want Ctrl-C to still generate SIGINT, LEAVE ISIG enabled.
    // raw.c_lflag &= ~(ISIG);

    // Make read() return immediately:
    // - VMIN=0, VTIME=0 => read returns 0 if no bytes are available
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;

    // Apply settings now
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) {
        // Best effort: restore fd flags on failure
        (void)fcntl(STDIN_FILENO, F_SETFL, g_orig_fl);
        return -1;
    }

    g_raw_enabled = 1;
    return 0;
}

void disable_raw_mode(int signum)
{
    if (!g_raw_enabled)
        return;

    int rc = 0;

    // Restore termios if it was a TTY
    if (isatty(STDIN_FILENO)) {
        if (tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios) == -1)
            rc = -1;
    }

    // Restore original fd flags
    if (g_orig_fl != -1) {
        if (fcntl(STDIN_FILENO, F_SETFL, g_orig_fl) == -1)
            rc = -1;
    }

    g_raw_enabled = 0;

	printf("Exiting...\n");

	exit(EXIT_SUCCESS);
}

static int fd = -1;

// usage: monitor <-b baudrate> <device>
int main(int argc, char **argv) {
	signal(SIGINT, disable_raw_mode); // ensure raw mode is disabled on Ctrl+C
	
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
	fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
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

	enable_raw_mode();



	simple_echo();



	disable_raw_mode(0);

	close(fd);

	return EXIT_SUCCESS;
}

void simple_echo() {
	uint8_t rx_buffer[BUFFER_SIZE];
	uint8_t tx_buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	ssize_t bytes_written;

	while (1) {
		// read stdin
		bytes_read = read(STDIN_FILENO, tx_buffer, 1);

		// send stdin to device
		if (bytes_read > 0) {
			bytes_written = write(fd, tx_buffer, bytes_read);
			if (bytes_written < 0) {
				perror("Failed to write to device");
				return;
			} else if (bytes_written > 0) {
				printf("<-- ");
				print_bits(tx_buffer[0]);
				printf("\n");
			}
		}

		// read from device
		bytes_read = read(fd, rx_buffer, BUFFER_SIZE);
		if (bytes_read > 0) {
			for (ssize_t i = 0; i < bytes_read; i++) {
				printf("--> ");
				print_bits(rx_buffer[i]);
				printf("\n");
			}
		}
	}
}

void ascii_check() {
	uint8_t rx_buffer[BUFFER_SIZE];
	uint8_t tx_buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	ssize_t bytes_written;
	static int ascii_curr = 1;

	while (1) {
		// read stdin
		tx_buffer[0] = ascii_curr++; // cycle through ASCII characters
		bytes_read = 1;
		if (ascii_curr == 255) {
			return;
		}

		// send stdin to device
		if (bytes_read > 0) {
			bytes_written = write(fd, tx_buffer, bytes_read);
			if (bytes_written < 0) {
				perror("Failed to write to device");
				return;
			} else if (bytes_written > 0) {
				printf("\n <-- ");
				print_bits(tx_buffer[0]);
			}
		}

		usleep(100000); // 10ms delay

		// read from device
		bytes_read = read(fd, rx_buffer, BUFFER_SIZE);
		if (bytes_read > 0) {
			for (ssize_t i = 0; i < bytes_read; i++) {
				printf(" --> ");
				print_bits(~rx_buffer[i]);
			}
		}
	}

	printf("\n");
}
