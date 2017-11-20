#ifndef _CARD_H_
#define _CARD_H_

enum suits {clubs, hearts, spades, diamonds};

class Card
{
 protected:
  int x_pos, y_pos, w, h, val;
  suits suit;
 public:	
  Card(){val = -1; }
	
  //Constructor
  Card(int v, int s){if(v >= 0 && v < 13) val = v; if(s >= 0 && s < 4) suit = s;}
	
  bool mouse_over(int x,int y); //mouse x and mouse y

  int get_val () {return val;}
  suits get_suit () {return suit;}
  void set_suit (suits s) (suit = s;)
  void set_val (int v) {val = v;}
};

#endif //_CARD_H_
