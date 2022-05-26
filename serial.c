#include "serial.h"
#include "io.h"

#define SERIAL_DATA_PORT(base)  (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80
#define SERIAL_BAUD_RATE_DEFAULT 115200

static int serial_initialized = 0;

static int serial_is_transmit_fifo_empty(unsigned short com);
static void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

void serial_init(unsigned short com, unsigned int baud_rate) {
    // Configure baud rate.
    unsigned int baud_divisor = SERIAL_BAUD_RATE_DEFAULT / baud_rate;
    serial_configure_baud_rate(com, baud_divisor);

    // Configure serial line: data length = 8 bits, 0 parity bits, 1 stop bit, break control disabled.
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);

    // Configure serial port buffers: FIFO, clear both buffers on receiver and transmitter, queue size = 14 bytes.
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);

    // Configure modem: RTS (ready-to-transmit) and DTR (data terminal ready) are both 1.
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);

    serial_initialized = 1;
}

int serial_write_byte(unsigned short com, char data) {
    if (!serial_initialized) {
        return -1;
    }

    while (!serial_is_transmit_fifo_empty(com));

    outb(SERIAL_DATA_PORT(com), data);

    return 0;
}

int serial_write(unsigned short com, char *buf, unsigned int len) {
    if (!serial_initialized) {
        return -1;
    }

    for (unsigned int i = 0; i < len; i++) {
        serial_write_byte(com, buf[i]);
    }

    return 0;
}

static int serial_is_transmit_fifo_empty(unsigned short com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

static void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}
