#ifndef _CARD_H_
#define _CARD_H_

class Card
{
	protected:
	int x_pos, y_pos w, h;
	
	public:
	//2=0 - Ace = 12
	enum cardvals {
		two, three, four, five, six, seven,
		eight, nine, ten, jack, queen, king, ace
	};
	//clubs, hearts, spades, diamonds
	enum suit {c, h, s, d};
	
	//Enum implementaion is a little broken, but we don't need it for the demo.
	//I'll comment it out for now -Bennett (Should work now) -AO
	
	Card(){val = -1; }
	
	//Constructor
	Card(int v){if(v >= 0 && v < 52) val = v;}
	
	bool mouse_over(int x,int y);
	//void show(); <- Good chance this won't be used
	//void animate(); <- Same here, both of these ought to be handled elsewhere
	
	int get_val () {return val;}
	void set_val (int v) {val = v;}
};

#endif //_CARD_H_
