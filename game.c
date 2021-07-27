#include "game.h"


void draw_gamefield(int *winCount) {
    for (int i = 0; i <= WIDTH + 1; i++) {
        print_square(i, 0, BORDERS_COLOR);
        print_square(i, HEIGHT+1, BORDERS_COLOR);
    }
    for (int i = 0; i <= HEIGHT + 1; i++) {
        print_square(0, i, BORDERS_COLOR);
        print_square(WIDTH+1, i, BORDERS_COLOR);
    }
    print_text(0, HEIGHT + 2, "score     - 0", DEFAULT);
    if (*winCount)
        print_text(0, HEIGHT + 3, "wins      - 0", DEFAULT);
    else
        print_text(0, HEIGHT + 3, "bestScore - 0", DEFAULT);
}

bool is_points_collided(struct Point *point1, struct Point *point2) {
    return (*point1).x == (*point2).x && (*point1).y == (*point2).y;
}

bool is_point_inside_gamefield(struct Point *point) {
    return (*point).x > 0 && (*point).y > 0 && (*point).x <= WIDTH && (*point).y <= HEIGHT;
}

void respawn_apple(struct Point *player, struct Point *apple, int *score) {
    int player_length = SNAKE_START_LENGTH + *score;
    if (*score <= 0) player_length = 1;
    int field_area = WIDTH*HEIGHT;
    int awailable_amount = field_area - player_length;
    struct Point *all = malloc(field_area * sizeof(struct Point));
    struct Point *awailable = malloc(awailable_amount * sizeof(struct Point));

    for (int i = 0; i < field_area; i++) {
        all[i].y = i / WIDTH + 1;
        all[i].x = i % WIDTH + 1;
    }

    for (int i = 0; i < player_length; i++) {
        int index = (player[i].y - 1) * WIDTH + (player[i].x - 1);
        if (index < 0 || index >= field_area) continue;

        all[index].x = 0;
        all[index].y = 0;
    }

    int offset = 0;
    for (int i = 0; i < awailable_amount; i++) {
        struct Point point = all[i + offset];
        if (is_point_inside_gamefield(&point)) {
            awailable[i].x = point.x;
            awailable[i].y = point.y;
        }
        else {
            offset += 1;
            i--;
        }
    }

    struct Point chousen_point = awailable[rand() % awailable_amount];
    (*apple).x = chousen_point.x;
    (*apple).y = chousen_point.y;

    free(all);
    free(awailable);
}

void restart(struct Point *player, enum direction *dir, struct Point *apple, int *score, int *winCount) {
    clear_terminal();
    hide_cursor();
    draw_gamefield(winCount);
    *dir = Stop;
    *score = 0;

    int max_player_length = WIDTH * HEIGHT;
    for (int i = 0; i < max_player_length+1; i++) {
        player[i].x = 0;
        player[i].y = 0;
    }
    (*player).x = WIDTH / 2;
    (*player).y = HEIGHT / 2;

    respawn_apple(player, apple, score);
}

bool is_collised_with_wals(struct Point *player, int *score) {
    if ((*player).x < 1) return true;
    if ((*player).x > WIDTH) return true;
    if ((*player).y < 1) return true;
    if ((*player).y > HEIGHT) return true;

    int player_length = SNAKE_START_LENGTH + *score;
    for (int i = 1; i < player_length; i++) {
        if (is_points_collided(&player[0], &player[i]))
            return true;
    }

    return false;
}

void prepare_player_to_move(struct Point *player, int *score) {
    int player_length = SNAKE_START_LENGTH + *score;
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
        (*player).x++;
    }
    if (*dir == Left) {
        (*player).x--;
    }
    if (*dir == Up) {
        (*player).y--;
    }
    if (*dir == Down) {
        (*player).y++;
    }
}

void draw_changes(struct Point *player, struct Point *apple, int *score, int *bestScore, int *winCount) {
    int player_length = SNAKE_START_LENGTH + *score;

    if (is_point_inside_gamefield(&player[player_length]))
        print_square(player[player_length].x, player[player_length].y, DEFAULT);
    for (int i = 0; i < player_length; i++) {
        if (is_point_inside_gamefield(&player[i]))
            print_square(player[i].x, player[i].y, SNAKE_COLOR);
    }

    if (is_point_inside_gamefield(apple))
        print_square((*apple).x, (*apple).y, APPLE_COLOR);

    print_num(6, HEIGHT + 2, *score, DEFAULT);
    if (*winCount)
        print_num(6, HEIGHT + 3, *winCount, DEFAULT);
    else
        print_num(6, HEIGHT + 3, *bestScore, DEFAULT);
}

bool is_max_score(int *score) {
    return SNAKE_START_LENGTH + *score >= WIDTH * HEIGHT;
}

void* update_game(void *_dir) {
    srand(time(0));
    struct Point *player = 0;
    int max_player_length = WIDTH * HEIGHT;
    player = malloc((max_player_length+1) * sizeof(struct Point));
    enum direction *dir = (enum direction*)_dir;
    struct Point apple;
    int score = 0;
    int bestScore = 0;
    int winCount = 0;

    restart(player, dir, &apple, &score, &winCount);

    while (1) {
        move_by_direction(player, dir, &score);
        if (is_collised_with_wals(player, &score))
            restart(player, dir, &apple, &score, &winCount);
        if (is_points_collided(player, &apple)) {
            score++;
            if (score > bestScore)
                bestScore = score;
            if (is_max_score(&score)) {
                winCount++;
                restart(player, dir, &apple, &score, &winCount);
                continue;
            }
            respawn_apple(player, &apple, &score);
        }

        draw_changes(player, &apple, &score, &bestScore, &winCount);
        usleep(1000000/FPS);
    }
    return 0;
}

