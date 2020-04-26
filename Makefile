run: myiso.iso
	qemu-system-i386 -kernel isodir/boot/myos.bin

myiso.iso: isodir/boot/myos.bin isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir


kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

isodir/boot/myos.bin: kernel.o boot.o
	i686-elf-gcc -T linker.ld -o isodir/boot/myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

clean: 
	rm isodir/boot/myiso.bin kernel.o boot.o myos.iso 
