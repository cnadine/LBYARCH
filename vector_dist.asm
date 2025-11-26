section .text
bits 64
default rel
global vector_dist

vector_dist:

    ; Setup stack frame
    push rbp
    mov rbp, rsp
    add rbp, 16

    mov r10, [rbp + 32]   ; Load y2 to r10
    mov r11, [rbp + 40]   ; Load z to r11

    mov rsi, 0            ; Counter

.compute:
    movsd xmm0, [r8 + rsi*8]    ; x2[i]
    subsd xmm0, [rdx + rsi*8]   ; dx = x2[i] - x1[i]

    movsd xmm1, [r10 + rsi*8]   ; y2[i]
    subsd xmm1, [r9 + rsi*8]    ; dy = y2[i] - y1[i]

    mulsd xmm0, xmm0            ; dx^2
    mulsd xmm1, xmm1            ; dy^2

    addsd xmm0, xmm1            ; dx^2 + dy^2

    sqrtsd xmm0, xmm0           ; sqrt(dx^2 + dy^2)

    movsd [r11 + rsi*8], xmm0   ; z[i] = sqrt(...)

    inc rsi
    cmp rsi, rcx
    jl .compute

.end:
    pop rbp
    ret