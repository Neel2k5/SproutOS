global gdt_flush

gdt_flush:
    mov eax,[esp+4] ; holds the argument from stack which is the address of gdt
    lgdt [eax] ; points to the gdt table

    mov ax,0x10
    ; segment registers pointing to gdt, 0x10 is offset to gdt
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    mov ss,ax
    jmp 0x08:.flush ; far jmp back to code segment

.flush:
    ret