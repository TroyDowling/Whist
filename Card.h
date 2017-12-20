<<<<<<< HEAD
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

  //Helpers for getting protc. vals
  int get_x() { return x_pos; }
  int get_y() { return y_pos; }
  int get_w() { return w; }
  int get_h() { return h; }
  int get_val () {return val;}
  int get_suit () {return suit;}

  //"Set" Helpers
  void set_suit (int s) {suit = s;}
  void set_val (int v) {if(v >= 0 && v <= 12) val = v; else val = -1;}
  void set_pos(int x, int y, int width, int height){w = width; h = height; x_pos = x; y_pos = y;}
  Card& operator = (Card&);
};

#endif //_CARD_H_
=======
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

  //Helpers for getting protc. vals
  int get_x() { return x_pos; }
  int get_y() { return y_pos; }
  int get_w() { return w; }
  int get_h() { return h; }
  int get_val () {return val;}
  int get_suit () {return suit;}

  //"Set" Helpers
  void set_suit (int s) {suit = s;}
  void set_val (int v) {if(v >= 0 && v <= 12) val = v; else val = -1;}
  void set_pos(int x, int y, int width, int height){w = width; h = height; x_pos = x; y_pos = y;}
  Card& operator = (Card&);
};

#endif //_CARD_H_
>>>>>>> e10e6c07685f42fdfeb282564a296f0f13c84f6f
