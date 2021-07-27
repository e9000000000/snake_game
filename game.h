#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

#include "input.h"
#include "terminal.h"

#define WIDTH 16
#define HEIGHT 16
#define SNAKE_START_LENGTH 3
#define FPS 11
#define SNAKE_COLOR GREEN
#define BORDERS_COLOR GREY
#define APPLE_COLOR RED


struct Point {
    int x;
    int y;
};

void* update_game(void *_dir);

