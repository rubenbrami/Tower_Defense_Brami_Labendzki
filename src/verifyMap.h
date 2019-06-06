#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool estDansLeCercle30Px(int largeur, int hauteur, int X_Cercle, int Y_Cercle);
bool estDansLeRect(int largeur, int hauteur, int X_Cercle, int Y_Cercle, int dimX_Gauche, int dimX_Droite, int dimY_Haut, int dimY_Bas);
bool scanMap(char * filename, ITD* itd);