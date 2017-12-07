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
