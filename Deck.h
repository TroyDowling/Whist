#ifndef _DECK_H_
#define _DECK_H_
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "Card.h"
/** Class Deck is a fixed - size conatiner of Card objects, and can be 
manipulated in various ways. It is at the core of this project.
*/
class Deck
{
  Card * deck[52]; /** An array of pointers to cards */
 public:
  Deck(); /** default constructor, sets up an array. */
  void shuffle(); /** shuffles up the array of cards using a stdlib random method.  */
  Card ** get_deck() {return deck;} /** returns the entire deck array. */
  Card * getCard(int index) {return deck[index];}/** returns a specific card @param index the index of the deck class to be found */
};

#endif
