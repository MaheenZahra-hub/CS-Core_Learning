[org 0x100]       ; COM program start

    mov ax, 0x1254
    mov bx, 0x0FFF

    ; (a) add ax, 0xEDAB
    add ax, 0xEDAB
    ; check flags in debugger here

    ; (b) add ax, bx
    add ax, bx
    ; check flags

    ; (c) add bx, 0xF001
    add bx, 0xF001
    ; check flags

    mov ah, 0x4C
    int 0x21        ; exit program
