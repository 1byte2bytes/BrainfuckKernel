all:
	i686-elf-as boot.asm -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c brainfuck.c -o brainfuck.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o brainfuck.kernel -ffreestanding -O2 -nostdlib boot.o kernel.o brainfuck.o -lgcc