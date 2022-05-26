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
static unsigned int fb_curr_row = 0;
static unsigned int fb_curr_col = 0;

static void fb_newline();
static void fb_scroll();

int fb_write_cell(unsigned int position, char c, unsigned char fg, unsigned char bg) {
    if (c == '\n') {
        fb_newline();
    } else if (c == '\t') {
        static char tab_buf[4] = "    ";
        fb_write(tab_buf, 4);
    } else {
        // `position * 2` since each entry in the fb is 2 bytes.
        fb[position * 2] = c;
        fb[position * 2 + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
    }

    return 0;
}

int fb_move_cursor(unsigned short pos) {
    // Send upper half of `pos`
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (pos >> 8) & 0x00FF);

    // Send lower half of `pos`
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);

    return 0;
}

int fb_write(char *buf, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        int fb_curr_pos = fb_curr_row * FB_COLS + fb_curr_col;
        fb_write_cell(fb_curr_pos, buf[i], FB_COLOR_WHITE, FB_COLOR_BLACK);

        if (buf[i] == '\n' || buf[i] == '\t') {
            // fb_write_cell() calls fb_newline() which already handles updating cursor position.
            // Similarily, fb_write_cell() calls this function for tabs which also already handles updating the cursor position.
            continue;
        }

        if (fb_curr_col >= FB_COLS - 1) {
            fb_newline();
        } else {
            fb_curr_col++;
            fb_move_cursor(fb_curr_pos + 1);
        }
    }

    return 0;
}

int fb_clear() {
    int old_pos = fb_curr_row * FB_COLS + fb_curr_col;
    for (unsigned int i = 0; i < FB_ROWS; i++) {
        for (unsigned int j = 0; j < FB_COLS; j++) {
            int curr_pos = i * FB_COLS + j;
            fb_write_cell(curr_pos, ' ', FB_COLOR_BLACK, FB_COLOR_BLACK);
            fb_move_cursor(curr_pos + 1);
        }
    }
    fb_move_cursor(old_pos);

    return 0;
}

static void fb_newline() {
    if (fb_curr_row >= FB_ROWS - 1) {
        fb_scroll();
    } else {
        fb_curr_row++;
    }

    fb_curr_col = 0;
    fb_move_cursor(fb_curr_row * FB_COLS + fb_curr_col);
}

static void fb_scroll() {
    int fb_size_to_copy = FB_COLS * FB_ROWS - FB_COLS;
    for (int i = 0; i < fb_size_to_copy; i++) {
        fb[i] = fb[i + FB_COLS];
    }
}
