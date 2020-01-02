mkdir -p obj
# compile src
i386-elf-as -c src/boot.s -o obj/boot.o
i386-elf-gcc -c src/kernel.c -o obj/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
# link
i386-elf-gcc -T src/linker.ld -o obj/small_kernel.bin -ffreestanding -O2 -nostdlib obj/boot.o obj/kernel.o -lgcc
