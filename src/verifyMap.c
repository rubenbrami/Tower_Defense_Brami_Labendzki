// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <stdbool.h>
// #define I -4
// #define J 16

#include "verifyMap.h"

bool estDansLeCercle30Px(int largeur, int hauteur, int X_Cercle, int Y_Cercle){
	return((largeur >= X_Cercle-4 && largeur <= X_Cercle+3 && (hauteur==Y_Cercle-14 || hauteur==Y_Cercle+15))   
		|| (largeur >= X_Cercle-7 && largeur <= X_Cercle+6 && (hauteur==Y_Cercle-13 || hauteur==Y_Cercle+14))
		|| (largeur >= X_Cercle-8 && largeur <= X_Cercle+7 && (hauteur==Y_Cercle-12 || hauteur==Y_Cercle+13))
		|| (largeur >= X_Cercle-10 && largeur <= X_Cercle+9 && (hauteur==Y_Cercle-11 || hauteur==Y_Cercle+12))
	  	|| (largeur >= X_Cercle-11 && largeur <= X_Cercle+10 && (hauteur==Y_Cercle-10 || hauteur==Y_Cercle+11))
	  	|| (largeur >= X_Cercle-12 && largeur <= X_Cercle+11 && (hauteur==Y_Cercle-9 || hauteur==Y_Cercle+10))
	 	|| (largeur >= X_Cercle-12 && largeur <= X_Cercle+11 && (hauteur==Y_Cercle-8 || hauteur==Y_Cercle+9))
	 	|| (largeur >= X_Cercle-13 && largeur <= X_Cercle+12 && (hauteur==Y_Cercle-7 || hauteur==Y_Cercle+8))
	 	|| (largeur >= X_Cercle-14 && largeur <= X_Cercle+13 && (hauteur==Y_Cercle-6 || hauteur==Y_Cercle+7))
	 	|| (largeur >= X_Cercle-14 && largeur <= X_Cercle+13 && (hauteur==Y_Cercle-5 || hauteur==Y_Cercle+6))
	 	|| (largeur >= X_Cercle-14 && largeur <= X_Cercle+13 && (hauteur==Y_Cercle-4 || hauteur==Y_Cercle+5))
	  	|| (largeur >= X_Cercle-15 && largeur <= X_Cercle+14 && (hauteur==Y_Cercle-3 || hauteur==Y_Cercle+4))
	 	|| (largeur >= X_Cercle-15 && largeur <= X_Cercle+14 && (hauteur==Y_Cercle-2 || hauteur==Y_Cercle+3))
	  	|| (largeur >= X_Cercle-15 && largeur <= X_Cercle+14 && (hauteur==Y_Cercle-1 || hauteur==Y_Cercle+2))
	  	|| (largeur >= X_Cercle-15 && largeur <= X_Cercle+14 && (hauteur==Y_Cercle-0 || hauteur==Y_Cercle+1))
	);
}

bool estDansLeRect(int largeur, int hauteur, int X_Cercle, int Y_Cercle, int dimX_Gauche, int dimX_Droite, int dimY_Haut, int dimY_Bas){
	return(largeur >= X_Cercle-dimX_Gauche && largeur <= X_Cercle+dimX_Droite && hauteur >= Y_Cercle-dimY_Haut && hauteur <= Y_Cercle+dimY_Bas);
}

