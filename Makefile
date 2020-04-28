KERNEL_CC := i686-elf-gcc -g -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra



run: myiso.iso
	qemu-system-i386 -kernel isodir/boot/myos.bin

myiso.iso: isodir/boot/myos.bin isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir


kernel.o: kernel.c 
	${KERNEL_CC} kernel.c -o kernel.o

mem.o: mem.c mem.h
	${KERNEL_CC} mem.c -o mem.o


tty.o: tty.c tty.h
	${KERNEL_CC} tty.c -o tty.o

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

isodir/boot/myos.bin: kernel.o boot.o mem.o tty.o
	i686-elf-gcc -T linker.ld -o isodir/boot/myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o mem.o tty.o -lgcc

clean: 
	rm isodir/boot/myiso.bin kernel.o boot.o myos.iso 
