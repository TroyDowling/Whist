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
using namespace std;
#ifdef MACOSX
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#include "Gamestate.h"
#include "texture.h"
//End Imported Libraries(tm)

bool mouseIsDragging = false;

int game_Width = 1080;
int game_Height = 720;
char programName[] = "Whist";
int bg, fs;
int dummyWidth = 100, dummyHeight = 140;

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
  //Starting with 10 cards per row.
  //...also, only 2 hands. Oh well.
  glColor3f(0.5,0.5,0.5);
  for(int i = 0; i < 8; i++){
    drawBox(25+(i*(dummyWidth+31)), 25, dummyWidth, dummyHeight);
  }
  for(int j = 0; j < 8; j++){
    drawBox(25+(j*(dummyWidth+31)), 555, dummyWidth, dummyHeight);
  }
}

void drawWindow(){
  glClear(GL_COLOR_BUFFER_BIT);
  drawTexture(bg,0,0,1080,720);
  drawCards();
  //This is be the implementation for drawing a *half* board of cards,
  //suitable only for testing.
  //The final implementaion will (in all good favor) be dynamic.
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
  glutReshapeWindow(1080,720);
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

  bg = loadTexture("bg.pam");
  fs = loadTexture("fibspir.pam");

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
