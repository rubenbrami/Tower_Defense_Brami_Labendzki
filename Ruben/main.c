#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "verify.c"
#include "verifyMap.c"
#include "createMap.c"
#include <math.h>

int main(int argc, char const *argv[])
{
	ITD itd;
	scanITD("map1.itd",&itd);
	printf("dejaScanne = %d\n",itd.dejaScanne );
	for(int i=0; i<itd.nombreNoeuds; i++){
		printf("- noeud %d = %d --- son type est %d\n", i+1,itd.indices[i],itd.types[i]);
	}
	// scanMap(itd.nameImage,&itd);

	time_t t = time(NULL);
	printf("\n%ld",t);
	//printf("%d\n",itd.pixelsConstructibles[1][3]);
	// for(int i=0; i<800;i++){
	// 	for(int j=0; j<600; j++){
	// 		printf("au pixel [%d][%d] = > [%d]\n",i,j,itd.pixelsConstructibles[i][j]);
	// 	}
	// }
	int i= 0;
	if(i)
		printf("c\n");
	creerCarte(scanMap(itd.nameImage,&itd),itd.nameImage,&itd,800,600);
	printf("dejaScanne = %d\n",itd.dejaScanne );

	// int a = 300;
	// int b = 300;
	// float rapport  = (float)a/b;
	// printf("rapport = %f\n", rapport);
	// printf("epaisseur = %d\n",(int)(30*sqrt(1+rapport*rapport)+1));
	// printf("%d",(34/2) - (34+1)%2);
	// char * chaine = malloc(5*sizeof(char));
	// chaine = strcat(chaine,"dd");
	// sprintf(chaine,"%d",43);
	// strcat(chaine," ");
	// char * nb1 = malloc(2*sizeof(char));
	// sprintf(nb1,"%d",22);
	// strcat(chaine,nb1);
	// printf("chaine = %s",chaine);
	return 0;
}
