; note: naming this segments.s causes compiler issues (multiple definition of functions in segments.h)

global load_gdt
global load_segment_selectors

; load_gdt: loads GDT into processor
; Arguments: (pointer to gdt struct)
load_gdt:
    lgdt [esp + 4]
    ret

; load_segment_selectors: load segment selectors into registers
load_segment_selectors:
    mov ax, 0x10
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    jmp 0x08:flush_cs
flush_cs:
    ret
