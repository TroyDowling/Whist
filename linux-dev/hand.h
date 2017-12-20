#ifndef _Hand_
#define _Hand_
#include "Card.h"


/** Class Hand is a fixed-size container of Card objects, and can be manipulated in various ways.
 */
class Hand{
  int length; /** Contains the current 'size' of the hand, used by the Gamestate class. */
  /*
   * hand will always be 13, but the length will change
   * because we are only worried about a certain number
   * of cards in this hand.
   *
   */
 public:
  Card* hand[13]; /** An array of pointers to Card objects. Used by the Gamestate class. */
  Hand(); /** Default constructor. */

  void addCard(Card * c); /** A member function which adds cards to the Hand. */

  /** A member function which removes a Card from the Hand.
   * @param c The index in hand[] of the card to be removed. 
   */	
  void removeCard(int c);
  
  /**A member function which removes a target Card from the Hand.
   * @param c The target Card object to be removed.
   */
  void removeCard(Card * c);
  /** Pulls a card from the hand.
   * @param c The index of the card (in hand[]) to be pulled.
   */
  Card * getCard(int c){return hand[c];} 
  /** Returns the length of the hand currently.
   * @return length The length of the Hand currently.
   */	
  int getLen(){return length;}
  /** Sets the length of the hand.
   * @param l The new Length of the hand.
   */
  void setLen(int l){length = l;}
  /** Returns the specific Hand.
   * @return hand The requested array of Cards.
   */
  Card ** getHand(){return hand;}
  /** An operator which allows Hand objects to be equated.
   * @param Hand the Hand to be copied.
   * @return this the resultant Hand object.
   */
  Hand & operator= (const Hand&);
};

#endif
