#include "ktests.h"
#include "fb.h"
#include "serial.h"

void test_newline_and_tab() {
    fb_clear();
    char message[] = "Hello World!\tHello World!\nHello World!\tHello World!\n";
    fb_write(message, sizeof(message));
}

void test_scrolling() {
    // Each line in framebuffer is 80 chars wide and there are 25 total lines.
    // At the end, the framebuffer becomes full and needs to scroll,
    // so the first line should be all 'B's while the last line is all 'Z's.
    fb_clear();
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 80; j++) {
            char value = i + 'A';
            fb_write(&value, 1);
        }
    }
}

void test_serial_write() {
    // Out should be in `com1.out` (configured in .bochsrc)
    serial_init(SERIAL_COM1, 56700);
    char message[] = "Hello World!\tHello World!\nHello World!\tHello World!\n";
    serial_write(SERIAL_COM1, message, sizeof(message));
}
