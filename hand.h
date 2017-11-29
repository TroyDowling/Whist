#ifndef _Hand_
#define _Hand_
#include "Card.h"

class Hand{
  Card* hand[13];
 public:
  Hand(){
    for(int i = 0; i < 13; i++){
      hand[i] = NULL;
    }
  }

  void addCard(Card c){
    bool inserted = false;
    int i = 0;
    while(!inserted){
      if(hand[i] != NULL){
	*hand[i] = c;
	inserted = true;
      }
      else i++;
    }
  }
  void removeCard(int c){
    hand[c] = NULL;
  }
};

#endif
