#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"

void kernel_main(void)
{
    clear_screen();
    size_t i;
    for (i = 0; i < 10; i++)
    {
        print_i(i);
        println();
    }
}