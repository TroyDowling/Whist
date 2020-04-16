#include "Deck.h"
using namespace std;

Deck::Deck()
{
  for(int i = 0; i < 52; ++i) deck[i] = new Card; //sets up pointers to cards
  int i = 0, val = 0;
  while(i < 52)
    {
      //val=>card --- 0=>2, 12=>Ace
      deck[i]->set_val(val);
      //cout << val << " ";
      if(i < 13) deck[i]->set_suit(1);
      else if(i < 26) deck[i]->set_suit(2);
      else if(i < 39) deck[i]->set_suit(3);
      else if(i < 52) deck[i]->set_suit(4);
      else deck[i]->set_suit(1);
      if(val < 12) ++val;
      else val = 0;
      ++i;
    }
  //cout << endl;
}

void Deck::shuffle()
{
  srand(time(0));
  for(int i = 0; i < 52; ++i) {
    int r = rand() % 52;
    Card * temp = deck[i];
    deck[i] = deck[r];
    deck[r] = temp;
  }
}
