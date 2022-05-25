#include "fb.h"
#include "io.h"

#define FB_MMIO_BASE 0x000B8000
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

static char *fb = (char *) FB_MMIO_BASE;

void fb_write_cell(unsigned int position, char c, unsigned char fg, unsigned char bg) {
    fb[position] = c;
    fb[position + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_move_cursor(unsigned short pos) {
    // Send upper half of `pos`
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);

    // Send lower half of `pos`
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}
