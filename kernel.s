	.file	"kernel.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello, kernel World!\n"
.LC1:
	.string	"Fuck me \n"
	.text
	.align 16
	.globl	kernel_main
	.type	kernel_main, @function
kernel_main:
.LFB0:
	.file 1 "kernel.c"
	.loc 1 17 1 view -0
	.cfi_startproc
	.loc 1 19 2 view .LVU1
	.loc 1 17 1 is_stmt 0 view .LVU2
	subl	$12, %esp
	.cfi_def_cfa_offset 16
	.loc 1 19 2 view .LVU3
	call	terminal_initialize
.LVL0:
	.loc 1 20 3 is_stmt 1 view .LVU4
	call	init_gdt
.LVL1:
	.loc 1 23 2 view .LVU5
	subl	$12, %esp
	.cfi_def_cfa_offset 28
	pushl	$.LC0
	.cfi_def_cfa_offset 32
	call	terminal_writestring
.LVL2:
	.loc 1 26 2 view .LVU6
	.loc 1 27 2 view .LVU7
	.loc 1 28 2 view .LVU8
	movl	$.LC1, (%esp)
	call	terminal_writestring
.LVL3:
	.loc 1 29 1 is_stmt 0 view .LVU9
	addl	$28, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	kernel_main, .-kernel_main
	.comm	idtp,6,4
	.comm	idt,2048,32
.Letext0:
	.file 2 "int.h"
	.file 3 "tty.h"
	.file 4 "mem.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x17d
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF21
	.byte	0xc
	.long	.LASF22
	.long	.LASF23
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF1
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF2
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF8
	.uleb128 0x4
	.long	.LASF13
	.byte	0x8
	.byte	0x2
	.byte	0x6
	.byte	0x8
	.long	0xba
	.uleb128 0x5
	.long	.LASF9
	.byte	0x2
	.byte	0x8
	.byte	0x14
	.long	0x48
	.byte	0
	.uleb128 0x6
	.string	"sel"
	.byte	0x2
	.byte	0x9
	.byte	0x14
	.long	0x48
	.byte	0x2
	.uleb128 0x5
	.long	.LASF10
	.byte	0x2
	.byte	0xa
	.byte	0x13
	.long	0x41
	.byte	0x4
	.uleb128 0x5
	.long	.LASF11
	.byte	0x2
	.byte	0xb
	.byte	0x13
	.long	0x41
	.byte	0x5
	.uleb128 0x5
	.long	.LASF12
	.byte	0x2
	.byte	0xc
	.byte	0x14
	.long	0x48
	.byte	0x6
	.byte	0
	.uleb128 0x4
	.long	.LASF14
	.byte	0x6
	.byte	0x2
	.byte	0xf
	.byte	0x8
	.long	0xe2
	.uleb128 0x5
	.long	.LASF15
	.byte	0x2
	.byte	0x11
	.byte	0x14
	.long	0x48
	.byte	0
	.uleb128 0x5
	.long	.LASF16
	.byte	0x2
	.byte	0x12
	.byte	0x12
	.long	0x64
	.byte	0x2
	.byte	0
	.uleb128 0x7
	.long	0x6b
	.long	0xf2
	.uleb128 0x8
	.long	0x4f
	.byte	0xff
	.byte	0
	.uleb128 0x9
	.string	"idt"
	.byte	0x2
	.byte	0x22
	.byte	0x12
	.long	0xe2
	.uleb128 0x5
	.byte	0x3
	.long	idt
	.uleb128 0xa
	.long	.LASF17
	.byte	0x2
	.byte	0x23
	.byte	0x10
	.long	0xba
	.uleb128 0x5
	.byte	0x3
	.long	idtp
	.uleb128 0xb
	.long	.LASF24
	.byte	0x1
	.byte	0x10
	.byte	0x6
	.long	.LFB0
	.long	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x15c
	.uleb128 0xc
	.string	"i"
	.byte	0x1
	.byte	0x1a
	.byte	0x6
	.long	0x5d
	.byte	0x5
	.uleb128 0xd
	.long	.LVL0
	.long	0x15c
	.uleb128 0xd
	.long	.LVL1
	.long	0x168
	.uleb128 0xd
	.long	.LVL2
	.long	0x174
	.uleb128 0xd
	.long	.LVL3
	.long	0x174
	.byte	0
	.uleb128 0xe
	.long	.LASF18
	.long	.LASF18
	.byte	0x3
	.byte	0x26
	.byte	0x6
	.uleb128 0xe
	.long	.LASF19
	.long	.LASF19
	.byte	0x4
	.byte	0x19
	.byte	0x6
	.uleb128 0xe
	.long	.LASF20
	.long	.LASF20
	.byte	0x3
	.byte	0x30
	.byte	0x6
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF3:
	.string	"long long int"
.LASF23:
	.string	"/home/carl/Dokument/OS/Bebbe"
.LASF8:
	.string	"unsigned int"
.LASF20:
	.string	"terminal_writestring"
.LASF11:
	.string	"flags"
.LASF17:
	.string	"idtp"
.LASF6:
	.string	"long unsigned int"
.LASF15:
	.string	"limit"
.LASF7:
	.string	"long long unsigned int"
.LASF14:
	.string	"idt_ptr"
.LASF9:
	.string	"base_lo"
.LASF10:
	.string	"always0"
.LASF4:
	.string	"unsigned char"
.LASF13:
	.string	"idt_entry"
.LASF2:
	.string	"long int"
.LASF18:
	.string	"terminal_initialize"
.LASF24:
	.string	"kernel_main"
.LASF21:
	.string	"GNU C99 9.3.0 -mtune=generic -march=pentiumpro -g -O2 -std=gnu99 -ffreestanding"
.LASF5:
	.string	"short unsigned int"
.LASF0:
	.string	"signed char"
.LASF22:
	.string	"kernel.c"
.LASF19:
	.string	"init_gdt"
.LASF16:
	.string	"base"
.LASF1:
	.string	"short int"
.LASF12:
	.string	"base_hi"
	.ident	"GCC: (GNU) 9.3.0"
