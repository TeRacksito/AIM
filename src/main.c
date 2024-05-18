#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "file_manage/pkg.h"
#include "screen_manage/pkg.h"
#include "special_keybind/pkg.h"

const int FPS = 60;

int main(int argc, char *argv[])
{
    // You can pass the file path as an argument.
    char *filename = argv[1];
    if (filename == NULL)
    {
        filename = "test.txt"; // Default file path.
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    clock_t t;

    char **lines;
    int num_lines;
    load_file(filename, &lines, &num_lines);

    int top = 0;

    for (int j = 0; j < num_lines; j++)
    {
        mvprintw(j, 0, lines[j]);
    }

    int ch;
    int i = 0;
    t = clock();
    while (true)
    {
        if (clock() - t < CLOCKS_PER_SEC / FPS)
        {
            continue;
        }
        t = clock();

        int y, x;
        getyx(stdscr, y, x);

        screen_update(lines, num_lines, top);

        mvprintw(LINES - 1, 0, "Pointer: x: %d, y: %d | ch: %d | num_lines: %d | top: %d", x, y, ch, num_lines, top);

        move(y, x);

        ch = getch();

        // All the special keys are handled here.
        // We want to move this to a separate file.

        bool is_movement = is_movement_key(ch);
        if (is_movement)
        {
            movement_key(ch, &y, &x);
            int line_index = y + top;
            if (line_index < 0)
            {
                y = 0;
                line_index = 0;
            }

            check_cursor_position(&top, num_lines, &y, &x);

            while (line_index >= num_lines)
            {
                y = num_lines - top - 1;
                line_index = y + top;
            }

            char *line = lines[line_index];

            if (x >= strlen(line))
            {
                x = strlen(line);
            }

            move(y, x);
            refresh();
            continue;
        }

        bool is_fast_movement = is_fast_movement_key(ch);
        if (is_fast_movement)
        {
            fast_movement_key(ch, lines, &y, &x);
            check_cursor_position(&top, num_lines, &y, &x);
            move(y, x);
            refresh();
            continue;
        }

        bool is_remove = is_remove_key(ch);
        if (is_remove)
        {
            remove_key(&lines, &num_lines, &top, &y, &x);
            check_cursor_position(&top, num_lines, &y, &x);
            move(y, x);
            refresh();
            continue;
        }

        bool is_suppr = is_suppr_key(ch);
        if (is_suppr)
        {
            suppr_key(&lines, &num_lines, &top, &y, &x);
            check_cursor_position(&top, num_lines, &y, &x);
            move(y, x);
            refresh();
            continue;
        }

        bool is_new_line = is_new_line_key(ch);
        if (is_new_line)
        {
            new_line_key(&lines, &num_lines, &top, &y, &x);
            check_cursor_position(&top, num_lines, &y, &x);
            move(y, x);
            refresh();
            continue;
        }

        bool is_save = is_save_key(ch);
        if (is_save)
        {
            save_file(filename, lines, num_lines);
            continue;
        }

        if (ch == 410)
        {
            resize_term(0, 0);
            continue;
        }

        // bool special_key = checkSpecialKeys(ch, lines, &num_lines, &top, &y, &x);
        // if (special_key)
        // {
        //     move(y, x);
        //     refresh();
        //     continue;
        // }

        // Normal key press.

        getyx(stdscr, y, x);
        int line = y + top;
        int col = x;
        int len = strlen(lines[line]);
        char *new_line = malloc(len + 2);
        if (new_line == NULL)
        {
            break;
        }
        strcpy(new_line, lines[line]);
        new_line[len + 1] = '\0';
        for (int i = len; i >= col; i--)
        {
            new_line[i + 1] = new_line[i];
        }
        new_line[col] = ch;
        free(lines[line]);
        lines[line] = new_line;

        move(y, x + 1);
        refresh();
    }

    endwin();
    return 0;
}
