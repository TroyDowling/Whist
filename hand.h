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
  Card* hand[13];
 public:
  Hand();

  void addCard(Card * c);
	
  void removeCard(int c){for(int card = c; card < length-1; card++) hand[card] = hand[card+1]; hand[length-1] = 0; length--;}

  Card * getCard(int c){return hand[c];}
	
  int getLen(){return length;}
  Card ** getHand(){return hand;}

  Hand & operator= (const Hand&);

};

#endif
