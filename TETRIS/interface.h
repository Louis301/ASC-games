#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>

void SetCur(int x, int y); 
void PrintFrame();
void SetColor(int text, int bg);
void CursorHide(); 

enum ConsoleColor {
	BLACK = 0,
	BLUE,
	DARK_GREEN,
	CYAN,
	DARK_RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	LIGHT_BLUE,
	GREEN,
	LIGHT_CYAN,	
	RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};

extern const int HEIGHT, WIDTH;
extern bool field[15][23];

#endif  // INTERFACE_H
