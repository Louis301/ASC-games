#ifndef LOGIC_H 
#define LOGIC_H

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

//global
const int width = 40;
const int height = 15;

//funcs
class body;
body genFood(vector <body> snake);
void game();
void logo();

class body
{	
public:
	body();
	body(int x, int y);
	~body();
	void toLeft();
	void toRight();
	void toUp();
	void toDown();
	void print();
	void print(char simb);
	void clear();
	void check();
	bool operator == (const body & other);
	bool operator != (const body & other);	
	void operator = (const body & other);
	int getX();
	int getY();
		
private:
	int x, y;
	char simbol;
};

#endif //LOGIC_H
