/* Whist.cpp --- Main project file for the Whist app

========================================================
This file is where the 'int main()' function is.

The layout for this code is as follows:

- All #includes
- All global variable definitions
- Most drawing functions
- AI
- Input functions
- Glut init functions
- Main

Admittedly, the layout above is not perfect, but it can
be trusted to a reasonable degree.
=========================================================

 --- REV 1.0 12/15/2017 Anders Olson ---
*/




//Include all imports, including relevant OpenGL libraries.
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
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
#include "AI.h"
#include <unistd.h>
using namespace std;
//End Imported Libraries

//Begin global variables

bool mouseIsDragging = false, userTurn = true;

int game_Width = 720;
int game_Height = 405;
char programName[] = "Whist";
int whistT,w2T,w3T,oT,eT,dT,bT,mT,gear, gpT,mbg, pwT; //texture IDs
int deT, dmT, dhT; //difficulty buttons
double PI = 3.14159264;

int cardMatch = 0;

int mouseX = 0, mouseY = 0;

//0 = stolaf cards, 1 = black, 2 = blue, 3 = red
int whichcb = 0;

//texture for game background
int bkg;
//texture for card back
//use bg in code, set bg# to bg
int bg, bg2, bg3, bg4, bg5;
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

// button in the Menu
bool PlayBIsPressed = false, overButton = false;
double PlaygamePos[] = { 300, 120,   150, 60 };  // upper left, width, height
//button2
bool button2IsPressed = false, overButton2 = false;
double OptionPos[] = { 300, 200,   150, 60 };
//button3
bool button3IsPressed = false, overButton3 = false;
double ExitPos[] = {300,280,150,60};


//buttons for Option Screen
bool AiBISPressed = false, overButton5 = false;
double AiPos[] = {300,80,150,60};
bool SouBISPressed = false, overButton4 = false;
double SouPos[] = {300,160,150,60};
bool ConBISPressed = false, overButton6 = false;
double ConPos[] = {300,240,150,60};
bool BackBISPressed = false, overButton7 = false;
double BackPos[] = {505,318,90,62};

//buttons for Difficulty screen
bool EBISPressed = false, overButton8 = false;
double EPos[] = {300,80,150,60};
bool MBISPressed = false, overButton9 = false;
double MPos[] = {300,160,150,60};
bool HBISPressed = false, overButton10 = false;
double HPos[] = {300,240,150,60};
bool Back2BISPressed = false, overButton11 = false;
double Back2Pos[] = {505,318,90,62};
bool Back3BIsPressed = false, overButton12 = false;
double Back3Pos[] = {70,20,90,62};

bool z=false;
//Cards to be drawn in order they appear:
Card * drawcards[4];

//Initializes AI - Use ai.set_diff(int) to change difficulty later
AI ai1(game,1,0);
AI ai2(game,2,0);
AI ai3(game,3,0);

//Runs a timer for delaying the change in tricks
void timer(double arg){
  clock_t startTime = clock();
  double secondsPassed;
  double secondsToDelay = arg;
  bool running = true;
  while(running){
    secondsPassed = (clock() - startTime) / (CLOCKS_PER_SEC/10);
    if(secondsPassed >= secondsToDelay){
      //cout << "Erasing playedText[], game.playedCards[]" << endl;
      running = false;
    }
  }
}

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


/* Keeps track of the mouse at all times,
 * uses the passive glut update cycle.
 * (In other words, this will be called
 * whenever the mouse moves, regardless
 * of actual input.) 
 */
void mouse_update(int x, int y)
{
  mouseX = x; mouseY = y;
  glutPostRedisplay();
}

//Loads the textures to be displayed as the user's hand
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

