#include "game.h"


void print_borders() {
    for (int i = 0; i <= WIDTH; i++) {
        print_square(i, 0, GREY);
        print_square(i, HEIGHT, GREY);
    }
    for (int i = 0; i <= HEIGHT; i++) {
        print_square(0, i, GREY);
        print_square(WIDTH, i, GREY);
    }
}

void restart(struct Point *player, enum direction *dir) {
    clear_terminal();
    hide_cursor();
    print_borders();
    *dir = Right;

    int max_player_length = WIDTH * HEIGHT;
    for (int i = 0; i < max_player_length+1; i++) {
        player[i].x = 0;
        player[i].y = 0;
    }
    (*player).x = WIDTH / 2;
    (*player).y = HEIGHT / 2;
}

bool is_collised_with_wals(struct Point *player) {
    if ((*player).x < 1) return true;
    if ((*player).x >= WIDTH) return true;
    if ((*player).y < 1) return true;
    if ((*player).y >= HEIGHT) return true;

    return false;
}

void move_by_direction(struct Point *player, enum direction *dir) {
    if (*dir == Right) {
        (*player).x += 1;
    }
    if (*dir == Left) {
        (*player).x -= 1;
    }
    if (*dir == Up) {
        (*player).y -= 1;
    }
    if (*dir == Down) {
        (*player).y += 1;
    }
}

void update_tail(struct Point *player, int *score) {
    int player_length = SNAKE_START_LEGTH + *score;
    for (int i = player_length; i > 0; i--) {
        player[i].x = player[i - 1].x;
        player[i].y = player[i - 1].y;
    }
}

bool is_point_inside_gamefield(struct Point *point) {
    return (*point).x > 0 && (*point).y > 0 && (*point).x <= WIDTH && (*point).y <= HEIGHT;
}

void print_player(struct Point *player, int *score) {
    int player_length = SNAKE_START_LEGTH + *score;

    if (is_point_inside_gamefield(&player[player_length]))
        print_square(player[player_length].x, player[player_length].y, BLACK);
    for (int i = 0; i < player_length; i++) {
        if (is_point_inside_gamefield(&player[i]))
            print_square(player[i].x, player[i].y, GREEN);
    }
}

void* update_game(void *_dir) {
    struct Point *player = 0;
    int max_player_length = WIDTH * HEIGHT;
    player = malloc((max_player_length+1) * sizeof(struct Point));
    enum direction *dir = (enum direction*)_dir;
    int score = 0;

    restart(player, dir);

    while (1) {
        print_square((*player).x, (*player).y, GREEN);
        update_tail(player, &score);
        move_by_direction(player, dir);
        print_player(player, &score);
        if (is_collised_with_wals(player))
            restart(player, dir);

        usleep(1000000/FPS);
    }
    return 0;
}

