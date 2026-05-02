; Binary Search in COM style
; AX = 1 if found
; AX = 0 if not found

[org 0x0100]

start:
    ; -----------------------------
    ; Setup array, size, and key
    ; -----------------------------
    mov cx, 0          ; low = 0
    mov dx, 4          ; high = n-1 = 4 (since 5 elements)
    mov si, 30         ; key = 30

search_loop:
    cmp cx, dx
    jg not_found       ; if low > high -> not found

    ; mid = (low+high)/2
    mov bx, cx
    add bx, dx
    shr bx, 1          ; BX = mid index

    ; get arr[mid]
    mov di, bx
    shl di, 1          ; word index → byte offset
    mov ax, [arr+di]   ; AX = arr[mid]

    cmp ax, si
    je found
    jl go_right        ; if arr[mid] < key → go right

    ; go left
    dec bx
    mov dx, bx
    jmp search_loop

go_right:
    inc bx
    mov cx, bx
    jmp search_loop

found:
    mov ax, 1
    jmp exit

not_found:
    mov ax, 0

exit:
    mov ah, 0x4c
    int 0x21

; -----------------------------
; Data (comes after code in .COM)
; -----------------------------
arr dw 10, 20, 30, 40, 50
