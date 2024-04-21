
#include "snake_singly.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SLEEPTIME 200000

int main() {
    initscr();
    srand(time(NULL));
    g_main_window = initscr();
    if (!g_main_window) {
        fprintf(stderr, "Error initializing ncurses.\n");
        exit(EXIT_FAILURE);
    }
    noecho();
    cbreak();
    nodelay(stdscr, true);
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
    snake_move(head);

    mvprintw(g_height / 2, g_width / 2, "Game Over! Press any key to exit.");
    getch();
    endwin();
    return 0;
}
