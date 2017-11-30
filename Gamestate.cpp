#include "Gamestate.h"
using namespace std;

/*
Number identifier of save game
Scores
turn
Hands (suit and value of cards separated by newlines)
*/
void Gamestate::save_game(int num_save_game)
{
	ofstream savefile ("saves.txt");
	if (savefile.is_open())
	{
		//allocate an address (greater than 15)
		savefile << num_save_game << endl;
		//save scores
		savefile << score[0] <<" "<< score[1] << endl;
		//save whose turn
		savefile << turn;
		int numCardsInHand;
		
		//save hands 
		//--- 
		//number of cards in hand
		//suit value
		//---
		for(int currenthand = 0; currenthand < 4; ++currenthand)
		{ 
			numCardsInHand = hands[currenthand].size();
			for(int currentcard = 0; currentcard < numCardsInHand; ++currentcard)
			{
				savefile << hands[currenthand][currentcard]->get_suit() <<" ";
				savefile << hands[currenthand][currentcard]->get_val() << endl;
			}
			savefile << endl;
		}
		savefile.close();		
	}
	else
	{
		cout << "Invalid save location." << endl;
		return;
	}
}

void Gamestate::load_game(int num_load_game)
{
	ifstream loadfile;
	int save_id, numCardsInHand, card_val;
	Card::suits card_suit;
	loadfile.open("saves.txt");
	if(!loadfile)
	{
		cout << "Invalid load location." << endl;
		return;
	}
	//No idea if this will work on the first try.
	while(true)
	{
		loadfile >> save_id;
		if(save_id == num_load_game)
		{
			//load scores
			loadfile >> score[0]; loadfile >> score[1];
			//load turn
			loadfile >> turn;
			//load hands
			for(int currenthand = 0; currenthand < 4; currenthand++)
			{
				loadfile >> numCardsInHand;
				for(int currentcard = 0; currentcard < numCardsInHand; currentcard++)
				{
					loadfile >> card_suit;
					hands[currenthand][currentcard]->set_suit(card_suit);
					loadfile >> card_val;
					hands[currenthand][currentcard]->set_val(card_val);
				}
			}
			loadfile.close();
			return;
		}
	}
}

void Gamestate::deal()
{
	deck.shuffle();
	cards = deck.get_deck();
	for(int i = 0; i < 13; ++i)
	{
		hands[0].addCard(*cards[i]);
	}
	for(int i = 13; i < 26; ++i)
	{
		hands[1].addCard(*cards[i]);
	}
	for(int i = 26; i < 39; ++i)
	{
		hands[2].addCard(*cards[i])
	}
	for(int i = 39; i < 52; ++i)
	{
		hands[3].addCard(*cards[i]);
	}
}
