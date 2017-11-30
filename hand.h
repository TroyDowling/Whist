#ifndef _Hand_
#define _Hand_
#include "Card.h"

class Hand{
	int length;
  Card* hand[13];
 public:
  Hand(){
		length = 13;
    for(int i = 0; i < length; i++){
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
	
  void removeCard(int c){hand[c] = NULL; length--;}
	
  int getLen(){return length;}
  Card ** getHand(){return hand;}
};

#endif
