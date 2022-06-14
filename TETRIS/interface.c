#include "interface.h"

const int HEIGHT = 15, WIDTH = 23;
bool field[15][23];

void PrintFrame()
{
	int y, x;
	
	for(y = 0; y < HEIGHT; y ++)
	{
		for(x = 0; x < WIDTH; x ++)
		{
			if(x == 1 || x == WIDTH - 2 
			|| y == 1 || y == HEIGHT - 2 ||
			x == 12 || (y == 4 && x > 11))
				field[y][x] = true;
			else
				field[y][x] = false;
		}
	}
		
			
	for(y = 1; y < HEIGHT - 1; y ++)
	{
		for(x = 1; x < WIDTH - 1; x ++)
		{
			SetCur(x, y);
			
			if (field[y - 1][x] == true &&
			    field[y + 1][x] == true &&
			    field[y][x + 1] == true &&
			    field[y][x - 1] == true)
					printf("+");
					
			else if (field[y][x - 1] == true &&
					 field[y][x + 1] == true)
					 	printf("-");
					 	
			else if (field[y - 1][x] == true &&
					 field[y + 1][x] == true)
					 	printf("|");
			else 
				printf(" ");
		}
		printf("\n");
	}
}

void CursorHide() 
{
	CONSOLE_CURSOR_INFO curs = {0};
   	curs.dwSize = sizeof(curs);
  	curs.bVisible = FALSE;
   	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void SetCur(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

