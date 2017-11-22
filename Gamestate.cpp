#include "Gamestate.h"
using namespace std;

void Gamestate::new_round ()
{
	deck.shuffle();
	cards = deck.get_deck();
}

void Gamestate::save_game(int num_save_game)
{
	ofstream savefile ("saves.txt");
	if (savefile.is_open())
	{
		savefile << num_save_game << endl;
		savefile << score[0] <<" "<< score[1] << endl;
		
	}
}

void Gamestate::deal()
{
	deck.shuffle();
	cards = deck.get_deck();
	for(int i = 0; i < 52; ++i)
	{
		if(i < 13)
		{
			hands[p1][i] = cards[i];
		}
		else if(i < 26)
		{
			hands[p2][i-13] = cards[i];
		}
		else if(i < 39)
		{
			hands[p3][i-26] = cards[i];
		}
		else if(i < 52)
		{
			hands[p4][i-39] = cards[i];
		}
	}
}