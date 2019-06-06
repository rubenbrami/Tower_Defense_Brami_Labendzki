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

int traductionX_Inverse(float x){
    return((int)75*x+400);
}

int traductionY_Inverse(float y){
    return((int)-75*y+300);    
}





// void drawYellow(i, int nombre){
//     for(int i=0; i<nombre){
//         drawTowerYellow2(Xtower[i-nombre],Ytower[i-nombre]);
//     }
// }

int i=0;
int j=0;
bool peutCommencer = false;

static float px = 0.013333;
static int x_in ,y_in, x_end, y_end ;
static int x_out, y_out;
static float x_1, y_1;
static float x_2, y_2;
static float x_4, y_4;

int d_x=0;
int d_y=0;

int d_p=0;
int deltaE=0;
int deltaNE=0;

int indiceVoisin = -1;

float XtowerJaune[100];
float YtowerJaune[100];

float TowerJaune[100][2];
float TowerRouge[100][2];
float TowerBleu[100][2];
float TowerVert[100][2];

float Xt[100];
float Yt[100];
//int ColorTower[100];
int ColorTower =0;
int Argent = 2;



float PV = 30;
float radiusYellow2 = 4;
float radiusBleu2 = 10;
float radiusRed2 = 6;
float radiusGreen2 = 4;

int AtakJ = 1;
int AtakR = 10;
int AtakB = 5;
int AtakV = 8;

// float radiusJaune = 1;
// float radiusBleu = 5;
// float radiusRouge = 3;
// float radiusVert = 2;


// static float varx = 0.;
// static float vary = 0.;
// static float varx2 = 0.;
// static float vary2 = 0.;
// static float speed = 1;

// static float curx = -4;
// static float cury = 1;

// static float route_x = 0;
// static float route_y = 0;

// int current =0;

// static int dest1 = 1;
// static int dest2 = 2;
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



float norme(float x1, float y1, float x2, float y2){
    return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}
// int a=0;
// int b=0;
// int c=1;
// int d=1;    
bool estDansRayon(float x1, float y1, float x2, float y2,float rayon){
    if (norme(x1,y1,x2,y2)<=rayon) return true;
    return false;
}

bool estDansZoneConstructible(int X, int Y, int** zoneConstructible){
    return(zoneConstructible[X][Y]==1);
}
bool zoneConstructibleEstDansCercle(int X, int Y, int** zoneConstructible, int rayon){
    for(int i = -rayon; i<rayon+1; i++){
        for(int j= -rayon; j<rayon+1; j++){
            if(estDansRayon(X,Y,X+i,Y+i,rayon))
                if(!estDansZoneConstructible(X+i,Y+j,zoneConstructible))
                    return false;
        }
    }
    return true;
}

