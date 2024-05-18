#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Load a file into an array of strings and return the number of lines */
void load_file(char *filepath, char ***lines, int *num_lines)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        // File does not exist, not implemented yet
        return;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int capacity = 10;
    *num_lines = 0;
    *lines = malloc(capacity * sizeof(char *));

    if (*lines == NULL)
    {
        fclose(file);
        return;
    }

    while ((read = getline(&line, &len, file)) != -1)
    {
        if (*num_lines >= capacity)
        {
            capacity *= 2;
            *lines = realloc(*lines, capacity * sizeof(char *));
            if (*lines == NULL)
            {
                free(line);
                fclose(file);
                return;
            }
        }

        if (line[read - 1] == '\n')
        {
            line[read - 1] = '\0';
            read--;
        }

        (*lines)[*num_lines] = malloc((read + 1) * sizeof(char));
        if ((*lines)[*num_lines] == NULL)
        {
            free(line);
            fclose(file);
            return;
        }
        strcpy((*lines)[*num_lines], line);
        (*num_lines)++;
    }

    free(line);
    fclose(file);
}