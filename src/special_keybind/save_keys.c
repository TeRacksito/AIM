#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/* Check if the key is for saving the file. */
bool is_save_key(int ch)
{
    return ch == KEY_F(2);
}