#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//#include"draw.c"

void drawOrigin(); 
void drawSquare(int filled); 
void drawCircle(int filled);
void drawTowerYellow();
void drawTowerRed();
void drawTowerGreen();
void drawTowerBlue();
void drawMonster1();
void drawMonster2();
void drawLegende();
void drawTowerBlue2(float Xt,float Yt);
void drawTowerGreen2(float Xt,float Yt);
void drawTowerYellow2(float Xt,float Yt);
void drawTowerRed2(float Xt,float Yt);