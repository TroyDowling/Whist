#ifndef _Hand_
#define _Hand_
#include "Card.h"

class Hand{
  int length;
  Card* hand[13];
 public:
  Hand();

  void addCard(Card * c);
	
  void removeCard(int c){hand[c] = 0; length--;}

  Card * getCard(int c){return hand[c];}
	
  int getLen(){return length;}
  Card ** getHand(){return hand;}
};

#endif
