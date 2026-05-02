; quiz_clean_fixed.asm - NASM .COM quiz (fixed: forced near jumps where needed)
org 100h

section .data
MSG_WELCOME     db '.....WELCOME TO OUR QUIZ PORTAL.....$'
MSG_RULES1      db 'Follow the Rules:$'
MSG_RULES2      db '1) +1 for every correct answer.$'
MSG_RULES3      db '2) -1 for every wrong answer.$'
MSG_START       db 'Press Enter to start the quiz: $'
MSG_PROMPT      db 'Your answer (a/b/c): $'
MSG_INVALID     db 'Invalid choice. Press a, b or c.$'
MSG_CORRECT     db '--> CORRECT ANSWER.$'
MSG_WRONG       db '--> WRONG ANSWER.$'
MSG_SCORE       db 'Your Quiz is completed. Assessing your Score......$'
MSG_RESULT      db '=> Result: $'
MSG_CORRECT_CNT db '1> Correct Answers: $'
MSG_WRONG_CNT   db '2> Incorrect Answers: $'
MSG_THANKS      db 'Thank you for attempting the Quiz.$'
MSG_BLANK       db ' $'                ; small blank to avoid weird concatenation if needed

; --- Questions and option strings (each ends with $)
q1  db '1. Identify a Bird:$'
q1o db '   a) Crow$'
q1o2 db '   b) Dog$'
q1o3 db '   c) Car$'

q2  db '2. Which is an odd number?:$'
q2o db '   a) 10$'
q2o2 db '   b) 11$'
q2o3 db '   c) 12$'

q3  db '3. A place where you go to see lots of animals?:$'
q3o db '   a) School$'
q3o2 db '   b) Hospital$'
q3o3 db '   c) Zoo$'

q4  db '4. What do caterpillars turn into?:$'
q4o db '   a) Frog$'
q4o2 db '   b) Butterflies$'
q4o3 db '   c) Dragon fly$'

q5  db '5. How many continents are there in the world?:$'
q5o db '   a) 7$'
q5o2 db '   b) 10$'
q5o3 db '   c) 4$'

q6  db '6. Who was the first man to step on the moon?:$'
q6o db '   a) Dracula$'
q6o2 db '   b) John Cena$'
q6o3 db '   c) Neil Armstrong$'

q7  db '7. A scientist who studies rock is called:$'
q7o db '   a) Writer$'
q7o2 db '   b) Geologist$'
q7o3 db '   c) Dentist$'

q8  db '8. What do you get when you boil water?:$'
q8o db '   a) Nothing happens$'
q8o2 db '   b) Ice$'
q8o3 db '   c) Steam$'

q9  db '9. What is opposite of Happy?:$'
q9o db '   a) Sad$'
q9o2 db '   b) Angry$'
q9o3 db '   c) Stupid$'

q10 db '10. 56 divided by 8 is:$'
q10o db '   a) 7$'
q10o2 db '   b) 9$'
q10o3 db '   c) 6$'

; Pointer table: for each question we store four word pointers:
; word0 = question label, word1 = option a, word2 = option b, word3 = option c
QPTBL:
    dw q1,  q1o,  q1o2,  q1o3
    dw q2,  q2o,  q2o2,  q2o3
    dw q3,  q3o,  q3o2,  q3o3
    dw q4,  q4o,  q4o2,  q4o3
    dw q5,  q5o,  q5o2,  q5o3
    dw q6,  q6o,  q6o2,  q6o3
    dw q7,  q7o,  q7o2,  q7o3
    dw q8,  q8o,  q8o2,  q8o3
    dw q9,  q9o,  q9o2,  q9o3
    dw q10, q10o, q10o2, q10o3

; Correct answers (bytes)
ANSWERS db 'a','b','c','b','a','c','b','c','a','a'

section .bss
correct resb 1
wrong   resb 1
index   resb 1
user_in resb 1

section .text
start:
    ; ensure DS = CS for all data references
    push cs
    pop  ds

    xor ax, ax
    mov byte [correct], 0
    mov byte [wrong], 0
    mov byte [index], 0

    call print_newline
    mov dx, MSG_WELCOME
    call print_string
    call print_newline
    mov dx, MSG_RULES1
    call print_string
    call print_newline
    mov dx, MSG_RULES2
    call print_string
    call print_newline
    mov dx, MSG_RULES3
    call print_string
    call print_newline
    mov dx, MSG_START
    call print_string
    call wait_enter

