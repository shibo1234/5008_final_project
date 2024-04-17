//
// Created by shibo zheng on 4/15/24.
//

#include "snake_game.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    g_main_window = initscr();
    if (!g_main_window) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }
    noecho();
    curs_set(0);
    keypad(g_main_window, TRUE);

    initialize_game();
    getmaxyx(g_main_window, g_height, g_width);
    g_width = DESIRED_WIDTH;
    g_height = DESIRED_HEIGHT;


    snake_draw_board();
    snake_draw_fruit();

    pos head = {5, 5};
    enqueue(head);
//    int key = KEY_RIGHT;

    while (true) {
        int ch = getch();
        switch (ch) {
            case KEY_DOWN: head.y++; break;
            case KEY_RIGHT: head.x++; break;
            case KEY_UP: head.y--; break;
            case KEY_LEFT: head.x--; break;
        }

        if (!snake_move_player(head)) {
            snake_game_over();
            break;
        }
    }
    mvprintw(g_height / 2, g_width / 2, "Game Over! Press any key to exit.");
    getch();
    endwin();
    return 0;
}
