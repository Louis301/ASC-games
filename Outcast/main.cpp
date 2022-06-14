#include "game.h"
#include "outputFormatters.h"

int main(int argc, char** argv) {
	
	inicGlobal();
	
	while(!exitGame)
	{
		CursorHide();
		
		switch(enableMonitor)
		{
			case GAME_MENU:
				system("cls");
				main_menu();
				break;
				
			case MAP:
				system("cls");
				map_movement();
				break;
				
			case INVENTORY_STORAGE:
				system("cls");
				inventory_to_storage();
				break;
				
			case GAMER_INVENTORY:
				system("cls");
				gamer_to_inventory();
				break;
				
			case HELP_TEXT:
				system("cls");
				helpPanel();
				break;
				
			case KNOW_PANEL:
				system("cls");
				knowledgesPanel();
				break;
		}
	}
	
	return 0;
}
