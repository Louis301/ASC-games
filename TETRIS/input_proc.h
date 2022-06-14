#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>
#include <windows.h>

typedef struct 
{
	int startX, startY;
	bool *data;
	char name;
	int height, width;
	int color;
	bool can_put;	
} Shape;

bool RecognitionInput(int key, Shape *current_s);

enum ConsoleKey {
	UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    ESCAPE = 27,
    ENTER = 13,
    PAUSE = 32
};

#endif  // input_proc.h
