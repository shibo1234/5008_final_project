//
// Created by shibo zheng on 4/15/24.
//

#ifndef FINAL_PROJECT_SNAKE_GAME_H
#define FINAL_PROJECT_SNAKE_GAME_H
#include <stdbool.h>
#include <ncurses.h>

#define DESIRED_WIDTH  70
#define DESIRED_HEIGHT 25

typedef struct {
    int x;
    int y;
} pos;

typedef struct snake {
    pos position;
    struct snake *pre;
    struct snake *tail;
} snake;

extern WINDOW *g_main_window;
extern int g_score, g_width, g_height;
extern pos fruit;
extern bool *spaces;
extern snake *front, *back;

void enqueue(pos position);
pos dequeue();
void snake_game_over();
void snake_draw_board();
void snake_draw_fruit();
bool snake_move_player(pos head);


#endif //FINAL_PROJECT_SNAKE_GAME_H
