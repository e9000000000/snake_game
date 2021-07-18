#pragma once
#include <stdio.h>

#define BLACK "\033[40m"
#define GREEN "\033[42m"
#define RED "\033[41m"
#define GREY "\033[47m"


void hide_cursor();

void show_cursor();

void clear_terminal();

void print_in(int x, int y, char* str, char* color);

void print_square(int x, int y, char* color);
