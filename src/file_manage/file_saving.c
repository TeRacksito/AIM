#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Save the lines into a file */
void save_file(char *filepath, char **lines, int num_lines)
{
    FILE *file = fopen(filepath, "w");
    if (file == NULL)
    {
        // File does not exist, not implemented yet
        return;
    }

    for (int i = 0; i < num_lines; i++)
    {
        fprintf(file, "%s\n", lines[i]);
    }

    fclose(file);
}