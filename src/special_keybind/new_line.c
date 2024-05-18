#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

/* Check if the key is a new line key. */
bool is_new_line_key(int ch)
{
    return ch == KEY_ENTER || ch == 10;
}

/* Add a new line at the cursor position. */
void new_line_key(char ***lines, int *num_lines, int *top, int *y, int *x)
{
    int line = *y + *top;
    int col = *x;
    int len = strlen((*lines)[line]);

    // Case 1: Cursor is at the beginning of the line.
    if (col == 0)
    {
        char *new_line = malloc(1 * sizeof(char));
        if (new_line == NULL)
        {
            return;
        }
        new_line[0] = '\0';

        char **temp = realloc(*lines, (*num_lines + 1) * sizeof(char *));
        if (temp == NULL)
        {
            free(new_line);
            return;
        }
        *lines = temp;

        for (int i = *num_lines; i > line; i--)
        {
            (*lines)[i] = (*lines)[i - 1];
        }

        (*lines)[line] = new_line;

        (*num_lines)++;
        *x = 0;
    }

    // Case 2: Cursor is at the end of the line.
    else if (col == len)
    {
        char *new_line = malloc(1 * sizeof(char));
        if (new_line == NULL)
        {
            return;
        }
        new_line[0] = '\0';

        char **temp = realloc(*lines, (*num_lines + 1) * sizeof(char *));
        if (temp == NULL)
        {
            free(new_line);
            return;
        }
        *lines = temp;

        for (int i = *num_lines; i > line + 1; i--)
        {
            (*lines)[i] = (*lines)[i - 1];
        }

        (*lines)[line + 1] = new_line;

        (*num_lines)++;
        *x = 0;
    }

    // Case 3: Cursor is somewhere in the middle of the line.
    else
    {
        char *new_line = malloc((len - col + 1) * sizeof(char));
        if (new_line == NULL)
        {
            return;
        }
        strcpy(new_line, &(*lines)[line][col]);

        char *temp = realloc((*lines)[line], (col + 1) * sizeof(char));
        if (temp == NULL)
        {
            free(new_line);
            return;
        }
        (*lines)[line] = temp;
        (*lines)[line][col] = '\0';

        char **temp_lines = realloc(*lines, (*num_lines + 1) * sizeof(char *));
        if (temp_lines == NULL)
        {
            free(new_line);
            return;
        }
        *lines = temp_lines;

        for (int i = *num_lines; i > line + 1; i--)
        {
            (*lines)[i] = (*lines)[i - 1];
        }
        (*lines)[line + 1] = new_line;

        (*num_lines)++;
        *x = 0;
    }

    // Cursor unchecked reallocation.
    (*y)++;
}