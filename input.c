#include "input.h"


int getch() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void set_direction_from_input(enum direction *dir) {
    int key = getch();
    if (key == 0x44)
        *dir = Left;
    else if (key == 0x43)
        *dir = Right;
    else if (key == 0x42)
        *dir = Down;
    else if (key == 0x41)
        *dir = Up;
}
