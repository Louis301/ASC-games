//game.h

#ifndef GAME_H 
#define GAME_H

//#include <windows.h>

enum MONITORS
{
	MAP,
	GAME_MENU,
	INVENTORY_STORAGE,
	GAMER_INVENTORY,
	HELP_TEXT,
	KNOW_PANEL
};

enum CMD
{
	w = 119,
	s = 115,
	a = 97, 
	d = 100, 
	esc = 27,
	h = 104,
	i = 105,
	e = 101,
	k = 107,
	UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    ENTER = 13
};


void map_movement();
void inventory_to_storage();
void main_menu();
void inicGlobal();
void gamer_to_inventory();
void helpPanel();
void knowledgesPanel();

//global
extern bool exitGame;
extern int enableMonitor;

#endif

