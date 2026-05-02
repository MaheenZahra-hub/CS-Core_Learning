 [org 0x0100]
mov cl, 10
mov dl, 0
mov al, 0
l1:
	mov al, dl
	inc dl
	dec cl
jnz l1
mov ax, 0x4c00
int 0x21
