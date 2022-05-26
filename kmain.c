#include "fb.h"

static char message[] = "Hello World!";

void kmain() {
    /*
    fb_write_cell(0, 'A', FB_COLOR_WHITE, FB_COLOR_BLACK);
    fb_write_cell(20, 'B', FB_COLOR_LIGHT_CYAN, FB_COLOR_BLACK);

    fb_move_cursor(80);
    */
    fb_clear();
    fb_write(message, sizeof(message));
}
