#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "terminal.h"
#include "input.h"

#define WIDTH 20
#define HEIGHT 15


char** create_field() {
    char **field = (char**)malloc(HEIGHT * sizeof(char*));
    for (int i = 0; i < HEIGHT; i++) {
        field[i] = (char*)malloc(WIDTH * sizeof(char));
        for (int j = 0; j < WIDTH; j++)
            field[i][j] = '#';
    }
    return field;
}

void print_field(char **field) {
    int newLineSymbolAmount = HEIGHT;
    int lineLength = (WIDTH * HEIGHT + newLineSymbolAmount);
    char *printLine = malloc((lineLength+1) * sizeof(char));
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printLine[(WIDTH + 1) * i + j] = field[i][j];
        }
        int lineEndIndex = (WIDTH + 1) * i + WIDTH;
        printLine[lineEndIndex] = '\n';

    }
    printLine[lineLength] = '\0';
    printf(printLine);
    free(printLine);
}


int main(int argc, char **argv) {
    char **field = create_field();
    clear_terminal();
    hide_cursor();
    print_field(field);

    int x = 0;
    int y = 0;
    while (1) {
        print_in(x, y, "7");
        int key = getch();
        if (key == 0x44)
            x--;
        if (key == 0x43)
            x++;
        if (key == 0x42)
            y--;
        if (key == 0x41)
            y++;
    }

    show_cursor();
    return 0;
}
