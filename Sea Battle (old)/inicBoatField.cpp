#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

class cursorPosition
{
	public:
		int x, y;
};

//changing the text color
void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void pause()
{
	for(int i = 0; i < 1000000000; i++) 
	{
	}
}

int main()
{
	srand(time(NULL));
	
	const int map_lenght = 12; 
	vector<string> gamerField_vector;
	vector<string> computerField_vector;
	int boatNum = 4;
	int qualityUsed_frameCheck = 0; 
	int qualityUsed_dir = 0; 
	int numBoats = 0; 
	int dir;
	
	cursorPosition gamer;
	cursorPosition leftUp;
	cursorPosition rightDown;
	
	char field[map_lenght][map_lenght] = {0};
	
	//inicialization of gamer's field first condition 
	for(int i = 0; i < map_lenght; i++)
	{
		string s = "";
		for(int j = 0; j < map_lenght; j++)
		{
			if(i == 0 || j == 0 || i == map_lenght - 1 || j == map_lenght - 1) field[i][j] = 'f';
			else
			field[i][j] = 's';
			
			s += field[i][j];
		}
		
		computerField_vector.push_back(s);
	}
	
	//filling cicle
	do
	{
		METKA_1: 
		
		qualityUsed_dir = 0;
		qualityUsed_frameCheck = 0;
		gamer.x = rand() % 10 + 1;
		gamer.y = rand() % 10 + 1;
		
		if(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		while(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		{
			gamer.x = rand() % 10 + 1;
			gamer.y = rand() % 10 + 1;
		}
		
		METKA_2: 
		
		dir = rand() % 4;
		if(dir == 0) // left
		{
			if(gamer.x - boatNum >= 0)
			{
				leftUp.x = gamer.x - boatNum;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 1) //up
		{
			if(gamer.y - boatNum >= 0)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - boatNum; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 2) //right
		{
			if(gamer.x + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + boatNum;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 3) //down
		{
			if(gamer.y + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + boatNum;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		
		bool emptyFrame = true;
            	for(int i = leftUp.y; i <= rightDown.y; i++)
				{
					for(int j = leftUp.x; j <= rightDown.x; j++)
					{
						if(i == leftUp.y || j == leftUp.x || i == rightDown.y || j == rightDown.x) 
						{
							if(computerField_vector[i][j] == 'b') 
							{
								emptyFrame = false;
								break;
							}
						}
					}
					if(!emptyFrame) 
					{
						qualityUsed_frameCheck++;
						if(qualityUsed_frameCheck == 4) goto METKA_1;
						else goto METKA_2;
						break;
					}
				}
				if(emptyFrame)
				{
					//print the frame
					for(int i = leftUp.y; i <= rightDown.y; i++)
					{
						for(int j = leftUp.x; j <= rightDown.x; j++)
						{
							computerField_vector[i][j] = 'm';
						}
					}
					
					//print ship
					for(int i = leftUp.y + 1; i < rightDown.y; i++)
					{
						for(int j = leftUp.x + 1; j < rightDown.x; j++)
						{
							computerField_vector[i][j] = 'b';
						}
					}
					
					numBoats++;
					
					if(numBoats == 1 || numBoats == 2) boatNum = 3;
					if(numBoats == 3 || numBoats == 4 || numBoats == 5) boatNum = 2;
					if(numBoats == 6 || numBoats == 7 || numBoats == 8 || numBoats == 9) boatNum = 1;
					
					qualityUsed_frameCheck = 0;
				}
	}
	while(numBoats != 10);
	
	//----------------------------field output_BEGIN
	for(int i = 0; i < map_lenght; i++)
	{
		for(int j = 0; j < map_lenght; j++)
		{
			if(computerField_vector[i][j] == 'b') {SetColor(14, 0); cout << computerField_vector[i][j];}
			if(computerField_vector[i][j] == 'm') {SetColor(7, 0); cout << computerField_vector[i][j];}
			if(computerField_vector[i][j] == 'f') {SetColor(8, 0); cout << computerField_vector[i][j];}
			if(computerField_vector[i][j] == 's') {SetColor(15, 0); cout << computerField_vector[i][j];}
		}
		cout << endl;
	} 
	
	//getch();
	pause();
	system("cls");
	main();
	//----------------------------field output_END
	
	return 0;
}

//inicilization fields
void inicFields()
{
	char field[map_lenght][map_lenght] = {0};
	cursorPosition leftUp;
	cursorPosition rightDown;
	cursorPosition gamer;
	int boatNum = 4;
	int value;
	int dir = 1;
	int numBoats = 0;
	
	gamer.x = 1;
	gamer.y = 4;
	
	SetColor(15, 0);
	setcur(map_lenght, 0); cout << "\tWorking keys";
	setcur(map_lenght, 1); cout << "\t--------------------------------";
	setcur(map_lenght, 2); SetColor(14, 0); cout << "\tEnter"; SetColor(15, 0); cout << " - put the boat";
	setcur(map_lenght, 3); SetColor(14, 0); cout << "\tSpace"; SetColor(15, 0); cout << " - change of boat direction";
	setcur(map_lenght, 4); SetColor(14, 0); cout << "\tArrows"; SetColor(15, 0); cout << " - moving the boat";
	setcur(map_lenght, 5); cout << "\t--------------------------------";
	setcur(map_lenght, 6); cout << "\tNumber of put boats: ";
	
	//---------------------------------filling field of gamer_BEGIN
	//inic of gamer's field first condition 
	for(int i = 0; i < map_lenght; i++)
	{
		string s = "";
		
		for(int j = 0; j < map_lenght; j++)
		{
			if(i == 0 || j == 0 || i == map_lenght - 1 || j == map_lenght - 1) field[i][j] = 'f';
			else
			field[i][j] = 's';
			
			s += field[i][j];
		}
		
		gamerField_vector.push_back(s);
		computerField_vector.push_back(s);
	}
	
	//print gamer's field of first condition
		for(int i = 0; i < map_lenght; i++)
		{
			for(int j = 0; j < map_lenght; j++)
			{
				if(gamerField_vector[i][j] == 's') field_printer('s', 9, 1, 1, 1, j, i);
				if(gamerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j, i);
			}
			cout << "\n";
		}
	
	//filling cicle (for gamer)
	do
	{
		//-------------inicialization coords of boat frame_BEGIN
		if(dir == 0) // left
		{
			if(gamer.x - boatNum >= 0)
			{
				leftUp.x = gamer.x - boatNum;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
		}
		
		if(dir == 1) //up
		{
			if(gamer.y - boatNum >= 0)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - boatNum; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
		}
		
		if(dir == 2) //right
		{
			if(gamer.x + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + boatNum;
				rightDown.y = gamer.y + 1;
			}
		}
		
		if(dir == 3) //down
		{
			if(gamer.y + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + boatNum;
			}
		}
		
		//-------------inicialization coords of boat frame_END
		
		//print boat
		for(int i = leftUp.y + 1; i < rightDown.y; i++)
		{
			for(int j = leftUp.x + 1; j < rightDown.x; j++)
			{
				field_printer('b', 15, 7, 1, 1, j, i);
				field_printer('u', 15, 0, 1, 1, gamer.x, gamer.y);
			}
		}
		
		//---------------------------keyboard inputs processing_BEGIN
		value = getch();
		switch(value)
		{
			case 224: break;
			
			case 72: if(leftUp.y > 0) gamer.y--; break; //up
            case 80: if(rightDown.y < map_lenght - 1) gamer.y++; break; //down
            case 75: if(leftUp.x > 0) gamer.x--; break; //left
            case 77: if(rightDown.x < map_lenght - 1) gamer.x++; break; //right
            
            case 32: //change of direction
            {
            	dir++;
				if(dir == 4) dir = 0;
				
			} break;
			
			case 13: //putting the boat
            {
            	bool emptyFrame = true;
            	
            	for(int i = leftUp.y; i <= rightDown.y; i++)
				{
					for(int j = leftUp.x; j <= rightDown.x; j++)
					{
						if(i == leftUp.y || j == leftUp.x || i == rightDown.y || j == rightDown.x) 
						{
							if(gamerField_vector[i][j] == 'b') 
							{
								emptyFrame = false;
								break;
							}
						}
					}
					if(emptyFrame == 0) break;
				}
				
				if(emptyFrame)
				{
					for(int i = leftUp.y + 1; i < rightDown.y; i++)
					{
						for(int j = leftUp.x + 1; j < rightDown.x; j++)
						{
							gamerField_vector[i][j] = 'b';
						}
					}
					numBoats++;
					setcur(map_lenght + 25, 6); cout << numBoats;
					
					if(numBoats == 1 || numBoats == 2) boatNum = 3;
					if(numBoats == 3 || numBoats == 4 || numBoats == 5) boatNum = 2;
					if(numBoats == 6 || numBoats == 7 || numBoats == 8 || numBoats == 9) boatNum = 1;
				}
				
			} break;
			
	    }
	    //---------------------------keyboard inputs processing_END
	    
	    //reprint boat
		for(int i = leftUp.y + 1; i < rightDown.y; i++)
		{
			for(int j = leftUp.x + 1; j < rightDown.x; j++)
			{
				if(gamerField_vector[i][j] == 'b') field_printer('b', 15, 7, 1, 1, j, i);
				if(gamerField_vector[i][j] == 's') field_printer('s', 9, 1, 1, 1, j, i);
			}
		}
	    
	} 
	while(numBoats != 10);
	//---------------------------------filling field of gamer_END
	
	system("cls");
	SetColor(15, 0);
	
	//---------------------------------filling field of computer_BEGIN
	srand(time(NULL));
	
	boatNum = 4;
	int qualityUsed_frameCheck = 0; 
	int qualityUsed_dir = 0; 
	numBoats = 0; 
	
	//filling cicle (for computer)
	do
	{
		METKA_1: 
		
		qualityUsed_dir = 0;
		qualityUsed_frameCheck = 0;
		gamer.x = rand() % 10 + 1;
		gamer.y = rand() % 10 + 1;
		
		if(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		while(computerField_vector[gamer.y][gamer.x] == 'b' || computerField_vector[gamer.y][gamer.x] == 'f')
		{
			gamer.x = rand() % 10 + 1;
			gamer.y = rand() % 10 + 1;
		}
		
		METKA_2: 
		
		dir = rand() % 4;
		if(dir == 0) // left
		{
			if(gamer.x - boatNum >= 0)
			{
				leftUp.x = gamer.x - boatNum;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 1) //up
		{
			if(gamer.y - boatNum >= 0)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - boatNum; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 2) //right
		{
			if(gamer.x + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + boatNum;
				rightDown.y = gamer.y + 1;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		if(dir == 3) //down
		{
			if(gamer.y + boatNum < map_lenght)
			{
				leftUp.x = gamer.x - 1;
				leftUp.y = gamer.y - 1; 
				rightDown.x = gamer.x + 1;
				rightDown.y = gamer.y + boatNum;
			}
			else
			{
				qualityUsed_dir++;
				if(qualityUsed_dir == 4) goto METKA_1;
				else 
				{
					goto METKA_2;
				}
			}
		}
		
		bool emptyFrame = true;
            	for(int i = leftUp.y; i <= rightDown.y; i++)
				{
					for(int j = leftUp.x; j <= rightDown.x; j++)
					{
						if(i == leftUp.y || j == leftUp.x || i == rightDown.y || j == rightDown.x) 
						{
							if(computerField_vector[i][j] == 'b') 
							{
								emptyFrame = false;
								break;
							}
						}
					}
					if(!emptyFrame) 
					{
						qualityUsed_frameCheck++;
						if(qualityUsed_frameCheck == 4) goto METKA_1;
						else goto METKA_2;
						break;
					}
				}
				if(emptyFrame)
				{
					//print ship
					for(int i = leftUp.y + 1; i < rightDown.y; i++)
					{
						for(int j = leftUp.x + 1; j < rightDown.x; j++)
						{
							computerField_vector[i][j] = 'b';
						}
					}
					
					numBoats++;
					
					if(numBoats == 1 || numBoats == 2) boatNum = 3;
					if(numBoats == 3 || numBoats == 4 || numBoats == 5) boatNum = 2;
					if(numBoats == 6 || numBoats == 7 || numBoats == 8 || numBoats == 9) boatNum = 1;
					
					qualityUsed_frameCheck = 0;
				}
	}
	while(numBoats != 10);
	//---------------------------------filling field of computer_END
	
	system("cls");
	SetColor(15, 0);
}

