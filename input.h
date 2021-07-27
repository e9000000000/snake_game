#pragma once

#include <termios.h>
#include <unistd.h>
#include <stdio.h>


enum direction {
    Up,
    Down,
    Left,
    Right,
    Stop
};

int getch();
void restore_terminal_attrs();

void set_direction_from_input(enum direction *dir);
