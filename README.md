# Bebbe-OS

Bebbe-OS is an operating system for X86 that is named after one of my cats. Bebbe is not the favorite cat, but the other one is named "The sausage" so it was an easy pick.

Bebbe is written in C with some elements of inline asm and standalone Assembly files. Assembly used is AT&T.

## Prerequisites 

```
i686 cross-compiler, both asm and gcc
qemu
grub-mkrescue
```

The sad news is that you need to build a cross-compiler in order to compile this operatingsystem yourself.
https://wiki.osdev.org/GCC_Cross-Compiler 
Is a good resource on getting started on how to setup the cross-compiler. 
This project is currently compiled with GCC 9.2.0


## Usage

```
make run
```

## Contributing
Is sadly not welcomed, this is a hobby project of mine where I develop my coding skills.

## Authors
Carl Söyseth

## License
[MIT](https://choosealicense.com/licenses/mit/)
