; fill screen with 'A' in green color
[org 0x0100]
              jmp  start

charA:        db  'A'              ; character to print
length:       dw  1                

; subroutine to clear the screen
clrscr:       push es
              push ax
              push di

              mov  ax, 0xb800
              mov  es, ax             ; point es to video base
              mov  di, 0              ; point di to top-left column

nextloc:      mov  word [es:di], 0x0720 ; clear char (space + normal attrib)
              add  di, 2
              cmp  di, 4000           ; finished 80×25?
              jne  nextloc

              pop  di
              pop  ax
              pop  es
              ret

; subroutine to fill full screen with 'A'
fillA:        push es
              push ax
              push cx
              push si
              push di

              mov  ax, 0xb800
              mov  es, ax
              mov  di, 0
              mov  si, charA          ; pointer to our 'A'
              mov  cx, 2000           ; total characters
              mov  ah, 0x02           ; green foreground attribute

nextchar:     mov  al, [si]           ; load 'A'
              mov  [es:di], ax        ; store 'A' + green
              add  di, 2
              loop nextchar

              pop  di
              pop  si
              pop  cx
              pop  ax
              pop  es
              ret

start:        call clrscr             ; clear the screen
              call fillA              ; fill with green A’s

              mov  ax, 0x4c00
              int  0x21
