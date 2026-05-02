[org 0x100]      

    mov ax, 1234h   ; put a known word in AX
    mov [200h], ax  ; store it at memory 0200h

    mov ah, 4Ch     ; exit program
    int 21h
