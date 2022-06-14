/*
*	moveMapProc.h
*	This header stores prototypes of classes and functions responsible 
*	for processing the player's movement on the map
*
*/

#ifndef MoveMapProc_H 
#define MoveMapProc_H

#include <fstream>
#include <vector>
#include <iostream>

#include "menu.h"

using namespace std;

class Nature : public Point
{
private:
	char simbol;
	int text, bg;
	
public:
	Nature(int x, int y, char simbol);
	void Print();
	char GetSimbol();
};

class Person : public Point
{
public:
	bool toLeft(bool canPass);
	bool toRight(bool canPass);
	bool toUp(bool canPass);
	bool toDown(bool canPass);
};

class Cls
{	
public:
	void SetCls(Point start, Point end);
	void toLeft();
	void toRight();
	void toUp();
	void toDown();
	void Print(vector<string> map);
	
private:
	Point start, end;
};

//Global vars
extern Nature *globEnvirCell;
const int clsHeight = 11;
const int clsWidth = 21;
extern int mapHeight;
extern int mapWidth;
extern Point startClsPrint;
extern Point endClsPrint;
extern Cls cls;
extern Person person;
extern vector<string> map;

extern string action;

//others funcs
bool recognEnvirCell(Nature *envirCell, vector<string> &map);
vector<Nature *> GetEnvir(vector<string> map, Person person);
vector<string> FileReading();
void framePrint();
void collectRes(string resource, int quan);

#endif //MoveMapProc_H

