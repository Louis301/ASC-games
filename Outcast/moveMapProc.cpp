//moveMapProc.cpp

#include "outputFormatters.h"
#include "moveMapProc.h"

//global vars
Nature *globEnvirCell;
Point startClsPrint;
Point endClsPrint;
int mapHeight = 0;
int mapWidth = 0;
Person person;
Cls cls;
vector<string> map(1);

string action;

//Nature's funcs 
Nature::Nature(int x, int y, char simbol) {
	text = 15;
	bg = 0;
	this->x = x;
	this->y = y;
	this->simbol = simbol;
		
	if(simbol == 'W' || simbol == 'w') {
		text = yellow; 
		bg = darkYellow;
	}
		
	if(simbol == 'r') { //river
		text = lightBlue; 
		bg = blue;
	}
	
	if(simbol == 'k') { //kanabis
		text = darkGreen; 
		bg = white;
	}
	
	if(simbol == 's') { //stone
		text = grey; 
		bg = darkGrey;
	}
		
	if(simbol == 'g') {
		this->simbol = char(176);
		text = green; 
		bg = darkGreen;
	}
		
	if(simbol == 'c') {
		text = darkYellow; 
		bg = darkRed;
	}
}
	
void Nature::Print() {
	FieldPrinter(simbol, text, bg, 1, 1, x + 1, y + 1);
	SetColor(black, black);
	CursorHide();
}
	
char Nature::GetSimbol() {
	return simbol;
}


//Point's funcs
void Point::toLeft() {
	if(x > 1) x--;
}
	
void Point::toRight() {
	if(x < mapWidth - 2) x++;
}
	
void Point::toUp() {	
	if(y > 1) y--;
}
	
void Point::toDown() {	
	if(y < mapHeight - 2) y++;
}
	

//Person's funcs
bool Person::toLeft(bool canPass) {	
	if(canPass) 
	{
		if(x > 1) x--;
		return true;
	} 
}
	
bool Person::toRight(bool canPass) {	
	if(canPass) 
	{
		if(x < mapWidth - 2) x++;
		return true;
	} 
}
	
bool Person::toUp(bool canPass) {	
	if(canPass) 
	{
		if(y > 1) y--;
		return true;
	} 
}
	
bool Person::toDown(bool canPass) {	
	if(canPass) 
	{
		if(y < mapHeight - 2) y++;
		return true;
	} 
}
	
	
//Cls's funcs
void Cls::SetCls(Point start, Point end) {
	this->start = start;
	this->end = end;
}
	
void Cls::toLeft() {
	if(start.GetX() > 1) end.toLeft();
	start.toLeft(); 
}
	
void Cls::toRight() {
	if(end.GetX() < mapWidth - 2) start.toRight();
	end.toRight();  
}
	
void Cls::toUp() {
	if(start.GetY() > 1) end.toUp();
	start.toUp(); 
}
	
void Cls::toDown() {
	if(end.GetY() < mapHeight - 2) start.toDown();
	end.toDown(); 
}
	
void Cls::Print(vector<string> map) {
	
	vector<Nature *> cls;
	int clsX = 0, clsY = 0;
	
	for(int y = start.GetY(); y <= end.GetY(); y++)
	{
		for(int x = start.GetX(); x <= end.GetX(); x++)
			cls.push_back(new Nature(clsX++, clsY, map[y][x]));		
		clsY++;
		clsX = 0;
	} 	
	
	for(int i = 0; i < cls.size(); i++) 
		cls[i]->Print();
	cls.clear();
}


//others funcs
void framePrint() {
	
	int setX = 0, setY = 0;
	for(int y = setY; y <= setY + clsHeight + 1; y++)
	{
		for(int x = setX; x <= setX + clsWidth + 1; x++)
		{
			if(y == setY && x == setX) {FieldPrinter(char(201), white, black, 1, 1, x, y); continue;} //left_up
			if(y == setY && x == setX + clsWidth + 1) {FieldPrinter(char(187), white, black, 1, 1, x, y); continue;} //right_up
			if(y == setY + clsHeight + 1 && x == setX + clsWidth + 1) {FieldPrinter(char(188), white, black, 1, 1, x, y); continue;} //right_down
			if(y == setY + clsHeight + 1 && x == setX) {FieldPrinter(char(200), white, black, 1, 1, x, y); continue;} //left_down
			if(x == setX || x == setX + clsWidth + 1) {FieldPrinter(char(186), white, black, 1, 1, x, y); continue;} //right
			if(y == setY || y == setY + clsHeight + 1) {FieldPrinter(char(205), white, black, 1, 1, x, y); continue;} //up continue;} //down
		}
	}
}

