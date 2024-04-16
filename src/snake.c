//
// Created by shibo zheng on 4/15/24.
//

#include "snake_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <tclTomMath.h>

int main() {
    srand(time(NULL));

    g_main_window = initscr();
    if (g_main_window == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }

    noecho();
    curs_set(0);
    keypad(g_main_window, TRUE);


    getmaxyx(g_main_window, g_height, g_width);
    g_width = MIN(g_width, DESIRED_WIDTH);
    g_height = MIN(g_height, DESIRED_HEIGHT);

    spaces = (bool *) calloc(g_width * g_height, sizeof(bool));
    if (spaces == NULL) {
        endwin();
        fprintf(stderr, "Failed to allocate memory for spaces.\n");
        exit(EXIT_FAILURE);
    }

    snake_draw_board();
    snake_draw_fruit();

    pos head = {5, 5};
    enqueue(head);

    int key = KEY_RIGHT;
    while (true) {
        int ch = getch();
        switch (ch) {
            case KEY_DOWN:
                head.y++;
                break;
            case KEY_RIGHT:
                head.x++;
                break;
            case KEY_UP:
                head.y--;
                break;
            case KEY_LEFT:
                head.x--;
                break;
            default:
                continue;
        }

        if (!snake_move_player(head)) {
            break;
        }
    }

    snake_game_over();
    return 0;
}