#include "Card.h"

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
