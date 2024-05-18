#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/* Check if the key is a remove key. */
bool is_remove_key(int ch)
{
    return ch == KEY_BACKSPACE || ch == 127;
}

/* Check if the key is a suppr key. */
bool is_suppr_key(int ch)
{
    return ch == KEY_DC;
}

/* Remove the character before the cursor. */
void remove_key(char ***lines, int *num_lines, int *top, int *y, int *x)
{
    int line = *y + *top;
    int col = *x;
    int len = strlen((*lines)[line]);

    // No need of removal.
    if (col == 0 && line == 0)
    {
        return;
    }

    // Special case 1: Cursor is at the beginning of a empty line.
    if (col == 0 && (*lines)[line][0] == '\0')
    {
        free((*lines)[line]);

        for (int i = line; i < *num_lines - 1; i++)
        {
            (*lines)[i] = (*lines)[i + 1];
        }

        (*lines)[*num_lines - 1] = NULL;

        (*num_lines)--;

        if (*y > 0)
        {
            (*y)--;
        }

        *x = strlen((*lines)[*y + *top]);

        return;
    }

    // Special case 2: Cursor is at the beginning of a line.
    if (col == 0)
    {
        int above_len = strlen((*lines)[line - 1]);
        int new_len = len + above_len;

        (*lines)[line - 1] = realloc((*lines)[line - 1], (new_len + 1) * sizeof(char));
        if ((*lines)[line - 1] == NULL)
        {
            return;
        }

        strcat((*lines)[line - 1], (*lines)[line]);

        free((*lines)[line]);

        for (int i = line; i < *num_lines - 1; i++)
        {
            (*lines)[i] = (*lines)[i + 1];
        }

        (*lines)[*num_lines - 1] = NULL;

        (*num_lines)--;

        (*y)--;

        *x = above_len;

        return;
    }

    // Move all characters to the left.
    for (int i = col; i < len; i++)
    {
        (*lines)[line][i - 1] = (*lines)[line][i];
    }
    (*lines)[line][len - 1] = '\0';
    (*x)--;
}

/* Remove the character after the cursor. */
void suppr_key(char ***lines, int *num_lines, int *top, int *y, int *x)
{
    int line = *y + *top;
    int col = *x;
    int len = strlen((*lines)[line]);

    // Special case 1: Cursor is at the end of the line, but not at the end of the file.
    if (col >= len && line < *num_lines - 1)
    {
        int above_len = strlen((*lines)[line + 1]);
        int new_len = len + above_len;

        (*lines)[line] = realloc((*lines)[line], (new_len + 1) * sizeof(char));
        if ((*lines)[line] == NULL)
        {
            return;
        }

        strcat((*lines)[line], (*lines)[line + 1]);

        free((*lines)[line + 1]);

        for (int i = line + 1; i < *num_lines - 1; i++)
        {
            (*lines)[i] = (*lines)[i + 1];
        }

        (*lines)[*num_lines - 1] = NULL;

        (*num_lines)--;

        *x = len;

        return;
    }

    // No need of removal (Last character of the file)
    if (col >= len)
    {
        return;
    }

    // Move all characters to the left.
    for (int i = col; i < len; i++)
    {
        (*lines)[line][i] = (*lines)[line][i + 1];
    }
    (*lines)[line][len - 1] = '\0';
}