#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "verify.c"
#include "verifyMap.c"
#include "createMap.c"


#include "draw.c"
#include "deplacementMonstres.h"

//#include <FreeImage.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
//#include "mapToScale.c"
#define WIDTH 800
#define HEIGHT 600 

/* Dimensions de la fenetre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

float traductionX(float x){
	return (x-400)/75.0;
}

float traductionY(float y){
	return -(y-300)/75.0;
}

// static float px = 0.013333;
static float x_in ,y_in ;
// static float x_out, y_out;
// static float x_1, y_1;
// static float x_2, y_2;
// static float x_4, y_4;

float Xtower[100];
float Ytower[100];
float Xt[100];
float Yt[100];
int ColorTower[100];
int Argent = 2;
/*float XtowerB;
float YtowerB;*/
// float radiusJaune = 2;
// float radiusBleu = 10;
// float radiusRouge = 6;
// float radiusVert = 4;


static float varx = 0.;
static float vary = 0.;
// static float varx2 = 0.;
// static float vary2 = 0.;
// static float speed = 1;

static float curx = -4;
static float cury = 1;

// static float route_x = 0;
// static float route_y = 0;

// int current =0;

// static int dest1 = 4;
// static int dest2 = 3;
// static int dest3 = 3;


static float aspectRatio;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 8.;

/* Subdivisions cercle */
// static const int CIRCLE_SUBDIVS = 2<<5;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;






void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

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





// void vBitmapOutput(int x, int y, char *string, void *font);

// void vBitmapOutput(int x, int y, char *string, void *font)
// {
// 	int len,i; // len donne la longueur de la chaîne de caractères

// 	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
// 	len = (int) strlen(string); // Calcule la longueur de la chaîne
// 	for (i = 0; i < len; i++) {
// 		glutBitmapCharacter(font,string[i]); 
		
// 		// Affiche chaque caractère de la chaîne
// 	}
// 	//printf("%s",string);
// 	// Réinitialise la position du premier caractère de la chaîne
// 	glRasterPos2f(0, 0);
// }

// void RenderText(TTF_Font *font, const GLubyte R, const GLubyte G, const GLubyte B,
//                 const double X, const double Y,  char  *texte)
// {
//     /*Create some variables.*/
//     SDL_Color color = {R, G, B};
//     SDL_Surface *Message = TTF_RenderText_Blended(font, texte, color);
//     GLuint Texture = 0;
 
//     SDL_Surface *tmp = SDL_CreateRGBSurface(0,Message->w,Message->h,32,0,0,0,0);
//     SDL_BlitSurface(Message,NULL,tmp,NULL);
 
//     /*Generate an OpenGL 2D texture from the SDL_Surface*.*/
//     glGenTextures(1, &Texture);
 
//     glEnable(GL_TEXTURE_2D);
 
//     glBindTexture(GL_TEXTURE_2D, Texture);
 
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
//     glTexImage2D(GL_TEXTURE_2D, 0, 4, Message->w, Message->h, 0, GL_RGBA,
//                  GL_UNSIGNED_BYTE, tmp->pixels);
 
//             glColor3f(1,1,1);
 
//         glLoadIdentity();
//         glTranslated(X, Y, 0);
//         glBegin(GL_QUADS);
//         glTexCoord2d(0, 0); glVertex2d(0, 0);
//         glTexCoord2d(1, 0); glVertex2d(0.5, 0);
//         glTexCoord2d(1, 1); glVertex2d(0.5, 0.5);
//         glTexCoord2d(0, 1); glVertex2d(0, 0.5);
//         glEnd();
 
//     glDisable(GL_TEXTURE_2D);
 
//     /*Clean up.*/
//     //SDL_SaveBMP(Message,"rendu.bmp");
//     glDeleteTextures(1, &Texture);
//     SDL_FreeSurface(Message);
//     SDL_FreeSurface(tmp);
// }


