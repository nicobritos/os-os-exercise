GLOBAL div0exc

section .text

div0exc:
  mov rax, 0
  div rax
  ret
