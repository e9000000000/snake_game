#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "terminal.h"
#include "input.h"

#define WIDTH 20
#define HEIGHT 15


void* update_game(void *_dir) {
    int x = 0;
    int y = 0;
    enum direction *dir = (enum direction*)_dir;
    while (1) {
        print_square(x, y, BLACK);
        if (*dir == Right) {
            x++;
        }
        if (*dir == Left) {
            x--;
        }
        if (*dir == Up) {
            y--;
        }
        if (*dir == Down) {
            y++;
        }
        if (x < 0) x = 0;
        if (x >= WIDTH) x = WIDTH - 1;
        if (y < 0) y = 0;
        if (y >= HEIGHT) y = HEIGHT - 1;
        print_square(x, y, GREEN);

        usleep(100000);
    }
    return 0;
}

int main(int argc, char **argv) {
    clear_terminal();
    hide_cursor();
    enum direction dir = Right;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, update_game, &dir);
    pthread_detach(thread_id);

    while (1) {
        set_direction_from_input(&dir);
        //printf("dir: %d", dir);
    }

    show_cursor();
    return 0;
}
