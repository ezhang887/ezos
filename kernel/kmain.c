#include "ktests.h"
#include "segments.h"

void kmain() {
    /*
    fb_write_cell(0, 'A', FB_COLOR_WHITE, FB_COLOR_BLACK);
    fb_write_cell(20, 'B', FB_COLOR_LIGHT_CYAN, FB_COLOR_BLACK);

    fb_move_cursor(80);
    */

    segments_init();

    test_newline_and_tab();
    //test_scrolling();
    test_serial_write();
}
