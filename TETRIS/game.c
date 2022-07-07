#include "game.h"
#include "interface.h"

int score = 0;

void GameOver(void)
{
	SetColor(WHITE, BLACK);
	SetCur(WIDTH + 1, 2);
	printf("Game over");
}

void ScorePrinter()
{
	SetColor(WHITE, BLACK);

	SetCur(14, 7);
	printf("Score");
	
	SetCur(14, 8);
	printf("%d", score);
	
	SetCur(14, 10);
	printf("LVL %d", score / 1000 + 1);
}
