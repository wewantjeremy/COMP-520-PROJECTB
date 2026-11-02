	;; Jeremy Wise Project B
        .global _putInMemory
        .global _interrupt
        .global _makeInterrupt21
        .extern _handleInterrupt21

_putInMemory:
        push bp
        mov bp,sp
        push ds
        mov ax,[bp+4]
        mov si,[bp+6]
        mov cl,[bp+8]
        mov ds,ax
        mov [si],cl
        pop ds
        pop bp
        ret

_interrupt:
        push bp
        mov bp,sp
        mov ax,[bp+4]
        push ds
        mov bx,cs
        mov ds,bx
        mov si,#intr
        mov [si+1],al
        pop ds
        mov ax,[bp+6]
        mov bx,[bp+8]
        mov cx,[bp+10]
        mov dx,[bp+12]
intr:   int #0x00
        mov ah,#0
        pop bp
        ret

_makeInterrupt21:
        mov dx,#_interrupt21ServiceRoutine
        push ds
        mov ax,#0
        mov ds,ax
        mov si,#0x84
        mov ax,cs
        mov [si+2],ax
        mov [si],dx
        pop ds
        ret

_interrupt21ServiceRoutine:
        push dx
        push cx
        push bx
        push ax
        call _handleInterrupt21
        pop ax
        pop bx
        pop cx
        pop dx
        iret
