// interaction_with_shape.c

#include "interaction_with_shape.h"
#include "interface.h"

void ShapeRotation(Shape *sh)
{	
	bool tmp[sh->height][sh->width];
	int x, y, i = 0;
	
	for(y = 0; y < sh->height; y ++)
		for(x = 0; x < sh->width; x ++)
			tmp[y][x] = sh->data[i ++];
			
	i = 0;
	bool *tmp2 = (bool *)malloc(sh->width * sh->height);
	
	for(y = 0; y < sh->width; y ++)
		for(x = sh->height - 1; x >= 0; x --)
			tmp2[i ++] = tmp[x][y];
	
	sh->data = tmp2;
	sh->startY = sh->startY + sh->height - sh->width;
	
	int tmp3 = sh->height;
	sh->height = sh->width;
	sh->width = tmp3;
	
	sh->can_put = false;
}

char GetNameNewShape()
{
	switch(rand() % 7)
	{
		case 0: return 'o';
		case 1: return 't';
		case 2: return 's';
		case 3: return 'l';
		case 4: return 'j';
		case 5: return 'i';
		case 6: return 'z';
	}
}

bool CheckColission(Shape *shape)
{
	int x, y, i = 0;
	
	for(y = 0; y < shape->height; y ++) 
		for(x = 0; x < shape->width; x ++) 
			if(shape->data[i ++] == true && field[shape->startY + y][shape->startX + x] == true)
				return true;
		
	return false;
}

void ChangeStartPoint(Shape *shape, int dx, int dy)
{				
	shape->startX += dx;
	shape->startY += dy;
	shape->can_put = (dy != 0) ? true : false;
}

Shape MakeShape(char name)
{
	Shape shape;
	
	bool _I[] = { 1, 1, 1, 1 };
	bool _J[] = { 1, 0, 0, 1, 1, 1 };
	bool _L[] = { 0, 0, 1, 1, 1, 1 };
	bool _O[] = { 1, 1, 1, 1 };
	bool _S[] = { 0, 1, 1, 1, 1, 0 };
	bool _T[] = { 1, 1, 1, 0, 1, 0 };
	bool _Z[] = { 1, 1, 0, 0, 1, 1 };
	
	shape.name = name;
	shape.startX = 16;
	shape.startY = 2;
	shape.color = rand() % 15 + 1;
	shape.can_put = false;
	
	void InitShape(bool *tmp_data, int height, int width)
	{
		shape.data = (bool *)malloc(sizeof(tmp_data));
		int i;	
		
		for(i = 0; i < height * width; i ++)
			shape.data[i] = *(tmp_data ++);
		
		shape.height = height;
		shape.width = width;
	}
	
	switch(name)
	{		
		case 'i': InitShape(_I, 1, 4); break;
		case 's': InitShape(_S, 2, 3); break;
		case 't': InitShape(_T, 2, 3); break;
		case 'z': InitShape(_Z, 2, 3); break;
		case 'o': InitShape(_O, 2, 2); break;
		case 'l': InitShape(_L, 2, 3); break;
		case 'j': InitShape(_J, 2, 3); break;
	} 
	
	return shape;
}

void DrawShape(Shape *shape, bool draw_mode)
{	
	CursorHide();
	int x, y, i = 0;
	
	for(y = 0; y < shape->height; y ++) 
	{
		for(x = 0; x < shape->width; x ++) 
		{
			if(shape->data[i ++] == true)
			{
				SetCur(shape->startX + x, shape->startY + y);
				
				if(draw_mode)
				{
					SetColor(shape->color, shape->color);
				}
				else
				{
					SetColor(BLACK, BLACK);
				}
				
				printf("%c", shape->name);
			}
		}
	}
}



