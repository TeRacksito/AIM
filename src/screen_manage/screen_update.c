#include <stdio.h>
#include <ncurses.h>

/*
 * This function updates the screen with the given lines.
 * Starting from the top line, it prints the lines on the screen.
 * If the number of lines is less than the number of lines on the screen,
 * it prints '~' on the remaining lines.
 */
void screen_update(char **lines, int num_lines, int top)
{
    clear();

    int j;
    for (j = 0; j < LINES - 1; j++)
    {
        if (j + top < 0)
        {
            continue;
        }

        char *line = lines[j + top];
        if (line == NULL || j + top >= num_lines)
        {
            break;
        }

        mvprintw(j, 0, line);
    }

    
    if (num_lines > LINES - 2)
    {
        return;
    }

    // Fill inexistent (but potentially displayable) lines with '~'
    for (; j < LINES - 1; j++)
    {
        mvprintw(j, 0, "~");
    }
}

/*
 * General cursor position checking. In relation to the boundaries of the screen and the number of lines.
 */
void check_cursor_position(int *top, int num_lines, int *y, int *x)
{
    // If the cursor is below the screen, the screen is scrolled down and the cursor is moved to the last line.
    if (*y >= LINES - 2)
    {
        *top += *y - (LINES - 2);
        *y = LINES - 2;
    }

    // If the current top line gives too much space at the bottom of the screen (not enough lines to fill the screen),
    // the screen is scrolled up.
    if (*top + LINES - 1 > num_lines)
    {
        if (*top > 0)
        {
            *y += 1;
        }
        *top -= *top + LINES - 1 - num_lines;
    }

    if (*top < 0)
    {
        *top = 0;
    }

    if (*y < 0)
    {
        *top -= 0 - *y; // reallocate top considering the new y
        *y = 0;
    }
}