bool recognEnvirCell(Nature *envirCell, vector<string> &map) {
	
	FieldPrinter(' ', black, black, 30, 1, 0, clsHeight + 2);
	FieldPrinter(' ', black, black, 23, 1, clsWidth + 3, 0);
	
	if(envirCell->GetSimbol() == 'c') 
	{	
		action = "openChest";
		
		SetCur(clsWidth + 3, 0);
		setColorText(yellow, "e", white);
		cout << " - open the chest";
		
		SetCur(0, clsHeight + 2);
		setColorText(red, "You seen: ", white);
		cout << "chest";
		
		return false;
	}
	else if(envirCell->GetSimbol() == 'W') 
	{	
		SetCur(0, clsHeight + 2);
		setColorText(red, "You seen: ", white);
		cout << "tree";
		
		if(checkPresenceItem(inventoryItems, "axe", 1))
		{
			action = "collect_wood";
			
			globEnvirCell = envirCell;
			
			SetCur(clsWidth + 3, 0);
			setColorText(yellow, "e", white);
			cout << " - cut down the wood";
		}
		
		return false;
	}
	else if(envirCell->GetSimbol() == 'r') 
	{	
		if(checkPresenceItem(inventoryItems, "raft", 1)) return true;
		else
		{
			SetCur(0, clsHeight + 2);
			setColorText(red, "You seen: ", white);
			cout << "river (need a raft)";
			
			return false;
		}
	}
	else if(envirCell->GetSimbol() == 'k') 
	{	
		SetCur(0, clsHeight + 2);
		setColorText(red, "You seen: ", white);
		cout << "cannabis bush";
		
		action = "collect_cannabis";
		globEnvirCell = envirCell;
		SetCur(clsWidth + 3, 0);
		setColorText(yellow, "e", white);
		cout << " - take cannabis";
		
		return false;
	}
	else if(envirCell->GetSimbol() == 's') 
	{	
		SetCur(0, clsHeight + 2);
		setColorText(red, "You seen: ", white);
		cout << "heap of stones";
		
		action = "collect_stone";
		globEnvirCell = envirCell;
		SetCur(clsWidth + 3, 0);
		setColorText(yellow, "e", white);
		cout << " - take stones";
		
		return false;
	}
	else return true;
}

vector<Nature *> GetEnvir(vector<string> map, Person person) {
	
	vector<Nature *> environment;
	int x = person.GetX();
	int y = person.GetY();
	
	environment.push_back(new Nature(x, y - 1, map[y - 1][x]));
	environment.push_back(new Nature(x - 1, y, map[y][x - 1]));
	environment.push_back(new Nature(x + 1, y, map[y][x + 1]));
	environment.push_back(new Nature(x, y + 1, map[y + 1][x]));
		
	return environment;
}

vector<string> FileReading() {
	
	ifstream fin("save 2.txt");
	vector<string> map;
	
	if(!fin.is_open())
	{
		cout << "File not found";
	}
	else
	{	
		while(!fin.eof())
		{	
			string s;
			getline(fin, s);
			mapWidth = s.size();
			while(!fin.eof())
			{
				map.push_back(s);
				getline(fin, s);
			}
			mapHeight = map.size();
		}
	}
	fin.close();
	
	return map;
}

void collectRes(string resource, int quan) {
	
	if(!checkPresenceItem(inventoryItems, resource, 1)) inventoryItems.push_back(new Item(resource, quan));
	else 
	for(int i = 0; i < inventoryItems.size(); i++)
		if(inventoryItems[i]->GetName() == resource) inventoryItems[i]->Add(quan);
	
	SetCur(0, clsHeight + 2);
	setColorText(red, "Received: ", white);
	
	cout << resource << " (" << quan << ")";
}

