#include "AI.h"

AI::AI (Card ** h, short diff)
{
	difficulty = diff;
	for(int i = 0; i < 13; ++i)
	{
		hand[i] = h[i];
	}
}

AI::makePlay(int suitLed)
{
	
}