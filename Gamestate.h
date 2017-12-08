//Gamestate.h
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include<vector>
#include<iostream>
#include<fstream>
#include<iostream>
#include "Card.h"
#include "Deck.h"
#include "hand.h"


class Gamestate
{
	//State Variables
	protected:
	int score[2];
	enum players {p1, p2, p3, p4} turn;
	Deck deck;
	Card * cards[52];
	Hand * hands[4];

    public:
	//Default Constructor
	Gamestate();
	
	//Constructor (if needed)
	
	//Needs to record the score, and the hands
	void save_game(int);
	
	//Reads the save_game file and sets up the game as such
	void load_game(int);
	
	//Deals out a shuffled deck into four hands (helper)
	void deal();
	
	//Is this play a legal move?
	bool isLegal(Card c,int s){if(c.get_suit() == s) return true; else return false;}
	
	//return a requested hand
	//0 = user, 1 = ai1, etc;
	Card ** get_hand(int h){return hands[h];}
	Card * get_card(int h, int c){return hands[h]->getCard(c);}
	int get_handLen(int h){return hands[h]->getLen();}
};

#endif //_GAMESTATE_H_
