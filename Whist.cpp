/* Whist.cpp --- Main project file for the Whist app
This is where the main function is, and should also
probably be where all or most of the OpenGL things are
taken care of. --- REV 0.1 11/15/2017 Anders Olson ---
*/

//As of implementations at 10:00 PM 16 Nov '17,
//this file (in addition to texture.cpp)
//contains barely enough functional code to constitute a demo.

//Turns out we're gonna be stuck with Texture.h/cpp
//-Bennett

//Include all imports, including relevant OpenGL libraries.
#include <iostream>
#include <fstream>
#ifdef MACOSX
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include <string>
#include "Gamestate.h"
#include "texture.h"
#include "hand.h"
using namespace std;
//End Imported Libraries(tm)

bool mouseIsDragging = false;

int game_Width = 720;
int game_Height = 405;
char programName[] = "Whist";
int whistT,w2T,w3T; //texture IDs
double PI = 3.14159264;

int mouseX = 0, mouseY = 0;

//texture for card back
int bg;
//textures for hearts
int hText[13];
//textures for spades
int sText[13];
//textures for clubs
int cText[13];
//textures for diamonds
int dText[13];
//textures for user hand
int userHandLen, ai1HandLen, ai2HandLen, ai3HandLen;
int userText[13];
int aiText[13];

//textures for the played cards of each trick
int playedText[4];

//Card parameters (sizes)
int card_Height = game_Height/7;
int card_Width = card_Height*.618;

//all of the grey rectangles (used for locations)
int dummyWidth = 30, dummyHeight = 40;
int sdummyWidth = 40, sdummyHeight = 30;
int pDummyW = 40, pDummyH = 50;

//What should be displayed? 0 = main menu, 1 = options, 2 = playgame
int DisplayState = 0;

Gamestate game;

// button info
bool buttonIsPressed = false, overButton = false;
double buttonPos[] = { 300, 150,   150, 60 };  // upper left, width, height
//button2
bool button2IsPressed = false, overButton2 = false;
double buttonPos2[] = { 300, 230,   150, 60 };

//A wonderful "borrowed" helper funtion.
void drawBox(double x, double y, double width, double height)
{
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}

void drawBox(double *pos)
{
  drawBox(pos[0], pos[1], pos[2], pos[3]);
 } 

void mouse_update(int x, int y)
{
  mouseX = x; mouseY = y;
  glutPostRedisplay();
}

void loadUserText()
{
	//The 0 stands for the user's hand
	//returns the integer value for how many cards there are in the user's hand
	userHandLen = game.get_handLen(0);
	Card * cardsInHand[userHandLen];

	for(int j = 0; j < userHandLen; ++j){
	  cardsInHand[j] = game.get_card(0,j);
	  //cout << cardsInHand[j]->get_suit() <<" "<< cardsInHand[j]->get_val() << endl;
	}
	for(int i = 0; i < userHandLen; ++i)
	{
		//clubs
	        if(cardsInHand[i]->get_suit() == 1)
		{
			//returns the value (0-12) of the i-th card in the list of cards.
			userText[i] = cText[cardsInHand[i]->get_val()];
		}
		//hearts
		else if(cardsInHand[i]->get_suit() == 2)
		{
			userText[i] = hText[cardsInHand[i]->get_val()];
		}
		//spades
		else if(cardsInHand[i]->get_suit() == 3)
		{
			userText[i] = sText[cardsInHand[i]->get_val()];
		}
		//diamonds
		else if(cardsInHand[i]->get_suit() == 4)
		{
			userText[i] = dText[cardsInHand[i]->get_val()];
		}
	}	
	
}

void loadPlayedText(){
  Card* cardsPlayed[4];
  for(int i = 0; i < 4; i++){
    cardsPlayed[i] = game.cards_played[i];
  }
  for(int l = 0; l < 4; l++){
    if(cardsPlayed[l] != NULL){
      //clubs
      if(cardsPlayed[l]->get_suit() == 1){
	playedText[l] = cText[cardsPlayed[l]->get_val()];
      }
      //hearts
      else if(cardsPlayed[l]->get_suit() == 2){
	playedText[l] = hText[cardsPlayed[l]->get_val()];
      }
      //spades
      else if(cardsPlayed[l]->get_suit() == 3){
	playedText[l] = sText[cardsPlayed[l]->get_val()];
      }
      //diamonds
      else if(cardsPlayed[l]->get_suit() == 4){
	playedText[l] = dText[cardsPlayed[l]->get_val()];
      }
    }
  }
}


