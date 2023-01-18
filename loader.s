.set MAGIC, 0x1badb002 
# magic number for Grub bootloader.
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern kernel
.global loader

loader:
    mov $kernel_stack, %esp
    push %eax
    push %ebx
    call kernel

_stop:
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024 # 2 MB
kernel_stack: