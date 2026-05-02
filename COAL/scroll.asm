[org 0x100]
start:
scroll_loop:

push ax
push bx
push cx
push dx
mov ah, 06h
mov al, 3
mov bh, 07h
mov cx, 0
mov dx, 184Fh
int 10h
pop dx
pop cx
pop bx
pop ax
call Delay1sec

push ax
push bx
push cx
push dx
mov ah, 07h
mov al, 3
mov bh, 07h
mov cx, 0
mov dx, 184Fh
int 10h
pop dx

pop cx
pop bx
pop ax
call Delay1sec
jmp scroll_loop

Delay1sec:
push cx
push bx
mov cx, 500
.outer:
mov bx, 500
.inner:
dec bx
jnz .inner
loop .outer
pop bx
pop cx
ret