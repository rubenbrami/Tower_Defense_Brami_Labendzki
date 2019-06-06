#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAILLE_MAX 1000

int* allouerTabInt(int taille);
bool appartientAuTabInt(int element, int*tab, int longueurTab);
bool contientDoubleInt(int*tab, int longueurTab);
int longueurChaine(char *chaine);
bool stringInInt(char *chaine, int *nombre);
bool contientCaractere(char *chaine, char carac);
char* retirerDernierCaractereTabChar(char * chaine);

typedef struct{
	char nameImage[TAILLE_MAX];//peut-être modifier ceci notamment avec TAILLE_MAX.
	int couleurChemin[3];
	int couleurNoeud[3];
	int couleurConstruct[3];
	int couleurIn[3];
	int couleurOut[3];
	int nombreNoeuds;
	int *indices;//tableau qui stocke les indices de chaque noeud.
	int *nombreNoeudsVoisins;//tableau qui stocke le nombre de voisin pour chaque noeud.
	int ** coordonnees;
	int *types;//tableau qui stocke les types de chaque noeud.
	int ** voisins;//tableau qui stocke les voisins en fonction du noeud. Dans la première dimension, les indices du noeud, dans la deuxième les voisins.
	int ** pixelsConstructibles;
	bool dejaScanne;
}ITD;

void reinitialiserITD(ITD* itd);
bool scanITD(char * filename, ITD* itd);