#ifndef FINAL_PROJECT_SNAKE_SINGLY_H
#define FINAL_PROJECT_SNAKE_SINGLY_H
#include <stdbool.h>
#include <ncurses.h>

#define DESIRED_WIDTH  50
#define DESIRED_HEIGHT 15
#define SPEED 1

typedef struct {
    int x;
    int y;
} pos;

typedef struct snake {
    pos position;
    struct snake *next;
} snake;

extern WINDOW *g_main_window;
extern int g_score, g_width, g_height;
extern pos fruit;
extern bool spaces[DESIRED_HEIGHT][DESIRED_WIDTH];
extern snake *front;

bool collision_detect(pos position);
void initialize_game();
void enqueue(pos position);
pos dequeue();
void snake_game_over();
void snake_draw_board();
void snake_draw_fruit();
bool snake_move_player(pos head);
void snake_move(pos head);


#endif //FINAL_PROJECT_SNAKE_GAME_H
