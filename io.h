#pragma once

/*
 * I/O interface.
 */

/*
 * Send a byte into an I/O port.
 */
void outb(unsigned short port, unsigned char data);

/*
 * Read a byte from an I/O port.
 */
unsigned char inb(unsigned short port);