bool scanMap(char * filename, ITD* itd){
	//if(!(itd->dejaScanne)){
		FILE *myFile = NULL;
		char caractere ='.';
		char caracterePrecedent = '.';
		char chaine[12];
		char * morceau;
		int dimX = 0;
		int dimY = 0;

		char emplacement[10+longueurChaine(filename)];
	    strcat(emplacement,"images/");
	    strcat(emplacement,filename);

		// ouvre le fichier
	  	if (!(myFile = fopen(emplacement, "rt")))
	    {
	      printf("verifyMap : error opening file %s.\n",emplacement);
	      return EXIT_FAILURE;
	    }

	    // char nomFichier = malloc((longueurChaine(filename)+longueurChaine(emplacement))*sizeof(char));
	    // for(int i=0; i<10; i++){
	    // 	nomFichier[i]=emplacement[i];
	    // }

	    for(int i=0; i<3; i++){
	    	fgets(chaine, 12, myFile);
	    	if(i==1){
	    		morceau = strtok(chaine, " ");
	    		dimX = atoi(morceau);
	    		morceau = strtok(NULL, " ");
	    		dimY = atoi(morceau);
	    	}
	    }
	    // printf("coucou");

	    /*
	    	On va créer un tableau à deux dimensions qui indiquera quelles pixels sont constructibles.
	    */

	   	itd->pixelsConstructibles = malloc(dimX*sizeof(int*));
		if(itd->pixelsConstructibles == NULL){
			printf("ERREUR\n");
			exit(EXIT_FAILURE);
		}
	   	for(int i = 0; i<dimX; i++){
	   		itd->pixelsConstructibles[i]=allouerTabInt(dimY);
	   	}

	    printf("\n");
		printf("X = %d\n",dimX);
		printf("Y = %d\n",dimY);
		printf("\n");

	// printf("coucou");

		int X_In = 0;
		int Y_In = 0;

		int X_Out = 0;
		int Y_Out = 0;

		for(int i=0; i<itd->nombreNoeuds; i++){
			printf("- indice = %d\n- type = %d\n   coordonnee x = %d\n   coordonnee y = %d\n\n",itd->indices[i],itd->types[itd->indices[i]],itd->coordonnees[itd->indices[i]][0],itd->coordonnees[itd->indices[i]][1]);
			if(itd->types[itd->indices[i]]==1){
				X_In = itd->coordonnees[itd->indices[i]][0];
				Y_In = itd->coordonnees[itd->indices[i]][1];
			}
			else if(itd->types[itd->indices[i]]==2){
				X_Out = itd->coordonnees[itd->indices[i]][0];
				Y_Out = itd->coordonnees[itd->indices[i]][1];
			}
		}

		strcmp(chaine,"");
		for(int i=0; i<strlen(chaine);i++){/*Sans savoir pourquoi, la chaine chaine "déteignait" sur les suivantes..*/
			chaine[i]=0;
		}

		/*
			Important de bien penser à ce qui suit. Les coordonnées ne vont pas avoir le même 
			signification selon que les dimensions de la fenêtre soient paires ou impaires

		*/
		int decalageX = 1;
		int decalageY = 0;

		if(dimY%2==1)
			decalageY = 1;

		int c = 0;
		int indicePixel = 0;

		bool finiR = false;
		bool finiG = false;
		bool finiB = false;

		bool finiUltime = false;

		int longCoulR = 0;
		int longCoulG = 0;
		int longCoulB = 0;

		int estOkR = 0;
		int estOkG = 0;
		int estOkB = 0;

		char * StringR = malloc(3*sizeof(char));
		char * StringG = malloc(3*sizeof(char));
		char * StringB = malloc(3*sizeof(char));

		int indiceStringR = 0;
		int indiceStringG = 0;
		int indiceStringB = 0;

		int R=0;
		int G=0;
		int B=0;

		int R_ToCompare = 0;
		int G_ToCompare = 0;
		int B_ToCompare = 0;

		// Coordonnées des cercles, pour vérifier qu'ils sont bien conformes à l'ITD.
		int X_Cercle;
		int Y_Cercle;


		// Coordonnées des cercles, pour vérifier les chemins qui les relient.
		int X_0_Cercle;
		int Y_0_Cercle;

		int X_1_Cercle;
		int Y_1_Cercle;

		int X_0_Cercle_Centre;
		int Y_0_Cercle_Centre;
		int X_1_Cercle_Centre;
		int Y_1_Cercle_Centre;

		int decR = 1000;
		int decG = 1000;
		int decB = 1000;
		int parite = 0;
		//int cc = 0;

		int hauteur = 1;
		int largeur = 0;

		/*
			Tableau qui va stocker les noeuds déja analysés.
			Comme ça on ne se repète pas !
		*/
		int tabNoeudsDejaVerifies[itd->nombreNoeuds];// = {-1};//Toutes les cases du tableau sont initialisées à -1.
		for(int i=0; i<itd->nombreNoeuds; i++){
			tabNoeudsDejaVerifies[i]=-1;
		}
		int nbElementsTab = 0; 

		int d_X = 0;
		int d_Y = 0;

		int d_P = 0;
		int deltaE = 0;
		int deltaNE = 0;

		float rapport_d_X_d_Y = 0;

		/*
			Ce prochain booléen va être très utile car il va permettre d'indiquer au programme
			que le pixel n'est ni un élément d'un noeud, ni un élément du chemin.
		*/
		bool estConstructible = true;
		bool estCercle = false;
		int epaisseurChemin = 0;

		do{
			// caracterePrecedent = caractere;
			caractere = fgetc(myFile);
	    	
	 		if(caractere == ' '){
	    		c++;
	    		indicePixel++;
		   		if(indicePixel==3)
	    			indicePixel=0;
	    			
	 			if(indicePixel==0)
	 				largeur++;
	 			if (largeur >= dimX+1){
	 				hauteur ++;
	 				largeur = 1;
	 			}
	 		}

	 		/*
	 			À chaque bout de ligne, la largeur recommence à 1 et la hauteur s'incrémente de 1.
	 		*/
	 		
	 		for(int i=0; i<itd->nombreNoeuds; i++){
		 		
		 		if(itd->types[itd->indices[i]] == 3 || itd->types[itd->indices[i]] == 4){
		 			R_ToCompare = itd->couleurNoeud[0];
		 			G_ToCompare = itd->couleurNoeud[1];
		 			B_ToCompare = itd->couleurNoeud[2];
		 		}
		 		else if(itd->types[itd->indices[i]] == 1){
		 			R_ToCompare = itd->couleurIn[0];
		 			G_ToCompare = itd->couleurIn[1];
		 			B_ToCompare = itd->couleurIn[2];
		 		}
		 		else if(itd->types[itd->indices[i]] == 2){
		 			R_ToCompare = itd->couleurOut[0];
		 			G_ToCompare = itd->couleurOut[1];
		 			B_ToCompare = itd->couleurOut[2];
		 		}

		 		X_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX;
				Y_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

				/*
		 			Cette grosse condition correspond à la vérification des cercles ayant un diamètre de 30 pixels.
		 		*/
		 		
		 		if(finiUltime && estDansLeCercle30Px(largeur,hauteur,X_Cercle,Y_Cercle)){
		 			// 	printf("\nR = %d G = %d B = %d\n",R,G,B );
		 			// 	printf("largeur = %d\n",largeur);
					// printf("hauteur = %d\n",hauteur);
					estConstructible = false;
	 				estCercle = true;
	 				
	 				if(R != R_ToCompare || G != G_ToCompare || B != B_ToCompare){
	 					printf("La carte ne correspond pas à l'ITD... Les cercles sont : \n - soit de la mauvaise couleur pour leur type. \n - soit plus petits que 30 px de diamètre. \n - soit non conformes (floutés par ex).\n");
	 					free(itd->pixelsConstructibles);
	 					return false;
	 				}
	 			}

	 			/*
	 				On va s'attarder sur les voisins des noeuds afins de pouvoir 
	 				vérifier si une ligne les relie.
	 			*/
	 			if(finiUltime && !appartientAuTabInt(itd->indices[i],tabNoeudsDejaVerifies,itd->nombreNoeuds)){
	 				tabNoeudsDejaVerifies[i]=itd->indices[i];
	 				
		 		// for(int u = 0; u<itd->nombreNoeuds;u++){
		 		// 	if(u==0)printf("tab[");
		 		// 	printf("%d, ",tabNoeudsDejaVerifies[u]);
		 		// 	if(u==itd->nombreNoeuds-1)printf("]\n");
		 		// }
	 			//if(!estCercle)
	 				// nbElementsTab++;
	 				for(int j=0; j<itd->nombreNoeudsVoisins[i]; j++){
	 					if(!appartientAuTabInt(itd->voisins[i][j],tabNoeudsDejaVerifies,itd->nombreNoeuds)){
	 						if(itd->coordonnees[itd->indices[i]][0]  <  itd->coordonnees[itd->voisins[i][j]][0]){

		 						X_0_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX/*-1*/ ;//on rajoute -1 pour que le premier passage du while le ramène à sa bonne valeur.
								Y_0_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

								X_1_Cercle = itd->coordonnees[itd->voisins[i][j]][0] + decalageX;//coordonnées des voisins du noeud (X_0, Y_0).
								Y_1_Cercle = itd->coordonnees[itd->voisins[i][j]][1] + decalageY;
							}
							else{

								X_1_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX;
								Y_1_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

								X_0_Cercle = itd->coordonnees[itd->voisins[i][j]][0] + decalageX/*-1*/;//coordonnées des voisins du noeud (X_0, Y_0). //on rajoute -1 pour que le premier passage du while le ramène à sa bonne valeur.
								Y_0_Cercle = itd->coordonnees[itd->voisins[i][j]][1] + decalageY;
							}
							// printf("X_0 = %d et Y_0 = %d\n",X_0_Cercle,Y_0_Cercle);
							// printf("X_1 = %d et Y_1 = %d\n\n",X_1_Cercle,Y_1_Cercle);

							d_X = X_1_Cercle - X_0_Cercle ;
							d_Y = Y_0_Cercle - Y_1_Cercle ; //C'est dans l'autre sens car n'oublions pas que l'axe des Y va du haut vers le bas.

							X_0_Cercle_Centre = X_0_Cercle;
							Y_0_Cercle_Centre = Y_0_Cercle;
							X_1_Cercle_Centre = X_1_Cercle;
							Y_1_Cercle_Centre = Y_1_Cercle;

							// printf("d_X = %d\n",d_X);
							// printf("d_Y = %d\n\n\n",d_Y);

							if(d_Y >= 0){//pente entre 0 et pi/2
								// if((largeur<=X_0_Cercle_Centre || largeur >=X_1_Cercle_Centre) && (hauteur <= Y_0_Cercle_Centre || hauteur >= Y_1_Cercle_Centre)){
								// 	printf("COUCOU\n");
								// 	estConstructible = false;
								// }

								if(d_X >= abs(d_Y)){//pente entre 0 et pi/4
									
									d_P = 2 * d_Y - d_X;
									deltaE = 2 * d_Y;
									deltaNE = 2 * (d_Y - d_X);
									rapport_d_X_d_Y = (float) d_Y/d_X;
									epaisseurChemin = (int)(30*sqrt(1+rapport_d_X_d_Y*rapport_d_X_d_Y)+1);
									while(X_0_Cercle < X_1_Cercle){
										if(d_P <= 0){//cela signifie que l'on va choisir le pixel Est.
											d_P += deltaE;
											X_0_Cercle++;
										}
										else{//on choisit le pixel Nord-Est.
											d_P += deltaNE;
											X_0_Cercle++;
											Y_0_Cercle--;//on remonte.
										}

										if((finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle+epaisseurChemin/2 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if((finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle+epaisseurChemin/2+1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if(estDansLeRect(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre,14,0,23,23)
										   || estDansLeRect(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre,0,14,23,23)	
										  ){
										  	// printf("c  = %d\n",c);
										  	// printf("largeur = %d\n",largeur);
										  	// printf("hauteur = %d\n\n",hauteur);

											estConstructible = false;
										}
										
										if(finiUltime && largeur==X_0_Cercle && hauteur >= Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && hauteur <= Y_0_Cercle+epaisseurChemin/2-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 	
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);
											estConstructible = false;
											if(hauteur < Y_0_Cercle_Centre+14 && hauteur > Y_1_Cercle_Centre-14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle < X_1_Cercle_Centre-14){	
												if(R!=itd->couleurChemin[0] || G!=itd->couleurChemin[1] || B!=itd->couleurChemin[2]){
													printf("La carte ne correspond pas à l'ITD... Au moins au pixel (%d,%d), la couleur devrait être celle du chemin. Or elle est (R=%d, G=%d, B=%d)",largeur,hauteur,R,G,B);
													free(itd->pixelsConstructibles);
													return false;
												}
											}
										}
									}
								}
								else{//pente entre pi/4 et pi/2.
									d_P = 2 * d_X - d_Y;
									deltaE = 2 * d_X;
									deltaNE = 2 * (d_X - d_Y);
									rapport_d_X_d_Y = (float) d_X/d_Y;
									epaisseurChemin = (int)(30*sqrt(1+rapport_d_X_d_Y*rapport_d_X_d_Y)+1);

									while(Y_0_Cercle > Y_1_Cercle){
										// interrupteur = false;
										if(d_P <= 0){//cela signifie que l'on va choisir le pixel Est.
											d_P += deltaE;
											Y_0_Cercle--;
										}
										else{//on choisit le pixel Nord-Est.
											d_P += deltaNE;
											X_0_Cercle++;
											Y_0_Cercle--;//on remonte.
										}
										if((finiUltime && largeur == X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle+epaisseurChemin/2 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if((finiUltime && largeur == X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)-1 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle+epaisseurChemin/2+1 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}

										if(estDansLeRect(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre,23,23,14,0)
										   || estDansLeRect(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre,23,23,14,0)	
										  )
											estConstructible = false;

										if(finiUltime && largeur>=X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && largeur<=X_0_Cercle+epaisseurChemin/2-1 && hauteur== Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 
											//printf("C'est  blanc et ça monte !");
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);
											estConstructible = false;
											if(Y_0_Cercle < Y_0_Cercle_Centre && Y_0_Cercle > Y_1_Cercle_Centre && largeur > X_0_Cercle_Centre && largeur < X_1_Cercle_Centre){
												if(R!=itd->couleurChemin[0] || G!=itd->couleurChemin[1] || B!=itd->couleurChemin[2]){
													printf("La carte ne correspond pas à l'ITD... Au moins au pixel (%d,%d), la couleur devrait être celle du chemin. Or elle est (R=%d, G=%d, B=%d)",largeur,hauteur,R,G,B);
													free(itd->pixelsConstructibles);
													return false;
												}
											}
										}
									}
								}
							}
							else{//pente entre 0 et -pi/2.
								
								// if((largeur<=X_0_Cercle_Centre || largeur >=X_1_Cercle_Centre) && (hauteur >= Y_0_Cercle_Centre || hauteur <= Y_1_Cercle_Centre)){
								// 	printf("COUCOU\n");
								// 	estConstructible = false;
								// }

								if(d_X >= abs(d_Y)){//pente entre 0 et -pi/4.
									// printf("X_0_Cercle = %d\n",X_0_Cercle);
									// printf("Y_0_Cercle = %d\n\n",Y_0_Cercle);
									d_P = 2 * (-d_Y) - d_X;
									deltaE = 2 * (-d_Y);
									deltaNE = 2 * (-d_Y - d_X);
									rapport_d_X_d_Y = (float) d_Y/d_X;
									epaisseurChemin = (int)(30*sqrt(1+rapport_d_X_d_Y*rapport_d_X_d_Y)+1);
									if(largeur == 416 && hauteur == 137)
										printf("epaisseurChemin = %d\n",epaisseurChemin);
									while(X_0_Cercle < X_1_Cercle){
										// interrupteur = false;
										if(d_P <= 0){//cela signifie que l'on va choisir le pixel Est.
											d_P += deltaE;
											X_0_Cercle++;
										}
										else{//on choisit le pixel Nord-Est.
											d_P += deltaNE;
											X_0_Cercle++;
											Y_0_Cercle++;//on remonte.
										}
										
										if((finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle+epaisseurChemin/2 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if((finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle && hauteur == Y_0_Cercle+epaisseurChemin/2+1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}

										if(estDansLeRect(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre,14,0,23,23)
										   || estDansLeRect(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre,0,14,23,23)	
										  )
											estConstructible = false;


										if(finiUltime && largeur == X_0_Cercle && hauteur >= Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && hauteur <= Y_0_Cercle+epaisseurChemin/2-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 																									
											estConstructible = false;
											if(hauteur > Y_0_Cercle_Centre-14 && hauteur < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle < X_1_Cercle_Centre-14){
												// printf("\nR = %d G = %d B = %d\n",R,G,B );
												// printf("largeur = %d\n",largeur);
												// 	printf("hauteur = %d\n",hauteur);
												if(R!=itd->couleurChemin[0] || G!=itd->couleurChemin[1] || B!=itd->couleurChemin[2]){
													printf("La carte ne correspond pas à l'ITD... Au moins au pixel (%d,%d), la couleur devrait être celle du chemin. Or elle est (R=%d, G=%d, B=%d)\n",largeur,hauteur,R,G,B);
													free(itd->pixelsConstructibles);
													return false;
												}
											}
										}
										
									}
								}
								else{ //pente entre -pi/4 et -pi/2.
									d_P = 2 * d_X + d_Y;
									deltaE = 2 * d_X;
									deltaNE = 2 * (d_X + d_Y);
									rapport_d_X_d_Y = (float) d_X/d_Y;
									epaisseurChemin = (int)(30*sqrt(1+rapport_d_X_d_Y*rapport_d_X_d_Y)+1);


									while(Y_0_Cercle < Y_1_Cercle){
										// interrupteur = false;
										if(d_P <= 0){//cela signifie que l'on va choisir le pixel Est.
											d_P += deltaE;
											Y_0_Cercle++;
										}
										else{//on choisit le pixel Nord-Est.
											d_P += deltaNE;
											X_0_Cercle++;
											Y_0_Cercle++;//on remonte.
										}
									
										if((finiUltime && largeur == X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle+epaisseurChemin/2 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if((finiUltime && largeur == X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)-1 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) > Y_0_Cercle_Centre-14 && Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2) < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle <= X_1_Cercle_Centre+14*/)
											|| (finiUltime && largeur == X_0_Cercle+epaisseurChemin/2+1 && hauteur == Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre) /*&& Y_0_Cercle+epaisseurChemin/2 > Y_0_Cercle_Centre-14 && Y_0_Cercle+epaisseurChemin/2 < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre-14 && X_0_Cercle < X_1_Cercle_Centre-14*/)
											){
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);											
											estConstructible = false;
										}
										if(estDansLeRect(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre,23,23,14,0)
										   || estDansLeRect(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre,23,23,14,0)	
										  )
											estConstructible = false;
										
										if(finiUltime && largeur>=X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && largeur<=X_0_Cercle+epaisseurChemin/2-1 && hauteur== Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 
											 // printf("\nR = %d G = %d B = %d\n",R,G,B );
											 // printf("largeur = %d\n",largeur);
											 // printf("hauteur = %d\n",hauteur);
											estConstructible = false;
											if(Y_0_Cercle > Y_0_Cercle_Centre && Y_0_Cercle < Y_1_Cercle_Centre && largeur > X_0_Cercle_Centre && largeur < X_1_Cercle_Centre){	
												//printf("C'est blanc et ça descend !")
												if(R!=itd->couleurChemin[0] || G!=itd->couleurChemin[1] || B!=itd->couleurChemin[2]){
													printf("La carte ne correspond pas à l'ITD... Au moins au pixel (%d,%d), la couleur devrait être celle du chemin. Or elle est (R=%d, G=%d, B=%d)",largeur,hauteur,R,G,B);
													free(itd->pixelsConstructibles);
													return false;
												}
											}
										}
									}
								}
							}
	 					}
	 				}
	 			}
	 		}	
	 		/*
	 			À la fin d'un passage, on réinitialise le tableau tabNoeudsDejaVerifies à -1 (valeurs qui ne peuvent
	 			pas correspondre à l'indice d'un noeud forcément positif).
	 		*/
	 		// printf("finiUltime = %d\n",finiUltime);
	 		// printf("estConstructible = %d\n",estConstructible);
	 		for(int i=0; i<itd->nombreNoeuds; i++){
					tabNoeudsDejaVerifies[i]=-1;
			}
	 		if(finiUltime && estConstructible && (R!=itd->couleurConstruct[0] || G!=itd->couleurConstruct[1] || B!=itd->couleurConstruct[2])){
					printf("La carte ne correspond pas à l'ITD... Au moins au pixel (%d,%d), la couleur devrait être celle de la zone constructible. Or elle est (R=%d, G=%d, B=%d)\n",largeur,hauteur,R,G,B);
					free(itd->pixelsConstructibles);
					return false;
			}
			if(finiUltime && estConstructible){
				//printf("SALUT LA COMPAGNIE !\n");
				itd->pixelsConstructibles[largeur-1][hauteur]=1;
			}
			// else
			estConstructible = true;
			estCercle = false;
			

	 		if(indicePixel==0){
	 			finiB = true;
		 		if(caractere !=' '){	
		    		finiUltime = false;
		    		finiR = false;
		    		StringR[indiceStringR]=caractere;
	    	 		longCoulR++;
		    		indiceStringR ++;
		    		R = atoi(StringR);
		    	}
		    	else{
		    		indiceStringR=0;
		    		free(StringR);
		    		StringR = malloc(3*sizeof(char));
		    		estOkB++;
		    		finiUltime = true;
		    	}
	 		}
	 		else if(indicePixel==1){
	 			finiR = true;
		 		if(caractere !=' '){
					finiG = false;
					StringG[indiceStringG]=caractere;
		    		longCoulG++;
					indiceStringG++;
					G = atoi(StringG);
				}
				else{
					indiceStringG=0;
					free(StringG);
		    		StringG = malloc(3*sizeof(char));
		    		estOkR++;
				}
	 		}
	 		else if(indicePixel==2){
	 			finiG = true;
	 			if(caractere !=' '){
					finiB = false;
					StringB[indiceStringB]=caractere;
	    			longCoulB++;
					indiceStringB++;
					B = atoi(StringB);
				}
				else{
					indiceStringB=0;
					free(StringB);
		    		StringB = malloc(3*sizeof(char));
					estOkG++;
				}
			}

	    }while(caractere !=EOF);

		printf("\nLa carte est valide !!!!!!!!!!!!!!!\n");
		return true;
	//}
	// return false;
}