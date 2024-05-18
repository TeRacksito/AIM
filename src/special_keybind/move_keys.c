#include <stdio.h>
#include <ncurses.h>

/* Check if the key is a movement key. */
bool is_movement_key(int ch)
{
    return ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT;
}

/* Check if the key is a fast movement key. */
bool is_fast_movement_key(int ch)
{
    return ch == KEY_HOME || ch == KEY_END;
}

/* Move the cursor according to the key pressed. */
void fast_movement_key(int ch, char **lines, int *y, int *x)
{
    switch (ch)
    {
    case KEY_HOME:
        *x = 0;
        break;
    case KEY_END:
        *x = strlen(lines[*y]);
        break;
    }
}

/* Move the cursor according to the key pressed.
 * Unchecked movement. */
void movement_key(int ch, int *y, int *x)
{
    switch (ch)
    {
    case KEY_UP:
        (*y)--;
        break;
    case KEY_DOWN:
        (*y)++;
        break;
    case KEY_LEFT:
        if (*x == 0)
        {
            break;
        }
        (*x)--;
        break;
    case KEY_RIGHT:
        (*x)++;
        break;
    }
}
