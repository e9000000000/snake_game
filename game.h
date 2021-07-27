#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "input.h"
#include "terminal.h"

#define WIDTH 2
#define HEIGHT 2
#define SNAKE_START_LENGTH 3
#define FPS 4
#define SNAKE_COLOR GREEN
#define BORDERS_COLOR GREY
#define APPLE_COLOR RED


struct Point {
    int x;
    int y;
};

void* update_game(void *_dir);

