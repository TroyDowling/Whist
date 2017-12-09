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

        //self explanatory
	int score[2];

	//makes code easier to read
        int turn;

	//Deck class
	Deck deck;

	//Essentially the deck
	Card * cards[52];

	//Pointers to the hand class
	Hand * hands[4];

    public:
	//Default Constructor
	Gamestate();
	
	//Constructor (if needed)
	
	//Entire round
	Card * allCardsPlayed[52];
	int allWhoPlayed[52];
	void set_allCardPlayed(int i, Card* c){allCardsPlayed[i]=c;}
	void set_allWhoPlayed(int i, int v){allWhoPlayed[i]=v;}

	//This trick (renamed slightly for convenience)
	Card * cards_played[4]; 
	int who_played[4];
	void set_cards_played(int i, Card* c){cards_played[i] = c;}
	void set_who_played(int i, int v){who_played[i] = v;}

	//Needs to record the score, and the hands
	void save_game(int);
	
	//Reads the save_game file and sets up the game as such
	void load_game(int);
	
	//Deals out a shuffled deck into four hands (helper)
	void deal();

	//Returns the current turn.
	int getTurn(){ return turn; }
       
	
	//Is this play a legal move?
	bool isLegal(Card c,int s);
	
	//return a requested card in a requested hand
	//0 = user, 1 = ai1, etc;
	Hand * get_hand(int h){return hands[h];}
	Card * get_card(int h, int c){return hands[h]->getCard(c);}
	int get_handLen(int h){return hands[h]->getLen();}
};

#endif //_GAMESTATE_H_
