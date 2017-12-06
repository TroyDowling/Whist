#ifndef _CARD_H_
#define _CARD_H_
#include<iostream>

//         1      2       3       4
//suits {clubs, hearts, spades, diamonds};

class Card
{
 protected:
  int x_pos, y_pos, w, h;
  int suit, val;

 public:
  Card(){val = -1; suit = 0;}
	
  //Constructor
  Card(int v, int s){if(v >= 0 && v <= 12) val = v; if(s >= 1 && s <= 4) suit = s;}
	
  bool mouse_over(int x,int y); //mouse x and mouse y

  int get_val () {return val;}
  int get_suit () {return suit;}
  void set_suit (int s) {suit = s;}
  void set_val (int v) {if(v >= 0 && v <= 12) val = v; else val = -1;}
};

#endif //_CARD_H_