void drawCards(int over = -1){
  //Updated to 13 cards per row
  //Displays all hand zones.

  card_Height = game_Height/7;
  card_Width = card_Height * .618;
  ai3HandLen = game.get_handLen(3);
  ai2HandLen = game.get_handLen(2);
  ai1HandLen = game.get_handLen(1);
  userHandLen = game.get_handLen(0);
  loadUserText();
  loadPlayedText();

  //spacing to align cards in center of screen
  double uwspacing = (game_Width/2) - (card_Width/2)*((userHandLen/2)+1);
  double wspacing = (game_Width/2) - (card_Width/2)*((ai1HandLen/2)+1);
  double hspacing = (game_Height/2) - (card_Width/2)*((ai3HandLen/2)+2);

  //drawTexture(texture ID, x, y, width, height, alpha, angle -in radians- );

  //Draw top cards
  for(int i = 0; i < ai2HandLen; i++){
    drawTexture(bg, wspacing+(i*(card_Width/2)), 10, card_Width, card_Height, 1, 0);
  }
  //Draw right cards
  for(int j = 0; j < ai3HandLen; j++){
    drawTexture(bg, game_Width - (card_Height-10), (hspacing + (j*(card_Width/2))), card_Width, card_Height, 1, (3*PI)/2);
  }
  //Draw left cards
  for(int i = 0; i < ai1HandLen; i++){
    drawTexture(bg, card_Height/3.5, (hspacing + (i*(card_Width/2))), card_Width, card_Height, 1, PI/2);
  }
  //Draw user cards
  for(int l= 0; l < userHandLen; l++){
    //if(game.get_card(0,l)->mouse_over(mouseX,mouseY)) {
    if(l == over){
      drawTexture(userText[l], uwspacing+(l*(card_Width/2)),
		  game_Height - (card_Height*1.1 + 10), card_Width*1.1, card_Height*1.1, 1, 0);
      game.get_card(0,l)->set_pos((uwspacing+(l*(card_Width/2))),
				  (game_Height - (card_Height + 10)), card_Width, card_Height);
    }
    else{
      drawTexture(userText[l], uwspacing+(l*(card_Width/2)),
		  game_Height - (card_Height + 10), card_Width, card_Height, 1, 0);
      game.get_card(0,l)->set_pos((uwspacing+(l*(card_Width/2))),
				  (game_Height - (card_Height + 10)), card_Width, card_Height);
    }
  }

  //Draw PLAYED cards
  for(int k = 0; k < 4; k++){
    if(game.cards_played[k] != NULL){
      //Draw the Player's Card
      if(k == 0){
	drawTexture(playedText[k], ((game_Width/2)-(card_Width/2)),
		    (((game_Height/2) - (card_Height/2))+card_Height),
		    card_Width, card_Height, 1, 0);
      }
      //Draw AI[1]'s Card
      //Draw AI[2]'s Card
      //Draw AI[3]'s Card
    }
  }

}

