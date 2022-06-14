#include "outputFormatters.h"
#include "logic.h"
		
body::body() {
	(*this).x = 0;
	(*this).y = 0;
}
		
body::body(int x, int y) {
	this->x = x;
	this->y = y;
	simbol = '>';
}
		
void body::toLeft() {
	x--;
	simbol = '<';
}
	
void body::toRight() {
	x++;
	simbol = '>';
}
	
void body::toUp() {
	y--;
	simbol = 'A';
}
		
void body::toDown() {
	y++;
	simbol = 'V';
}
		
void body::print() {
	SetCur(x, y);
	cout << simbol;
}
		
void body::print(char simb) {
	SetCur(x, y);
	cout << simb;
}
		
void body::clear() {
	SetCur(x, y);
	cout << ' ';
}
		
void body::check() {
	if(x == width - 1) x = 1;
	if(x == 0) x = width - 2;
	if(y == height - 1) y = 1;
	if(y == 0) y = height - 2;
}
		
bool body::operator == (const body & other) {
	return this->x == other.x && this->y == other.y;
}
		
bool body::operator != (const body & other) {
	return this->x != other.x && this->y != other.y;
}
		
void body::operator = (const body & other) {
	this->x = other.x;
	this->y = other.y;
}
		
int body::getX() {return x;}

int body::getY() {return y;}

body::~body() {}
		

//other funcs
body genFood(vector <body> snake) {
	
	bool enabled;
	
	againGen:
	enabled = false;
	body food(1 + rand() % (width - 2), 1 + rand() % (height - 2));
	
	for(int i = 0; i < snake.size(); i++)
	{
		if(food == snake[i]) 
		{
			enabled = true;
			break;
		} 
	}
	
	if(enabled) goto againGen;
	else return food;
}

void game() {
	
	system("cls");
	
	FieldPrinter('#', 10, 0, width, height, 0, 0);
	FieldPrinter(' ', 0, 0, width - 2, height - 2, 1, 1);
	SetColor(10, 0);
	
	body head(width / 2, height / 2);
	body secondSegment(width / 2 - 1, height / 2);
	body tail(width / 2 - 2, height / 2);
	body more(width / 2 - 3, height / 2);
	
	bool fd = false;
	bool exit = false;
	int *cmdSignal = new int; 
	vector <body> snake;
	int *score = new int;
	
	*score = 0;
	*cmdSignal = 77;
	snake.push_back(head);
	snake.push_back(secondSegment);
	snake.push_back(tail);
	
	CursorHide();
	
	body food = genFood(snake);
	
	while(!exit)
	{
		food.print('$');
		SetCur(0, height);
		cout << "Score: " << *score << "\tLenght of snake: " << snake.size();
		
		if(kbhit()) *cmdSignal = getch(); 
		else Sleep(128);
		
		if(snake[0] == food) 
		{
			fd = true;
			*score += 100;
		}
		
		snake[0].clear(); //clearing of head
		snake[snake.size() - 1].clear(); //clearing of tail
		
		if(!fd)
		{
			for(int i = snake.size() - 1; i > 0; i--)
			{
				snake[i] = snake[i - 1];
			}
		}
		else
		{	
			//if second segment of body up of tail
			if(snake[snake.size() - 2].getY() + 1 == snake[snake.size() - 1].getY()) 
			{
				body elem1(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() + 1);
				body elem2(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() + 2);
				body elem3(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() + 3);
				snake.push_back(elem1);
				snake.push_back(elem2);
				snake.push_back(elem3);
			}
			
			//if second segment of body right of tail
			if(snake[snake.size() - 2].getX() - 1 == snake[snake.size() - 1].getX()) 
			{
				body elem1(snake[snake.size() - 1].getX() - 1, snake[snake.size() - 1].getY());
				body elem2(snake[snake.size() - 1].getX() - 2, snake[snake.size() - 1].getY());
				body elem3(snake[snake.size() - 1].getX() - 3, snake[snake.size() - 1].getY());
				snake.push_back(elem1);
				snake.push_back(elem2);
				snake.push_back(elem3);
			}
			
			//if second segment of body down of tail
			if(snake[snake.size() - 2].getY() - 1 == snake[snake.size() - 1].getY()) 
			{
				body elem1(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() - 1);
				body elem2(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() - 2);
				body elem3(snake[snake.size() - 1].getX(), snake[snake.size() - 1].getY() - 3);
				snake.push_back(elem1);
				snake.push_back(elem2);
				snake.push_back(elem3);
			}
			
			//if second segment of body left of tail
			if(snake[snake.size() - 2].getX() + 1 == snake[snake.size() - 1].getX()) 
			{
				body elem1(snake[snake.size() - 1].getX() + 1, snake[snake.size() - 1].getY());
				body elem2(snake[snake.size() - 1].getX() + 2, snake[snake.size() - 1].getY());
				body elem3(snake[snake.size() - 1].getX() + 3, snake[snake.size() - 1].getY());
				snake.push_back(elem1);
				snake.push_back(elem2);
				snake.push_back(elem3);
			}
			
			for(int i = snake.size() - 1; i > 0; i--)
			{
				snake[i] = snake[i - 1];
			}
			
			food = genFood(snake);
			fd = false;	
		}
		
		switch(*cmdSignal)
		{
			case 72: snake[0].toUp(); break;
        	case 80: snake[0].toDown(); break;
        	case 75: snake[0].toLeft(); break;
        	case 77: snake[0].toRight(); break;
        	case 27: exit = true; break;
        	default: break;
		} 
		
		snake[0].check();
		snake[snake.size() - 1].check();
			
		for(int i = 1; i < snake.size(); i++)
		{
			if(snake[0] == snake[i + 1]) exit = true;
		} 
		
		for(int i = 0; i < snake.size(); i++) //print of snake 
		{
			if(i == 0) snake[i].print();
			else snake[i].print('@');
		}
		
		if(exit) 
		{
			SetColor(15, 0);
			SetCur(width / 2 - 8, height / 2);
			cout << "g a m e  o v e r";
			break;
		}	
	}
	
	delete cmdSignal, score;
	snake.clear();
	
	//SetColor(15, 0);
	
	SetCur(width / 2 - 8, height / 2 + 1);
	cout << " Repeat? (y/n): \n";
	
	while(true)
	{
		switch(getch())
		{
			case 27: case 110:
				SetCur(0, height);
				return;
				break;
				
			case 121: //y
				game();
				break;
			
			default:
				break;
		}
	}
}

void logo() {
	
	cout << "@Yuriy Orlik\n\n";
	
	SetColor(green, black); 
	printf("*********************\n");
	printf("*                   *\n");
	printf("*     S N A K E     *\n");
	printf("*                   *\n");
	printf("*********************\n\n");
	
	SetColor(green, black); 
	cout << "arrows"; 
	SetColor(white, black);
	cout << " - control";

	SetColor(green, black); 
	cout << "\nesc"; 
	SetColor(white, black);
	cout << " - exit\n\n";
	
	SetColor(green, black);
	cout << "Press any key for continue... \n";
	
	getch();
}
