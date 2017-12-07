#ifndef _AI_H_
#define _AI_H_
#include "Gamestate.h"
#include "Card.h"
#include "Hand.h"

class AI
{
        //This is the array of cards in the AI hand
	Card * handarr[13];
	int len;

	/* There will be different algorithms in
	 * makePlay that correspond to difficulty
	 * settings. 0 = easy, 1 = interm, etc.
	 */
	short difficulty;
	int partnerInvite;

	public:
	AI(){hand = 0; difficulty = 0;}
	//gamestate reference, hand ID, diff
	AI(Gamestate, int, short);
	AI(Card**, short);
	AI(Hand, short);
	
	Card * makePlay(int suitLed, Card ** cardsPlayed);
}


#endif //_AI_H_
