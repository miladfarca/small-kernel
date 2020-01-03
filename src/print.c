#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"

//80×25 character display, rendered with a 9×16 pixel font, with an effective resolution of 720×400
uint16_t *vga_buffer = (uint16_t *)0xB8000;
size_t vga_width = 80;
size_t vga_height = 25;
size_t vga_buffer_index_x = 0;
size_t vga_buffer_index_y = 0;

void move_to_next_row()
{
    // check y boundaries
    if (vga_buffer_index_y >= vga_height - 1)
    {
        // scroll down one row
        uint16_t *start_point = vga_buffer + vga_width;
        size_t i;
        size_t count = (vga_width * vga_height) - vga_width;
        for (i = 0; i < count; i++)
        {
            vga_buffer[i] = start_point[i];
        }
    }
    else
    {
        vga_buffer_index_y++;
    }
}
void print_char_at(size_t x, size_t y, char input)
{
    uint16_t vga_input = (uint16_t)input;
    // convert x,y to linear array position, x + (y * screen width)
    size_t linear_position = x + (y * vga_width);
    // set bg color to black, text color to white
    vga_buffer[linear_position] = (0xf << 8) | vga_input;
}

void print_char(char input)
{
    // check x boundaries
    if (vga_buffer_index_x >= vga_width - 1)
    {
        vga_buffer_index_x = 0;
        // if screen is full scroll down, 1 row
        move_to_next_row();
    }
    print_char_at(vga_buffer_index_x++, vga_buffer_index_y, input);
}

void print_s(char *input)
{
    size_t index = 0;
    while (input[index])
    {
        print_char(input[index++]);
    }
}

void print_i(int input)
{
    char *c = NULL;
    print_s(itoa(input, c, 10));
}

void println(void)
{
    vga_buffer_index_x = 0;
    move_to_next_row();
}

void clear_screen()
{
    size_t i;
    for (i = 0; i < vga_width * vga_height; i++)
    {
        print_char(' ');
    }
    vga_buffer_index_x = 0;
    vga_buffer_index_y = 0;
}