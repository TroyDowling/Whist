#ifndef _BUTTON_
#define _BUTTON_

/** Represents a Button */
class Button {
protected:
	double x;  /**< Top left x-coordinate of a Button */
	double y;  /**< Top left y-coordinate of a Button */
	double width;  /**< width of a Button */
	double height; /**< height of a Button */
public:
	/** Default constructor */
	Button();

	/** 4-argument constructor
		@param xcoord x-coordinate of a Button, to copy to x
		@param ycoord y-coordinate of a Button, to copy to y
		@param w width of a Button, to copy to width
		@param h height of a Button, to copy to height */
	Button(double xcoord, double ycoord, double w, double h);

	/** draw this Button */
	void drawButton();

	/** draw a Button at specified position with specified width and height
		@param pos a pointer to an array containing top left x and y coordinates, and width and height of a Button */
	void drawButton(double *pos);

	/** draw a text on this Button 
		@param text a pointer to a C-style string to be drawn*/
	void drawText(const char* text);

	/** draw a text at a specified location
		@param x x-coordinate of the text location
		@param y y-coordinate of the text location
		@param text a pointer to a C-style string to be drawn */
	void drawText(double x, double y, const char* text);

	/** draw a number at a specified location 
		@param x x-coordinate of the number's location
		@param y y-coordinate of the number's location
		@param num Number to be drawn */
	void drawNumber(double x, double y, double num);
};

#endif // _BUTTON_