/*
	Name: TIC TAC TOE
	Copyright: -
	Author: Orlik
	Date: 26.02.22 18:05
	Description: Console game 
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

//----------------------prototypes
class Gamer;
void setCur(int x, int y);
void setColor(int text, int bg);
void pauseAnimation();
void printMessActiveUser(bool); 
bool checkingTheWin(vector<string>, bool);
void selectCellHit(Gamer *, vector<string> &field);
void logo();


//----------------------Global
enum CMD
{
	W = 119,
	S = 115,
	A = 97, 
	D = 100, 
	ESC = 27,
	UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13,
    Y = 121,
    N = 110
};

enum COLORS
{
	RED = 12,
	GREEN = 10,
	DARK_GREY = 8,
	GREY = 7,
	BLUE = 1, 
	YELLOW = 14, 
	WHITE = 15, 
	BLACK = 0, 
	DARK_YELLOW = 6,
	LIGHT_BLUE = 3,
	DARK_GREEN = 2, 
	DARK_RED = 4
};

enum FRAME_ELEMENTS
{
	VERT = (char)179,
	HOR = (char)196,
	CROSS = (char)197
};

enum LOTS 
{
	ANGLE,
	SIDE,
	CENTER	
};


//-------------------classes
class Point
{
	public:
		~Point() {}
		Point() {x = 0; y = 0;}
		
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
		
		int GetX() {return x;}
		int GetY() {return y;}
		void Print() {cout << x << "   " << y << endl;}
		
		void SetCoord(int x, int y) {
			this->x = x;
			this->y = y;
		}
		
	protected:
		int x, y;
};

class Gamer : public Point
{
	public:
		~Gamer() {
		}
		
		Gamer(int x, int y) {this->x = x; this->y = y;}
		void Input() {setCur(this->x, this->y);}
		void ToUp() {if(this->y != 1) this->y -= 2;}
		void ToDown() {if(this->y != 5) this->y += 2;}
		void ToLeft() {if(this->x != 1) this->x -= 2;}
		void ToRight() {if(this->x != 5) this->x += 2;}
		
		void PrintSimbol(bool motionUser) {
			
			if(motionUser)
			{
				setColor(12, 0);
				cout << 'X';
			}
			else
			{
				setColor(14, 0);
				cout << 'O';
			}
			
			setColor(15, 0);
		}
};


int main() {
	
	//--------------------print of logo
	logo();
	forNewGame:
	
	//--------------------init the vars
	srand(time(NULL));
	
	vector<string> field;
	bool exit = false;
	Gamer user(1, 1);
	Gamer comp(0, 0);
	bool motionUser = rand() % 2; 
	
	//---------------------------fulling the game field
	for(int i = 0; i < 7; i++) 
		field.push_back("fffffff");
		
	for(int i = 0; i < 7; i++) 
	{
		for(int j = 0; j < 7; j++) 
		{
			if(i > 0 && i < 7 && j > 0 && j < 7)
				if(i % 2 != 0 && j % 2 != 0) 
					field[i][j] = 'e';
		}
	}
	
	//---------------------------printing of gameField
	for(int y = 1; y < 6; y++) 
	{
		for(int x = 1; x < 6; x++) 
		{
			setCur(x, y);
			
			if(field[y][x] == 'f') 
			{
				if(field[y - 1][x] == 'f' &&
				field[y][x + 1] == 'f' &&
				field[y + 1][x] == 'f' &&
				field[y][x - 1] == 'f') cout << (char)CROSS;
				
				else if(field[y][x - 1] == 'f' &&
				field[y][x + 1] == 'f') cout << (char)HOR;
				
				else if(field[y - 1][x] == 'f' &&
				field[y + 1][x] == 'f') cout << (char)VERT;
			}
			else
			{
				cout << ' ';
			}
		}
	}
	
	//---------------------------CMD signal's processing
	while(!exit)
	{
		MOTION_COMPUTER:
		if(checkingTheWin(field, !motionUser)) break;
		printMessActiveUser(motionUser);
		
		if(motionUser)
		{
			user.Input();
		
			switch(getch())
			{
				case UP:
					user.ToUp();
					break;
				 
				case DOWN:
					user.ToDown();
					break;
				 
				case LEFT:
					user.ToLeft();
					break; 
				
				case RIGHT:
					user.ToRight();
					break;
					
				case ENTER:
					if(field[user.GetY()][user.GetX()] == 'e')
					{
						user.PrintSimbol(motionUser);
						field[user.GetY()][user.GetX()] = 'x';
						motionUser = false;
						//Beep(1000, 100);
						goto MOTION_COMPUTER;
					}
					break;
				
				case ESC:
					setColor(WHITE, BLACK);
					exit = true;
					break;
					
				default:
					break; 
			}
		}
		else
		{
			pauseAnimation();
			selectCellHit(&comp, field); //изменение координат экземпл€ра comp
			comp.Input();
			
			comp.PrintSimbol(motionUser); //печать нолика
			field[comp.GetY()][comp.GetX()] = 'o';
			//Beep(1200, 100);
			
			motionUser = true;
		}
	}

	setCur(0, 7);
	cout << "Repeat? (y/n): \n";
	
	switch(getch())
	{
		case ESC: case N:
			return 0;
			break;
			
		case ENTER: case Y:
			system("cls");
			//main();
			goto forNewGame;
			break;
		
		default:
			return 0;
			break;
	}
}

//---------------------------funcs
void logo() {
	
	cout << "@Yuriy Orlik\n\n";
	
	setColor(RED, BLACK); 
	printf("*********************\n");
	printf("*                   *\n");
	printf("*    TIC TAC TOE    *\n");
	printf("*                   *\n");
	printf("*********************\n\n");
	
	setColor(YELLOW, BLACK); 
	cout << "arrows"; 
	setColor(WHITE, BLACK);
	cout << " - control";

	setColor(YELLOW, BLACK); 
	cout << "\nenter"; 
	setColor(WHITE, BLACK);
	cout << " - hit\n\n";
	
	setColor(WHITE, BLACK); 
	cout << "Press any key for continue... \n";
	
	getch();
	system("cls");
}

void setCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void setColor(int text, int bg) { 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void pauseAnimation() {
	setCur(8, 0);
	for(int i = 0; i < 3; i++) 
	{
		cout << "* ";
		Sleep(500);
	}	
	
	setCur(8, 0);
	cout << "      ";
}

void printMessActiveUser(bool motionUser) {

	setCur(0, 7);
	
	if(motionUser)
	{
		setColor(RED, BLACK);
		cout << "X - your move"; //red
	}
	else
	{
		setColor(YELLOW, BLACK);
		cout << "O - comp move"; //yellow
	}
}

bool checkingTheWin(vector<string> field, bool motionUser) {
	
	bool win = false;
	char simbolGamer;
	
	if(motionUser) simbolGamer = 'x';
	else simbolGamer = 'o';
	
	if(field[1][1] == simbolGamer && field[1][3] == simbolGamer && field[1][5] == simbolGamer) win = true;
	else if(field[3][1] == simbolGamer && field[3][3] == simbolGamer && field[3][5] == simbolGamer) win = true;
	else if(field[5][1] == simbolGamer && field[5][3] == simbolGamer && field[5][5] == simbolGamer) win = true;
	else if(field[1][1] == simbolGamer && field[3][1] == simbolGamer && field[5][1] == simbolGamer) win = true;
	else if(field[1][3] == simbolGamer && field[3][3] == simbolGamer && field[5][3] == simbolGamer) win = true;
	else if(field[1][5] == simbolGamer && field[3][5] == simbolGamer && field[5][5] == simbolGamer) win = true;
	else if(field[1][1] == simbolGamer && field[3][3] == simbolGamer && field[5][5] == simbolGamer) win = true;
	else if(field[1][5] == simbolGamer && field[3][3] == simbolGamer && field[5][1] == simbolGamer) win = true;
	
	int quan_empty = 0;
	for(int y = 1; y <= 5; y += 2)
		for(int x = 1; x <= 5; x += 2)
			if(field[y][x] == 'e') quan_empty++;
	
	if(win) 
	{
		setCur(7, 3);
		if(motionUser) cout << "---- YOU WIN! ----"; else cout << "---- YOU FAIL ----";
		return true; 
	}
	else if(quan_empty == 0)
	{
		setCur(7, 3);
		cout << "---- NOBODY ----";
		return true;
	}
	else return false;
}

void selectCellHit(Gamer *comp, vector<string> &field) {
	
	//-----------------------init data
	int position;
	Point start, end, hit_point;
	char simbol = 'o';
	vector<Point *> lotOfEndPoint;
	
	//-------------------------
	forCheckSecurePos: //if there is no winning position for the computer (O)
	
	for(int y = 1; y < 7; y += 2)
	{
		for(int x = 1; x < 7; x += 2)
		{
			if(field[y][x] == simbol) 
			{
				start.SetCoord(x, y);
				
				//-------------------init the lot of posible end points
				lotOfEndPoint.clear();
				
				if(x == 1 && y == 1)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i == 1 && j > 1 || i > 1 && j == 1 || i == j && i != y)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 3 && y == 1)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(j != x && i == 1 || j == x && i > 1)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 5 && y == 1) //+diag
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i == 1 && j < 5 || i > 1 && j == 5 || i + j == 6 && i != y)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 1 && y == 3)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i != y && j == 1 || i == y && j > 1)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 3 && y == 3)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i != y || j != x)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 5 && y == 3)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i != y && j == x || i == y && j < x)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 1 && y == 5) 
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i == 5 && j > 1 || i < 5 && j == 1 || i + j == 6 && i != y)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 3 && y == 5)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i == 5 && j != x || i < 5 && j == x)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				else if(x == 5 && y == 5)
				{
					for(int i = 1; i <= 5; i += 2)
						for(int j = 1; j <= 5; j += 2)
							if(i == 5 && j < 5 || i < 5 && j == 5 || i == j && i != y)
							{
								if(field[i][j] == simbol)
									lotOfEndPoint.push_back(new Point(j, i));
							}
				}
				
				//----------------------------search the end point
				for(auto elem : lotOfEndPoint)
				{
					end.SetCoord(elem->GetX(), elem->GetY());
					
					if(start.GetX() == end.GetX()) //vert
					{
						if((start.GetY() + end.GetY()) / 2 == 3) 
							hit_point.SetCoord(x, 3);
						else 
						{
							if(start.GetY() < 5 && end.GetY() < 5)
								hit_point.SetCoord(x, 5);
							else if(start.GetY() > 1 && end.GetY() > 1)
								hit_point.SetCoord(x, 1);
						}
					}
					else if(start.GetY() == end.GetY()) //hor
					{
						if((start.GetX() + end.GetX()) / 2 == 3) 
							hit_point.SetCoord(3, y);
						else 
						{
							if(start.GetX() < 5 && end.GetX() < 5)
								hit_point.SetCoord(5, y);
							else if(start.GetX() > 1 && end.GetX() > 1)
								hit_point.SetCoord(1, y);
						}
					}
					else if(start.GetX() == start.GetY() && end.GetX() == end.GetY()) //main diag
					{
						if((start.GetX() + end.GetX()) / 2 == 3) 
							hit_point.SetCoord(3, 3);
						else 
						{
							if(start.GetX() < 5 && end.GetX() < 5)
								hit_point.SetCoord(5, 5);
							else if(start.GetX() > 1 && end.GetX() > 1)
								hit_point.SetCoord(1, 1);
						}
					}
					else if(start.GetX() + start.GetY() == end.GetX() + end.GetY()) //other diag
					{
						if((start.GetX() + end.GetX()) / 2 == 3) 
							hit_point.SetCoord(3, 3);
						else 
						{
							if(start.GetX() < 5 && end.GetX() < 5)
								hit_point.SetCoord(5, 1);
							else if(start.GetX() > 1 && end.GetX() > 1)
								hit_point.SetCoord(1, 5);
						}
					}
						
					//---------------------checking the impact cell
					if(field[hit_point.GetY()][hit_point.GetX()] == 'e')
					{
						comp->SetCoord(hit_point.GetX(), hit_point.GetY());
						return;
					} 
				}
				
				continue;
			}
		}
	}
	
	if(simbol == 'o') 
	{
		simbol = 'x';
		goto forCheckSecurePos;
	}
	
	//----------------------random
	randomGeneration:
		
	int x, y;
	
	do {
		x = rand() % 5 + 1;
		y = rand() % 5 + 1;
	} while(x % 2 == 0 || y % 2 == 0);
	
	if(field[y][x] == 'e') 
		comp->SetCoord(x, y);
	else goto randomGeneration;
}

