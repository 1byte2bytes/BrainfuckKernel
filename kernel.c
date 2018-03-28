#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0x7;

volatile uint16_t* terminal_buffer = (uint16_t*)0xB8000;

void term_putentry(char c, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = (uint16_t)c | (uint16_t)terminal_color << 8;
}

void term_putchar(char c) {
	term_putentry(c, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT) {
			terminal_row = 0;
		}
	}
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len]) { len++; }
	return len;
}

/* -------------------------------------------------------- */

extern void brainfuck_main();

void kernel_main() {
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = (uint16_t)' ' | (uint16_t)terminal_color << 8;
		}
	}
	brainfuck_main();
}