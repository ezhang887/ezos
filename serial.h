#pragma once

#define SERIAL_COM1 0x3F8

/*
 * Serial interface.
 */

/*
 * Initializes the serial port with the specified baud rate and other default settings.
 */
void serial_init(unsigned short com, unsigned int baud_rate);

/*
 * Writes a byte to the specified serial port.
 */
int serial_write_byte(unsigned short com, char data);

/*
 * Writes a buffer to the specified serial port.
 */
int serial_write(unsigned short com, char *buf, unsigned int len);
