#ifndef KERNEL_H
#define KERNEL_H

/* プロトタイプ宣言 */
void init_kernel();
void start_kernel();
void stop_kernel();
void handle_interrupt(int interrupt_number);

#endif /* KERNEL_H */

