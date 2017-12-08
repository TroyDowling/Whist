#ifndef _AI_H_
#define _AI_H_
#include "Gamestate.h"

class AI
{
	Card * hand[13];
	short difficulty;
	public:
	AI(){hand = 0; difficulty = 0;}
	AI(Card**, short);
	
	void aiSetHand(Card ** h, int len){for(int i=0; i<len; ++i) hand[i] = h[i];}
	void setDiff(int d){difficulty = d;}
	
	Card * makePlay(int suitLed);
}


#endif //_AI_H_