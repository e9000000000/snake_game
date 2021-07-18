#include "terminal.h"

void hide_cursor() {
    printf("\e[?25l");
}

void show_cursor() {
    printf("\e[?25h");
}

void clear_terminal() {
    printf("\033c");
}

void print_in(int x, int y, char* str) {
    printf("\033[%d;%dH%s\n", y+1, x+1, str);
}
