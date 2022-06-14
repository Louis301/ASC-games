#include "map_conversion.h"
#include "interface.h"
#include "game.h"

void PutShape(Shape *shape)
{
	int x, y, i = 0;
	
	for(y = 0; y < shape->height; y ++) 
	{
		for(x = 0; x < shape->width; x ++) 
		{
			if(shape->data[i ++] == true)
				field[shape->startY + y][shape->startX + x] = true;
		}
	}
	
	for(y = shape->startY; y < shape->startY + shape->height; y ++)
	{
		bool row_for_remove = true; 
		
		for(x = 2; x < WIDTH - 11; x ++)
		{
			if(field[y][x] == false)
			{
				row_for_remove = false;
				break;
			}
		}
		
		if(row_for_remove)
		{
			OffsetDown(y, shape);
		}
	}
}

void OffsetDown(int border, Shape *shape)
{
	int y = border, x;
	score += 100;
	
	while(y > 1)
	{
		for(x = 2; x < WIDTH - 11; x ++)
		{	
			if(y != 2)
				field[y][x] = field[y - 1][x];
			else
				field[y][x] = false;
		}
		
		y --;
	}
	
	for(y = 2; y < HEIGHT - 2; y ++)
	{
		for(x = 2; x < WIDTH - 11; x ++)
		{
			SetCur(x, y);
			
			if(field[y][x] == false)
			{
				SetColor(BLACK, BLACK);
				printf("0");
			}
			else
			{
				SetColor(WHITE, GREY);
				printf(" ");
			}
		}
	}
}