quiz_loop:
    mov al, [index]
    cmp al, 10
    je near quiz_done

    ; calculate pointer offset: each question entry has 4 words (8 bytes)
    xor bx, bx
    mov bl, [index]       ; BL = index (0..9)
    shl bx, 3             ; multiply by 8 (4 words * 2 bytes)
    lea si, [QPTBL]
    add si, bx            ; SI -> start of this question's 4-word block

    ; print question
    mov bx, [si]          ; word 0 = question ptr
    mov dx, bx
    call print_string
    call print_newline

    ; print option a
    mov bx, [si+2]        ; word 1 = option a ptr
    mov dx, bx
    call print_string
    call print_newline

    ; print option b
    mov bx, [si+4]        ; word 2 = option b ptr
    mov dx, bx
    call print_string
    call print_newline

    ; print option c
    mov bx, [si+6]        ; word 3 = option c ptr
    mov dx, bx
    call print_string
    call print_newline

    ; prompt for answer
    mov dx, MSG_PROMPT
    call print_string

get_input:
    call get_char         ; AL = key
    ; convert uppercase to lowercase
    cmp al, 'A'
    jb near .chk_other
    cmp al, 'Z'
    ja near .chk_other
    or al, 20h
.chk_other:
    ; only accept 'a','b','c'
    cmp al, 'a'
    je near .valid
    cmp al, 'b'
    je near .valid
    cmp al, 'c'
    je near .valid

    ; invalid: print message and ask again
    call print_newline
    mov dx, MSG_INVALID
    call print_string
    call print_newline
    mov dx, MSG_PROMPT
    call print_string
    jmp near get_input

.valid:
    mov [user_in], al

    ; compare with correct answer
    xor bx, bx
    mov bl, [index]        ; BX = index
    mov al, [ANSWERS + bx] ; AL = correct answer for this question
    cmp byte [user_in], al
    je near .is_correct

    ; wrong
    call print_newline
    mov dx, MSG_WRONG
    call print_string
    inc byte [wrong]
    jmp near .next_q

.is_correct:
    call print_newline
    mov dx, MSG_CORRECT
    call print_string
    inc byte [correct]

.next_q:
    ; increment index and continue
    inc byte [index]
    call print_newline
    jmp near quiz_loop

quiz_done:
    call print_newline
    mov dx, MSG_SCORE
    call print_string
    call print_newline

    ; compute total = correct - wrong (signed)
    mov al, [correct]
    sub al, [wrong]
    call print_signed_score
    call print_newline

    ; print detailed result
    mov dx, MSG_RESULT
    call print_string
    call print_newline

    mov dx, MSG_CORRECT_CNT
    call print_string
    mov al, [correct]
    call print_score_char
    call print_newline

    mov dx, MSG_WRONG_CNT
    call print_string
    mov al, [wrong]
    call print_score_char
    call print_newline

    call print_newline
    mov dx, MSG_THANKS
    call print_string
    call print_newline

    mov ah, 4Ch
    int 21h

; ----------------------------
; Helper routines
; ----------------------------
print_string:
    mov ah, 09h
    int 21h
    ret

get_char:
    mov ah, 01h
    int 21h
    ret

wait_enter:
.wait:
    mov ah, 01h
    int 21h
    cmp al, 0Dh
    jne near .wait
    ret

print_newline:
    mov ah, 02h
    mov dl, 0Dh
    int 21h
    mov dl, 0Ah
    int 21h
    ret

print_score_char:
    add al, '0'
    mov dl, al
    mov ah, 2
    int 21h
    ret

print_signed_score:
    ; AL is signed after subtraction; print optionally '-' then magnitude
    cmp al, 0
    jge near .pos
    mov ah, 2
    mov dl, '-'
    int 21h
    neg al
.pos:
    cmp al, 10
    jne near .single
    ; value == 10
    mov ah, 2
    mov dl, '1'
    int 21h
    mov dl, '0'
    int 21h
    ret
.single:
    add al, '0'
    mov dl, al
    mov ah, 2
    int 21h
    ret
