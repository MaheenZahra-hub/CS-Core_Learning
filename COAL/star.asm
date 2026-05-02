[org 0x100]

ATTR   equ 0x0F

start:
    mov ax, 0xb800
    mov es, ax

main_loop:
    mov cx, 0        ; left star position
    mov dx, 79       ; right star position

.move_in:
    push cx
    push dx
    call ClearScreen

    pop dx
    pop cx

    call DrawStars
    push cx
    push dx
    call Delay
    pop dx
    pop cx

    inc cx
    dec dx
    cmp cx, dx
    jbe .move_in

.move_out:
    push cx
    push dx
    call ClearScreen
    pop dx
    pop cx

    call DrawStars
    push cx
    push dx
    call Delay
    pop dx
    pop cx

    dec cx
    inc dx
    cmp cx, 0

    jmp main_loop

DrawStars:
    push ax
    push bx

    ; left star
    mov bx, cx
    shl bx, 1
    mov byte [es:bx], '*'
    mov byte [es:bx+1], ATTR

    ; right star
    mov bx, dx
    shl bx, 1
    mov byte [es:bx], '*'
    mov byte [es:bx+1], ATTR

    pop bx
    pop ax
    ret

ClearScreen:
    push ax
    push di
    push cx

    mov di, 0
    mov cx, 80*25
.cls:
    mov word [es:di], 0x0720
    add di, 2
    loop .cls

    pop cx
    pop di
    pop ax
    ret


Delay:
    push cx
    push bx

    mov cx, 500
.d1:
    mov bx, 500
.d2:
    dec bx
    jnz .d2
    loop .d1

    pop bx
    pop cx
    ret