#ifndef _AI_H_
#define _AI_H_
#include "Gamestate.h"
#include "Card.h"
#include "hand.h"

class AI
{
  int len, id, partner, invite;
  bool invited = false;
  
  /* There will be different algorithms in
   * makePlay that correspond to difficulty
   * settings. 0 = easy, 1 = interm, etc.
   */
  short difficulty;
  
 public:
  //gamestate reference, hand ID, diff
  
  AI(const Gamestate&, int, short);
  
  Card * makePlay(Gamestate&);
};

#endif //_AI_H_
