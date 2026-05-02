;It repeatedly replaces AX with the number of 1-bits in it until AX becomes 1, counting how many iterations that takes.


[org 0x0100]
    mov ax, 0C5A3h      ; Set initial non-zero value in AX 
    mov bx, 0           ; Initialize the iteration counter 
start:
    ; Check termination condition
    cmp ax, 1
    je done             ; If AX = 1, jump to the end
    ; Setup for Inner Bit Counting Loop
    mov cx, 0           ; Initialize the 1s count (CX will store the result)
    mov dx, 16          ; Set loop counter to 16, as AX is a 16-bit register
count_bits:
    ; Shift Right and Check
    shr ax, 1           ; Right shift AX by 1
    ; Conditional Increment
    jc bit_is_one       ; Jump if Carry Flag is set
    jmp next_bit        ; If CF=0, skip the increment

bit_is_one:
    inc cx              ; Increment the 1s count (CX)
    next_bit:
    ; Loop Control
    dec dx              ; Decrement the bit counter
    jnz count_bits      ; Jump back to count_bits if DX is not zero
    ; --- End of Inner Loop ---
    mov ax, cx          ; Store the total count of 1s (CX) back into AX
    inc bx              ; Increment the main iteration counter (BX)
    jmp start           ; Restart the main loop with the new value in AX

done:
    mov ax, 0x4c00
    int 0x21
