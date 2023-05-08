#include <stdint.h>
#include "keyboard.h"
#include "ports.h"
#include "interrupts.h"

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_SCANCODE_BUFFER_SIZE 64

static char keyboard_scancode_buffer[KEYBOARD_SCANCODE_BUFFER_SIZE];
static int keyboard_scancode_buffer_position = 0;

static char keyboard_layout[128] = {
  0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
  'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

void keyboard_handler() {
  uint8_t scancode = port_byte_in(KEYBOARD_DATA_PORT);
  if (keyboard_scancode_buffer_position < KEYBOARD_SCANCODE_BUFFER_SIZE) {
    keyboard_scancode_buffer[keyboard_scancode_buffer_position++] = scancode;
  }
}

void keyboard_initialize() {
  register_interrupt_handler(IRQ1, keyboard_handler);
}

int keyboard_has_scancode() {
  return keyboard_scancode_buffer_position > 0;
}

char keyboard_get_scancode() {
  if (!keyboard_has_scancode()) {
    return '\0';
  }
  char scancode = keyboard_scancode_buffer[0];
  for (int i = 1; i < keyboard_scancode_buffer_position; i++) {
    keyboard_scancode_buffer[i - 1] = keyboard_scancode_buffer[i];
  }
  keyboard_scancode_buffer_position--;
  return scancode;
}

char keyboard_get_char() {
  char scancode = keyboard_get_scancode();
  if (scancode >= 0 && scancode < 128) {
    return keyboard_layout[scancode];
  } else {
    return '\0';
  }
}
