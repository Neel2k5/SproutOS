global idt_flush
idt_flush:
    mov edx, [esp + 4] 
    lidt [edx]          ; Load idtr
    ret
