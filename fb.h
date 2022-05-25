#pragma once

/*
 * Framebuffer interface.
 */

#define FB_MMIO_BASE 0x000B8000

#define FB_COLOR_BLACK 0
#define FB_COLOR_BLUE 1
#define FB_COLOR_GREEN 2
#define FB_COLOR_CYAN 3
#define FB_COLOR_RED 4
#define FB_COLOR_MAGENTA 5
#define FB_COLOR_BROWN 6
#define FB_COLOR_LIGHT_GRAY 7
#define FB_COLOR_DARK_GRAY 8
#define FB_COLOR_LIGHT_BLUE 9
#define FB_COLOR_LIGHT_GREEN 10
#define FB_COLOR_LIGHT_CYAN 11
#define FB_COLOR_LIGHT_RED 12
#define FB_COLOR_LIGHT_MAGENTA 13
#define FB_COLOR_LIGHT_BROWN 14
#define FB_COLOR_WHITE 15

void fb_write_cell(unsigned int position, char c, unsigned char fb, unsigned char bg);
