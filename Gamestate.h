//Gamestate.h
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include<vector>
#include<iostream>
#include<fstream>
#include<iostream>
#include "Card.h"
#include "Deck.h"

class Gamestate
{
	//State Variables
	protected:
	int score[2];
	std::vector< vector< <Card*> > hands(4, vector<Card*>(13));
	enum players {p1, p2, p3, p4} turn;
	Deck deck;
	Card * cards;

    public:
	//Default Constructor
	Gamestate() {score[0] = score[1] = 0; turn = p1;}
	
	//Constructor (if needed)
	
	//Shuffles deck and calls the deal function
	void new_round();
	
	//Needs to record the score, and the hands
	void save_game(int);
	
	//Reads the save_game file and sets up the game as such
	void load_game(int);
	
	//Deals out a shuffled deck into four hands (helper)
	void deal();
};

#endif //_GAMESTATE_H_
