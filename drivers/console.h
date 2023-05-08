#ifndef CONSOLE_H
#define CONSOLE_H

#include <stddef.h>
#include <stdint.h>

void console_init(void);
void console_putchar(char c);
void console_write(const char *str, size_t len);
void console_writestring(const char *str);

#endif /* CONSOLE_H */
