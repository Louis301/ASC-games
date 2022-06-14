//game.cpp

#include "moveMapProc.h"
#include "outputFormatters.h"
#include "menu.h"
#include "game.h"

bool exitGame = false;
int enableMonitor;

void helpPanel() {
	
	//SetCur(4, 3); //startpoint of printing
	setColorText(red, "w, a, s, d", white); cout << " - movement on the map\n";
	setColorText(red, "Esc", white); cout << " - exit to previous monitor\n";
	setColorText(red, "i", white); cout << " - inventory\n";
	setColorText(red, "e", white); cout << " - action\n";
	setColorText(red, "k", white); cout << " - knowledges\n";
	
	switch(getch())
	{
		case esc:
			enableMonitor = GAME_MENU;
			break;
	}
}

void inicGlobal() {
	
	enableMonitor = GAME_MENU;
	enableMenu = MAIN_MENU;
	
	inicGlobalVectors();
	map = FileReading();
	
	startClsPrint.SetCoord(1, 1);
	endClsPrint.SetCoord(clsWidth, clsHeight);
	cls.SetCls(startClsPrint, endClsPrint);
	person.SetCoord(clsWidth / 2 + 1, clsHeight / 2 + 1);
}

void gamer_to_inventory() {
	
	craftItems.clear();
	GenCraftsList();
	enableMenu = CRAFTING;
	exitItemsMonitor = false;
	
	//--------------------------------checking for emptiness
	if(inventoryItems.empty()) inventoryItems.push_back(new Item("- empty -", 0));
	if(craftItems.empty()) craftItems.push_back(new Item("- empty -", 0));
	
	//--------------------------------inic points of start drawing
	Point startDrawInv; startDrawInv.SetCoord(0, 0);
	Point startDrawCraft; startDrawCraft.SetCoord(20, 0);
	
	//--------------------------------inic list's and menu
	Menu inventory(startDrawInv, "Inventory", lightBlue, inventoryItems);
	Menu crafts(startDrawCraft, "Crafting", yellow, craftItems);
	
	//--------------------------------printing the final data
	inventory.PrintList();
	crafts.PrintList();
	
	//--------------------------------outputting cicle 
	while(!exitItemsMonitor)
	{
		switch(enableMenu)
		{
			case INVENTORY:
				inventory.Choice();
				break;
				
			case CRAFTING:
				crafts.Choice();
				break;
		}
	}
}

void knowledgesPanel() {
	
	enableMenu = KNOWLEDGES;
	exitItemsMonitor = false;
	
	if(knowledgesItems.empty()) knowledgesItems.push_back(new Item("- empty -", 0));
	Point startDrawKnow; startDrawKnow.SetCoord(0, 0);
	Menu knowledges(startDrawKnow, "Knowledges", darkGreen, knowledgesItems);
	knowledges.PrintList();
	knowledges.Choice();
}

void main_menu() {
	
	enableMenu = MAIN_MENU;
	
	vector<Item *> mainMenuItems;
	mainMenuItems.push_back(new Item("Load", 0));
	mainMenuItems.push_back(new Item("Help", 0));
	mainMenuItems.push_back(new Item("Exit", 0));
		
	Point startDrawMainMenu; 
	startDrawMainMenu.SetCoord(4, 3);
	
	Menu mainMenu(startDrawMainMenu, "OUTCAST", red, mainMenuItems);
	mainMenu.PrintList();
	mainMenu.Choice();
}

void inventory_to_storage() {
	
	craftItems.clear();
	GenCraftsList();
	
	enableMenu = memorizedMenu;
	exitItemsMonitor = false;
	
	//--------------------------------checking for emptiness
	if(inventoryItems.empty()) inventoryItems.push_back(new Item("- empty -", 0));
	if(storageItems.empty()) storageItems.push_back(new Item("- empty -", 0));
	if(craftItems.empty()) craftItems.push_back(new Item("- empty -", 0));
	
	//--------------------------------inic points of start drawing
	Point startDrawInv; startDrawInv.SetCoord(0, 0);
	Point startDrawStorage; startDrawStorage.SetCoord(20, 0);
	Point startDrawCraft; startDrawCraft.SetCoord(40, 0);
	
	//--------------------------------inic list's and menu
	Menu inventory(startDrawInv, "Inventory", lightBlue, inventoryItems);
	Menu storage(startDrawStorage, "Chest", red, storageItems);
	Menu crafts(startDrawCraft, "Crafting", yellow, craftItems);
	
	//--------------------------------printing the final data
	inventory.PrintList();
	storage.PrintList();
	crafts.PrintList();
	
	//--------------------------------outputting cicle 
	while(!exitItemsMonitor)
	{
		switch(enableMenu)
		{
			case INVENTORY:
				inventory.Choice();
				break;
				
			case STORAGE:
				storage.Choice();
				break;
				
			case CRAFTING:
				crafts.Choice();
				break;
		}
	}
}

void map_movement() {
	
	vector<Nature *> envir;
	framePrint();
	
	bool exit = false;
	
	while(!exit)
	{	
		envir = GetEnvir(map, person); 
		char memoryMap = map[person.GetY()][person.GetX()];
		map[person.GetY()][person.GetX()] = 'I'; 
		cls.Print(map); 
		int cmdSignal = getch(); 
		map[person.GetY()][person.GetX()] = memoryMap; 
			
		switch(cmdSignal)
		{
			case w: 
				if(person.toUp(recognEnvirCell(envir[0], map))) 
				if(person.GetY() < (mapHeight - 2) - clsHeight / 2) cls.toUp(); 
				break;
        	case s: 
				if(person.toDown(recognEnvirCell(envir[3], map))) 
				if(person.GetY() > clsHeight / 2 + 1) cls.toDown(); 
				break;
        	case a: 
				if(person.toLeft(recognEnvirCell(envir[1], map))) 
				if(person.GetX() < (mapWidth - 2) - clsWidth / 2) cls.toLeft(); 
				break;
        	case d: 
				if(person.toRight(recognEnvirCell(envir[2], map))) 
				if(person.GetX() > clsWidth / 2 + 1) cls.toRight(); 
				break;
			
			case e:
				if(action == "openChest") {
					enableMonitor = INVENTORY_STORAGE;
					exit = true; 
				}
				if(action == "collect_wood") {
					collectRes("wood", 1);
					map[globEnvirCell->GetY()][globEnvirCell->GetX()] = 'g';
				}
				if(action == "collect_cannabis") {
					collectRes("cannabis", 8);
					map[globEnvirCell->GetY()][globEnvirCell->GetX()] = 'g';
				}
				if(action == "collect_stone") {
					collectRes("stone", 3);
					map[globEnvirCell->GetY()][globEnvirCell->GetX()] = 'g';
				}
				FieldPrinter(' ', black, black, 30, 1, 0, clsHeight + 2);
				FieldPrinter(' ', black, black, 23, 1, clsWidth + 3, 0);
				action = "";
				break;
				
			case k:
				enableMonitor = KNOW_PANEL;
				exit = true; 
				break;
				
			case i:
				enableMonitor = GAMER_INVENTORY;
				exit = true; 
				break;
				
        	case esc: 
        		enableMonitor = GAME_MENU;
				exit = true; 
				break;
		}
	}
}

