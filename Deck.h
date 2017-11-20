#ifndef _DECK_H_
#define _DECK_H_
#include <algorithm>

#include "Card.h"

class Deck
{
  Card * deck[52];
 public:
  Deck();
  void shuffle();
  Card * get_deck() {return deck;}
}


