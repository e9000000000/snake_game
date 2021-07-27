#include "input.h"

struct termios oldattr;

int getch() {
    struct termios newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void restore_terminal_attrs() {
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
}

void set_direction_from_input(enum direction *dir) {
    int key = getch();
    if (key == 0x44) // arrows
        *dir = Left;
    else if (key == 0x43)
        *dir = Right;
    else if (key == 0x42)
        *dir = Down;
    else if (key == 0x41)
        *dir = Up;
    else if (key == 0x77) // w a s d
        *dir = Up;
    else if (key == 0x61)
        *dir = Left;
    else if (key == 0x73)
        *dir = Down;
    else if (key == 0x64)
        *dir = Right;
    else if (key == 0x68) // h j k l
        *dir = Left;
    else if (key == 0x6a)
        *dir = Down;
    else if (key == 0x6b)
        *dir = Up;
    else if (key == 0x6c)
        *dir = Right;
}
