#include "game.h"


void draw_gamefield() {
    for (int i = 0; i <= WIDTH + 1; i++) {
        print_square(i, 0, BORDERS_COLOR);
        print_square(i, HEIGHT+1, BORDERS_COLOR);
    }
    for (int i = 0; i <= HEIGHT + 1; i++) {
        print_square(0, i, BORDERS_COLOR);
        print_square(WIDTH+1, i, BORDERS_COLOR);
    }
    print_text(0, HEIGHT + 2, "Score     - 0", DEFAULT);
    print_text(0, HEIGHT + 3, "Max score - 0", DEFAULT);
}

void respawn_apple(struct Point *apple) {
    (*apple).x = 1 + rand() % WIDTH;
    (*apple).y = 1 + rand() % HEIGHT;
}

void restart(struct Point *player, enum direction *dir, struct Point *apple, int *score) {
    clear_terminal();
    hide_cursor();
    draw_gamefield();
    *dir = Stop;
    *score = 0;

    int max_player_length = WIDTH * HEIGHT;
    for (int i = 0; i < max_player_length+1; i++) {
        player[i].x = 0;
        player[i].y = 0;
    }
    (*player).x = WIDTH / 2;
    (*player).y = HEIGHT / 2;

    respawn_apple(apple);
}

bool is_points_collided(struct Point *point1, struct Point *point2) {
    return (*point1).x == (*point2).x && (*point1).y == (*point2).y;
}

bool is_collised_with_wals(struct Point *player, int *score) {
    if ((*player).x < 1) return true;
    if ((*player).x > WIDTH) return true;
    if ((*player).y < 1) return true;
    if ((*player).y > HEIGHT) return true;

    int player_length = SNAKE_START_LEGTH + *score;
    for (int i = 1; i < player_length; i++) {
        if (is_points_collided(&player[0], &player[i]))
            return true;
    }

    return false;
}

void prepare_player_to_move(struct Point *player, int *score) {
    int player_length = SNAKE_START_LEGTH + *score;
    for (int i = player_length; i > 0; i--) {
        player[i].x = player[i - 1].x;
        player[i].y = player[i - 1].y;
    }
}

void move_by_direction(struct Point *player, enum direction *dir, int *score) {
    if (*dir == Stop)
        return;

    prepare_player_to_move(player, score);

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

bool is_point_inside_gamefield(struct Point *point) {
    return (*point).x > 0 && (*point).y > 0 && (*point).x <= WIDTH && (*point).y <= HEIGHT;
}

void draw_changes(struct Point *player, struct Point *apple, int *score, int *maxScore) {
    int player_length = SNAKE_START_LEGTH + *score;

    if (is_point_inside_gamefield(&player[player_length]))
        print_square(player[player_length].x, player[player_length].y, DEFAULT);
    for (int i = 0; i < player_length; i++) {
        if (is_point_inside_gamefield(&player[i]))
            print_square(player[i].x, player[i].y, SNAKE_COLOR);
    }

    if (is_point_inside_gamefield(apple))
        print_square((*apple).x, (*apple).y, APPLE_COLOR);

    print_num(6, HEIGHT + 2, *score, DEFAULT);
    print_num(6, HEIGHT + 3, *maxScore, DEFAULT);
}

void* update_game(void *_dir) {
    srand(time(0));
    struct Point *player = 0;
    int max_player_length = WIDTH * HEIGHT;
    player = malloc((max_player_length+1) * sizeof(struct Point));
    enum direction *dir = (enum direction*)_dir;
    struct Point apple;
    int score = 0;
    int maxScore = 0;

    restart(player, dir, &apple, &score);

    while (1) {
        print_square((*player).x, (*player).y, SNAKE_COLOR);
        move_by_direction(player, dir, &score);
        draw_changes(player, &apple, &score, &maxScore);
        if (is_collised_with_wals(player, &score))
            restart(player, dir, &apple, &score);
        if (is_points_collided(player, &apple)) {
            score += 1;
            if (score > maxScore)
                maxScore = score;
            respawn_apple(&apple);
        }

        usleep(1000000/FPS);
    }
    return 0;
}

