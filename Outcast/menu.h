//menu.h

#ifndef MENU_H 
#define MENU_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <iterator>

enum MENU
{
	INVENTORY,
	STORAGE,
	KNOWLEDGES,
	CRAFTING,
	MAIN_MENU
};

class Point 
{
public:
	int x, y;
	
	Point();
	void SetCoord(int x, int y);
	void toLeft();
	void toRight();
	void toUp();
	void toDown();
	int GetX();
	int GetY();
	~Point();
};  

class Item
{	
public:
	Item(std::string name, int quantity);
	std::string GetName();
	int GetQuan();
	void Add(int addMean);
	void Dim(int numResUsed);
	void Print(Point startDrawMenu, int colorItem, int id);
	void PrintDiscription();
	
private:
	std::string name;
	int quantity;
};

class Menu
{
public:
	Menu(Point startDraw, std::string title, int colorTitle, std::vector<Item *> items);
	void PrintList();
	void Choice();
	~Menu();
	
private:
	std::string title;
	int colorTitle;
	std::vector<Item *> items;
	Point startDraw;
	int enablePos;
};

//global
extern std::vector<Item *> knowledgesItems;
extern std::vector<Item *> inventoryItems;
extern std::vector<Item *> storageItems;
extern std::vector<Item *> craftItems;

extern bool exitItemsMonitor;
extern int enableMenu;
extern int memorizedMenu;
extern int memorizedPos;

//funcs
void inicGlobalVectors();
template<typename type> bool checkPresenceItem(std::vector<type *> menuList, std::string item, int quan);
void addItemToMenu(std::vector<Item *> &menuItems, std::string nameAddItem);
void delElemVect(std::vector<Item *> &items, int &enablePos);
void GenCraftsList();
void deleteUsedRes(std::string itemForMaking);

#endif //MENU_H
