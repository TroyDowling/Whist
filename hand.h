#ifndef _Hand_
#define _Hand_
#include "Card.h"

class Hand{
  int length;
  /*
   * hand will always be 13, but the length will change
   * because we are only worried about a certain number
   * of cards in this hand.
   *
   */
 public:
  Card* hand[13];
  Hand();

  void addCard(Card * c);
	
  void removeCard(int c);
  void removeCard(Card * c);

  Card * getCard(int c){return hand[c];}
	
  int getLen(){return length;}
  void setLen(int l){length = l;}
  Card ** getHand(){return hand;}
  Hand & operator= (const Hand&);
};

#endif
