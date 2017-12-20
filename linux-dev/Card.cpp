#include "Card.h"
using namespace std;

bool Card::mouse_over(int x, int y)
{
  if(x >= x_pos && x <= x_pos + (w/2))
	{
		if(y >= y_pos && y <= y_pos + h)
		{
		  return true;
		}
		else return false;
	}
	else return false;
}

Card& Card::operator = (Card& c){
  this->x_pos = c.get_x();
  this->y_pos = c.get_y();
  this->w = c.get_w();
  this->h = c.get_h();
  this->suit = c.get_suit();
  this->val = c.get_val();
  return *this;
}
