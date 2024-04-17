//
// Created by shibo zheng on 4/15/24.
//
#include "snake_game.h"
#include <stdlib.h>
#include <time.h>


WINDOW *g_main_window;
int g_width, g_height;
pos fruit;
snake *front = NULL, *back = NULL;
bool spaces[DESIRED_HEIGHT][DESIRED_WIDTH];

void initialize_game() {
    for (int y = 0; y < DESIRED_HEIGHT; y++) {
        for (int x = 0; x < DESIRED_WIDTH; x++) {
            spaces[y][x] = false;
        }
    }
}

void enqueue(pos position) {
    snake *new_node = (snake*)malloc(sizeof(snake));
    if (new_node == NULL) {
        endwin();
        fprintf(stderr, "Failed to allocate memory!\n");
        exit(EXIT_FAILURE);
    }
    new_node->position = position;
    new_node->tail = NULL;
    new_node->pre = back;

    if (back != NULL) {
        back->tail = new_node;
    }
    back = new_node;

    if (front == NULL) {
        front = new_node;
    }
}

pos dequeue() {
    if (front == NULL) {
        endwin();
        fprintf(stderr, "Queue is empty!\n");
        exit(EXIT_FAILURE);
    }

    snake *previous_front = front;
    pos position = previous_front->position;
    front = front->tail;

    if (front != NULL) {
        front->pre = NULL;
    } else {
        back = NULL;
    }

    free(previous_front);
    return position;
}

void snake_game_over() {
    snake *current = front;
    while (current != NULL) {
        snake *temp = current;
        current = current->tail;
        free(temp);
    }
//    endwin();
//    exit(0);
}

void snake_draw_board() {
    for (int i = 0; i < g_height; i++) {
        mvwaddch(g_main_window, i, 0, ACS_VLINE);
        mvwaddch(g_main_window, i, g_width - 1, ACS_VLINE);
    }
    for (int i = 1; i < g_width - 1; i++) {
        mvwaddch(g_main_window, 0, i, ACS_HLINE);
        mvwaddch(g_main_window, g_height - 1, i, ACS_HLINE);
    }
}


void snake_draw_fruit() {
    int idx_x, idx_y;
    do {
        idx_x = rand() % (g_width - 2) + 1;
        idx_y = rand() % (g_height - 2) + 1;
    } while (spaces[idx_y][idx_x]);

//    spaces[idx_y][idx_x] = true;
    fruit.x = idx_x;
    fruit.y = idx_y;
    mvwaddch(g_main_window, idx_y, idx_x, 'F');
}

bool collision_detect(pos position) {
    return position.x < 0 || position.x >= g_width - 1 || position.y < 0 || position.y >= g_height - 1;
}


bool snake_move_player(pos head) {
//    if (collision_detect(head)) {
////        snake_game_over();
//        return false;
//    }

    if (spaces[head.y][head.x]) {
//        snake_game_over();
        return false;
    }
    spaces[head.y][head.x] = true;
    enqueue(head);

    if (head.x == fruit.x && head.y == fruit.y) {
        snake_draw_fruit();
    } else {
        pos tail = dequeue();
        spaces[tail.y][tail.x] = false;
        mvwaddch(g_main_window, tail.y, tail.x, ' ');
    }
    mvwaddch(g_main_window, head.y, head.x, 'S');
    wrefresh(g_main_window);
    return true;
}
