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
#include "Button.h"
#include "Gamestate.h"
#include "texture.h"
#include "hand.h"
using namespace std;
//End Imported Libraries(tm)

bool mouseIsDragging = false;

int game_Width = 720;
int game_Height = 405;
char programName[] = "Whist";
int whistT,w2T,w3T,oT,eT; //texture IDs
double PI = 3.14159264;

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

// button in the Menu
bool buttonIsPressed = false, overButton = false;
double PlaygamePos[] = { 300, 120,   150, 60 };  // upper left, width, height
//button2
bool button2IsPressed = false, overButton2 = false;
double OptionPos[] = { 300, 200,   150, 60 };
//button3
bool button3IsPressed = false, overButton3 = false;
double ExitPos[] = {300,280,150,60};


//buttons for Option Screen
bool SouBISPressed = false, overButton4 = false;
double SouPos[] = {300,120,150,60};
bool AiBISPressed = false, overButton5 = false;
double AiPos[] = {300,220,150,60};



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


void drawCards(){
  //Updated to 13 cards per row
  //Displays all hand zones.

  card_Height = game_Height/7;
  card_Width = card_Height * .618;
  ai1HandLen = ai2HandLen = ai3HandLen = 13;

  //spacing to align cards in center of screen
  double wspacing = (game_Width/2) - (card_Width/2)*((userHandLen/2)+1);
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
    drawTexture(userText[l], wspacing+(l*(card_Width/2)), game_Height - (card_Height + 10), card_Width, card_Height, 1, 0);
  }
}

void drawOption() {
   cout <<DisplayState<<endl;
  if ( SouBISPressed ) glColor3f(1., 0., 0.);  // make it red
  else if ( overButton4 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0.0, .65, .1);  // gray
  drawBox(SouPos);

  Button Ai;
  if ( AiBISPressed ) glColor3f(1., 0., 0.);  // make it red
  else if ( overButton5 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0.0, .65, .1);  // gray
  Ai.drawButton(AiPos);


    }


void drawWindow(){
  glClear(GL_COLOR_BUFFER_BIT);

  if(DisplayState == 0){
       // draw the button
  cout <<DisplayState<<endl;
  if ( buttonIsPressed ) glColor3f(1., 0., 0.);  // make it red
  else if ( overButton ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(0.0, .65, .1);  // gray
  drawBox(PlaygamePos);
//draw button2
  if ( button2IsPressed ) glColor3f(1., 0., 0.);  // make it green
  else if ( overButton2 ) glColor3f(.75,.75,.75);  // light gray
  else glColor3f(.0, .70, .1);  // white
  drawBox(OptionPos);
  //Button funtion
  Button Exit;
  if ( button3IsPressed) glColor3f(1., 0., 0.);
  else if (overButton3) glColor3f(.75, .75, .75);
  else glColor3f(0., .65, 0.1);
  Exit.drawButton(ExitPos); 

  //draw stuff
  drawTexture(whistT,  94,30,    400, 150, .9); // texID,   x,y,    width, height
  drawTexture(w2T,  500,210,    300, 200, .45);
//main menu buttons textures
  drawTexture(w3T,  290,115,    170, 70 );
  drawTexture(oT,  302, 203,    145, 50 );
  drawTexture(eT,  300, 285,    152, 50 );


}
else if (DisplayState ==1){
  drawOption();
}
else if(DisplayState == 2){
  cout <<DisplayState<<endl;
    drawCards();
  }
    /*for(int i = 0; i < 13; ++i){
      if(game.get_card(0,i)->mouse_over(mouseX, mouseY))
*/

  else if (DisplayState ==3){}
  glutSwapBuffers();
}
//}


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
bool onButton(int x, int y, double* buttonPos)
{
  return x >= buttonPos[0]  && y >= buttonPos[1] &&
         x <= buttonPos[0] + buttonPos[2] &&
         y <= buttonPos[1] + buttonPos[3];
}

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y){
  if(GLUT_LEFT_BUTTON == button){
    if(GLUT_DOWN == state){
      //mouseIsDragging = true;
      // the user just pressed down on the mouse-- do something
      if(DisplayState==2){
	     for(int i = 0; i < 13; i++){
	      if(game.get_hand(0)->getCard(i)->mouse_over(x,y)){
	    //if(game.isLegal((game.hands[0]->getCard(i)), 0){
      //game.cards_played[0] = game.get_card(0,i);

	         game.get_hand(0)->removeCard(i);
	         cout << "Card Removed." << endl;
	    //}
	       }
	  //else{ cout << "Card not removed (Conditions not met)." << endl; }
	     }
      //}
      }
    else if (DisplayState == 0){
	   if ( onButton(x,y, PlaygamePos) ) buttonIsPressed = true;
      else buttonIsPressed = false;
      if ( onButton(x,y, OptionPos) ) button2IsPressed = true;
      else button2IsPressed = false;
      if ( onButton(x,y, ExitPos) ) button3IsPressed = true;
      else button3IsPressed = false;
        }

    else if (DisplayState == 1){
      if ( onButton(x,y, SouPos) ) SouBISPressed = true;
      else SouBISPressed = false;
      if ( onButton(x,y, AiPos) ) SouBISPressed = true;
      else SouBISPressed = false;

    }

    }
    else{
      //mouseIsDragging = false;
    	// the user just let go the mouse-- do something
      if ( onButton(x,y, PlaygamePos) && buttonIsPressed ){
        DisplayState=2;
        game.deal();
        loadUserText();
          cout << "PlayGame Button press." << endl;
      }
      buttonIsPressed = false;
      if ( onButton(x,y,OptionPos) && button2IsPressed ){
        DisplayState=1;
        cout << "Options Button press." << endl;
      }
      button2IsPressed = false;
      if ( onButton(x,y,ExitPos) && button3IsPressed ){
        DisplayState=3;
        cout << "Exit Button press." << endl;
      }
      button3IsPressed = false;

      if ( onButton(x,y,SouPos) && SouBISPressed ){
          cout << "Sound Button press." << endl;
      }
      SouBISPressed = false;
    }
  }
  else if(GLUT_RIGHT_BUTTON == button){ /*empty*/ };
  glutPostRedisplay();
}
//}


// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x, int y){
  //The mouse is moving?!?! Will be integrated in time.


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
void loadAllTextures(){
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
 
  whistT= loadTexture("imgs/whist1.pam"); // key to textures:  load them!
  w2T= loadTexture("imgs/w2.pam");

  w3T= loadTexture("imgs/p1.pam");
  oT= loadTexture("imgs/o1.pam");
  eT= loadTexture("imgs/e1.pam");

   //LOAD ALL THE TEXTURES
  loadAllTextures();  
  //Draw stuff
  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutMainLoop();
}

//This stays like this.
int main ()
{
  init_gl_window();
}
