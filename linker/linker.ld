ENTRY(_start)

SECTIONS {
  . = 1M;
  
  /* Multiboot header */
  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.text)
  }

  /* read-only data */
  .rodata BLOCK(4K) : ALIGN(4K)
  {
    *(.rodata)
  }

  /* read-write data (initialized) */
  .data BLOCK(4K) : ALIGN(4K)
  {
    *(.data)
  }

  /* read-write data (uninitialized) and stack */
  .bss BLOCK (4K) : ALIGN(4K)
  {
    *(COMMON)
    *(.bss)
    *(.bootstrap_stack)
  }
}
