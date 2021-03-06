C_OBJECTS = $(patsubst %.c,%.o,$(wildcard kernel/*.c))
ASM_OBJECTS = $(patsubst %.s,%.o,$(wildcard kernel/*.s))
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

.PHONY: all
all: kernel.elf

.PHONY: clean
clean:
	rm -f kernel/*.o *.elf *.iso

.PHONY: run
run: ezos.iso
	bochs -f .bochsrc -q

kernel.elf: $(C_OBJECTS) $(ASM_OBJECTS)
	ld $(LDFLAGS) $(C_OBJECTS) $(ASM_OBJECTS) -o kernel.elf

ezos.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o ezos.iso iso

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/%.o: kernel/%.s
	$(AS) $(ASFLAGS) $< -o $@
