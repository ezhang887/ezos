global outb
global inb

; outb: send a byte into an I/O port
; Arguments: (port, data)
outb:
    mov al, [esp + 8]	    ; move data into $al
    mov dx, [esp + 4]	    ; move port into $dx
    out dx, al		    ; send data into io port
    ret

; inb: read a byte from an I/O port
; Arguments: (port)
; Returns: data
inb:
    mov dx, [esp + 4]	    ; move port into $dx
    in al, dx		    ; read data from io port
    ret
