# Declare constants for the multiboot header
.set ALIGN,    1<<0            
.set MEMINFO,  1<<1            
.set FLAGS,    ALIGN | MEMINFO 
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)
 
# set the multiboot header
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
 
# create the stack
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
# linker specifies _start as the entry point to the kernel 
.section .text
.global _start
.type _start, @function
_start: 
	# set the stack
	mov $stack_top, %esp
 
	# call the main kernel function
	call kernel_main
 
    # halt the processor indefinitely
	cli
1:	hlt
	jmp 1b
