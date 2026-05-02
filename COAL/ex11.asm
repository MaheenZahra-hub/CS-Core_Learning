[org 0x100]

    mov dl, '0'      ; start from ASCII '0'
    mov cx, 10       ; loop counter

next:
    mov ah, 2        ; DOS print char function
    int 21h          ; print DL
    inc dl           ; move to next digit
    loop next        ; repeat until CX=0

    mov ah,4Ch
    int 20h          ; terminate program
