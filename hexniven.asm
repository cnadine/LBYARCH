%include "io64.inc"
section .data
    prompt_num db "Input number: ", 0
    prompt db "Do you want to continue (Y/N)?", 0
    
    msg_dec db "Decimal equivalent: ", 0
    msg_hex db "Hex digits: ", 0
    msg_sum db "Sum of digits: ", 0
    msg_quotient db "Quotient: ", 0
    msg_rem db "Remainder: ", 0
    msg_yes db "HexNiven Number: Yes", 0
    msg_no db "HexNiven Number: No", 0
    
    perror db "Error: Your input hex is invalid!", 0
    perror_cont db "Error: Invalid input. Please only enter Y or N!", 0
    uinput db 'Y'

section .bss
    hexinput resb 64    ; 64 max hex nlng muna (one byte kasi kahit 4 bits isang hex, get_char is 1 byte)
    cur_hex_digit resb 1    ; Current hex digit
    cur_dec_value resq 1    ; Current decimal equivalent value
    hex_sum resq 1          ; Sum of hex digits

section .text
global main
main:
    mov rbp, rsp; for correct debugging
    
    init:
        ;Ask for user input
        PRINT_STRING prompt_num
        
        ;Reset
        xor rsi, rsi
        lea rsi, hexinput ; put address ni hexinput kay rsi, free af kasi one byte one address, inc nlng mamaya
        xor rax, rax
        xor rbx, rbx
        mov [hex_sum], rax          ;set to 0
        mov [cur_dec_value], rax    ;set to 0
        
        jmp mainloop
        
    mainloop:
        GET_CHAR cur_hex_digit
        movzx rdi, byte[cur_hex_digit]

        ; Big compare to check for valid hex, note order is important because ASCII stuff
        cmp byte[cur_hex_digit], 10
        je evaluate_hexniven
   
        cmp byte[cur_hex_digit], '0'
        jl not_hex
        cmp byte[cur_hex_digit], '9'
        jle hex_0_9
    
        cmp byte[cur_hex_digit], 'A'
        jl not_hex
        cmp byte[cur_hex_digit], 'F'
        jle hex_A_F
    
        cmp byte[cur_hex_digit], 'a'
        jl not_hex
        cmp byte[cur_hex_digit], 'f'
        jle hex_a_f
        cmp byte[cur_hex_digit], 'g'
        jge not_hex
        
    process:
        ; Hex to decimal conversion
        imul rax, [cur_dec_value], 16   ;rax <- dec*16
        mov [cur_dec_value], rax
        add [cur_dec_value], rdi
        
        ; Store hex for output
        mov rbx, [cur_hex_digit]
        mov [rsi], rbx
        inc rsi
        mov byte[rsi], ','
        inc rsi
        
        ; Add hex number to current sum
        add [hex_sum], rdi
        
        jmp mainloop
    
    not_hex:
        PRINT_STRING perror
        NEWLINE
        jmp skip_to_newline
    
    hex_0_9:
        sub rdi, '0'
        jmp process
    
    hex_A_F: 
        sub rdi, 'A'
        add rdi, 10
        jmp process
        
    hex_a_f:
        sub rdi, 'a'
        add rdi, 10
        jmp process
            
    skip_to_newline:
        GET_CHAR cur_hex_digit
        cmp byte[cur_hex_digit], 10
        jne skip_to_newline
        jmp await_continue
    
    evaluate_hexniven: 
        xor rdx, rdx
        mov rax, [cur_dec_value]
        idiv qword[hex_sum]
   
    print_output: 
        PRINT_STRING msg_dec
        PRINT_DEC 8, cur_dec_value
        NEWLINE
        
        ; Remove last comma 
        dec rsi
        mov byte [rsi], 0

        PRINT_STRING msg_hex
        PRINT_STRING hexinput
        NEWLINE
        
        PRINT_STRING msg_sum
        PRINT_DEC 8, hex_sum
        NEWLINE
        
        PRINT_STRING msg_quotient
        PRINT_DEC 8, rax
        NEWLINE
        
        PRINT_STRING msg_rem
        PRINT_DEC 8, rdx
        NEWLINE
        
        cmp rdx, 0
        je is_hexniven
        PRINT_STRING msg_no
        NEWLINE
        
        jmp await_continue
        
    is_hexniven:
        PRINT_STRING msg_yes
        NEWLINE
        
    await_continue:
        PRINT_STRING prompt
        get_char:
            GET_CHAR uinput
        cmp byte[uinput], 10
        je err_uinput
        cmp byte[uinput], 'N'
        je END
        cmp byte[uinput], 'Y'
        je consume_enter
        
        jmp get_char
    
    err_uinput: 
        PRINT_STRING perror_cont
        NEWLINE
        jmp await_continue
        
    consume_enter: 
        GET_CHAR uinput
        cmp byte[uinput], 10
        je init
        
    END: nop
    
    xor rax, rax
    ret
