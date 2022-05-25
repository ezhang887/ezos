global outb

; outb: send a byte into an I/O port
; Arguments: (port, data)
outb:
    mov al, [esp + 8]	    ; move data into $al
    mov dx, [esp + 4]	    ; move port into $dx
    out dx, al		    ; send data into io port
    ret
