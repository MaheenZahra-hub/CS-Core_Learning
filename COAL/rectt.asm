[org 0x0100]
jmp start

clrscr:
push es
push ax
push si
push di
mov ax,0xb800
mov di,0
mov es,ax
mov ax,0x0720
mov cx,2000
cld
rep stosw
pop di
pop si
pop ax
pop es
ret 

print_rect:

push bp
mov bp, sp
sub sp,2    
mov word [bp-2],0
push es
push ax
push cx
push di
push dx
mov ax, 0xb800
mov es, ax          
mov al, 80          
mul byte [bp+10]     
add ax, [bp+12]       
shl ax, 1           
mov di,ax           
mov [bp-2],di
mov dx,[bp+6]
sub dx,[bp+12]
mov cx,dx           
inc cx
mov ah, [bp+8]      
mov al,'#'          
call top
mov di,[bp-2]
mov dx,[bp+4]   
sub dx,[bp+10]  
mov cx,dx
inc cx
mov al,'#'
mov ah,[bp+8]
call side
mov al, 80          
mul byte [bp+4]     
add ax, [bp+12]     
shl ax, 1           
mov di,ax
add di,2
mov dx,[bp+6]
sub dx,[bp+12]
mov cx,dx
mov ah, [bp+8]      
mov al,'#'           
call top 
mov al, 80          
mul byte [bp+10]    
add ax, [bp+6]      
shl ax, 1           
mov di,ax 
mov dx,[bp+4]
sub dx,[bp+10]
mov cx,dx
inc cx
mov al,'#'
mov ah,[bp+8]
call side
pop dx
pop di
pop cx
pop ax
pop es
add sp,2
pop bp
ret 10
 
top:
cld
rep stosw
ret 

side:
mov [es:di],ax
add di,160
loop side
sub di,160
ret 

start:
call clrscr 
mov ax,5  
push ax
mov ax,2  
push ax
mov ax,0X1E  
push ax 
mov ax,25  
push ax
mov ax,8  
push ax 
call print_rect 
mov ax,30  
push ax
mov ax,10 
push ax
mov ax,0x4E   
push ax
 
mov ax,55 
push ax
mov ax,17  
push ax 
call print_rect
mov ax,60  
push ax
mov ax,15  
push ax
mov ax,0x4C   
push ax
mov ax,78  
push ax
mov ax,23  
push ax 
call print_rect

mov ax,0x4c00
int 0x21