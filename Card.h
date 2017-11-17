#ifndef _CARD_H_
#define _CARD_H_

class Card
{
	protected:
	enum cardvals {
		H_A, H_2, H_3, H_4, H_5, H_6, H_7, H_8, H_9, H_10, H_J, H_Q, H_K,
		C_A, C_2, C_3, C_4, C_5, C_6, C_7, C_8, C_9, C_10, C_J, C_Q, C_K, 
		S_A, S_2, S_3, S_4, S_5, S_6, S_7, S_8, S_9, S_10, S_J, S_Q, S_K,
		D_A, D_2, D_3, D_4, D_5, D_6, D_7, D_8, D_9, D_10, D_J, D_Q, D_K 
	} val;
	public:
	//Enum implementaion is a little broken, but we don't need it for the demo.
	//I'll comment it out for now -Bennett
	Card(); //Temp default constr.
	//Card(int v){if(v >= 0 && v < 52) val = v;}
	bool Clicked(int x,int y); //Not finished
	//void show(); <- Good chance this won't be used
	//void animate(); <- Same here, both of these ought to be handled elsewhere
	int get_val () {return val;}
	//changed int to void return, removed temp.
	//void set_val (int v) {val = v;}
};

#endif //_CARD_H_
