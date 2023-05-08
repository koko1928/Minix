#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "console.h"
#include "io.h"

#define VGA_BUFFER_ADDRESS 0xB8000

static uint16_t* console_buffer;
static size_t console_row;
static size_t console_column;
static uint8_t console_color;

static void console_move_cursor(void) {
    uint16_t cursor_location = console_row * 80 + console_column;

    outb(0x3D4, 14);
    outb(0x3D5, cursor_location >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_location);
}

void console_init(void) {
    console_buffer = (uint16_t*) VGA_BUFFER_ADDRESS;
    console_row = 0;
    console_column = 0;
    console_color = CONSOLE_COLOR_LIGHT_GREY << 4 | CONSOLE_COLOR_BLACK;

    for (size_t y = 0; y < 25; y++) {
        for (size_t x = 0; x < 80; x++) {
            console_buffer[y * 80 + x] = (uint16_t) ' ' | console_color;
        }
    }

    console_move_cursor();
}

void console_putc(char c) {
    switch (c) {
        case '\n':
            console_row++;
            console_column = 0;
            break;
        case '\r':
            console_column = 0;
            break;
        default:
            console_buffer[console_row * 80 + console_column] = (uint16_t) c | console_color;
            console_column++;
            break;
    }

    if (console_column >= 80) {
        console_row++;
        console_column = 0;
    }

    if (console_row >= 25) {
        for (size_t y = 0; y < 24; y++) {
            for (size_t x = 0; x < 80; x++) {
                console_buffer[y * 80 + x] = console_buffer[(y + 1) * 80 + x];
            }
        }

        for (size_t x = 0; x < 80; x++) {
            console_buffer[24 * 80 + x] = (uint16_t) ' ' | console_color;
        }

        console_row = 24;
    }

    console_move_cursor();
}

void console_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        console_putc(data[i]);
    }
}

void console_printf(const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    int result = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    console_write(buffer, result);
}
