#include "game.h"
#include "interface.h"
#include "input_proc.h"
#include "interaction_with_shape.h"
#include "map_conversion.h"

void AtExitProgram(void);


int main(int argc, char *argv[]) {
	
	PrintFrame();
	
	srand(time(NULL));
	
	Shape current_s, saved_s, next_s;
	bool exit = false;
	bool _new = true;

	next_s = MakeShape(GetNameNewShape());
	
	while(!exit)
	{
		ScorePrinter(score);
		
		if(_new)
		{
			current_s = next_s;
			next_s = MakeShape(GetNameNewShape());
			DrawShape(&next_s, true);
			
			current_s.startX = 5;
			current_s.startY = 2;
		}
		
		if(CheckColission(&current_s))
		{
			if(_new)
			{
				exit = true;
				GameOver();
				continue;
			}
			else
			{	
				if(current_s.can_put == true)
				{
					DrawShape(&saved_s, true);
					DrawShape(&next_s, false);
					PutShape(&saved_s);
					_new = true;
					continue;
				}
				else
				{
					current_s = saved_s;
				}
			}
		}
		
		DrawShape(&current_s, true);
		saved_s = current_s;
		_new = false;

		
		if(kbhit()) 
		{
			Sleep(20);
			exit = RecognitionInput(getch(), &current_s);
		}
		else 
		{
			Sleep(500);
			ChangeStartPoint(&current_s, 0, 1); 
		}
		
		DrawShape(&saved_s, false);
	}
	
	AtExitProgram();
	return 0;
}

void AtExitProgram(void)
{
	SetCur(WIDTH, HEIGHT);
	SetColor(WHITE, BLACK);
}

/*
void AtExitProgram(void);

int main(int argc, char *argv[]) {
	
	PrintFrame();
	
	srand(time(NULL));
	
	Shape current_s, saved_s, next_s;
	bool exit = false;
	bool _new = true;

	next_s = MakeShape(GetNameNewShape());
	
	while(!exit)
	{
		ScorePrinter(score);
		
		if(_new)
		{
			current_s = next_s;
			next_s = MakeShape(GetNameNewShape());
			DrawShape(&next_s, true);
			
			current_s.startX = 5;
			current_s.startY = 2;
		}
		
		if(CheckColission(&current_s))
		{
			if(_new)
			{
				exit = true;
				GameOver();
				continue;
			}
			else
			{	
				if(current_s.can_put)
				{
					DrawShape(&saved_s, true);
					DrawShape(&next_s, false);
					PutShape(&saved_s);
					_new = true;
					continue;
				}
				else
				{
					current_s = saved_s;
				}
			}
		}
		
		DrawShape(&current_s, true);
		saved_s = current_s;
		_new = false;
		
		if(kbhit()) 
		{
			Sleep(20);
			exit = RecognitionInput(getch(), &current_s);
		}
		else 
		{
			Sleep(500);
			ChangeStartPoint(&current_s, 0, 1); 
		}
		
		DrawShape(&saved_s, false);
	}

	AtExitProgram();
	
	return 0;
}

void AtExitProgram(void)
{
	SetCur(WIDTH, HEIGHT);
	SetColor(WHITE, BLACK);
}*/
