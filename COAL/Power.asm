[org 0x0100]
jmp start

base:    db  3       ; base number
power:   db  3       ; exponent
result:  db  0       ; final result stored here

start:
    mov bl, [base]    ; base into BL
    mov cl, [power]   ; power into CL
    mov al, 1         ; AL = 1

Power:
    cmp cl, 0         ; if power = 0, we’re done
    je done_power

    mov bh, bl        ; copy base into BH 
    call multiply
    dec cl            ; power = power - 1
    jmp Power         ; loop until power becomes 0

done_power:
    mov [result], al 
    mov ax, 0x4C00
    int 0x21

multiply:
    mov dl, bh        ; copy multiplier which is base
    mov ah, al        ; copy multiplicand which is right now result
    mov al, 0         ; clear result

mul_loop:
    shr dl, 1         ; shr bit of DL into carry flag
    jnc skip_add      ; if carry=0, skip addition
    add al, ah        ; if bit=1, add multiplicand to result
skip_add:
    shl ah, 1         ; shift multiplicand left
    dec ch            ; decrease bit counter
    jnz mul_loop      ; repeat for all bits
    ret
