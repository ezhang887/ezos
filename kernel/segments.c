#include "segments.h"

static void create_gdt_entry(gdt_entry_t *dst, int privilege_level, int type);

void segments_init() {
    gdt_entry_t gdt_entries[3];
    gdt_t gdt;
    gdt.address = (unsigned int) &gdt_entries;
    gdt.size = sizeof(gdt_entries);

    // NULL entry
    create_gdt_entry(gdt_entries + 0, 0, 0);

    // Kernel text segment
    create_gdt_entry(gdt_entries + 1, 0, 0xA);

    // Kernel data segment
    create_gdt_entry(gdt_entries + 2, 0, 0x2);

    load_segment_selectors();
    load_gdt(&gdt);
}

static void create_gdt_entry(gdt_entry_t *dst, int privilege_level, int type) {
    dst->base_low = 0x0;
    dst->base_mid = 0x0;
    dst->base_high = 0x0;

    dst->limit_low = 0xFFFF;
    dst->limit_high = 0xF;

    dst->flags = (0x01 << 3) | (0x01 << 2);

    dst->access = (0x1 << 7) | ((privilege_level & 0x3) << 5) | (0x1 << 4) | (type & 0xF);
}
