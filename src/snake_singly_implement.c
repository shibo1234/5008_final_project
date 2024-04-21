#include "snake_singly.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

WINDOW *g_main_window;
int g_score, g_width, g_height;
pos fruit;
snake *front = NULL;
bool spaces[DESIRED_HEIGHT][DESIRED_WIDTH];

double speed = 1.0;
int sleep_time = 200000;
int last_dir = KEY_RIGHT;

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
    new_node->next = NULL;

    if (front == NULL) {
        front = new_node;
    } else{
        snake *current = front;
        while(current -> next != NULL){
            current = current -> next;
        }
        current -> next = new_node;
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
    front = front->next;

    free(previous_front);
    return position;
}

void snake_game_over() {
    snake *current = front;
    while (current != NULL) {
        snake *temp = current;
        current = current->next;
        free(temp);
    }
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
    mvwprintw(g_main_window, g_height + 1, 2, "Score: %d", g_score);
}


void snake_draw_fruit() {
    int idx_x, idx_y;
    do {
        idx_x = rand() % (g_width - 2) + 1;
        idx_y = rand() % (g_height - 2) + 1;
    } while (spaces[idx_y][idx_x]);

    fruit.x = idx_x;
    fruit.y = idx_y;
    mvwaddch(g_main_window, idx_y, idx_x, 'F');
}

bool collision_detect(pos position) {
    return position.x <= 0 || position.x >= g_width - 1 || position.y <= 0 || position.y >= g_height - 1;
}

void snake_move(pos head){
    while (true) {
        int ch = getch();
        if (ch != ERR) {
            switch (ch) {
                case KEY_DOWN: last_dir = KEY_DOWN; break;
                case KEY_RIGHT: last_dir = KEY_RIGHT; break;
                case KEY_UP: last_dir = KEY_UP; break;
                case KEY_LEFT: last_dir = KEY_LEFT; break;
            }
        }
        switch (last_dir) {
            case KEY_DOWN: head.y += speed; break;
            case KEY_RIGHT: head.x += speed; break;
            case KEY_UP: head.y -= speed; break;
            case KEY_LEFT: head.x -= speed; break;
        }
        refresh();
        if (!snake_move_player(head)) {
            snake_game_over();
            break;
        }
        usleep(sleep_time);
    }
}


bool snake_move_player(pos head) {
    if (collision_detect(head)) {
        return false;
    }

    if (spaces[head.y][head.x]) {
        return false;
    }
    spaces[head.y][head.x] = true;
    enqueue(head);

    if (head.x == fruit.x && head.y == fruit.y) {
        g_score += 10;
        sleep_time -= 20000;
        snake_draw_fruit();
    } else {
        pos tail = dequeue();
        spaces[tail.y][tail.x] = false;
        mvwaddch(g_main_window, tail.y, tail.x, ' ');
    }

    mvwaddch(g_main_window, head.y, head.x, 'S');
    mvwprintw(g_main_window, g_height + 1, 9, "%d", g_score);
    wrefresh(g_main_window);
    return true;
}
