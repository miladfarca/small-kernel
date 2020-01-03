mkdir -p obj
# compile src
CFLAGS="-std=gnu99 -ffreestanding -O2 -Wall -Wextra"
i386-elf-as -c src/boot.s -o obj/boot.o
i386-elf-gcc -c src/kernel.c -o obj/kernel.o $CFLAGS
i386-elf-gcc -c src/utils.c -o obj/utils.o $CFLAGS
i386-elf-gcc -c src/print.c -o obj/print.o $CFLAGS
# link
i386-elf-gcc -T src/linker.ld -o obj/small_kernel.bin -ffreestanding -O2 -nostdlib obj/boot.o obj/kernel.o obj/utils.o obj/print.o -lgcc
