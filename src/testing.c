#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 20
#define INITIAL_LENGTH 5
#define SPEED 150000 // microseconds

typedef struct {
    int x, y;
} Position;

typedef struct Node {
    Position pos;
    struct Node *next;
} Node;

Node *head;
Position fruit;
int direction;
int score;

WINDOW *win;

void initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    win = newwin(HEIGHT, WIDTH, 0, 0);
    keypad(win, TRUE);
    nodelay(win, TRUE);
    score = 0;
    srand(time(NULL));
    fruit.x = rand() % (WIDTH - 2) + 1;
    fruit.y = rand() % (HEIGHT - 2) + 1;
    direction = KEY_RIGHT;
    head = malloc(sizeof(Node));
    head->pos.x = WIDTH / 2;
    head->pos.y = HEIGHT / 2;
    head->next = NULL;
}

void draw() {
    wclear(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, "Score: %d", score);
    mvwaddch(win, fruit.y, fruit.x, '@');
    Node *current = head;
    while (current != NULL) {
        mvwaddch(win, current->pos.y, current->pos.x, 'O');
        current = current->next;
    }
    wrefresh(win);
}

void move_snake() {
    int ch = wgetch(win);
    if (ch != ERR) {
        switch (ch) {
            case KEY_UP:
                if (direction != KEY_DOWN) direction = KEY_UP;
                break;
            case KEY_DOWN:
                if (direction != KEY_UP) direction = KEY_DOWN;
                break;
            case KEY_LEFT:
                if (direction != KEY_RIGHT) direction = KEY_LEFT;
                break;
            case KEY_RIGHT:
                if (direction != KEY_LEFT) direction = KEY_RIGHT;
                break;
            case 'q':
                endwin();
                exit(EXIT_SUCCESS);
        }
    }
    Node *new_head = malloc(sizeof(Node));
    if (new_head == NULL) exit(EXIT_FAILURE);
    new_head->pos = head->pos;
    switch (direction) {
        case KEY_UP: new_head->pos.y--; break;
        case KEY_DOWN: new_head->pos.y++; break;
        case KEY_LEFT: new_head->pos.x--; break;
        case KEY_RIGHT: new_head->pos.x++; break;
    }
    new_head->next = head;
    head = new_head;
    if (head->pos.x == fruit.x && head->pos.y == fruit.y) {
        score += 10;
        fruit.x = rand() % (WIDTH - 2) + 1;
        fruit.y = rand() % (HEIGHT - 2) + 1;
    } else {
        Node *current = head, *prev = NULL;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        prev->next = NULL;
        free(current);
    }
    if (head->pos.x <= 0 || head->pos.x >= WIDTH - 1 ||
        head->pos.y <= 0 || head->pos.y >= HEIGHT - 1) {
        endwin();
        exit(EXIT_SUCCESS);
    }
}

int main() {
    initialize();
    while (true) {
        draw();
        move_snake();
        usleep(SPEED);
    }
    return 0;
}
