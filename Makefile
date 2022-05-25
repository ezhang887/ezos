.PHONY: all
all: bochs

.PHONY: clean
clean:
	rm -f *.o iso/boot/*.elf *.iso

loader.o:
	nasm -f elf32 loader.s

kernel.elf: loader.o
	ld -T link.ld -melf_i386 loader.o -o iso/boot/kernel.elf

ezos.iso: kernel.elf
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o ezos.iso iso

.PHONY: bochs
bochs: ezos.iso
	bochs -f .bochsrc -q
