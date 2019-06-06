#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <FreeImage.h>

/* Dimensions de la fenetre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

static float aspectRatio;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 8.;

/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    /*if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;*/

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1.) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}

/* Objets cannoniques */
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

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

int main(int argc, char** argv) 
{
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
     SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
  
    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        

        glPushMatrix();
            glScalef(100,100,1);
            glColor3f(0.5,0.5,0.7);
            drawSquare(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,1,0);
            glScalef(8,0.4,1);
            glColor3f(1,1,1);
            drawSquare(1);
        glPopMatrix();

        
        glPushMatrix();
            glTranslatef(0,2,0);
            glPushMatrix();
                glColor3f(1,1,1);
                glScalef(0.4,2,1);
                drawSquare(1);
            glPopMatrix();
        glPopMatrix();
     
        glPushMatrix();
            glTranslatef(-2,2,0);
            glPushMatrix();
                glRotatef(26.5,0,0,1);
                glPushMatrix();
                    glScalef(4.5,0.4,1);
                    glColor3f(1,1,1);
                    drawSquare(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2,2,0);
            glPushMatrix();
                glRotatef(-26.5,0,0,1);
                glPushMatrix();
                    glScalef(4.5,0.4,1);
                    glColor3f(1,1,1);
                    drawSquare(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-2,-1,0);
            glPushMatrix();
                glRotatef(-45,0,0,1);
                glPushMatrix();
                    glScalef(5.56,0.4,1);
                    glColor3f(1,1,1);
                    drawSquare(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2,-1,0);
            glPushMatrix();
                glRotatef(45,0,0,1);
                glPushMatrix();
                    glScalef(5.56,0.4,1);
                    glColor3f(1,1,1);
                    drawSquare(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4,1,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(1,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();


        glPushMatrix();
            glTranslatef(0,1,0);
            glColor3f(0,0,0);
            glScalef(0.2,0.2,1);
            drawCircle(1);  
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-4,1,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(0,1,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
     
        glPushMatrix();
            glTranslatef(0,3,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,-3,0);
            glPushMatrix();
                glScalef(0.2,0.2,1);
                glColor3f(0,0,0);
                drawCircle(1);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-4,3,0);
            glScalef(0.2,0.2,1);
            drawTowerYellow();
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0,3,0);
            glScalef(0.2,0.2,1);
            drawTowerRed();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4,3,0);
            glScalef(0.2,0.2,1);
            drawTowerGreen();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-4,-3,0);
            glScalef(0.2,0.2,1);
            drawTowerBlue();
        glPopMatrix();

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    break;
                    
                default:
                    break;
            }
        }



        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

/*    int width=100;
int height=100;


BYTE *pixels = (BYTE*)malloc(width * height * 3);

glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels);

FIBITMAP *image = FreeImage_ConvertFromRawBits(pixels, width, height, 3 * width, 24, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

if (FreeImage_Save(FIF_BMP, image, "screenshot.bmp", 0))
    printf("Successfully saved!\n");
else
    printf("Failed saving!\n");

FreeImage_Unload(image);

free(pixels);*/

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;
}



