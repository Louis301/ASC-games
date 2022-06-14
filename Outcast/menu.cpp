//menu.cpp

#include "outputFormatters.h"
#include "menu.h"
#include "game.h"

vector<Item *> knowledgesItems(0);
vector<Item *> inventoryItems(0);
vector<Item *> storageItems(0);
vector<Item *> craftItems(0);

bool exitItemsMonitor = false;
int enableMenu;
int memorizedMenu = INVENTORY;
int memorizedPos = 0;


//---------------------------Point funcs
	void Point::SetCoord(int x, int y) {
		this->x = x;
		this->y = y;
	}
	
	int Point::GetX() {
		return x;
	}
	
	int Point::GetY() {
		return y;
	}
	
	Point::Point() {
	}
	
	Point::~Point() {
	}


//---------------------------Item funcs
	Item::Item(string name, int quantity) {
		this->name = name;
		this->quantity = quantity;
	}
	
	string  Item::GetName() {
		return name;
	}
	
	int Item::GetQuan() {
		return quantity;
	}
	
	void Item::Add(int addMean) {
		quantity += addMean;
	}
	
	void Item::Dim(int numResUsed) {
		quantity -= numResUsed;
	}
	
	void Item::Print(Point startDrawMenu, int colorItem, int id) {
		
		SetColor(colorItem, black);
		SetCur(startDrawMenu.GetX(), startDrawMenu.GetY() + 2 + id);
		
		if(quantity == 0) cout << name;
		else 
		cout << name << " (" << quantity << ")";
	}
	
void Item::PrintDiscription() {
	
	SetCur(0, 4 + knowledgesItems.size());
	SetColor(white, black);
	
	cout << "Discription\n";
	cout << "---------------\n";
	
	if(name == "Raft creating") {
		setColorText(green, "Need for make:\n", white);
		cout << "knife x1\nroap x6\nwood x3";
	}
	if(name == "Axe creating") {
		setColorText(green, "Need for make:\n", white);
		cout << "knife x1\nroap x1\nwood x1\nstone x1";
	}
	if(name == "Roap creating") {
		setColorText(green, "Need for make:\n", white);
		cout << "cannabis x4";
	}
	
	//others discriptions...
}


//-----------------------Menu funcs
Menu::Menu(Point startDraw, string title, int colorTitle, vector<Item *> items) {
	this->title = title;
	this->colorTitle = colorTitle;
	this->items = items;
	this->startDraw = startDraw;
	enablePos = memorizedPos;
}

Menu::~Menu() {
	//this->items.clear();
}
	
void Menu::PrintList() {
	SetColor(colorTitle, black);
	SetCur(startDraw.GetX(), startDraw.GetY()); cout << title;
	SetCur(startDraw.GetX(), startDraw.GetY() + 1); cout << "--------------";
	SetCur(startDraw.GetX(), startDraw.GetY() + 2);
	
	//output list
	for(int i = 0; i < items.size(); i++) 
		items[i]->Print(startDraw, white, i);
	
	SetColor(white, black);
}
	
void Menu::Choice() {
	
	bool exit = false;
	while(!exit)
	{
		if(enableMonitor == KNOW_PANEL) items[enablePos]->PrintDiscription();
		
		items[enablePos]->Print(startDraw, colorTitle, enablePos);
		if(enableMenu != MAIN_MENU) cout << " <-";
		
		switch(getch())
		{
			case w: case UP:
				enablePos --;
				if(enableMonitor == GAMER_INVENTORY) {
					if(enablePos < 0 && enableMenu == CRAFTING) {
						enableMenu = INVENTORY;
						exit = true;
						enablePos ++;
					}
					else if(enablePos < 0) enablePos ++;
				}
				else if(enablePos < 0 && enableMenu == STORAGE) {
					enableMenu = INVENTORY;
					exit = true;
					enablePos ++;
				}
				else if(enablePos < 0) enablePos ++;
				break;
				
			case s: case DOWN:
				enablePos ++;
				if(enablePos == items.size() && enableMenu == INVENTORY) {
					if(enableMonitor == GAMER_INVENTORY) enableMenu = CRAFTING;
					else enableMenu = STORAGE;
					exit = true;
					enablePos --;
				}
				else if(enablePos == items.size()) enablePos --;
				break;
					
			case a: case LEFT:
				//previously menu
				if(enableMonitor == GAMER_INVENTORY && enableMenu == CRAFTING) {
					enableMenu = INVENTORY;
				}
				else if(enableMenu == CRAFTING) enableMenu = STORAGE;
				else if(enableMenu == STORAGE) enableMenu = INVENTORY;
				exit = true;
				break;
					
			case d: case RIGHT:
				//next menu
				if(enableMonitor == GAMER_INVENTORY && enableMenu == INVENTORY) {
					enableMenu = CRAFTING;
				}
				else if(enableMenu == STORAGE) enableMenu = CRAFTING;
				else if(enableMenu == INVENTORY) enableMenu = STORAGE;
				exit = true;
				break;
				
			case e: case ENTER:
				if(items[enablePos]->GetName() != "- empty -") {
					
					if(enableMonitor == INVENTORY_STORAGE && enableMenu == INVENTORY) {
						items[enablePos]->Dim(1); 
						addItemToMenu(storageItems, items[enablePos]->GetName());
						if(items[enablePos]->GetQuan() == 0) delElemVect(inventoryItems, enablePos);
						memorizedMenu = INVENTORY;
					}
					
					if(enableMenu == STORAGE) {
						items[enablePos]->Dim(1); 
						addItemToMenu(inventoryItems, items[enablePos]->GetName());
						if(items[enablePos]->GetQuan() == 0) delElemVect(storageItems, enablePos);
						memorizedMenu = STORAGE;
					}
					 
					if(enableMenu == CRAFTING) {
						addItemToMenu(inventoryItems, items[enablePos]->GetName());
						deleteUsedRes(items[enablePos]->GetName());
						memorizedMenu = CRAFTING;
						enablePos = 0;
					}
					
					memorizedPos = enablePos;
					exitItemsMonitor = true;
					exit = true;
				}
			
				if(enableMenu == MAIN_MENU) 
				{
					if(items[enablePos]->GetName() == "Load") enableMonitor = MAP;
					if(items[enablePos]->GetName() == "Help") enableMonitor = HELP_TEXT;
					if(items[enablePos]->GetName() == "Exit") exitGame = true; 
					exit = true;
				}
				break;
				
			case k:
				if(enableMonitor == INVENTORY_STORAGE) enableMonitor = KNOW_PANEL;
				if(enableMonitor == GAMER_INVENTORY) enableMonitor = KNOW_PANEL;
				exitItemsMonitor = true;
				exit = true;
				break;
				
			case esc:
				if(enableMonitor == INVENTORY_STORAGE) enableMonitor = MAP;
				if(enableMonitor == GAMER_INVENTORY) enableMonitor = MAP;
				if(enableMonitor == KNOW_PANEL) enableMonitor = MAP;
				exitItemsMonitor = true;
				exit = true;
				break;
		}
			
		//reprint
		if(enableMenu != MAIN_MENU) FieldPrinter(' ', black, black, 3, 1, GetX_cur() - 3, GetY_cur());
		
		if(enableMonitor == KNOW_PANEL) FieldPrinter(' ', black, black, 18, 7, 0, 6 + knowledgesItems.size());
		   
		PrintList();
	}
}


