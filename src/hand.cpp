#include "hand.h"
using namespace std;

Hand::Hand()
{
  length = 13;
  for(int i = 0; i < length; i++)
    {
      hand[i] = 0;
    }
}

void Hand::addCard(Card * c)
{
  bool inserted = false;
  int i = 0;
  while(!inserted)
    {
      if(hand[i] == 0)
	{
	  hand[i] = c;
	  inserted = true;
	}
      else i++;
    }
}

Hand & Hand::operator=(const Hand & h)
{
  length = h.length;
  for(int i = 0; i < length; ++i){
    hand[i] = h.hand[i];
  }
  return *this;
}

void Hand::removeCard(int c)
{
    for(int curr = c; curr < 12; ++curr){
      hand[curr] = hand[curr+1];
    }
  --length;
}

void Hand::removeCard(Card * c)
{
  int index;
  for(int i = 0; i < length; ++i){
    if(c->get_val() == hand[i]->get_val() && c->get_suit() == hand[i]->get_suit()){
      index = i;
    }
  }
  removeCard(index);
}
