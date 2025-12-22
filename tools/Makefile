# Makefile for the tools

.PHONY: all clean monitor

all: monitor


monitor: monitor.c
	bear -- $(CC) -o monitor monitor.c


clean:
	rm -f monitor
