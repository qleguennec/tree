# Constants for multiboot header
.set ALIGN,     1<<0          
.set MEMINFO,   1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

# Multiboot Standard header. Force the header to be in the start of our final program.
.section        .multiboot
.align          4
.long           MAGIC
.long           FLAGS
.long           CHECKSUM

# Allocate a room far small temporary stack by creating a symbol at the top,
# and allocate 16kB for it
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384
stack_top:

# Kernel entry point
.section        .text
.global         _start
.type           _start, @function 
_start:
        # set the esp register to point to the top of our stack
        movl $stack_top, %esp
        
        # call main kernel function
        call kernel_main

        # infinite loop
        cli
        hlt

.Lhang:
        jmp .Lhang

.size _start, . - _start
