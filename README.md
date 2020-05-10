# Bebbe-OS

Bebbe-OS is an Protected mode 32 bit operating system for X86 that is named after one of my cats. Bebbe is not the favorite cat, but the other one is named "The sausage" so it was an easy pick.

Bebbe is written in C with some elements of inline asm and standalone Assembly files. Assembly used is AT&T. It follow mutliboot specification and is currenlty loaded with GRUB. It does not probe the BIOS for memory map, instead it kindly asks GRUB.

## Features
Interrupts

## Planned features
Virtuell memory (Paging)
User processes 
Basic filesystem FAT32
Build script that builds the cross-compiler for you



## Prerequisites 

```
i686 cross-compiler, both asm and gcc
qemu
grub-mkrescue
```

The sad news is that you need to build a cross-compiler in order to compile this operatingsystem yourself.
https://wiki.osdev.org/GCC_Cross-Compiler 
Is a good resource on getting started on how to setup the cross-compiler. 
This project is currently compiled with GCC 9.2.0. 



## Usage

```
make run
```


## Authors
Carl Söyseth

## License
[MIT](https://choosealicense.com/licenses/mit/)
