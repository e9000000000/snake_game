#pragma once

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


enum direction {
    Up,
    Down,
    Left,
    Right
};

int getch();

void set_direction_from_input(enum direction *dir);
