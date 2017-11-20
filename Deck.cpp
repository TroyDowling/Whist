#include "Deck.h"
using namespace std;

Deck::Deck()
{
  for(int i; i < 52; ++i) deck[i] = new Card*; //sets up pointers to cards
  int i = 0, val = 0;
  while(i < 52)
    {
      deck[i]->set_value[val];
      if(i < 13) deck[i]->set_suit(Card::suits::hearts);
      else if(i < 26) deck[i]->set_suit(Card::suits::clubs);
      else if(i < 39) deck[i]->set_suit(Card::suits::spades);
      else if(i < 52) deck[i]->set_suit(Card::suits::diamonds);
      ++i;
      if(val < 13) ++val;
      else val = 0;
    }
}

void Deck::shuffle()
{
  random_shuffle(begin(deck), end(deck));
}
