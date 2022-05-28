#include "segments.h"

static gdt_entry_t gdt_entries[3];

void segments_init() {
    gdt_t gdt;
    gdt.address = (unsigned int) &gdt_entries;
    gdt.size = sizeof(gdt_entries);

    // TODO: create gdt entries (NULL, kernel text, kernel data)

    load_segment_selectors();
    load_gdt(&gdt);
}
