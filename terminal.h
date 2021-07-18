#pragma once
#include <stdio.h>

#define DEFAULT "\033[49m"
#define GREEN "\033[42m"
#define RED "\033[41m"
#define GREY "\033[47m"


void hide_cursor();

void show_cursor();

void clear_terminal();

void print_text(int x, int y, char* str, char* color);
void print_num(int x, int y, int num, char* color);

void print_square(int x, int y, char* color);
