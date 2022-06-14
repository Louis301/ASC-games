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

const int map_lenght = 12; 
vector<string> gamerField_vector;
vector<string> computerField_vector;
int computerScore = 0;
int gamerScore = 0;
bool motion = rand() % 2; //0 - gamer, 1 - computer

void setcur(int x, int y); 
void SetColor(int text, int bg);
void load(int x, int y);
void field_printer(char simbol, int color_text, int color_bg, int dimension_x, int dimension_y, int offset_x, int offset_y);
void inicFields();
void printerFirstCondition();
char checkingCell(vector<string> Vector, cursorPosition gamer);
void scorePrinter();                  
void boatFrame(vector<string> &field, cursorPosition player);
void gameCicle();

//main...
int main()
{
	inicFields(); //inicialisation fields
	printerFirstCondition(); //printing first condition of fields
	gameCicle(); //game process
	scorePrinter(); //print winner
	
	getch();
	SetColor(15, 0);
	return 0;
}

//setting the cursor to the x y position 
void setcur(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

//changing the text color
void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

//loading designation
void load(int x, int y)
{
	SetColor(15, 0);
	
	for(int j = 0; j < 3; j++)
	{
		setcur(++x, y); cout << '*'; 
		for(int i = 0; i < 100000000; i++) {}
		setcur(x, y); cout << ' ';
	}
}

//printing objects
void field_printer(char simbol, int color_text, int color_bg, int dimension_x, int dimension_y, int offset_x, int offset_y)
{
	SetColor(color_text, color_bg);
	for(int i = 0; i < dimension_y; i++) 
    {
    	for(int j = 0; j < dimension_x; j++)
    	{
    		setcur(j + offset_x, i + offset_y);
    		cout << simbol;
		}
		cout << "\n";
	}
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

//printing first condition of fields
void printerFirstCondition()
{
	for(int i = 0; i < map_lenght; i++) //print gamer field
	{
		for(int j = 0; j < map_lenght; j++)
		{
			if(gamerField_vector[i][j] == 's') field_printer('s', 9, 1, 1, 1, j, i);
			if(gamerField_vector[i][j] == 'm') field_printer('m', 11, 1, 1, 1, j, i);
			if(gamerField_vector[i][j] == 'w') field_printer('w', 15, 14, 1, 1, j, i);
			if(gamerField_vector[i][j] == 'd') field_printer('d', 15, 12, 1, 1, j, i);
			if(gamerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j, i);
			if(gamerField_vector[i][j] == 'b') field_printer('b', 15, 7, 1, 1, j, i);
		}
		cout << "\n";
	}
	
	for(int i = 0; i < map_lenght; i++) //print computer field
	{ 
		for(int j = 0; j < map_lenght; j++)
		{
			if(computerField_vector[i][j] == 's' || computerField_vector[i][j] == 'b') field_printer('s', 9, 1, 1, 1, j + map_lenght + 3, i);
			if(computerField_vector[i][j] == 'm') field_printer('m', 11, 1, 1, 1, j + map_lenght + 3, i);
			if(computerField_vector[i][j] == 'w') field_printer('w', 15, 14, 1, 1, j + map_lenght + 3, i);
			if(computerField_vector[i][j] == 'd') field_printer('d', 15, 12, 1, 1, j + map_lenght + 3, i);
			if(computerField_vector[i][j] == 'f') field_printer('f', 8, 8, 1, 1, j + map_lenght + 3, i);
		}
		cout << "\n";
	}
	
	field_printer('s', 15, 0, 1, 1, 1 + map_lenght + 3, 1);
	
	SetColor(15, 0);
	setcur(0, map_lenght); cout << "Gamer";
	setcur(map_lenght + 3, map_lenght); cout << "Computer";
	
  	setcur(map_lenght * 2 + 3, 0); cout << "\tScore";
  	setcur(map_lenght * 2 + 3, 1); cout << "\t------------------";
  	setcur(map_lenght * 2 + 3, 2); cout << "\tGamer: ";
	setcur(map_lenght * 2 + 3, 3); cout << "\tComputer: ";
	setcur(map_lenght * 2 + 3, 4); cout << "\t------------------";
}

//checking cell condition
char checkingCell(vector<string> Vector, cursorPosition gamer)
{
	cursorPosition check_cursor; //checking cursor
    int boatCellQuality = 0;
        	    
    if(Vector[gamer.y][gamer.x] == 'b') //cell == 'b'
    {
		check_cursor.x = gamer.x; //up
    	check_cursor.y = gamer.y;
  	    while(Vector[--check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w') 
		{
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;				
		}
  	    			
  	    check_cursor.x = gamer.x; //down
        check_cursor.y = gamer.y;
  	    while(Vector[++check_cursor.y][check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w') 
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    check_cursor.x = gamer.x; //right
        check_cursor.y = gamer.y;
  	    while(Vector[check_cursor.y][++check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    check_cursor.x = gamer.x; //left
        check_cursor.y = gamer.y;
  	    while(Vector[check_cursor.y][--check_cursor.x] == 'b' || Vector[check_cursor.y][check_cursor.x] == 'w')
  	    {
  	    	if(Vector[check_cursor.y][check_cursor.x] == 'b') boatCellQuality++;					
		}
  	    			
  	    if(boatCellQuality == 0) 
		{
			if(motion == 0) gamerScore++;
			if(motion == 1) computerScore++;
			return 'd';
		}
        else return 'w';
        
        }
            	
        if(Vector[gamer.y][gamer.x] == 's') //cell == 's'
        {
            //gamer use
            if(motion == 0) 
			{ 
            	motion = 1;
            	return 'm';
			}
					
			//computer use
            if(motion == 1) 
			{
            	motion = 0;
            	return 'm';
			}
		}
				
		else return Vector[gamer.y][gamer.x];		
}
	
//print score of players
void scorePrinter()
{
	//reprint_player
	field_printer(' ', 0, 0, 27, 1, map_lenght * 2 + 7, 5);
	
	//printer gamer score
	if(gamerScore == 10) 
	{
		SetColor(14, 0);
	    setcur(0, map_lenght + 2); cout << "==============\n   You win!\n==============\n";
	}
		
	//printer computer score
	if(computerScore == 10) 
	{
		SetColor(12, 0);
	    setcur(0, map_lenght + 2); cout << "==============\n   You fail\n==============\n";
	}
		
	SetColor(15, 0);
	setcur(0, map_lenght + 5); cout << "\nPress any key to continue...";
}

//frame around boat
void boatFrame(vector<string> &field, cursorPosition player)
{
	cursorPosition frame_leftUp;
	cursorPosition frame_rightDown;
	
		if(field[player.y - 1][player.x] == 'w' || field[player.y + 1][player.x] == 'w') //vertical
		{
			//up
			while(field[--player.y][player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {}
			frame_leftUp.x = player.x - 1;
			frame_leftUp.y = player.y;
		
			//down
			while(field[++player.y][player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {} 
			frame_rightDown.x = player.x + 1;
			frame_rightDown.y = player.y;
			
			goto frameForming;
		}
		if(field[player.y][player.x - 1] == 'w' || field[player.y][player.x + 1] == 'w') //gorizontal
		{
			//left
			while(field[player.y][--player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {} 
			frame_leftUp.x = player.x;
			frame_leftUp.y = player.y - 1;
		
			//right
			while(field[player.y][++player.x] != 's' 
			 && field[player.y][player.x] != 'm'
			 && field[player.y][player.x] != 'f') {}
			frame_rightDown.x = player.x;
			frame_rightDown.y = player.y + 1;
			
			goto frameForming;
		}
		else //around
		{
			frame_leftUp.x = player.x - 1;
			frame_leftUp.y = player.y - 1;
			frame_rightDown.x = player.x + 1;
			frame_rightDown.y = player.y + 1;
		}
	
	frameForming:
	for(int i = frame_leftUp.y; i <= frame_rightDown.y; i++)
		{
			for(int j = frame_leftUp.x; j <= frame_rightDown.x; j++)
			{
				if(field[i][j] == 's') 
				{
					field[i][j] = 'm';
					if(motion == 1) field_printer('m', 11, 1, 1, 1, j, i);
					if(motion == 0) field_printer('m', 11, 1, 1, 1, j  + map_lenght + 3, i);
				}
			}
		}
		
}	

//game process
void gameCicle()
{
	srand(time(NULL));
	
	int value;
	cursorPosition gamer;
	cursorPosition computer;
	
	gamer.x = 1;
	gamer.y = 1;
	computer.x = rand() % 10 + 1;
	computer.y = rand() % 10 + 1;

    //intel vars
    int intelGenVariant;
    cursorPosition compMemory;
    vector<int> choiceIntel_x;
    vector<int> choiceIntel_y;
    bool firstHit = 1;
	
	//game cicle
	do
    {	
        //--------------------------motion of gamer_BEGIN
        if(motion == 0)
        {			
        	//printer player
        	SetColor(14, 0);
        	setcur(map_lenght * 2 + 3, 5);
			cout << "\tMotion of gamer\n";
		
			//---------------------------keyboard inputs processing_BEGIN
			value = getch();
		
			//reprint_TheGamerCursorSimbol
			if(computerField_vector[gamer.y][gamer.x] == 's' || computerField_vector[gamer.y][gamer.x] == 'b') field_printer('s', 9, 1, 1, 1, gamer.x  + map_lenght + 3, gamer.y);
			if(computerField_vector[gamer.y][gamer.x] == 'm') field_printer('m', 11, 1, 1, 1, gamer.x  + map_lenght + 3, gamer.y);
			if(computerField_vector[gamer.y][gamer.x] == 'w') field_printer('w', 15, 14, 1, 1, gamer.x  + map_lenght + 3, gamer.y);
			if(computerField_vector[gamer.y][gamer.x] == 'd') field_printer('d', 15, 12, 1, 1, gamer.x  + map_lenght + 3, gamer.y);
		
	    	switch(value)
			{
				case 224: break;
			
				case 72: if(gamer.y > 1) gamer.y--; break;
            	case 80: if(gamer.y < map_lenght - 2) gamer.y++; break;
            	case 75: if(gamer.x > 1) gamer.x--; break;
            	case 77: if(gamer.x < map_lenght - 2) gamer.x++; break;
            
            	//checking cell condition
            	case 32: 
				{
					SetColor(15, 0);
	            	computerField_vector[gamer.y][gamer.x] = checkingCell(computerField_vector, gamer); 
	            	
	            	if(computerField_vector[gamer.y][gamer.x] == 'd')
		    		{
		    			boatFrame(computerField_vector, gamer);
					}
					
	            	//printer Score
        	        SetColor(15, 0);
			        setcur(map_lenght * 2 + 3 + 12, 2); 
			        cout << gamerScore;
					break;
				}
	    	}
	    	
	    	//printerTheGamerCursorSimbol
			if(computerField_vector[gamer.y][gamer.x] == 's' || computerField_vector[gamer.y][gamer.x] == 'b') field_printer('s', 15, 0, 1, 1, gamer.x + map_lenght + 3, gamer.y);
			else 
			field_printer(computerField_vector[gamer.y][gamer.x], 15, 0, 1, 1, gamer.x + map_lenght + 3, gamer.y);
	    	//---------------------------keyboard inputs processing_END
	    	if(gamerScore == 10 || computerScore == 10) break;
		}
		//--------------------------motion of gamer_END


        //--------------------------motion of computer_BEGIN
        if(motion == 1)
        {
        	//printer player
        	SetColor(12, 0);
        	setcur(map_lenght * 2 + 3, 5);
			cout << "\tMotion of computer...\n";
			load(map_lenght * 2 + 7 + 22, 5);
			
			//reprint_player
			field_printer(' ', 0, 0, 27, 1, map_lenght * 2 + 7, 5);
		
		    //checking cell condition
		    gamerField_vector[computer.y][computer.x] = checkingCell(gamerField_vector, computer);
		    
		    //printer Score
        	SetColor(15, 0);
        	setcur(map_lenght * 2 + 3 + 15, 3); 
			cout << computerScore;
		    
		    //printer TheComputerCursorSimbol
			if(gamerField_vector[computer.y][computer.x] == 'm') field_printer('m', 11, 1, 1, 1, computer.x, computer.y);
			if(gamerField_vector[computer.y][computer.x] == 'w') field_printer('w', 15, 14, 1, 1, computer.x, computer.y);
			if(gamerField_vector[computer.y][computer.x] == 'd') field_printer('d', 15, 12, 1, 1,computer.x, computer.y);
			
            //-------------------------------------inicializating intellect generation variant_BEGIN
			if(gamerField_vector[computer.y][computer.x] == 'w') 
            {
                if(gamerField_vector[computer.y - 1][computer.x] == 'w' || gamerField_vector[computer.y + 1][computer.x] == 'w') //vertical
				{
					intelGenVariant = 2; 
					goto metka;
				}
                if(gamerField_vector[computer.y][computer.x - 1] == 'w' || gamerField_vector[computer.y][computer.x + 1] == 'w') //gorizontal
				{
					intelGenVariant = 3; 
					goto metka;
				}
                else //around
                {
                	intelGenVariant = 1; 
                	goto metka;
				}
            }

            if(gamerField_vector[computer.y][computer.x] == 'm' || gamerField_vector[computer.y][computer.x] == 'f')
            {
                if(gamerField_vector[computer.y][computer.x - 1] != 'w' 
                && gamerField_vector[computer.y - 1][computer.x] != 'w'
                && gamerField_vector[computer.y][computer.x + 1] != 'w'
                && gamerField_vector[computer.y + 1][computer.x] != 'w') intelGenVariant = 4;
                else
                {
                    computer.x = compMemory.x;
                    computer.y = compMemory.y;
                }
            }

            if(gamerField_vector[computer.y][computer.x] == 'd') 
            {
                intelGenVariant = 4;
                firstHit = 1;
                boatFrame(gamerField_vector, computer);
            }
            //-------------------------------------inicializating intellect generation variant_END
			
			metka:
            //-------------------------------------intel generating coordinats_BEGIN
            if(intelGenVariant == 1) //around generating coordinats
            {
                //memoring central of boat
                if(firstHit)
                {
                    compMemory.x = computer.x;
                    compMemory.y = computer.y;
                }

                //creating a circular intelligence selection 
                if(gamerField_vector[computer.y][computer.x - 1] != 'f' 
                && gamerField_vector[computer.y][computer.x - 1] != 'm' 
                && gamerField_vector[computer.y][computer.x - 1] != 'w') //left
                {
                    choiceIntel_x.push_back(computer.x - 1);
                    choiceIntel_y.push_back(computer.y);
                }

                if(gamerField_vector[computer.y - 1][computer.x] != 'f' 
                && gamerField_vector[computer.y - 1][computer.x] != 'm' 
                && gamerField_vector[computer.y - 1][computer.x] != 'w') //up
                {
                    choiceIntel_x.push_back(computer.x);
                    choiceIntel_y.push_back(computer.y - 1);
                }
                
                if(gamerField_vector[computer.y][computer.x + 1] != 'f' 
                && gamerField_vector[computer.y][computer.x + 1] != 'm' 
                && gamerField_vector[computer.y][computer.x + 1] != 'w') //right
                {
                    choiceIntel_x.push_back(computer.x + 1);
                    choiceIntel_y.push_back(computer.y);
                }

                if(gamerField_vector[computer.y + 1][computer.x] != 'f' 
                && gamerField_vector[computer.y + 1][computer.x] != 'm' 
                && gamerField_vector[computer.y + 1][computer.x] != 'w') //down
                {
                    choiceIntel_x.push_back(computer.x);
                    choiceIntel_y.push_back(computer.y + 1);
                }
                
                //generation coordinats
                int numHitCell;
				
                numHitCell = rand() % choiceIntel_x.size();

                computer.x = choiceIntel_x[numHitCell];
	            computer.y = choiceIntel_y[numHitCell];

                choiceIntel_x.clear();
                choiceIntel_y.clear();

                firstHit = 0;
            }

            if(intelGenVariant == 2) //vertical generating coordinats
            {
                if(gamerField_vector[computer.y + 1][computer.x] == 'w') computer.y--; //up hitting
                if(gamerField_vector[computer.y - 1][computer.x] == 'w') computer.y++; //down hitting
            }

            if(intelGenVariant == 3) //gorizontal generating coordinats
            {
                if(gamerField_vector[computer.y][computer.x + 1] == 'w') computer.x--; //left hitting
                if(gamerField_vector[computer.y][computer.x - 1] == 'w') computer.x++; //right hitting
            }

            if(intelGenVariant == 4) //random generating coordinats
            {
            	if(gamerScore == 10 || computerScore == 10) break;
            	
                while(gamerField_vector[computer.y][computer.x] != 's' && gamerField_vector[computer.y][computer.x] != 'b')
			    {
				    computer.x = rand() % 10 + 1;
	                computer.y = rand() % 10 + 1;
			    }
            }
            //-------------------------------------intel generating coordinats_END
			
		}
		//--------------------------motion of computer_END
	}
	while(value != 27);
}


