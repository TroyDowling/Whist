/* Whist.cpp --- Main project file for the Whist app
This is where the main function is, and should also
probably be where all or most of the OpenGL things are
taken care of. --- REV 0.1 11/15/2017 Anders Olson ---
*/

//As of implementations at 10:00 PM 16 Nov '17,
//this file (in addition to texture.cpp)
//contains barely enough functional code to constitute a demo.

/**********************
      SUPER GOAL:
   REMOVE DEPENDENCE
          ON
     TEXTURE.CPP/H
   AND USE OPENGL'S
    IMPLEMENTATION
**********************/
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

int game_Width = 700;
int game_Height = 700;
char programName[] = "Whist";
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
//all of the grey rectangles (used for locations)
int dummyWidth = 30, dummyHeight = 40;
int sdummyWidth = 40, sdummyHeight = 30;
int pDummyW = 40, pDummyH = 50;

void loadAllTextures();

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

void drawCards(){
  //Updated to 13 cards per row
  //(Will)Display all hand zones.
  for(int i = 0; i < 13; i++){
    drawTexture(bg, 120+(i*(30+5)), 10, 30, 40, 1, 0);
  }
  glColor3f(0.5,0.5,0.5);
  for(int j = 0; j < 13; j++){
    drawBox(30+(j*(pDummyW+10)), 600, pDummyW, pDummyH);
  }
  for(int i = 0; i < 13; i++){
    drawTexture(bg, 120+(i*(30+5)), 10, 30, 40, 1, 90);
  }
  for(int l= 0; l < 13; l++){
    drawBox(650, 70+(l*(sdummyHeight+5)), sdummyWidth, sdummyHeight);
  }
}

void drawWindow(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawCards();
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
  glutReshapeWindow(700,700);
}

void mouse(int button, int state, int x, int y){
  if(GLUT_LEFT_BUTTON == button){
    if(GLUT_DOWN == state){
      mouseIsDragging = true;
    }
    else{
      mouseIsDragging = false;
    }
  }
  else if(GLUT_RIGHT_BUTTON == button){ /*empty*/ };
  glutPostRedisplay();
}

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
  cout << "A \"Functional\" demo!" << endl;
}

//Loads all textures, 
void loadAllTextures()
{
	bg = loadTexture("cardback.pam");
	
	//load textures for clubs
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "clubs-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		cText[i] = loadTexture(param);
	}
	cText[9] = loadTexture("clubs-a-75.pam");
	cText[10] = loadTexture("clubs-j-75.pam");
	cText[11] = loadTexture("clubs-q-75.pam");
	cText[12] = loadTexture("clubs-k-75.pam");
	
	//load textures for hearts
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "hearts-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		hText[i] = loadTexture(param);
	}
	hText[9] = loadTexture("hearts-a-75.pam");
	hText[10] = loadTexture("hearts-j-75.pam");
	hText[11] = loadTexture("hearts-q-75.pam");
	hText[12] = loadTexture("hearts-k-75.pam");
	
	
	//load textures for spades
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "spades-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		sText[i] = loadTexture(param);
	}
	sText[9] = loadTexture("spades-a-75.pam");
	sText[10] = loadTexture("spades-j-75.pam");
	sText[11] = loadTexture("spades-q-75.pam");
	sText[12] = loadTexture("spades-k-75.pam");
	
	//load textures for diamonds
	for(int i = 0; i < 9; ++i)
	{
		string fname1 = "diamonds-";
		string fname2 = "-75.pam";
		int val = i + 2;
		string file = fname1 + to_string(val) +fname2;
		const char * param = file.c_str();
		dText[i] = loadTexture(param);
	}
	dText[9] = loadTexture("diamonds-a-75.pam");
	dText[10] = loadTexture("diamonds-j-75.pam");
	dText[11] = loadTexture("diamonds-q-75.pam");
	dText[12] = loadTexture("diamonds-k-75.pam");
}

//This function is OpenGL's GOD.
void init_gl_window(){
  char*argv[] = {programName};
  int argc = sizeof(argv)/sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(game_Width, game_Height);
  glutInitWindowPosition(200,200);
  glutCreateWindow(programName);
  init();

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
