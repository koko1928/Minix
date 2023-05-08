#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_BUFFER_SIZE 16

typedef struct {
    uint8_t buffer[KEYBOARD_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
} KeyboardBuffer;

void keyboard_init(void);
void keyboard_handler(void);
void keyboard_enable_interrupts(void);
uint8_t keyboard_get_scancode(void);
char keyboard_get_char(void);
int keyboard_buffer_empty(void);

#endif /* KEYBOARD_H */
