#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "input.h"
#include "terminal.h"

#define WIDTH 20
#define HEIGHT 15
#define SNAKE_START_LEGTH 3
#define FPS 3
#define SNAKE_COLOR GREEN
#define BORDERS_COLOR GREY
#define APPLE_COLOR RED


struct Point {
    int x;
    int y;
};

void* update_game(void *_dir);

