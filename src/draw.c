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

#include "draw.h"

float radiusJaune = 2;
float radiusBleu = 10;
float radiusRouge = 6;
float radiusVert = 4;

// static float aspectRatio;

// /* Nombre de bits par pixel de la fenetre */
// static const unsigned int BIT_PER_PIXEL = 32;

// /* Espace fenetre virtuelle */
// static const float GL_VIEW_SIZE = 8.;

/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

//  Nombre minimal de millisecondes separant le rendu de deux images 
// static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
/* Objets cannoniques */
// void drawOrigin() 
// {
//     float currentColor[4];
//     glGetFloatv(GL_CURRENT_COLOR,currentColor);

//     glBegin(GL_LINES);

//     glColor3f(1., 0., 0.);
//     glVertex2f( 0.0 , 0.0);
//     glVertex2f( 1.0 , 0.0);

//     glColor3f(0., 1., 0.);
//     glVertex2f( 0.0 , 0.0);
//     glVertex2f( 0.0 , 1.0);

//     glEnd();

//     glColor3fv(currentColor);
// }

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}
void drawCircle(int filled) 
{
    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}

void drawTowerYellow()
{
	    glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(1,1,0);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

		glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(1,1,0.5);
            glScalef(0.8,0.8,1);
            drawCircle(1);  
        glPopMatrix();
   

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.5,0.5,1);
                glColor3f(1,1,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();


}

void drawTowerRed()
{
	    glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(1,0,0);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.8,0.8,1);
                glColor3f(1,0.5,0.5);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.5,0.5,1);
                glColor3f(1,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
}

void drawTowerGreen()
{
	    glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(0,1,0);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.8,0.8,1);
                glColor3f(0.5,1,0.5);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.5,0.5,1);
                glColor3f(0,1,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
}

void drawTowerBlue()
{
	    glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(0,0,1);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.8,0.8,1);
                glColor3f(0.5,0.5,1);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.5,0.5,1);
                glColor3f(0,0,1);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
}

void drawMonster1()
{
	glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(0,0,0);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.8,0.8,1);
                glColor3f(1,1,1);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.6,0.6,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.4,0.4,1);
                glColor3f(1,1,1);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
}
void drawMonster2()
{
	glPushMatrix();
            glTranslatef(0,0,0);
            glColor3f(0,0,0);
            glScalef(1,1,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.8,0.8,1);
                glColor3f(1,1,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.6,0.6,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.4,0.4,1);
                glColor3f(1,1,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,0,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
}
void drawLegende(){
	glPushMatrix();
	    	glTranslatef(2.76,-1.46,0);
	    	glScalef(0.2,0.2,1);
	    	drawTowerBlue();
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(2.76,-2.20,0);
	    	glScalef(0.2,0.2,1);
	    	drawTowerYellow();
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(2.76,-2.90,0);
	    	glScalef(0.2,0.2,1);
	    	drawTowerGreen();
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(2.76,-3.70,0);
	    	glScalef(0.2,0.2,1);
	    	drawTowerRed();
	    glPopMatrix();
}

void drawTowerBlue2(float Xt,float Yt)
{
   	glPushMatrix();
	glTranslatef(Xt,Yt,0);
	   	glPushMatrix();
			glScalef(0.2,0.2,1);
			drawTowerBlue();
		glPopMatrix();

	    glPushMatrix();

	       	glScalef(radiusBleu*0.2,radiusBleu*0.2,1);
			drawCircle(0);
		glPopMatrix();

		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.0,0.0,1.0,0.2);
			glScalef(radiusBleu*0.2,radiusBleu*0.2,1);
			drawCircle(1);
		glPopMatrix();	
	glPopMatrix();	
	    }
void drawTowerGreen2(float Xt,float Yt){
		    glPushMatrix();
			glTranslatef(Xt,Yt,0);
			    glPushMatrix();
			       	glScalef(0.2,0.2,1);
			       	drawTowerGreen();
			    glPopMatrix();

			    glPushMatrix();
			       	glScalef(radiusVert*0.2,radiusVert*0.2,1);
			       	drawCircle(0);
			    glPopMatrix();	

			    glPushMatrix();
			    	glEnable(GL_BLEND);
			    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			    	glColor4f(0.0,1.0,0.0,0.2);
			    	glScalef(radiusVert*0.2,radiusVert*0.2,1);
			       	drawCircle(1);
			    glPopMatrix();
			glPopMatrix();
	    }
void drawTowerYellow2(float Xt,float Yt){
		   	
		   	glPushMatrix();
			glTranslatef(Xt,Yt,0); 
				glPushMatrix();
			        glScalef(0.2,0.2,1);
			       	drawTowerYellow();
			    glPopMatrix();

			    glPushMatrix();
			       	glScalef(radiusJaune*0.2,radiusJaune*0.2,1);
			       	drawCircle(0);
			    glPopMatrix();

			    glPushMatrix();
			    	glEnable(GL_BLEND);
			    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			    	glColor4f(1.0,1.0,0.0,0.2);
			    	glScalef(radiusJaune*0.2,radiusJaune*0.2,1);
			       	drawCircle(1);
			    glPopMatrix();
			glPopMatrix();
	    }
void drawTowerRed2(float Xt,float Yt){
			glPushMatrix();
			glTranslatef(Xt,Yt,0); 
			    glPushMatrix();
			       	glScalef(0.2,0.2,1);
			       	drawTowerRed();
			    glPopMatrix();

			    glPushMatrix();
			       	glScalef(radiusRouge*0.2,radiusRouge*0.2,1);
			       	drawCircle(0);
			    glPopMatrix();	

			    glPushMatrix();
			    	glEnable(GL_BLEND);
			    	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			    	glColor4f(1.0,0.0,0.0,0.2);
			    	glScalef(radiusRouge*0.2,radiusRouge*0.2,1);
			       	drawCircle(1);
			    glPopMatrix();
			glPopMatrix();
	    }
