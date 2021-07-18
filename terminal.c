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

void print_in(int x, int y, char* str, char* color) {
    printf("\033[%d;%dH%s%s\n", y + 1, x*2 + 1, color, str);
}

void print_square(int x, int y, char* color) {
    printf("\033[%d;%dH%s%s\n", y + 1, x*2 + 1, color, "  ");
}
