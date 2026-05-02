[org 0x100]        ; .COM program start

    mov ax, 5      ; number
    mov bx, ax     ; copy to BX
    mul bx         ; AX = AX * BX (unsigned multiply)

    ; now AX has the square of 5 (25)

    mov ah, 0x4C   ; exit program
    int 0x21