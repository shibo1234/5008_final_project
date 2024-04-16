//
// Created by shibo zheng on 4/15/24.
//
#include "snake_game.h"
#include <stdlib.h>
#include <time.h>


WINDOW *g_main_window;
int g_score, g_width, g_height;
pos fruit;
bool *spaces;
snake *front = NULL, *back = NULL;

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
    free(spaces);
    snake *current = front;
    while (current != NULL) {
        snake *temp = current;
        current = current->tail;
        free(temp);
    }
    endwin();
    exit(0);
}

void snake_draw_board() {
    for (int i = 0; i < g_height; i++) {
        mvwaddch(g_main_window, i, 0, 'X');
        mvwaddch(g_main_window, i, g_width - 1, 'X');
    }
    for (int i = 1; i < g_width - 1; i++) {
        mvwaddch(g_main_window, 0, i, 'X');
        mvwaddch(g_main_window, g_height - 1, i, 'X');
    }
    mvwprintw(g_main_window, g_height + 1, 2, "Score: %d", g_score);
}

void snake_draw_fruit() {
    int idx;
    do {
        idx = rand() % (g_width * g_height);
        fruit.y = idx / g_width;
        fruit.x = idx % g_width;
    } while (spaces[idx] || fruit.y == 0 || fruit.y == g_height - 1 || fruit.x == 0 || fruit.x == g_width - 1);

    mvwaddch(g_main_window, fruit.y, fruit.x, 'F');
}

bool snake_move_player(pos head) {
    int idx = g_width * head.y + head.x;
    if (spaces[idx]) {
        snake_game_over();
    }

    spaces[idx] = true;
    enqueue(head);
    g_score += 10;

    if (head.x == fruit.x && head.y == fruit.y) {
        g_score += 1000;
        snake_draw_fruit();
    } else {
        pos tail = dequeue();
        int tail_idx = g_width * tail.y + tail.x;
        spaces[tail_idx] = false;
        mvwaddch(g_main_window, tail.y, tail.x, ' ');
    }
    mvwaddch(g_main_window, head.y, head.x, 'S');
    mvwprintw(g_main_window, g_height + 1, 9, "%d", g_score);
    wrefresh(g_main_window);
    return true;
}
