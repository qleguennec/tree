#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
  COLOR_BLACK         = 0,
  COLOR_BLUE          = 1,
  COLOR_GREEN         = 2,
  COLOR_CYAN          = 3,
  COLOR_RED           = 4,
  COLOR_MAGENTA       = 5,
  COLOR_BROWN         = 6,
  COLOR_LIGHT_GREY    = 7,
  COLOR_DARK_GREY     = 8,
  COLOR_LIGHT_BLUE    = 9,
  COLOR_LIGHT_GREEN   = 10,
  COLOR_LIGHT_CYAN    = 11,
  COLOR_LIGHT_RED     = 12,
  COLOR_LIGHT_MAGENTA = 13,
  COLOR_LIGHT_BROWN   = 14,
  COLOR_WHITE         = 15,
};

uint8_t make_color (enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

uint16_t make_vgaentry (char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

size_t strlen (const char* str) {
  size_t ret = 0;
  while (str[ret] != 0)
    ret++;
  return ret;
}

static const size_t VGA_WIDTH  = 80;
static const size_t VGA_HEIGHT = 25;

size_t      term_row;
size_t      term_column;
uint8_t     term_color;
uint16_t*   term_buffer;

void term_init() {
  term_row    = 0;
  term_column = 0;
  term_color  = make_color (COLOR_LIGHT_GREY, COLOR_BLACK);
  term_buffer = (uint16_t*) 0xB8000;

  for (size_t y=0; y<VGA_HEIGHT; y++) {
    for (size_t x=0; x<VGA_WIDTH; x++) {

      const size_t index = y * VGA_WIDTH + x;
      term_buffer[index] = make_vgaentry (' ', term_color);
    }
  }
}

void term_putentryat (char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  term_buffer[index] = make_vgaentry (c, color);
}

void term_putchar (char c) {
  term_putentryat (c, term_color, term_column, term_row);

  if (++term_column == VGA_WIDTH)
    term_column = 0;

    if (++term_row == VGA_HEIGHT)
        term_row = 0;
}

void term_writestring (const char* data) {
  size_t datalen = strlen (data);
  for (size_t i=0; i<datalen; i++)
    term_putchar (data[i]);
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
  term_init();
  term_writestring ("Hello, kernel World!\n");
}

