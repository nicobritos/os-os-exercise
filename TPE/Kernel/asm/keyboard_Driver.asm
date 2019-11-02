GLOBAL key_pressed
GLOBAL get_key

section .text

get_key:
  push rbp
  mov rbp,rsp

  mov rax, 0
  in al,64h   ; Get the status byte from the keyboard
  test al, 01h
  jz return 
  in al, 60h

  return: 
  mov rsp,rbp
  pop rbp
  ret
