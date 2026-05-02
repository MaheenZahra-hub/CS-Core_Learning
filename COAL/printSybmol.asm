; fill screen: first 13 rows '_' then the rest '.'
[org 0x0100]
jmp start

char1:        db  '_'        ; for rows 0–12
char2:        db  '.'        ; for rows 13–24


clrscr:       push es
              push ax
              push di

              mov  ax, 0xb800
              mov  es, ax
              mov  di, 0

nextloc:      mov  word [es:di], 0x0720
              add  di, 2
              cmp  di, 4000
              jne nextloc

              pop  di
              pop  ax
              pop  es
              ret


fillScreen:   push es
              push ax
              push cx
              push si
              push di

              mov  ax, 0xb800
              mov  es, ax
              mov  di, 0

; First 13 rows = 13 * 80 = 1040 cells 
              mov  cx, 1040            ; cell count
              mov  si, char1           ; '_'
              mov  ah, 0x07            ; normal attribute

firstPart:
              mov  al, [si]
              mov  [es:di], ax
              add  di, 2
              loop firstPart

; Remaining rows → 960 cells 
              mov  cx, 960             ; cell count
              mov  si, char2           ; '.'

secondPart:
              mov  al, [si]
              mov  [es:di], ax
              add  di, 2
              loop secondPart

              pop  di
              pop  si
              pop  cx
              pop  ax
              pop  es
              ret


start:        call clrscr
              call fillScreen

              mov ax, 0x4c00
              int 0x21
