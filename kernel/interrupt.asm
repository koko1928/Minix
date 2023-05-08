section .text

global interrupt_handler

interrupt_handler:
  pushad            ; push general-purpose registers onto the stack

  ; Code to handle interrupt goes here

  popad             ; restore general-purpose registers from the stack
  iretd             ; return from interrupt, including popping flags