//-----------------------------other funcs
void deleteUsedRes(string itemForMaking) {
	
	if(itemForMaking == "raft") 
	{
		for(int j = 0; j < inventoryItems.size(); j++)
		{
			if(inventoryItems[j]->GetName() == "roap") inventoryItems[j]->Dim(6);
			if(inventoryItems[j]->GetName() == "wood") inventoryItems[j]->Dim(3);
			if(inventoryItems[j]->GetQuan() == 0) delElemVect(inventoryItems, j);
		}
	}
						
	if(itemForMaking == "axe") 
	{
		for(int j= 0; j < inventoryItems.size(); j++)
		{
			if(inventoryItems[j]->GetName() == "stone") inventoryItems[j]->Dim(1);
			if(inventoryItems[j]->GetName() == "wood") inventoryItems[j]->Dim(1);
			if(inventoryItems[j]->GetName() == "roap") inventoryItems[j]->Dim(1);
			if(inventoryItems[j]->GetQuan() == 0) delElemVect(inventoryItems, j);
		}
	}
	
	if(itemForMaking == "roap") 
	{
		for(int j= 0; j < inventoryItems.size(); j++)
		{
			if(inventoryItems[j]->GetName() == "cannabis") inventoryItems[j]->Dim(4);
			if(inventoryItems[j]->GetQuan() == 0) delElemVect(inventoryItems, j);
		}
	}
	
	//other items for making
}

void GenCraftsList() {	

	if(checkPresenceItem(knowledgesItems, "Raft creating", 0) &&
	checkPresenceItem(inventoryItems, "knife", 1) && 
	checkPresenceItem(inventoryItems, "wood", 3) && 
	checkPresenceItem(inventoryItems, "roap", 6)) craftItems.push_back(new Item("raft", 0));
	
	if(checkPresenceItem(knowledgesItems, "Axe creating", 0) &&
	checkPresenceItem(inventoryItems, "knife", 1) && 
	checkPresenceItem(inventoryItems, "stone", 1) && 
	checkPresenceItem(inventoryItems, "wood", 1) &&
	checkPresenceItem(inventoryItems, "roap", 2)) craftItems.push_back(new Item("axe", 0));
	
	if(checkPresenceItem(knowledgesItems, "Roap creating", 0) &&
	checkPresenceItem(inventoryItems, "cannabis", 4)) craftItems.push_back(new Item("roap", 0));
	
	//other crafts... 
}

void delElemVect(vector<Item *> &items, int &enablePos) {
	
	for(vector<Item *>::iterator id = items.begin(); id < items.end(); id++)
	{
		if(*id == items[enablePos]) 
		{
			items.erase(id);
			break;
		}
	}
	
	if(enablePos > 0) enablePos --;
}

void addItemToMenu(vector<Item *> &menuItems, string nameAddItem) {
	
	bool matchNames = false;
	if(menuItems[0]->GetName() == "- empty -") menuItems.clear();
	
	for(int id = 0; id < menuItems.size(); id++)
	{
		if(menuItems[id]->GetName() == nameAddItem) 
		{
			matchNames = true;
			menuItems[id]->Add(1);
			break;
		}
	}
	
	if(!matchNames) 
	{
		menuItems.push_back(new Item(nameAddItem, 1));
	}
}

void inicGlobalVectors() {
 	
	//--------------------------------inic vectors of items
	knowledgesItems.push_back(new Item("Raft creating", 0));
	knowledgesItems.push_back(new Item("Axe creating", 0));
	knowledgesItems.push_back(new Item("Roap creating", 0));
	
	inventoryItems.push_back(new Item("knife", 1));
	
	//storageItems.push_back(new Item("roap", 12));
	storageItems.push_back(new Item("wood", 1));
}

template<typename type>
bool checkPresenceItem(vector<type *> menuList, string item, int quan) {
	for(int i = 0; i < menuList.size(); i++)
		if(menuList[i]->GetName() == item && menuList[i]->GetQuan() >= quan) return true;
	return false;
}
