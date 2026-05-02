[org 0x0100]

jmp start

message:      db 'i am a student of coal',0
result_msg:   db 'Count of a:',0
digit:        db '0',0
count_a:      dw 0


clrscr:
    push es
    mov ax,0xb800
    mov es,ax
    xor di,di
    mov ax,0x0720
    mov cx,2000
    rep stosw
    pop es
    ret

countA:
    push bp
    mov bp,sp

    mov si,[bp+4]   ; SI points to string
    xor cx,cx       ; counter = 0

count_loop:
    lodsb           ; AL = [SI], SI++
    cmp al,0
    je done_count

    cmp al,'a'
    jne count_loop

    inc cx          ; found an 'a'
    jmp count_loop

done_count:
    mov [count_a],cx
    pop bp
    ret 2


printstr:
    push bp
    mov bp,sp

    push ax
    push cx
    push si
    push di
    push es

    mov si,[bp+4]   ; SI = string pointer

    ; calculate length
    mov cx,0ffffh
    xor al,al
    repne scasb
    xor cx,cx

len_loop:
    cmp byte [si],0
    je len_done
    inc si
    inc cx
    jmp len_loop
len_done:

    ; cx = length
    mov ax,0xb800
    mov es,ax

    mov ax,[bp+8]      ; y
    mov bl,80
    mul bl             ; ax = y*80
    add ax,[bp+10]     ; ax += x
    shl ax,1           ; convert to video offset
    mov di,ax

    mov si,[bp+4]      ; string start
    mov ah,[bp+6]      ; attribute in AH

print_loop:
    lodsb
    cmp al,0
    je print_done
    stosw
    loop print_loop

print_done:
    pop es
    pop di
    pop si
    pop cx
    pop ax
    pop bp
    ret 8


start:
    call clrscr

    mov ax,message
    push ax
    call countA

    ; convert the result to ASCII (single digit)
    mov ax,[count_a]
    add al,'0'
    mov [digit],al

    ; print "Count of a: "
    mov ax,5
    push ax        ; x
    mov ax,5
    push ax        ; y
    mov ax,1
    push ax        ; attribute
    mov ax,result_msg
    push ax
    call printstr

    ; print digit
    mov ax,20
    push ax
    mov ax,5
    push ax
    mov ax,1
    push ax
    mov ax,digit
    push ax
    call printstr

    mov ax,0x4c00
    int 21h