int main(int argc, char** argv) 
{	

    ITD itd;
    scanITD("data/map1.itd",&itd);
    for(int i=0; i<itd.nombreNoeuds; i++){
        printf("- noeud %d = %d --- son type est %d\n", i+1,itd.indices[i],itd.types[i]);
    }
    //printf("%d\n",itd.pixelsConstructibles[1][3]);
    // for(int i=0; i<800;i++){
    //  for(int j=0; j<600; j++){
    //      printf("au pixel [%d][%d] = > [%d]\n",i,j,itd.pixelsConstructibles[i][j]);
    //  }
    // }
    creerCarte(scanMap(itd.nameImage,&itd),itd.nameImage,&itd,800,600);
	
	int money = 50;
	int i = 0;
	int k =0;

	x_in=traductionX(100.0);
	y_in=traductionY(225.0);
	// x_out=traductionX(700.0);
	// y_out=traductionY(225.0);
	// x_1=traductionX(400.0);
	// y_1=traductionY(225.0);
	// x_2=traductionX(400.0);
	// y_2=traductionY(75.0);
	// x_4=traductionX(400);
	// y_4=traductionY(525);

	Xtower[i]=traductionX(Xtower[i]);
	Ytower[i]=traductionX(Ytower[i]);
	/*XtowerB=traductionX(XtowerB);
	YtowerB=traductionX(YtowerB);*/
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

    /* Initialisation du titre de la fenetre */
	SDL_WM_SetCaption("TOWER DEFENSE", NULL);

    /* Chargement de l'image */
    // char image_path[] = "images/MAP2SCORE.png";
    char image_path[10+longueurChaine(itd.nameImage)];
    strcat(image_path,"images/");
    strcat(image_path,itd.nameImage);
    
    SDL_Surface* image = IMG_Load(image_path);
    if(NULL == image) {
        fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
        exit(EXIT_FAILURE);
    }

    /* Initialisation de la texture */
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", image_path);
            return EXIT_FAILURE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */

		glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture_id);

        glMatrixMode(GL_MODELVIEW);
		

		glLoadIdentity();

		// glColor3d(0.5,0.5,1);
		// vBitmapOutput(400,100,"TEST one two one two",GLUT_BITMAP_HELVETICA_18);


		glPushMatrix();
            // glTranslatef(40., -20., 0.);
            // glRotatef(30., 0.0, 0.0, 1.0);
            // glScalef(1., 2., 0.);

			glColor3f(1,1,1);

            glBegin(GL_QUADS);
        	
		    glTexCoord2f(0, 1);
            glVertex2f(-5.33, -4);
        
            glTexCoord2f(1, 1);
            glVertex2f(5.33, -4);
        
            glTexCoord2f(1, 0);
            glVertex2f(5.33, 4);
        
            glTexCoord2f(0, 0);
            glVertex2f(-5.33, 4);

		    glEnd();

        glPopMatrix();

	// SDL_Init(SDL_INIT_VIDEO);
 //    TTF_Init();
 
 //    TTF_Font *font = TTF_OpenFont("police.ttf",20);
 //    SDL_Event event;
 //    int quit = 0;
 
 //    SDL_SetVideoMode(500,500, 24,SDL_OPENGL);
 
 //    glClearColor(0.5,0.5,0.5,0); //Couleur du fond
 
 //    while(quit == 0)
 //    {
 //        SDL_PollEvent(&event);
 //        switch(event.type)
 //        {
 //            case SDL_QUIT:
 //                quit = 1;
 //            break;
 //        }
 
 //        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
 //        RenderText(font,255,0,255,-1,0,"test");
 
 //        SDL_GL_SwapBuffers();
 //        SDL_Delay(33);
 //    }
 
 //    TTF_Quit();
        glBindTexture(GL_TEXTURE_2D, 0);
        
        glDisable(GL_TEXTURE_2D);
        


        glPushMatrix();
        	glTranslatef(x_in+varx, y_in+vary,0);
        	glScalef(0.2,0.2,1);
        	drawMonster2();
        glPopMatrix();

        drawLegende();
        
		
        
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
                    Xtower[i]=(-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio;
                    Ytower[i]= -(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.;
                    //printf("clic en (%d, %d) ,,,,,i= %d \n", e.button.x, e.button.y,i);
                    printf(" Xtower[%d] = %f \n", i,Xtower[i] );
                    printf(" Ytower[%d] = %f \n", i,Ytower[i] );
                    break;
                    	




		                /* Touche clavier */
				case SDL_KEYDOWN:   
					switch (e.key.keysym.sym) 
					{
						case SDLK_j :
							if (money>=5){
                                printf("Vous avez assez d'argent pour acheter la tour jaune !\n");
                                money = money -5;
                                printf("Il vous reste %d euro(s)\n", money);
                                Argent = 0;
                            } 
                            if (money<5){
                                printf("vous n'avez pas assez d'argent pour acheter la tour jaune... \n");
                                Argent = 1;
                            } 
                            ColorTower[i] = 1; 
							goto finally;
						case SDLK_r :
                            if (money>=10){
                                printf("Vous avez assez d'argent pour acheter la tour rouge !\n");
                                money = money -10;
                                printf("Il vous reste %d euro(s)\n", money);
                                Argent = 0;
                            } 
                            if (money<10) {
                                Argent = 1;
                                printf("vous n'avez pas assez d'argent pour acheter la tour rouge... \n");
                            }
							ColorTower[i] = 2; 
							goto finally;
						case SDLK_v :
                            if (money>=20){
                                printf("Vous avez assez d'argent pour acheter la tour verte !\n");
                                money = money -20;
                                printf("Il vous reste %d euro(s)\n", money);
                                Argent = 0;
                            } 
                            if (money<20) {
                                Argent = 1;
                                printf("vous n'avez pas assez d'argent pour acheter la tour verte... \n");
                            }
							ColorTower[i] = 4;
							goto finally;
						case SDLK_b :
                            if (money>=2){
                                printf("Vous avez assez d'argent pour acheter la tour blue !\n");
                                money = money -2;
                                printf("Il vous reste %d euro(s)\n", money);
                                Argent = 0;
                            } 
                            if (money<2) {
                                Argent = 1;
                                printf("vous n'avez pas assez d'argent pour acheter la tour blue... \n");
                            }
                            ColorTower[i] = 3;
							goto finally;
				
				finally:
					//printf(" appuye sur %c\n ", e.key.keysym.sym);	
					printf(" ColorTower[%d] = %d \n",i,ColorTower[i]);
                    printf("vous avez %d euro(s) \n",money);
                    printf("argent =  %d \n",Argent );
					
					i++;
					break;
						default:

							break;
					}
					break;
				
				default:
					break;
		            }
		        }
		        
			        if(ColorTower[i]==0){
			        	drawLegende();
			        }
			        if(ColorTower[i-1]==1 && Argent == 0){
			        	drawTowerYellow2(Xtower[i],Ytower[i]);
			        	drawTowerYellow2(Xtower[i-1],Ytower[i-1]);
			        	drawTowerYellow2(Xtower[i-2],Ytower[i-2]);
			        	drawTowerYellow2(Xtower[i-3],Ytower[i-3]);
			        }
			        if(ColorTower[i-1]==2  && Argent == 0){
			        	drawTowerRed2(Xtower[i],Ytower[i]);
			        }
			        if(ColorTower[i-1]==3  && Argent == 0){
			        	drawTowerBlue2(Xtower[i],Ytower[i]);
			        }
			        if(ColorTower[i-1]==4  && Argent == 0){
			        	drawTowerGreen2(Xtower[i],Ytower[i]);
			        }
		    	   // if (Argent == 1) printf("vous n'avez pas assez d'argent pour construire de tour");



		 /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();


        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }

        //MoveMonster();





        // if (curx==x_in && cury==y_in)
        // {
        // 	if (dest1==1){
	       //  	route_x = x_1 - curx;
	       //  	route_y = y_1 - cury;
	       //  	if(varx<=route_x-px){
	       //  		varx += route_x/84*speed;
	       //  	}
	       //  	if (varx>= route_x){
	       //  		curx= x_1;
	       //  		cury= y_1;
	       //  		printf("arrivé en 1 depuis 0 \n");;
	       //  	}
        // 	}

	       //  if (dest1==2){
	       //  	route_x = x_2 - curx;
	       //  	route_y = y_2 - cury;
	       //  	if(varx<=route_x-px && vary<=route_y-px){
	       //  		varx += route_x/100;
	       //  		vary += route_y/100;
	       //  	}
	       //  	if(varx>=route_x-0.001 && vary>=route_y-0.001){
	       //  		curx= x_2;
	       //  		cury= y_2;
	       //  		printf("arrivé en 2 depuis 0 \n");
	       //  	}
	       //  }
	       //  if (dest1==4){
	       //  	route_x = x_4 - curx;
	       //  	route_y = y_4 - cury;
	       //  	if(varx<=route_x-px && vary>=route_y-px){
	       //  		varx += route_x/126*speed;
	       //  		vary += route_y/126;
	       //  	}
	       //  	if(varx>=route_x-0.001 && vary>=route_y-0.001){
	       //  		curx= x_4;
	       //  		cury= y_4;
	       //  		printf("arrivé en 4 depuis 0 \n");
	       //  	}
	       //  }
        // }
         
        // if (curx==x_2 && cury==y_2){
        	
        // 	if (dest2 == 1){
        // 		route_x = x_1 - curx;
        // 		route_y = y_1 - cury;
        // 		if(varx2<=route_x && vary2>=route_y+px){
	       //  		varx += route_x/45*speed;
	       //  		vary2 += route_y/45*speed;
	       //  	}
	       //  	if(varx2==route_x && vary2==route_y){
	       //  		curx= x_1;
	       //  		cury= y_1;
	       //  		printf("arrivé en 1 depuis 2 \n");
	       //  	}
	       //  	varx=varx2+(x_2-x_in);
	       //  	vary=vary2+(y_2-y_in);
        // 	}
        // 	if (dest2 == 3 ){
        // 		route_x = x_out - curx;
        // 		route_y = y_out - cury;
        // 		if(varx2<=route_x-px && vary2>=route_y){
	       //  		varx2 += route_x/100*speed;
	       //  		vary2 += route_y/100*speed;
	       //  	}
	       //  	if(varx2>=route_x-px && vary2<=route_y+px){
	       //  		curx= x_out;
	       //  		cury= y_out;
	       //  		printf("arrivé en 3 depuis 2 \n");
	       //  	}
	       //  	varx=varx2+(x_2-x_in);
	       //  	vary=vary2+(y_2-y_in);
        // 	}
        	
        // }
        
        // if (curx==x_4 && cury==y_4){
        // 	if (dest2 == 3){
        // 		route_x = x_out - curx;
        // 		route_y = y_out - cury;
        // 		if(varx2<=route_x && vary2<=route_y-px){
	       //  		varx2 += route_x/126*speed;
	       //  		vary2 += route_y/126*speed;
	       //  	}
	       //  	if(varx2>=route_x && vary2>=route_y-px){
	       //  		curx= x_out;
	       //  		cury= y_out;
	       //  		printf("arrivé en 3 depuis 4 \n");
	       //  	}
	       //  	varx=varx2+(x_1-x_in);
	       //  	vary=vary2-4;

        // 	}	        	
        // }
        // if (dest3 == 3){
        // 	if(dest2==2 && (curx==x_2 && cury==y_2)){
        // 		route_x = x_out - curx;
        // 		route_y = y_out - cury;
        // 		if(varx2<=route_x-px && vary2>=route_y-px){
	       //  		varx2 += route_x/100*speed;
	       //  		vary2 += route_y/100*speed;
	       //  	}
	       //  	if(varx2>=route_x-px && vary2>=route_y-px){
	       //  		curx= x_out;
	       //  		cury= y_out;
	       //  		printf("arrivé en 3 depuis 2(et1)\n");
	       //  	}
	       //  	varx=varx2+(x_2-x_in);
	       //  	vary=vary2;
        // 	}
        // 	if(dest2==1 && (curx==x_1 && cury==y_1)){
        // 		route_x = x_out - curx;
        // 		route_y = y_out - cury;
        // 		if(varx2<=route_x-px && vary2<=route_y){
	       //  		varx2 += route_x/84*speed;
	       //  		vary2 += route_y/84*speed;
	       //  	}
	       //  	if(varx2>=route_x && vary2==route_y-2){
	       //  		curx= x_out;
	       //  		cury= y_out;
	       //  		printf("arrivé en 3 depuis 1(et2) \n");
	       //  	}
	       //  	varx=varx2+(x_2-x_in);
	       //  	vary=vary2+(y_2-y_in);
        // 	}
        // 	if(dest2==4 && (curx==x_4 && cury==y_4)){
        // 		route_x = x_out - curx;
        // 		route_y = y_out - cury;
        // 		if(varx2<=route_x-px && vary2<=route_y){
	       //  		varx2 += route_x/84*speed;
	       //  		vary2 += route_y/84*speed;
	       //  	}
	       //  	if(varx2>=route_x && vary2==route_y-2){
	       //  		curx= x_out;
	       //  		cury= y_out;
	       //  		printf("arrivé en 3 depuis 4(et1) \n");
	       //  	}
	       //  	varx=varx2+(x_2-x_in);
	       //  	vary=vary2+(y_2-y_in);
        // 	}
        // }
        

    }


    


    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, &texture_id);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;

}



