[org 0x0100]
jmp start

num:    db 5         ; number whose factorial we’ll calculate
result: db 0         ; will store the factorial result


; MAIN PROGRAM

start:
    mov al, [num]    ; load number(n)
    push ax          ; push n to stack
    call factorial   ; call factorial subroutine

    pop ax           ; get factorial result back
    mov [result], al ; store in memory

    mov ax, 0x4C00   ; exit program
    int 0x21


; FACTORIAL SUBROUTINE

factorial:
    pop cx           ; save return address
    pop bl           ; get number (n) into BL

    mov al, 1        ; start result = 1

fact_loop:
    cmp bl, 1        ; stop when n == 1
    je fact_done

    mov bh, bl       ; copy current n
    dec bl           ; n = n - 1
    push ax          ; push current result
    push bh          ; push current n
    call multiply    ; multiply (result * n)
    pop ax           ; get new result in AL
    jmp fact_loop

fact_done:
    push al          ; push final factorial result
    push cx          ; restore return address
    ret


; MULTIPLY SUBROUTINE

multiply:
    pop dx           ; pop return address
    pop bh           ; get multiplier
    pop al           ; get multiplicand

    mov bl, bh       ; BL = multiplier
    mov bh, al       ; BH = multiplicand
    mov al, 0        ; clear result register

mul_loop:
    cmp bl, 0        ; if multiplier = 0, done
    je mul_done
    add al, bh       ; result += multiplicand
    dec bl           ; multiplier--
    jmp mul_loop

mul_done:
    push al          ; push final product
    push dx          ; restore return address
    ret