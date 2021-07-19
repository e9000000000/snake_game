#pragma once
#include <stdio.h>

#define BLACK "\033[40m"
#define RED "\033[41m"
#define GREEN "\033[42m"
#define ORANGE "\033[43m"
#define BLUE "\033[44m"
#define MAGENTA "\033[45m"
#define CYAN "\033[46m"
#define GREY "\033[47m"
#define DEFAULT "\033[49m"


void hide_cursor();

void show_cursor();

void clear_terminal();

void print_text(int x, int y, char* str, char* color);
void print_num(int x, int y, int num, char* color);

void print_square(int x, int y, char* color);
