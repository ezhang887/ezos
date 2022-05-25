#include "fb.h"

static char *fb = (char *) FB_MMIO_BASE;

void fb_write_cell(unsigned int position, char c, unsigned char fg, unsigned char bg) {
    fb[position] = c;
    fb[position + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}
