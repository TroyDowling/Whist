//Gamestate.h
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include<iostream>
#include<fstream>
#include "Card.h"
#include "Deck.h"

class Gamestate
{
	//State Variables
	protected:
	int score[2];
	Card * hands[4];
	enum players {p1, p2, p3, p4} turn;
	Deck deck;
	Card * cards;

    public:
	//Default Constructor
	Gamestate() {score[0] = score[1] = 0; turn = p1;}
	
	//Constructor (if needed)
	
	/*essentially clears all data for hands,
	and shuffles up and deals a new round. */
	void new_round();
};

#endif //_GAMESTATE_H_
