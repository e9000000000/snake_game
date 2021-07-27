#include <pthread.h>
#include <signal.h>

#include "input.h"
#include "game.h"


void on_exit_signal(int dummy) {
    show_cursor();
    clear_terminal();
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, on_exit_signal);

    clear_terminal();
    hide_cursor();
    enum direction dir = Right;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, update_game, &dir);
    pthread_detach(thread_id);

    while (1) {
        set_direction_from_input(&dir);
    }

    return 0;
}
