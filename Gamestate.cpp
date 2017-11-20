#include "Gamestate.h"

void Gamestate::new_round ()
{
	deck.shuffle();
	cards = deck.get_deck();
}