//Loads the textures of cards that have been played (middle of screen)
void loadPlayedText(){
  Card* cardsPlayed[4];
  for(int i = 0; i < 4; i++){
    cardsPlayed[i] = drawcards[i];
  }
  for(int l = 0; l < 4; l++){
    if(cardsPlayed[l] != 0 && cardsPlayed[l] != NULL){
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

void AIgameplay();

//Draws the played cards in front of their respective hands
void drawPlayedCards(){
  loadPlayedText();
  int count = 0;
  for(int i = 0; i < 4; ++i){
    if(playedText[i] == 0) ++count;
  }
  if(count == 4) return;
  for(int k = 0; k < 4; k++){
    if(playedText[k] != 0){
      //Draw the Player's Card
      if(k == 0){
	drawTexture(playedText[k], ((game_Width/2)-(card_Width/2)),
		    (((game_Height/2) - (card_Height/2))+card_Height),
		    card_Width, card_Height, 1, 0);
      }
      //Draw AI[1]'s Card (RIGHT)
      else if(k == 3){
	drawTexture(playedText[k], (((game_Width/2)-(card_Width/2))+card_Width),
		    ((game_Height/2) - (card_Height/2)),
		    card_Width, card_Height, 1, 0);
      }
      //Draw AI[2]'s Card (TOP)
      else if(k ==2){
	drawTexture(playedText[k], ((game_Width/2)-(card_Width/2)),
		    (((game_Height/2) - (card_Height/2))-card_Height),
		    card_Width, card_Height, 1, 0);
      }
      //Draw AI[3]'s Card (LEFT)
      else if (k == 1){
	drawTexture(playedText[k], (((game_Width/2)-(card_Width/2))-card_Width),
		    ((game_Height/2) - (card_Height/2)),
		    card_Width, card_Height, 1, 0);
      }
    }
  }
}

//Draws all cards on the screen
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
  //AIgameplay();

  //spacing to align cards in center of screen
  double uwspacing = (game_Width/2) - (card_Width/2)*((userHandLen/2)+1);
  double wspacing = (game_Width/2) - (card_Width/2)*((ai1HandLen/2)+1);
  double hspacing = (game_Height/2) - (card_Width/2)*((ai3HandLen/2)+2);

  //drawTexture(texture ID, x, y, width, height, alpha, angle -in radians- );

  drawTexture(bkg, 0, 0, game_Width, game_Height, 1, 0);
  drawPlayedCards();

	//Button inside the playgame screen
	Button Back3;
    if ( Back3BIsPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, 0.0, 0.0);  // gray
    Back3.drawButton(Back3Pos);
drawTexture(gpT,  70, 20, 90, 62);

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
}


//This is where the AIs will make their plays, and their cards will be assigned to / removed from
//  the relevant places. *For more details, see AI.cpp
void AIgameplay(){
  int j = 0;
  Card * playedCard;
  userTurn = false;
  for(int count = 0; count < 4; ++count){
    if(game.who_played[count] != -1) ++j; //Has everyone played this hand?
  }
  if(j != 4){
    switch(game.getTurn()){
    case 0:
      cout << "Your turn!" << endl;
      break;
    case 1:
      cout<< "It is the LEFT AI's turn." << endl;
      //for(int i = 0; i < 4; ++i) cout << game.who_played[i] <<" ";
      playedCard = ai1.makePlay(game);
      for(int i = 0; i < 4; ++i){
	if(game.cards_played[i] == 0){
	  game.set_cards_played(i, playedCard);
	  break;
	}
      }
      //cout << playedCard->get_suit() <<" "<< playedCard->get_val()+2 << endl;
      drawcards[1] = playedCard;
      game.get_hand(1)->removeCard(playedCard);
      game.nextTurn();
      drawPlayedCards();
      AIgameplay();
      break;
    case 2:
      cout<<"It is the PARTNER AI's turn." << endl;
      //for(int i = 0; i < 4; ++i) cout << game.who_played[i] <<" ";
      playedCard = ai2.makePlay(game);
      for(int i = 0; i < 4; ++i){
	if(game.cards_played[i] == 0){
	  game.set_cards_played(i, playedCard);
	  break;
	}
      }
      //cout << playedCard->get_suit() <<" "<< playedCard->get_val()+2 << endl;
      drawcards[2] = playedCard;
      game.get_hand(2)->removeCard(playedCard);
      game.nextTurn();
      drawPlayedCards();
      AIgameplay();
      break;
    case 3:
      cout<<"It is the RIGHT AI's turn." << endl;
      //for(int i = 0; i < 4; ++i) cout << game.who_played[i] <<" ";
      playedCard = ai3.makePlay(game);
      for(int i = 0; i < 4; ++i){
	if(game.cards_played[i] == 0){
	  game.set_cards_played(i, playedCard);
	  break;
	}
      }
      //cout << playedCard->get_suit() <<" "<< playedCard->get_val()+2 << endl;
      drawcards[3] = playedCard;
      game.get_hand(3)->removeCard(playedCard);
      game.nextTurn();
      drawPlayedCards();
      AIgameplay();
      break;
    default:
      break;
    }
    cout << "======================================" << endl; //Makes terminal pretty
  }
}
  
//Draws menus
void drawOption() {
  if (DisplayState == 0){
    // draw the button
    Button Playgame;
    if ( PlayBIsPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, 0.0, 0.0);  // gray
    Playgame.drawButton(PlaygamePos);
    //draw button2
    Button Option;
    if ( button2IsPressed ) glColor3f(1., 0., 0.);  // make it green
    else if ( overButton2 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(.0, 0.0, 0.0);  // white
    Option.drawButton(OptionPos); 
    //Button funtion
    Button Exit;
    if ( button3IsPressed) glColor3f(1., 0., 0.);
    else if (overButton3) glColor3f(.75, .75, .75);
    else glColor3f(0.0, 0.0, 0.0);
    Exit.drawButton(ExitPos); 
    //draw stuff
    drawTexture(whistT, 0, 30,   400, 150); // texID,   x,y,    width, height
    drawTexture(w2T,  450,250,    300, 150, 1);
    //main menu buttons textures
    drawTexture(w3T,  290,115,    170, 70 );
    drawTexture(oT,  302, 203,    145, 50 );
    drawTexture(eT,  300, 285,    152, 50 ); 
  }
  if (DisplayState == 1){
    Button Sound;
    if ( SouBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton4 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Sound.drawButton(SouPos);
    Button Ai;
    if ( AiBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton5 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Ai.drawButton(AiPos);
    
    Button Con;
    if ( ConBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton6 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Con.drawButton(ConPos);
    
    Button Back;
    if ( BackBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton7 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Back.drawButton(BackPos);
    //button texture
    drawTexture(dT,  305, 85, 142, 50);
    drawTexture(mT,  305, 165, 142, 50);
    drawTexture(bg,  305, 245, 142, 50);
    drawTexture(bT,  509, 324,  82, 50 );
    drawTexture(pwT,  10, 205, 250, 200);

  }

  else if (DisplayState ==4){
    Button Easy;
    if ( EBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton4 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Easy.drawButton(EPos);
    
    Button Medium;
    if ( MBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton5 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Medium.drawButton(MPos);
    
    Button Hard;
    if ( HBISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton6 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Hard.drawButton(HPos);
    
    Button Back2;
    if ( Back2BISPressed ) glColor3f(1., 0., 0.);  // make it red
    else if ( overButton7 ) glColor3f(.75,.75,.75);  // light gray
    else glColor3f(0.0, .65, .1);  // gray
    Back2.drawButton(Back2Pos);
    //button textures
    drawTexture(w2T,  10,250,    300, 150, 1);

    drawTexture(deT,  305, 85, 142, 50);
    drawTexture(dmT,  305, 165,  142, 50 );
    drawTexture(dhT,  305, 245, 142, 50);
    drawTexture(bT,  509, 324,  82, 50 );
  }
}
    
void loadAllTextures();

//Glut sees this, then it calls other functions
void drawWindow(){
  int j = 0;
  glClear(GL_COLOR_BUFFER_BIT);
  if(DisplayState == 0){
    drawOption(); //Draw the main menu
  }
  else if (DisplayState ==1){
    drawOption(); //Draw the options menu
  }
  else if(DisplayState == 2){ //Drwa the game, run a few checks periodically
    drawTexture(bkg,0,0,game_Width, game_Height, 1, 0);
    drawCards();
    for(int i = 0; i < game.get_handLen(0); ++i){
      if(game.get_card(0,i)->mouse_over(mouseX, mouseY)) drawCards(i);
    }
    for(int i = 0; i < 4; ++i){
      if(game.who_played[i] != -1) ++j;
    }
    if(j == 4){
      game.chkWinner();
      for(int i = 0; i < 4; ++i) drawcards[i] = 0;
      cout << "Tricks played so far: " << game.tricksPlayed << endl;
      if(game.tricksPlayed == 13){
	game.chkWinnerH();
      }
      drawWindow();
      timer(30);
      for(int i = 0; i < 4; i++){
	drawWindow();
	timer(0.3);
	playedText[i] = 0;
	game.cards_played[i] = 0;
      }
      AIgameplay();
    }
  }
  else if (DisplayState ==3){
    int win = glutGetWindow();
    glutDestroyWindow(win);
    exit(0);
    glutPostRedisplay();
  }
  else if(DisplayState == 7){

    DisplayState=0;
    drawWindow();
  }
  else if(DisplayState == 8){
  	drawOption();
  	DisplayState=1;
  }
  	
  else if(DisplayState == 4){
    drawOption();
  }
glutSwapBuffers();

}

/*
  If the user presses Q, quit the game and end all processes.
*/
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

/*
  Borrowed from lab files, works very nicely.
*/
void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   game_Width = w;  game_Height = h;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.,game_Width -1, game_Height-1, 0., -1.0, 1.0);
}

// the following function tests whether a point at position x,y is inside
//   the rectangle on the screen corresponding to the button
bool onButton(int x, int y, double* buttonPos)
{
  return x >= buttonPos[0]  && y >= buttonPos[1] &&
         x <= buttonPos[0] + buttonPos[2] &&
         y <= buttonPos[1] + buttonPos[3];
}

int play_suit = 0; //GLOBAL - this one snuck down here somehow. Oh well.

// the mouse function is called when a mouse button is pressed down or released
void mouse(int button, int state, int x, int y){
  if(GLUT_LEFT_BUTTON == button){
    if(GLUT_DOWN == state){
      //mouseIsDragging = true;
      // the user just pressed down on the mouse-- do something
      if(DisplayState==2){
		if ( onButton(x,y, Back3Pos) ) Back3BIsPressed = true;
		else  Back3BIsPressed = false;
		z=true;


	if(game.cards_played[0] != 0) play_suit = game.cards_played[0]->get_suit();
	else play_suit = 0;
	if(game.getTurn() == 0){
	  for(int i = 0; i < 13; i++){
	    if(game.get_card(0,i)->mouse_over(x,y)){
	      cardMatch = i;
	    }
	  }
	}
      }
      else if (DisplayState == 0){
	if ( onButton(x,y, PlaygamePos) ) PlayBIsPressed = true;
	else PlayBIsPressed = false;
	if ( onButton(x,y, OptionPos) ) button2IsPressed = true;
	else button2IsPressed = false;
	if ( onButton(x,y, ExitPos) ) button3IsPressed = true;
	else button3IsPressed = false;
      }
      
      else if (DisplayState == 1){
	if ( onButton(x,y, SouPos) ) SouBISPressed = true;
	else  SouBISPressed = false;
	if ( onButton(x,y, AiPos) ) AiBISPressed = true;
	else AiBISPressed = false; 
	if ( onButton(x,y, ConPos) ) ConBISPressed = true;
	else ConBISPressed = false; 
	if ( onButton(x,y, BackPos) ) BackBISPressed = true;
	else BackBISPressed = false; 
      }
      else if (DisplayState == 4){
	if ( onButton(x,y, EPos) ) EBISPressed = true;
	else  EBISPressed = false;
	if ( onButton(x,y, MPos) ) MBISPressed = true;
	else MBISPressed = false; 
	if ( onButton(x,y, HPos) ) HBISPressed = true;
	else HBISPressed = false; 
	if ( onButton(x,y, Back2Pos) ) Back2BISPressed = true;
	else Back2BISPressed = false; 
}
      
    }
    else{
      //mouseIsDragging = false;
      // the user just let go the mouse-- do something
      if(DisplayState == 2){
	//If this is the same card that you just had your mouse over
	if(game.get_card(0,cardMatch)->mouse_over(x,y) && game.getTurn() == 0){
	  //If this is a legal play in the game
	  if(game.isLegal(game.get_card(0, cardMatch), play_suit, 0) || play_suit == 0){
	    //Tell the program you played this card
	    for(int i = 0; i < 4; ++i){
	      if(game.who_played[i] == -1){
		game.set_who_played(i, 0);
		break;
	      }
	    }
	    //Tell the program which card you played
	    for(int i = 0; i < 4; ++i){
	      if(game.cards_played[i] == 0){
		game.set_cards_played(i,game.get_card(0,cardMatch)); //The user played this card
		break;
	      }
	    }
	    //Add the card to this array to be drawn later
	    drawcards[0] = game.get_card(0,cardMatch);
	    game.get_hand(0)->removeCard(cardMatch);
	    game.nextTurn();
	    drawPlayedCards();
	    AIgameplay();
	  }
	}
	for(int i = 0; i < 4; i++){
	  playedText[i] = 0;
	}
      }

      if ( onButton(x,y, PlaygamePos) && PlayBIsPressed){
        DisplayState=2;
        game.deal();
        loadUserText();
		cout << "PlayGame Button press." << endl;
      }
      	PlayBIsPressed = false;
      
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
      
      if ( onButton(x,y,AiPos) && AiBISPressed ){
        DisplayState = 4;
	cout << "Ai Button press." << endl;
      }
      AiBISPressed = false;

      if ( onButton(x,y,Back3Pos) && Back3BIsPressed ){
      	DisplayState=8;
      		cout << "Back button in Playgame screen press." << endl;
      }
      Back3BIsPressed = false;

      if ( onButton(x,y,ConPos) && ConBISPressed ){
	if(whichcb < 3){
	  ++whichcb;
	}
	else whichcb = 0;
	if(whichcb == 0) bg = bg5; //cardback = stolaf
	else if(whichcb == 1) bg = bg2; //cardback = black
	else if(whichcb == 2) bg = bg3; //cardback = blue
	else if(whichcb == 3) bg = bg4; //cardback = red
	else bg = bg5; //default to ole
	cout << "Cardback Button press." << endl;
      }
      ConBISPressed = false;
      
      if ( onButton(x,y,BackPos) && BackBISPressed ){
      	if (z==false){DisplayState=7;}
      	else { 
      		DisplayState=2;
      		drawWindow();}
	cout << "Back Button press." << endl;
      }
      BackBISPressed = false;
      
      //difficulty button
      if ( onButton(x,y,EPos) && EBISPressed ){
	ai1.set_diff(0);
	ai2.set_diff(0);
	ai3.set_diff(0);
	cout << "Easy Difficulty Button press." << endl;
      }
      EBISPressed = false;
      
      if ( onButton(x,y,MPos) && MBISPressed ){
	ai1.set_diff(0);
	ai2.set_diff(0);
	ai3.set_diff(0);
	cout << "Medium difficulty Button press." << endl;
      }
      MBISPressed = false;
      
      if ( onButton(x,y,HPos) && HBISPressed ){
	ai1.set_diff(0);
	ai2.set_diff(0);
	ai3.set_diff(0);
	cout << "Hard difficulty Button press." << endl;
      }
      HBISPressed = false;
      
      if ( onButton(x,y,Back2Pos) && Back2BISPressed ){
        DisplayState=8;
	cout << "Back2 Button press." << endl;
      }
      Back2BISPressed = false;
    }
  }
  else if(GLUT_RIGHT_BUTTON == button){ /*empty*/ };
  mouseX = x; mouseY = y;
  glutPostRedisplay();
}
//}


// the mouse_motion function is called when the mouse is being dragged,
//   and gives the current location of the mouse
void mouse_motion(int x, int y){
  //The mouse is moving and a button is down?!?! Will likely not be integrated.
  mouseX = x, mouseY = y;
  if(userTurn) glutPostRedisplay();
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

  cout << "Welcome to " << programName << "!" << endl;
  //No longer a demo, and yet is nothing more...
  //cout << "A Functional demo!" << endl;
  cout << "The deck is shuffled and the cards are layed! /n /t Let's Play!" << endl;
}

//Loads all textures, 
void loadAllTextures(){
	bg = loadTexture("imgs/cardback.pam");
	bg2 = loadTexture("imgs/cbblack.pam");
	bg3 = loadTexture("imgs/cbblue.pam");
	bg4 = loadTexture("imgs/cbred.pam");
	bg5 = loadTexture("imgs/cardback.pam");
	bkg = loadTexture("imgs/gameback.pam");
	//gear = loadTexture("imgs/settings.pam");

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
  w2T= loadTexture("imgs/mo1.pam");

  w3T= loadTexture("imgs/p1.pam");
  oT= loadTexture("imgs/o1.pam");
  eT= loadTexture("imgs/e1.pam");
  pwT= loadTexture("imgs/pw1.pam");

  //options
  dT= loadTexture("imgs/dd.pam");
  mT= loadTexture("imgs/m1.pam");
  bT= loadTexture("imgs/b1.pam");
//Difficulty buttons
  deT= loadTexture("imgs/de1.pam");
  dmT= loadTexture("imgs/dm1.pam");
  dhT= loadTexture("imgs/dh1.pam");
  bT= loadTexture("imgs/b1.pam");
  //game play menu
  gpT= loadTexture("imgs/gpm.pam");
   //LOAD ALL THE TEXTURES
  loadAllTextures();  
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

	
	
