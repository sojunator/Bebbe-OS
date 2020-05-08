KERNEL_CC := i686-elf-gcc -g -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra



run: myiso.iso 
	qemu-system-i386 -kernel isodir/boot/myos.bin -serial file:serial.log

myiso.iso: isodir/boot/myos.bin isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir


system.o: system.c
	${KERNEL_CC} system.c -o system.o
kernel.o: kernel.c 
	${KERNEL_CC} kernel.c -o kernel.o

mem.o: mem.c mem.h
	${KERNEL_CC} mem.c -o mem.o


tty.o: tty.c tty.h
	${KERNEL_CC} tty.c -o tty.o

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

int.o: int.c
	${KERNEL_CC} int.c  -o int.o

serial.o: serial.c
	${KERNEL_CC} serial.c  -o serial.o

interrupt.o: interrupt.s
	i686-elf-as interrupt.s -o interrupt.o

isodir/boot/myos.bin: kernel.o boot.o mem.o tty.o interrupt.o system.o int.o serial.o
	i686-elf-gcc -T linker.ld -o isodir/boot/myos.bin -ffreestanding -O0 -nostdlib serial.o interrupt.o boot.o system.o int.o kernel.o mem.o tty.o -lgcc

clean: 
	rm isodir/boot/myiso.bin *.o myos.iso serial.log