void drawWindow(){
  glClear(GL_COLOR_BUFFER_BIT);

  if(DisplayState == 0){
    // draw the button
    if ( buttonIsPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    drawBox(buttonPos);
    //draw button2
    if ( button2IsPressed ) glColor3f(0., 1., 0.);  // make it green
    else if ( overButton2 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(1, 1, 1);  // white
    drawBox(buttonPos2);
    //draw stuff
    drawTexture(whistT,  94,55,    400, 150, .9); // texID,   x,y,    width, height
    drawTexture(w2T,  500,210,    300, 200, .45);
    drawTexture(w3T,  300,150,    150, 60 );
  }
  else if(DisplayState == 2){
    drawCards();
    for(int i = 0; i < 13; ++i){
      if(game.get_card(0,i)->mouse_over(mouseX, mouseY))
	drawCards(i);
    }
  }
  glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y){
  int win = glutGetWindow();
  switch(c){
  case'q':
  case'Q':
  case 27:
    glutDestroyWindow(win);
    exit(0);
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

//I don't want to mess with resizing textures and mipmaps, if at all possible.
//This likely only delays the inevitable ;_;
void reshape(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   game_Width = w;  game_Height = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.,game_Width -1, game_Height-1, 0., -1.0, 1.0);

  //glutReshapeWindow(game_Width,game_Height);
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the button
bool onButton(int x, int y)
{
  return x >= buttonPos[0]  && y >= buttonPos[1] &&
         x <= buttonPos[0] + buttonPos[2] &&
         y <= buttonPos[1] + buttonPos[3];
}
bool onButton2(int x, int y)
{
  return x >= buttonPos2[0]  && y >= buttonPos2[1] &&
         x <= buttonPos2[0] + buttonPos2[2] &&
         y <= buttonPos2[1] + buttonPos2[3];
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y){
  if(GLUT_LEFT_BUTTON == button){
    if(GLUT_DOWN == state){
      //mouseIsDragging = true;
      // the user just pressed down on the mouse-- do something
      if(DisplayState==2){
	for(int i = 0; i < 13; i++){
	  if(game.get_card(0,i)->mouse_over(x,y)){
	    //if(game.get_hand(0)->getCard(i)->mouse_over(x,y)){
	    //if(game.isLegal((game.hands[0]->getCard(i)), 0){

	    game.cards_played[0] = game.get_card(0,i);
	    game.get_hand(0)->removeCard(i);
	    cout << "Card Removed." << endl;
	    //}
	  }
	  //else{ cout << "Card not removed (Conditions not met)." << endl; }
	}
      }
      else if(DisplayState==0){
	if ( onButton(x,y) ) buttonIsPressed = true;
	else buttonIsPressed = false;
	if ( onButton2(x,y) ) button2IsPressed = true;
	else button2IsPressed = false;
      }
    }
    else{
      //mouseIsDragging = false;
    	// the user just let go the mouse-- do something
      if ( onButton(x,y) && buttonIsPressed ){
	DisplayState = 2;
	game.deal();
	loadUserText();
        cout << "Play Game" << endl;
      }
      buttonIsPressed = false;
      if ( onButton2(x,y) && button2IsPressed ){
        cout << "Button press." << endl;
      }
      button2IsPressed = false;
    }
  }
  else if(GLUT_RIGHT_BUTTON == button){ /*empty*/ };
  mouseX = x; mouseY = y;
  glutPostRedisplay();
}


// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x, int y){
  //The mouse is moving and a button is down?!?! Will be integrated in time.
  mouseX = x, mouseY = y;
  glutPostRedisplay();
}

//This function is important, I think.
void init(void){
  glClearColor(0.0,0.0,0.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., game_Width-1, game_Height-1, 0., -1.0, 1.0);

  //Just... rolls right off the tongue, doesn't it?
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  cout << "Welcome to " << programName << "." << endl;
  cout << "A Functional demo!" << endl;
  cout << "Shuffles the deck, and deals out four hands." << endl;
}

//Loads all textures, 
void loadAllTextures()
{
	bg = loadTexture("imgs/cardback.pam");
	
	//load textures for clubs
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "imgs/clubs-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		cText[i] = loadTexture(param);
	}
	cText[9] = loadTexture("imgs/clubs-j-75.pam");
	cText[10] = loadTexture("imgs/clubs-q-75.pam");
	cText[11] = loadTexture("imgs/clubs-k-75.pam");
	cText[12] = loadTexture("imgs/clubs-a-75.pam");
	
	//load textures for hearts
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "imgs/hearts-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		hText[i] = loadTexture(param);
	}
	hText[9] = loadTexture("imgs/hearts-j-75.pam");
	hText[10] = loadTexture("imgs/hearts-q-75.pam");
	hText[11] = loadTexture("imgs/hearts-k-75.pam");
	hText[12] = loadTexture("imgs/hearts-a-75.pam");
	
	
	//load textures for spades
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "imgs/spades-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		sText[i] = loadTexture(param);
	}
	sText[9] = loadTexture("imgs/spades-j-75.pam");
	sText[10] = loadTexture("imgs/spades-q-75.pam");
	sText[11] = loadTexture("imgs/spades-k-75.pam");
	sText[12] = loadTexture("imgs/spades-a-75.pam");
	
	//load textures for diamonds
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "imgs/diamonds-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		dText[i] = loadTexture(param);
	}
	dText[9] = loadTexture("imgs/diamonds-j-75.pam");
	dText[10] = loadTexture("imgs/diamonds-q-75.pam");
	dText[11] = loadTexture("imgs/diamonds-k-75.pam");
	dText[12] = loadTexture("imgs/diamonds-a-75.pam");
}

//This function is OpenGL's GOD.
void init_gl_window(){
  char*argv[] = {programName};
  int argc = sizeof(argv)/sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(game_Width, game_Height);
  glutInitWindowPosition(300,50);
  glutCreateWindow(programName);
  init();

  //LOAD ALL THE TEXTURES
  loadAllTextures();
 
  whistT= loadTexture("whist1.pam"); // key to textures:  load them!
  w2T= loadTexture("w2.pam");
  w3T= loadTexture("w3.pam");

  //Draw stuff
  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_update);
  glutMainLoop();
}

//This stays like this.
int main ()
{
  init_gl_window();
}
