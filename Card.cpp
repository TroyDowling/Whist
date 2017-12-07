#include "Card.h"
using namespace std;

bool Card::mouse_over(int x, int y)
{
  if(x >= x_pos && x <= x_pos + (w/2))
	{
		if(y >= y_pos && y <= y_pos + h)
		{
		  cout << "card clicked" << endl;
		  return true;
		}
		else return false;
	}
	else return false;
}