int main(int argc, char** argv) 
{	printf("Bonjour");

	//printf("voici la distance (norme) entre les points (%d;%d) et (%d;%d)\n  N= %f",a,b,c,d,norme(a,b,c,d));

	//printf("voici la distance (norme) entre les points (%d;%d) et (%d;%d)\n  N= %f",a,b,c,d,norme(a,b,c,d));

    ITD itd;
    scanITD("data/map1.itd",&itd);
    for(int i=0; i<itd.nombreNoeuds; i++){
        printf("- noeud %d = %d --- son type est %d\n", i+1,itd.indices[i],itd.types[i]);
    }
    int *tabNoeudsDejaVerifies = malloc(itd.nombreNoeuds*sizeof(int));// = {-1};//Toutes les cases du tableau sont initialisées à -1.
    for(int i=0; i<itd.nombreNoeuds; i++){
        tabNoeudsDejaVerifies[i]=-1;
    }
    //printf("%d\n",itd.pixelsConstructibles[1][3]);
    // for(int i=0; i<800;i++){
    //  for(int j=0; j<600; j++){
    //      printf("au pixel [%d][%d] = > [%d]\n",i,j,itd.pixelsConstructibles[i][j]);
    //  }
    // }
    // creerCarte(scanMap(itd.nameImage,&itd),itd.nameImage,&itd,800,600);
	bool map = scanMap(itd.nameImage,&itd);
    printf("map = %d\n",map);
    printf("%s\n",itd.nameImage);
    creerCarte(false,"image.ppm",&itd,800,600);
    // printf("\n%d\n",estDansZoneConstructible(23,232,itd.pixelsConstructibles));
    // printf("%d",itd.pixelsConstructibles[23][232]);
	int money = 50;
	int r = 0;
    int v = 0;
    int b = 0;
    int ja = 0;

    int i=0;
	int k =0;

	x_in=traductionX(100.0);
	y_in=traductionY(300.0);
	x_out=traductionX(700.0);
	y_out=traductionY(300.0);
	x_1=traductionX(400.0);
	y_1=traductionY(300.0);
	x_2=traductionX(400.0);
	y_2=traductionY(150.0);
	x_4=traductionX(400);
	y_4=traductionY(600);



	// Xtower[i]=traductionX(Xtower[i]);
	// Ytower[i]=traductionX(Ytower[i]);

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
        


        if (PV > 0){
            glPushMatrix();
            glTranslatef(traductionX(x_in),traductionY(y_in),0);
            glScalef(0.2,0.2,1);
            drawMonster2();
        glPopMatrix();
        // glPushMatrix();
        //     glTranslatef(x_in+varx, y_in+vary,0);
        //     glScalef(0.2,0.2,1);
        //     drawMonster2();
        // glPopMatrix();
        //printf("le monstre a encore %f point(s) de vie\n", PV);
        
        // if(ColorTower[i-1]==1)if (estDansRayon(x_in+varx, y_in+vary,Xtower[i],Ytower[i],0.2*radiusYellow2)) PV=PV-0.01*AtakJ;
        // if(ColorTower[i-1]==2)if (estDansRayon(x_in+varx, y_in+vary,Xtower[i],Ytower[i],0.2*radiusRed2)) PV=PV-0.01*AtakR;
        // if(ColorTower[i-1]==3)if (estDansRayon(x_in+varx, y_in+vary,Xtower[i],Ytower[i],0.2*radiusBleu2)) PV=PV-0.01*AtakB;
        // if(ColorTower[i-1]==4)if (estDansRayon(x_in+varx, y_in+vary,Xtower[i],Ytower[i],0.2*radiusGreen2)) PV=PV-0.01*AtakV;
        
        // if (estDansRayon(x_in+varx, y_in+vary,TowerJaune[ja][0],TowerJaune[ja][1],0.2*radiusYellow2)) PV=PV-0.01*AtakJ;
        // if (estDansRayon(x_in+varx, y_in+vary,TowerRouge[r][0],TowerRouge[r][1],0.2*radiusRed2)) PV=PV-0.01*AtakR;
        // if (estDansRayon(x_in+varx, y_in+vary,TowerBleu[b][0],TowerBleu[b][1],0.2*radiusBleu2)) PV=PV-0.01*AtakB;
        // if (estDansRayon(x_in+varx, y_in+vary,TowerVert[v][0],TowerVert[v][1],0.2*radiusGreen2)) PV=PV-0.01*AtakV;

        }
        // if (PV==0) printf("Dans la map, terrible map, le monstre est mort ce soir  OOOhimbowé");
        

        drawLegende();
        
        
        /* Boucle traitant les evenements */
        SDL_Event e;

        while(SDL_PollEvent(&e)) 
        {
            // printf("PV = %f\n",PV);
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
                    printf("\nX = %d\n",traductionX_Inverse((-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio));  
                    printf("Y = %d\n",traductionY_Inverse(-(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.));
                    printf("\n%d\n",estDansZoneConstructible(traductionX_Inverse((-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio), traductionY_Inverse(-(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.), itd.pixelsConstructibles));
                    if(zoneConstructibleEstDansCercle(traductionX_Inverse((-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio), traductionY_Inverse(-(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.), itd.pixelsConstructibles,13)){
                   // if(estDansLeCercle30Px()){
                        if(ColorTower==1){
                            TowerJaune[ja][0]=(-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio;
                            TowerJaune[ja][1]= -(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.;
                            ja++;
                        }
                        if(ColorTower==2){
                            TowerRouge[r][0]=(-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio;
                            TowerRouge[r][1]= -(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.;
                            r++;
                        }
                        if(ColorTower==3){
                            TowerBleu[b][0]=(-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio;
                            TowerBleu[b][1]= -(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.;
                            b++;
                        }
                        if(ColorTower==4){
                            TowerVert[v][0]=(-1 + 2. * e.button.x / (float) surface->w) * GL_VIEW_SIZE / 2. * aspectRatio;
                            TowerVert[v][1]= -(-1 + 2. * e.button.y / (float) surface->h) * GL_VIEW_SIZE / 2.;
                            v++;
                        } 
                    }
                    //}
                    //printf("clic en (%d, %d) ,,,,,i= %d \n", e.button.x, e.button.y,i);
                    // printf(" Xtower[%d] = %f \n", i,Xtower[i] );
                    // printf(" Ytower[%d] = %f \n", i,Ytower[i] );
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
                            //ja++;
                            //ColorTower[i] = 1;
                            ColorTower = 1; 
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
							//ColorTower[i] = 2; 
                            ColorTower = 2;
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
							//ColorTower[i] = 4;
                            ColorTower = 4;
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
                            //ColorTower[i] = 3;
                            ColorTower = 3;
							goto finally;
				
				finally:
					//printf(" appuye sur %c\n ", e.key.keysym.sym);	
					//printf(" ColorTower[%d] = %d \n",i,ColorTower[i]);
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
		        
			        // if(ColorTower[i]==0){
			        // 	drawLegende();
			        // }
			        // if(ColorTower[i-1]==1 && Argent == 0){
                   // if(ColorTower==1 && Argent == 0){
                        for(int j=0; j<ja; j++){
                            drawTowerYellow2(TowerJaune[j][0],TowerJaune[j][1]);
                            if (estDansRayon(traductionX(x_in), traductionY(y_in),TowerJaune[j][0],TowerJaune[j][1],0.2*radiusYellow2)){
                                PV=PV-0.01*AtakJ;
                                
                            }
       
                        }
                        // drawTowerYellow2(Xtower[i],Ytower[i]);
                        // for(int j=0; j<2; j++)
                        // drawTowerYellow2(Xtower[j]-100,Ytower[j]+100);

			        	// drawTowerYellow2(Xtower[i],Ytower[i]);
			        	// drawTowerYellow2(Xtower[i-1],Ytower[i-1]);
			        	// drawTowerYellow2(Xtower[i-2],Ytower[i-2]);
			        	// drawTowerYellow2(Xtower[i-3],Ytower[i-3]);
			      //  }
			        // if(ColorTower[i-1]==2  && Argent == 0){
                  //  if(ColorTower==2 && Argent == 0){
			        	//drawTowerRed2(Xtower[i],Ytower[i]);
			            for(int j=0; j<r; j++){
                            if (estDansRayon(traductionX(x_in), traductionY(y_in),TowerRouge[j][0],TowerRouge[j][1],0.2*radiusRed2)) PV=PV-0.01*AtakR;
                            drawTowerRed2(TowerRouge[j][0],TowerRouge[j][1]);
                        }     
                  //  }
			        //if(ColorTower[i-1]==3  && Argent == 0){
                 //   if(ColorTower==3 && Argent == 0){
			        	//drawTowerBlue2(Xtower[i],Ytower[i]);
			            for(int j=0; j<b; j++){
                            if (estDansRayon(traductionX(x_in), traductionY(y_in),TowerBleu[j][0],TowerBleu[j][1],0.2*radiusBleu2)){
                                PV=PV-0.01*AtakB;
                            }
                            drawTowerBlue2(TowerBleu[j][0],TowerBleu[j][1]);
                        }
               //     }
			        //if(ColorTower[i-1]==4  && Argent == 0){
                //    if(ColorTower==4 && Argent == 0){
			        	//drawTowerGreen2(Xtower[i],Ytower[i]);
			            for(int j=0; j<v; j++){
                             if (estDansRayon(traductionX(x_in), traductionY(y_in),TowerVert[j][0],TowerVert[j][1],0.2*radiusGreen2)) PV=PV-0.01*AtakV;
                            drawTowerGreen2(TowerVert[j][0],TowerVert[j][1]);
                        }
                    //}
		    	   // if (Argent == 1) printf("vous n'avez pas assez d'argent pour construire de tour");
       // printf("x_in = %f\n",x_in );
        
        // printf("x_in = %d\n",x_in);
        // printf("y_in = %d\n",y_in);
        // printf("x_out = %d\n",x_out);
        // printf("y_out = %d\n",y_out);

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
       
        //for(int i=0; i<itd.nombreNoeuds; i++){
            if(!appartientAuTabInt(itd.indices[i],tabNoeudsDejaVerifies,itd.nombreNoeuds)){
                  // printf("eee");
                   if(!peutCommencer)
            for(int k=0; k<itd.nombreNoeuds; k++){
                printf(" pc %d\n",peutCommencer );
                if(itd.types[itd.indices[k]] == 1){
                    x_in=itd.coordonnees[itd.indices[k]][0];
                    y_in=itd.coordonnees[itd.indices[k]][1];
                    tabNoeudsDejaVerifies[i]=itd.indices[k];
                    peutCommencer = true;
                }
                if(itd.types[itd.indices[k]] == 2){
                    x_end=itd.coordonnees[itd.indices[k]][0];
                    y_end=itd.coordonnees[itd.indices[k]][1];
                    tabNoeudsDejaVerifies[i]=itd.indices[k];
                    peutCommencer = true;
                }

            }
        }
                   // tabNoeudsDejaVerifies[i]=itd->indices[i];
            

            for(int j=0; j<itd.nombreNoeudsVoisins[i]; j++){
                if(!appartientAuTabInt(itd.voisins[i][j],tabNoeudsDejaVerifies,itd.nombreNoeuds)){
                    //tabNoeudsDejaVerifies[]=itd.voisins[i][j];
                    // if(itd->coordonnees[itd->indices[i]][0]  <  itd->coordonnees[itd->voisins[i][j]][0]){

                    //     X_0_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX/*-1*/ ;//on rajoute -1 pour que le premier passage du while le ramène à sa bonne valeur.
                    //     Y_0_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

                    //     X_1_Cercle = itd->coordonnees[itd->voisins[i][j]][0] + decalageX;//coordonnées des voisins du noeud (X_0, Y_0).
                    //     Y_1_Cercle = itd->coordonnees[itd->voisins[i][j]][1] + decalageY;
                    // }
                    // else{

                    //     X_1_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX;
                    //     Y_1_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

                    //     X_0_Cercle = itd->coordonnees[itd->voisins[i][j]][0] + decalageX/*-1*/;//coordonnées des voisins du noeud (X_0, Y_0). //on rajoute -1 pour que le premier passage du while le ramène à sa bonne valeur.
                    //     Y_0_Cercle = itd->coordonnees[itd->voisins[i][j]][1] + decalageY;
                    // }
                    x_out=itd.coordonnees[itd.voisins[i][j]][0];
                    y_out=itd.coordonnees[itd.voisins[i][j]][1];
                    
                    indiceVoisin = itd.voisins[i][j];
                    // printf("ib = %d\n",indiceVoisin);
                    break;
                }
            }

                    if(x_in <= x_out){
                        d_x = x_out - x_in;
                        d_y = y_in - y_out;

                        if(d_x >=0){
                            if(d_x >= abs(d_y)){
                                d_p = 2 * d_y - d_x;
                                deltaE = 2 * d_y;
                                deltaNE = 2 * (d_y - d_x);   
                                
                                if(x_in < x_out){
                                    if(d_p <= 0){//cela signifie que l'on va choisir le pixel Est.
                                        d_p += deltaE;
                                        x_in++;
                                        

                                        
                                    }
                                    else{//on choisit le pixel Nord-Est.
                                        d_p += deltaNE;
                                        x_in++;
                                        y_in--;//on remonte.
                                    }
                                }
                            }
                            else{
                                d_p = 2 * d_x - d_y;
                                deltaE = 2 * d_x;
                                deltaNE = 2 * (d_x - d_y);
                            
                                if(y_in > y_out){
                                    if(d_p<=0){
                                        d_p += deltaE;
                                        y_in--;
                                    }
                                    else{
                                        d_p += deltaNE;
                                        x_in++;
                                        y_in--;
                                    }
                                }
                            }
                        }
                        else{
                            if(d_x >= abs(d_y)){
                                d_p = 2 * (-d_y) - d_x;
                                deltaE = 2 * (-d_y);
                                deltaNE = 2 * (-d_y - d_x);
                            
                                if(x_in < x_out){
                                    // interrupteur = false;
                                    if(d_p <= 0){//cela signifie que l'on va choisir le pixel Est.
                                        d_p += deltaE;
                                        x_in++;
                                    }
                                    else{//on choisit le pixel Nord-Est.
                                        d_p += deltaNE;
                                        x_in++;
                                        y_in++;//on remonte.
                                    }
                                }
                            }
                            else{
                                d_p = 2 * d_x + d_y;
                                deltaE = 2 * d_x;
                                deltaNE = 2 * (d_x + d_y);
                            
                                if(y_in < y_out){
                                    if(d_p <= 0){//cela signifie que l'on va choisir le pixel Est.
                                        d_p += deltaE;
                                        y_in++;
                                }
                                    else{//on choisit le pixel Nord-Est.
                                        d_p += deltaNE;
                                        x_in++;
                                        y_in++;//on remonte.
                                    }
                                }
                            }

                        }


                    }

                }
            //}
        i++;
        if(i==itd.nombreNoeuds-1)
            i=0;
        if(x_in == x_out){
            tabNoeudsDejaVerifies[i]=indiceVoisin;
            i=0;
            printf("HELLLOOO !!");
            
        }
        // if(PV <0 && x_in < x_end){
        //     printf("VOUS AVEZ GAGNÉ !!!! \n");
        // }

        // if (curx==x_in && cury==y_in){
        // // {printf("za\n");
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
        

    


    


    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, &texture_id);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();
    
    return EXIT_SUCCESS;

}




