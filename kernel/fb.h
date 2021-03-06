#pragma once

/*
 * Framebuffer interface.
 */

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

/*
 * Write a character into a cell in the framebuffer.
 */
int fb_write_cell(unsigned int position, char c, unsigned char fb, unsigned char bg);

/*
 * Move the framebuffer's cursor.
 */
int fb_move_cursor(unsigned short pos);

/*
 * Write a buffer to the framebuffer.
 */
int fb_write(char *buf, unsigned int len);

/*
 * Clear the framebuffer.
 */
int fb_clear();
