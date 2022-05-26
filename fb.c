#include "fb.h"
#include "io.h"

#define FB_MMIO_BASE 0x000B8000

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

#define FB_COLS 80
#define FB_ROWS 25

static char *fb = (char *) FB_MMIO_BASE;
static int fb_curr_pos = 0;

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

    fb_curr_pos = pos;
}

void fb_write(char *buf, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        // `fb_curr_pos * 2` since each entry in the fb is 2 bytes.
        fb_write_cell(2 * fb_curr_pos, buf[i], FB_COLOR_WHITE, FB_COLOR_BLACK);
        fb_move_cursor(fb_curr_pos + 1);
    }
}

void fb_clear() {
    int old_pos = fb_curr_pos;
    for (unsigned int i = 0; i < FB_ROWS; i++) {
        for (unsigned int j = 0; j < FB_COLS; j++) {
            fb_write_cell(2 * fb_curr_pos, ' ', FB_COLOR_BLACK, FB_COLOR_BLACK);
            fb_move_cursor(fb_curr_pos + 1);
        }
    }
    fb_move_cursor(old_pos);
}
