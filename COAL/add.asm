;---------------------------------------------------
; Program: Add two 64-bit numbers
;---------------------------------------------------

[org 0x100] 
    jmp start       

;-----------------------------------------
; Data Section
;-----------------------------------------
num1    dd 0x95394880, 0x95394880   
num2    dd 0x7B9B5A08, 0x7B9B5A08   
result  dd 0,0                     

;-----------------------------------------
; Code Section
;-----------------------------------------
start:
    ; Add low 32 bits (stored as two words)
    mov ax, [num1]          ; AX = 0x4880
    add ax, [num2]          ; AX = 0x4880 + 0x5A08 = 0xA288
    mov [result], ax        ; store AX → result= 88 A2
			    ; CF=0

    mov ax, [num1+2]         ; AX = 0x9539
    adc ax, [num2+2]         ; 0x9539 + 0x7B9B + CF(0) = 0x110D4
    mov [result+2], ax	     ; store AX → 0x10D4
			     ; CF=1

    ; Add high 32 bits
    mov ax, [num1+4]        ; AX = 0x4880
    adc ax, [num2+4]        ; 0x4880 + 0x5A08 + CF(1) = 0xA289
    mov [result+4], ax      ; store = 0xA289
			    ; CF=0

    mov ax, [num1+6]        ; AX = 0x9539
    adc ax, [num2+6]        ; 0x9539 + 0x7B9B + CF(0) = 0x110D4
    mov [result+6], ax      ; store = 0x10D4
			    ; CF=1

    ; Exit program
    mov ax, 0x4C00
    int 0x21

