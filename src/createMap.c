// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>
// #include <stdbool.h>
// #include <time.h>
#include "createMap.h"

int longCouleur(int couleur){
	if(couleur<10)
		return 1;
	else if(couleur<100)
		return 2;
	else if(couleur<256)
		return 3;
	else 
		return -1;
}

bool creerCarte(bool scanMap, char * filename, ITD* itd, int dimX, int dimY){
	if(!scanMap){
		FILE *myFile = NULL;

		char emplacement[10+longueurChaine(filename)];
	    strcat(emplacement,"images/");
	    strcat(emplacement,filename);

		if (!(myFile = fopen(emplacement, "w")))
	    {
	      printf("creerMap : error opening file %s.\n",emplacement);
	      return EXIT_FAILURE;
	    }

	    fprintf(myFile,"P3\n%d %d\n255\n", dimX, dimY);
		
		int decalageX = 1;
		int decalageY = 0;

		if(dimY%2==1)
			decalageY = 1;


		int c = 0;
		int i = 0;
		int l=0;

		int R=0;
		int G=0;
		int B=0;

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
	    int hauteur = 1;
		int largeur = 0;

		int hauteurTampon = 0;
		int largeurTampon = 0;
		/*
			Tableau qui va stocker les noeuds déja analysés.
			Comme ça on ne se repète pas !
		*/
		int tabNoeudsDejaVerifies[itd->nombreNoeuds];// = {-1};//Toutes les cases du tableau sont initialisées à -1.
		for(int i=0; i<itd->nombreNoeuds; i++){
			tabNoeudsDejaVerifies[i]=-1;
		}
		int nbElementsTab = 0; 

		// int sousTabNoeudsDejaVerifies[itd->nombreNoeuds][itd->nombreNoeuds - 1];
		// for(int i=0; i<itd->nombreNoeuds; i++)
		// 	sousTabNoeudsDejaVerifies[i] = {-1};
		// int nbElementsSousTab = 0; 

		// bool interrupteur = true;

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
		bool estCercle = true;
		int epaisseurChemin = 0;
		bool estChemin = true;

	    do{
	 		for(int i=0; i<itd->nombreNoeuds; i++){
				// printf("i = %d\n",i ); 		
		 		if(itd->types[itd->indices[i]] == 3 || itd->types[itd->indices[i]] == 4){
		 			R = itd->couleurNoeud[0];
		 			G = itd->couleurNoeud[1];
		 			B = itd->couleurNoeud[2];
		 		}
		 		else if(itd->types[itd->indices[i]] == 1){
		 			R = itd->couleurIn[0];
		 			G = itd->couleurIn[1];
		 			B = itd->couleurIn[2];
		 		}
		 		else if(itd->types[itd->indices[i]] == 2){
		 			R = itd->couleurOut[0];
		 			G = itd->couleurOut[1];
		 			B = itd->couleurOut[2];
		 		}

		 		X_Cercle = itd->coordonnees[itd->indices[i]][0] + decalageX;
				Y_Cercle = itd->coordonnees[itd->indices[i]][1] + decalageY;

				
		 		if(estCercle && estDansLeCercle30Px(largeur,hauteur,X_Cercle,Y_Cercle)){
		 		// 	printf("c = %d\n", c);
		 		// 	printf("largeur = %d\n",largeur);
		 		// 	printf("hauteur = %d\n",hauteur);
					// //return false;
					// for(int u = 0; u<itd->nombreNoeuds;u++){
			 	// 		if(u==0)printf("tab[");
			 	// 		printf("%d, ",tabNoeudsDejaVerifies[u]);
			 	// 		if(u==itd->nombreNoeuds-1)printf("]\n");
			 	// 	}
					estConstructible = false;
					estCercle = false;

					fprintf(myFile,"%d %d %d ",R,G,B);	
	 				//break;
	 			}

	 			/*
	 				On va s'attarder sur les voisins des noeuds afins de pouvoir 
	 				vérifier si une ligne les relie.
	 			*/
	 			if(!appartientAuTabInt(itd->indices[i],tabNoeudsDejaVerifies,itd->nombreNoeuds)){
	 				//estConstructible = false;
	 				tabNoeudsDejaVerifies[i]=itd->indices[i];
		 			// for(int u = 0; u<itd->nombreNoeuds;u++){
			 		// 	if(u==0)printf("tab[");
			 		// 	printf("%d, ",tabNoeudsDejaVerifies[u]);
			 		// 	if(u==itd->nombreNoeuds-1)printf("]\n");
			 		// }
	 				// nbElementsTab++;
	 			//if(!estCercle){	
	 				for(int j=0; j<itd->nombreNoeudsVoisins[i]; j++){
	 					if(!appartientAuTabInt(itd->voisins[i][j],tabNoeudsDejaVerifies,itd->nombreNoeuds)){
	 						//tabNoeudsDejaVerifies[nbElementsTab]=itd->voisins[i][j];
	 						// sousTabNoeudsDejaVerifies[nbElementsSousTab] = itd->voisins[i][j];
	 						// nbElementsSousTab ++;

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
							//printf("X_0 = %d Y_0 = %d et X_1 = %d Y_1 = %d\n",X_0_Cercle,Y_0_Cercle,X_1_Cercle,Y_1_Cercle);

							//if(X_0_Cercle==100 && Y_0_Cercle == 300 && X_1_Cercle == 400 && Y_1_Cercle == 150){

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
								//d_Y = Y_1_Cercle - Y_0_Cercle;  // < 0
								if(d_X >= abs(d_Y)){//pente entre 0 et pi/4
									d_P = 2 * d_Y - d_X;
									deltaE = 2 * d_Y;
									deltaNE = 2 * (d_Y - d_X);
									rapport_d_X_d_Y = (float) d_Y/d_X;
									epaisseurChemin = (int)(30*sqrt(1+rapport_d_X_d_Y*rapport_d_X_d_Y)+1);
									// printf("Y_0_Cercle !!= %d\n",Y_0_Cercle);
									while(X_0_Cercle < X_1_Cercle){
										// interrupteur = false;
										if(d_P <= 0){//cela signifie que l'on va choisir le pixel Est.
											d_P += deltaE;
											X_0_Cercle++;
										}
										else{//on choisit le pixel Nord-Est.
											d_P += deltaNE;
											X_0_Cercle++;
											Y_0_Cercle--;//on remonte.
										}

										if(estChemin && largeur==X_0_Cercle && hauteur >= Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && hauteur <= Y_0_Cercle+epaisseurChemin/2-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 	
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);
											// printf("X_0_Cercle = %d\n",X_0_Cercle);
											// printf("Y_0_Cercle = %d\n",Y_0_Cercle);
											// estCercle = false;
											estChemin = false;
											estConstructible = false;
											//if(hauteur < Y_0_Cercle_Centre+14 && hauteur > Y_1_Cercle_Centre-14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle < X_1_Cercle_Centre-14){	
												fprintf(myFile,"%d %d %d ",itd->couleurChemin[0],itd->couleurChemin[1],itd->couleurChemin[2]);
											//}
											// break;
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

										if(estChemin && largeur>=X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && largeur<=X_0_Cercle+epaisseurChemin/2-1 && hauteur== Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 
											//largeurTampon=largeur;
											//hauteurTampon=hauteur;
											//printf("C'est  blanc et ça monte !");
											// printf("\nR = %d G = %d B = %d\n",R,G,B );
											// printf("largeur = %d\n",largeur);
											// printf("hauteur = %d\n",hauteur);
											// estCercle = false;
											estChemin = false;
											estConstructible = false;
										//	if(Y_0_Cercle < Y_0_Cercle_Centre && Y_0_Cercle > Y_1_Cercle_Centre && largeur > X_0_Cercle_Centre && largeur < X_1_Cercle_Centre){
												fprintf(myFile,"%d %d %d ",itd->couleurChemin[0],itd->couleurChemin[1],itd->couleurChemin[2]);
										//	}
											// break;
										}
									}
								}
								
							}
							else{//pente entre 0 et -pi/2.
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
										if(estChemin && largeur == X_0_Cercle && hauteur >= Y_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && hauteur <= Y_0_Cercle+epaisseurChemin/2-1 && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 													
												// largeurTampon=largeur;
												// hauteurTampon=hauteur;
												// printf("k = %d\n",k);

												// printf("X_0_Cercle = %d\n",X_0_Cercle);
												// printf("Y_0_Cercle = %d\n\n",Y_0_Cercle);
												//return true;
											// estCercle = false;
											estChemin = false;	
											estConstructible = false;
										//	if(hauteur > Y_0_Cercle_Centre-14 && hauteur < Y_1_Cercle_Centre+14 && X_0_Cercle > X_0_Cercle_Centre+14 && X_0_Cercle < X_1_Cercle_Centre-14){
												// printf("\nR = %d G = %d B = %d\n",R,G,B );
												// printf("largeur = %d\n",largeur);
												// 	printf("hauteur = %d\n",hauteur);
												fprintf(myFile,"%d %d %d ",itd->couleurChemin[0],itd->couleurChemin[1],itd->couleurChemin[2]);
											// break;
										//	}
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
										if(estChemin && largeur>=X_0_Cercle-((epaisseurChemin/2)-(epaisseurChemin+1)%2)+1 && largeur<=X_0_Cercle+epaisseurChemin/2-1 && hauteur== Y_0_Cercle && !estDansLeCercle30Px(largeur,hauteur,X_0_Cercle_Centre,Y_0_Cercle_Centre) && !estDansLeCercle30Px(largeur,hauteur,X_1_Cercle_Centre,Y_1_Cercle_Centre)){ 
											// estCercle=false;
											estChemin = false;
											estConstructible = false;
										//	if(Y_0_Cercle > Y_0_Cercle_Centre && Y_0_Cercle < Y_1_Cercle_Centre && largeur > X_0_Cercle_Centre && largeur < X_1_Cercle_Centre){	
												//printf("C'est blanc et ça descend !")
												fprintf(myFile,"%d %d %d ",itd->couleurChemin[0],itd->couleurChemin[1],itd->couleurChemin[2]);
											// break;
										//	}
										}
									}
								}
							}
	 					}
	 				}

	 			//}
	 			}

	 			/*
	 				À la fin d'un passage, on réinitialise le tableau tabNoeudsDejaVerifies à -1 (valeurs qui ne peuvent
	 				pas correspondre à l'indice d'un noeud forcément positif).
	 			*/
	 		//estCercle = true;
	 		}
	 		estChemin = true;
	 		estCercle = true;	
	 		for(int i=0; i<itd->nombreNoeuds; i++){
					tabNoeudsDejaVerifies[i]=-1;
			}
	 		if(estConstructible){
	 			fprintf(myFile,"%d %d %d ",itd->couleurConstruct[0],itd->couleurConstruct[1],itd->couleurConstruct[2]);
			}
				estConstructible = true;
	    		i++;
	    		c++;
		   		if(i==3){
	    			
	    			i=0;
		   		}
	    			
	 				largeur++;
	 			if (largeur >= dimX+1){
	 				hauteur ++;
	 				largeur = 1;
	 			}
	   
	    }while(c!=dimX*dimY);
		// time_t t = time(NULL);
	// 	int t2 = t;
	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf("\n");
	// 	t2=t;

	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf("\n");
	// 	t2=t;
	// 	printf("Mais\n");

	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf(".\n");
	// 	t2=t;
	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf(".\n");
	// 	t2=t;
	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf(".\n\n");
	// 	t2=t;
	// 	while(t<t2+2){
	// 		t = time(NULL);
	// 	}
	// 	printf("Pas de panique !\n\n");
	// 	t2 = t;
	// 	while(t<t2+2){
	// 		t = time(NULL);
	// 	}
	// 	printf("Votre ITD est valide ! Nous vous avons créé la carte associée.\n\n");
	// 	t2=t;
	// 	while(t<t2+3){
	// 		t = time(NULL);
	// 	}
	// 	printf("Ne nous remerciez pas ;)\n");
	// 	t2=t;

	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf("\n");
	// 	t2=t;

	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf("\n");
	// 	t2=t;

	// 	while(t<t2+1){
	// 		t = time(NULL);
	// 	}
	// 	printf("\n");
	// 	t2=t;

	// 	while(t<t2+2){
	// 		t = time(NULL);
	// 	}
	// 	printf("Bisous <3\n");
	}
	//itd->dejaScanne = true;
}