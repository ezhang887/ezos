#pragma once

typedef struct gdt {
    // Note: https://github.com/littleosbook/littleosbook/issues/13
    unsigned short size;
    unsigned int address;
} __attribute__((packed)) gdt_t;

typedef struct gdt_entry {
    // See https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor for layout
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_mid;
    unsigned char access;
    unsigned char limit_high: 4;
    unsigned char flags: 4;
    unsigned char base_high;
} __attribute__((packed)) gdt_entry_t;


/**
 * Initializes segmentation.
 */
void segments_init();

void load_gdt(gdt_t *gdt);
void load_segment_selectors();
