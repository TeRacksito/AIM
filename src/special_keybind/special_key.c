#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/*
 * Handle all special keys
 * UNDER DEVELOPMENT - NOT WORKING YET
 * No correct implementation has been found yet
 */
bool checkSpecialKeys(int ch, char **lines, int *num_lines, int *top, int *y, int *x)
{
    bool is_movement = is_movement_key(ch);
    if (is_movement)
    {
        movement_key(ch, y, x);

        int line_index = *y + *top;

        while (line_index >= *num_lines)
        {
            *y = *num_lines - *top - 1;
            line_index = *y + *top;
        }

        char *line = lines[line_index];

        if (*x >= strlen(line))
        {
            *x = strlen(line);
        }
        return true;
    }

    bool is_fast_movement = is_fast_movement_key(ch);
    if (is_fast_movement)
    {
        fast_movement_key(ch, lines, y, x);
        return true;
    }

    bool is_remove = is_remove_key(ch);
    if (is_remove)
    {
        remove_key(&lines, num_lines, top, y, x);
        return true;
    }

    bool is_suppr = is_suppr_key(ch);
    if (is_suppr)
    {
        suppr_key(&lines, num_lines, top, y, x);
        return true;
    }

    bool is_new_line = is_new_line_key(ch);
    if (is_new_line)
    {
        new_line_key(&lines, num_lines, top, y, x); // !Problematic
        return true;
    }

    if (ch == 410)
    {
        resize_term(0, 0);
        return true;
    }

    return false;
}