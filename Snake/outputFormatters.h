//outputFormatters.h

#ifndef output_formatters_H 
#define output_formatters_H

#include <iostream> 
#include <vector> 
#include <conio.h>
#include <windows.h>

using namespace std;

enum COLORS
{
	red = 12,
	green = 10,
	grey = 8,
	blue = 1, 
	yellow = 14, 
	white = 15, 
	black = 0, 
	darkYellow = 6,
	lightBlue = 3,
	darkGreen = 2, 
	darkRed = 4
};

void SetCur(int, int);
void SetColor(int, int); 
void CursorHide();
void FieldPrinter(char, int, int, int, int, int, int);
void setColorText(int color1, string text, int color2);
int GetX_cur();
int GetY_cur();

#endif //output_formatters_H
