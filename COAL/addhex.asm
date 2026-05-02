;---------------------------------------------------
; Program: Add two 64-bit numbers
;---------------------------------------------------

[org 0x100] 
    jmp start        

;-----------------------------------------
; Data Section 
;-----------------------------------------
num1    dd 0x95394880, 0x95394880     ;left=low 32 bits, right= high 32 bits
num2    dd 0xB97B5A08, 0xB97B5A08   
result  dd 0,0                     

;-----------------------------------------
; Code Section
;-----------------------------------------
start:
    ; Add low 32 bits (stored as two words)
    mov ax, [num1]          ; AX = 0x4880
    add ax, [num2]          ; AX = 0x4880 + 0x5A08
    mov [result], ax        ; result[0..1] = A2 88
			    ; CF=0

    mov ax, [num1+2]        ; AX = 0x9539
    adc ax, [num2+2]        ; 0x9539 + 0xB97B + CF(0)
    mov [result+2], ax      ; result[2..3] = 4E B4
			    ; CF=1

    ; Add high 32 bits
    mov ax, [num1+4]        ; AX = 0x4880
    adc ax, [num2+4]	    ; 0x4880 + 0x5A08 + CF(1)
    mov [result+4], ax	    ; result[4..5] = A2 89
			    ; CF=0

    mov ax, [num1+6]        ; AX = 0x9539
    adc ax, [num2+6]	    ; 0x9539 + 0xB97B + CF(0)
    mov [result+6], ax      ; result[6..7] = 4E B4
			    ; CF=1

    ; Exit program
    mov ax, 0x4C00
    int 0x21

