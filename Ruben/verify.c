#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAILLE_MAX 1000

int* allouerTabInt(int taille){
	int * tab = malloc(taille*sizeof(int));
	if(tab != NULL)
		return tab;
	printf("Echec d'allocation dynamique.\n");
	exit(EXIT_FAILURE);
} 

bool appartientAuTabInt(int element, int*tab, int longueurTab){
	for(int i=0; i<longueurTab; i++)
		if(tab[i]==element) return true;
	return false;
}

bool contientDoubleInt(int*tab, int longueurTab){
	for(int i=0; i<longueurTab; i++){
		for(int j=0; j<longueurTab; j++){
			if(i!=j && tab[i]==tab[j]) return true;
		}
	}
	return false;
}

int longueurChaine(char *chaine){
	int c=0;
	while(chaine[c]!='\0')
		c++;
	return c;
}

bool stringInInt(char *chaine, int *nombre){//Vérifie si la chaine est un entier et si oui nombre vaut l'entier de chaine.
	int valeur;
	int c=0;
	char chaine2[1];
	while(chaine[c]!='\0'){
		chaine2[0]=chaine[c];
		if(!sscanf(chaine2,"%d",&valeur)){
			return false;
		}
		c++;
	}
	sscanf(chaine,"%d",&(*nombre));
}

bool contientCaractere(char *chaine, char carac){
	int c=0;
	while(chaine[c]!='\0'){
		if(chaine[c]==carac)
			return true;
		c++;
	}
	return false;
}

char* retirerDernierCaractereTabChar(char * chaine){
	//printf("long chaine :%d",longueurChaine(chaine)-1);
	char * tab = malloc((longueurChaine(chaine)-1)*sizeof(char));
	
	if(tab == NULL){
		printf("Echec d'allocation dynamique de la chaine.\n");
		exit(EXIT_FAILURE);	
	}	
	for(int i=0; i<longueurChaine(chaine)-1; i++){
		tab[i]=chaine[i];
	}
	return tab;
}

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

void reinitialiserITD(ITD* itd){
	free(itd->indices);
	free(itd->nombreNoeudsVoisins);
	free(itd->coordonnees);
	/*À compléter*/
	printf("L'ITD a été réinitialisé à 0.");
}

bool scanITD(char * filename, ITD* itd){
	FILE *myFile = NULL;
	char chaine[TAILLE_MAX];
	char * morceau;
	
	// open the file
  	if (!(myFile = fopen(filename, "rt")))
    {
      printf("scanITD : error opening file %s.\n",filename);
      return EXIT_FAILURE;
    }

    //fgets(chaine,TAILLE_MAX,myFile);
    //fgets(chaine,TAILLE_MAX,myFile);
    
    /*
    On lit jusqu'à ce qu'il n'y ait plus de commentaire.
    */
    int numLigne=0;
    do{
    	fgets(chaine,TAILLE_MAX,myFile);
  		numLigne++;
  		//printf("%s",chaine);
  	}while (chaine[0]!='#');


    /*fgets(chaine,TAILLE_MAX,myFile);//on lit la ligne "carte".
  	if(chaine[0]!='c'||chaine[1]!='a'||chaine[2]!='r'||chaine[3]!='t'||chaine[4]!='e'){
  		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'carte'...");
  		return false; 
  	}*/

  	/*
	De nombreuse fois dans cette fonction, nous allons utiliser strtok.
	fgets va lire toute une ligne et la stocker dans chaine.
	Nous allons copier (grace à strtok) chaque partie de chaine délimitée par un espace
	dans morceau.
  	*/

  	/*morceau = strtok(chaine, " ");//copie la chaine sauf après l'espace.
  	if(strcmp(morceau,"carte")!=0){
  		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'carte'...");
  		return false;
  	}*/


  	/*
  	La variable c qui suit va prendre le rôle tout au long de cette
  	fonction d'un conteur. Grâce à elle, on va pouvoir gérer les actions
  	faites sur nos morceaux de l'itd, en fonction de la nature de ce morceau.
  	*/
  	int c=0;


  	/*while(morceau !=NULL){
  		if(c==1){
  			memset(nameImage, '\0', sizeof(nameImage));
  			strcpy(nameImage,morceau);
  		}
  		c++;*/
  		/*
  		Une fois que 
  		*/

  	/*	morceau = strtok(NULL, " ");//on prend chaine à l'espace d'après.
  	}
  	if(c!=2){
  		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'carte'... il y a trop ou pas assez d'arguments");
  		return false;
  	}*/

  	//peut-être rajouter energie.

  	char test[TAILLE_MAX];
  	char chaine2[TAILLE_MAX];
  	int num;

  	for(int i=0; i<6; i++){//comme les lignes carte, chemin, noeud, construct, in et out sont similaires on les regroupe dans une boucle.
  		fgets(chaine,TAILLE_MAX,myFile);//on lit la ligne "chemin" si i=0, "noeud" si i=1 etc.

  		/*
  		On copie chaine dans chaine 2. En effet avec nos prochaines opérations, chaine va se décomposer.
  		On veut conserver sa valeur. On en aura besoin pour vérifier que celle-ci se termine par des espaces.
  		*/
  		memset(chaine2, '\0', sizeof(chaine2));
	  	strcpy(chaine2,chaine);

  		/*
		De nombreuse fois dans cette fonction, nous allons utiliser strtok.
		fgets va lire toute une ligne et la stocker dans chaine.
		Nous allons copier (grace à strtok) chaque partie de chaine délimitée par un espace
		dans morceau.
	  	*/
	  	//printf("chaine = %s\n",chaine);
	  	//printf("long chaine = %d\n",longueurChaine(chaine));
  		if(!contientCaractere(chaine,' ')){//On regarde si la ligne scannée a plus d'un mot.
  			printf("Le fichier ITD n'est pas valide... La ligne %d n'a pas de paramètre...",i+numLigne+1);
  			return false;
  		}
	  	morceau = strtok(chaine, " ");//copie la chaine sauf après l'espace.
	  	//printf("test=%s\n",test);
	  	//printf("morceau=%s",morceau);printf(".\n");
	  	/*
	  	Problème ici : lorsqu'on n'écrit que carte par exemple (sans argument), on rentre dans la boucle suivante.
	  	Or on ne devrait pas car morceau est bien égal à "carte"... 
	  	*/
	  	if((strcmp(morceau,"carte")!=0 && strcmp(morceau,"chemin")!=0 && strcmp(morceau,"noeud")!=0 && strcmp(morceau,"construct")!=0 && strcmp(morceau,"in")!=0 && strcmp(morceau,"out")!=0) || strcmp(morceau,test)==0){
	  		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne %d...",i+numLigne+1);
	  		if(strcmp(morceau,test)==0) printf("Le mot clé est en double.\n");
	  		else printf("Il y a une erreur dans le mot clé.\n");
	  		return false;
	  	}	
	  	memset(test, '\0', sizeof(test));
	  	strcpy(test,morceau);
	  	
	  	c=0;
	  	
	  	while(morceau !=NULL){
	  	//	if(strcmp(morceau," ")!=0){
		  		/*printf("%d\n",c);
		  		printf("%s\n",test);
		  		printf("%s\n",morceau);*/
		  		if((c==1||c==2||c==3) && strcmp(test,"carte")!=0){
		  			/*num=atoi(morceau);
		  			printf("%d\n",num);
		  			if((num==0 && morceau[0]!='0')||(num<0 || num>255)){*/
		  			if(!stringInInt(morceau,&num)||(num<0 || num>255)){//On met la valeur de morceau dans num si c'est un entier. On vérifie si num est bien un entier compris entre 0 et 255. 
	  					//printf("morceau=%s.",morceau);
	  					/*if(strcmp(morceau,"\n")==0)
	  						printf("Le fichier ITD n'est pas valide... au niveau de la ligne '%s' il manque un argument.\n",test);
	  					else */printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne '%s' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n",test);
		  				
		  				/*if(strcmp(test,"chemin")==0){
		  					if(strcmp(morceau," ")==0)
		  						printf("Le fichier ITD n'est pas valide... au niveau de la ligne 'noeud' il manque un argument.\n");
		  					else printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'chemin' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n");
		  				}
		  				else if(strcmp(test,"noeud")==0){
		  					if(strcmp(morceau," ")==0)

		  					else printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'noeud' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n");
		  				}
						else if(strcmp(test,"construct")==0)printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'construct' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n");
						else if(strcmp(test,"in")==0)printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'in' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n");
						else if(strcmp(test,"out")==0)printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'out' et de ses paramètres (pas entiers, trop petits ou trop grands)...\n");
						*/
						return false;
		  			}
		  			if(strcmp(test,"chemin")==0)
		  				itd->couleurChemin[c-1]=num;
		  			if(strcmp(test,"noeud")==0)
		  				itd->couleurNoeud[c-1]=num;
		  			if(strcmp(test,"construct")==0)
		  				itd->couleurConstruct[c-1]=num;
		  			if(strcmp(test,"in")==0)
		  				itd->couleurIn[c-1]=num;
		  			if(strcmp(test,"out")==0)
		  				itd->couleurOut[c-1]=num;
		  		}

		  		if(c==1 && strcmp(test,"carte")==0){
		  			/*for(int j=0; j<longueurChaine(morceau);j++){
		  				if(morceau[longueurChaine(morceau)-])
		  			}*/

		  			if(morceau[longueurChaine(morceau)-3]!='m' || morceau[longueurChaine(morceau)-4]!='p'|| morceau[longueurChaine(morceau)-5]!='p' || morceau[longueurChaine(morceau)-6]!='.'){
		  				printf("Le fichier ITD n'est pas valide... La carte doit être du bon type.");
		  				return false;
		  			}
		  			// printf("morceau1 = %s.",morceau);
		  			morceau = retirerDernierCaractereTabChar(morceau);
		  			morceau = retirerDernierCaractereTabChar(morceau);
		  			// printf("morceau2 = %s.",morceau);
		  			if(longueurChaine(morceau) < 7){
		  				printf("Le fichier ITD n'est pas valide. Le nom de la carte est trop court. (Il doit avoir au moins quatre caractères).\n");
		  				return false;
		  			}
		  			//int nbMaxCaracteres = 0;
		  			
		  			/*
		  				La boucle suivante pouvait être utile (si améliorée) mais bon on a trouvé comment mieux faire.
		  			*/

		  			// for(int a=0; a<longueurChaine(morceau);a++){
		  			// 	if(morceau[a]!='.' || morceau[a+1]!='p' || morceau[a+2]!='p' || morceau[a+3]!='m')
		  			// 		nbMaxCaracteres ++;
		  			// 	else{
		  			// 		itd->nameImage[a]='.';
		  			// 		itd->nameImage[a+1]='p';
		  			// 		itd->nameImage[a+2]='p';
		  			// 		itd->nameImage[a+3]='m';
		  			// 		break;
		  			// 	}
		  			// 	if(nbMaxCaracteres > longueurChaine(morceau)-4){
		  			// 		printf("Le fichier ITD n'est pas valide. La carte doit être de type .ppm.\n");
		  			// 		return false;
		  			// 	}
		  			// 	itd->nameImage[a]=morceau[a];
		  			// }
		  			memset(itd->nameImage, '\0', sizeof(itd->nameImage));
	  				strcpy(itd->nameImage,morceau);
		  		}

		  		c++;
		  		/*
		  		Avec strtok(NULL, ) on indique que morceau vaut maintenant la partie
		  		de chaine après l'espace, jusqu'au prochain espace. 
		  		Et ainsi de suite jusqu'à ce que la chaine soit finie et que morceau soit NULL.
	  			
		  		*/
		  	//}
		  	//else //if(c!=0) 
		  	//	c--;

		  		//do{
		  			//printf("%s\n",morceau);
		  			//printf("c = %d\n", c);
		  			morceau = strtok(NULL, " ");//on prend chaine à l'espace d'après.
		  			//printf(".%s.\n",morceau);
		  			//printf("longueur morceau = %d\n",longueurChaine(morceau));
		  			//printf("%d\n",morceau[0]=='\n');
		  		//}while(morceau !=NULL || strcmp(morceau," ")==0);
		  		
	  	}
	  	
	  	//printf("COUCOU LES COPAINS \n");
	  	//printf(" chaine = %s\n",chaine);
	  	if(strcmp(test,"carte")==0){
	  		if(c!=2){
	  			if(!(c==3 && chaine2[longueurChaine(chaine2)-3]== ' ')){//S'il y a un espace après le titre il n'y a pas de problème.
		  			printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne 'carte'... il doit y avoir un argument : le nom du fichier.\n");
		  			return false;
  				}
  			}
  		}

	  	else if(c!=4){
		  	if(!(c==5 && chaine2[longueurChaine(chaine2)-3]== ' ')){//S'il y a un espace après les couleurs il n'y a pas de problème.
		  		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne %d)... il y a trop ou pas assez d'arguments (il doit y en avoir 3).\n",i+numLigne+1);
		  		return false;
	  		}
	  	}
	}


	fgets(chaine,TAILLE_MAX,myFile);
	//num=atoi(chaine);
	if(!stringInInt(chaine,&num)/*(num==0 && chaine[0]!='0')*/|| num<0){//On vérifie que le nombre de noeuds est bien un entier.
		printf("Le fichier ITD n'est pas valide (au moins au niveau de la ligne spécifiant le nombre de noeuds. Ça doit être un entier.\n");
	  	return false;
	}
	itd->nombreNoeuds = num;
	int nombreNoeuds = itd->nombreNoeuds;
	int nombresVoisinsMax = nombreNoeuds-1;//chaque noeud peut avoir au maximum nombreNoeuds-1 voisins.
	/*
	Dans indices, on va simplement mettre les indices de chaque noeud.
	*/
	itd->indices = allouerTabInt(nombreNoeuds);
	itd->nombreNoeuds = nombreNoeuds;
	itd->nombreNoeudsVoisins = allouerTabInt(nombreNoeuds);//nombreNoeudsVoisins stocke le nombre de voisins pour chaque noeud.

	/*
	Dans types, on va simplement mettre les types de chaque noeud.
	*/
	itd->types = allouerTabInt(nombreNoeuds);
	/*
	Le tableau coordonnees est un tableau de deux dimensions, il contient en première dimension
	les indices des noeuds et en deuxième dimension ses deux coordonnées.
	*/
	itd->coordonnees = malloc(nombreNoeuds*sizeof(int*));

	if(itd->coordonnees==NULL){
		printf("ERREUR\n");
		exit(EXIT_FAILURE);
	}
	for(int i=0; i<nombreNoeuds;i++)
		itd->coordonnees[i]=allouerTabInt(2);
	//int *voisins[nombreNoeuds]/*[nombresVoisinsMax]*/;
	//int **voisins;

	/*
	On alloue voisins. C'est un tableau de tableau d'entiers.
	*/
	itd->voisins = malloc(nombreNoeuds*sizeof(int*));
	if(itd->voisins == NULL){
		printf("ERREUR\n");
		exit(EXIT_FAILURE);
	}

	int * voisinsFinDeLigne;
	voisinsFinDeLigne = allouerTabInt(nombresVoisinsMax); //on va stocker dans ce tableau les voisins afin de les introduire plus tard dans le tableau voisins.

	for(int i=0; i<nombreNoeuds; i++){//On parcourt les prochaines lignes pour chaque noeud.
		c=0;
		fgets(chaine,TAILLE_MAX,myFile);

		/*
		Pour les lignes, valeurs-argument on a pu s'en sortir facilement pour le cas où il y avait un espace à la fin de la ligne.
		Ici comme on ne sait pas combien de voisins il y a, on ne peut faire de même.
		On va donc recréer chaine en lui enlevant l'espace de fin de ligne, tant qu'elle en a un.
		*/
	/*IIIICCCCCIIIIIII*/ 

		// printf("dernier element = espace : %d\n",chaine[longueurChaine(chaine)-3]== ' ');
		// printf("chaine : %s.",chaine);
		// printf("HELLO");
		// printf("chaine avortee : %s.",retirerDernierCaractereTabChar(chaine));
		while((chaine[longueurChaine(chaine)-3]== ' ')==1){
			// printf("COCO");
			strcpy(chaine,retirerDernierCaractereTabChar(chaine));
			// printf("%s.",chaine);
			//chaine[longueurChaine(chaine)-3]=chaine[longueurChaine(chaine)-2];
			//i++;
			/*char *chaine3 = malloc((longueurChaine(chaine)-1)*sizeof(char));
			//chaine ;
			if(chaine3 == NULL){
				printf("Echec d'allocation dynamique pour chaine2.\n");
				exit(EXIT_FAILURE);
			}
			for(int j=0; j<longueurChaine(chaine)-4;j++){
				chaine3[j]=chaine[j];
			}
			//free(chaine);
			memset(chaine, '\0', sizeof(chaine));
		  	strcpy(chaine,chaine3);
		  	printf("chaine = %s.\n",chaine);
		  	printf("chaine3 = %s.\n",chaine3);
		  	free(chaine3);*/
	  	}
	  	// printf("C'est cool");

		morceau = strtok(chaine, " ");
		// printf("|%s|",morceau);
		for(int j=0; j<4; j++){//pour chaque ligne on parcourt les 4 premières colonnes. En effet, elles correspondront toujours aux mêmes choses pour chaque noeud.
			//num=atoi(morceau);
			if(!stringInInt(morceau,&num)|| num<0){//peut-être rajouter une condition qui fasse en sorte que les coordonnées peuvent être négatives.
				printf("Le fichier ITD n'est pas valide... Il y a un problème pour le noeud %d à la colonne %d, ça doit être un entier positif.\n",itd->indices[i],j+1);
	  			return false;
			}
			if(j==0)
				itd->indices[i] = num;
			else if(j==1){
				if(num<1 || num>4){
					printf("Le fichier ITD n'est pas valide... Le noeud %d est d'un type inconnu.\n",itd->indices[i]);
					return false;
				}	
				itd->types[i] = num;
			}
			else if(j==2)
				itd->coordonnees[i][0] = num;
			else if(j==3)
				itd->coordonnees[i][1] = num;

			morceau = strtok(NULL, " ");
		}
		//printf("\n");
		//while(morceau != NULL){
		for(int j=0; j<nombresVoisinsMax+1; j++){//on va jusqu'à nombresVoisinsMax+1 pour voir s'il n'y a pas trop de voisins.
			if(morceau == NULL)
				break;
			if(j==nombresVoisinsMax){
				printf("Le fichier ITD n'est pas valide. Il y a plus de voisins que possible au noeud %d",itd->indices[i]);
				return false;
			}
			// printf("|%s|",morceau);
			//num = atoi(morceau);
			if(strcmp(morceau," ")!=0 && (!stringInInt(morceau,&num)|| num<0)){
				printf("Le fichier ITD n'est pas valide... Au noeud %d, le voisin %d n'est pas un entier.\n",i,j+1);
				//printf("Le fichier ITD n'est pas valide (au moins au niveau des lignes des noeuds - particulièrement au niveau des voisins)\n");
	  			return false;
			}
			c++;
			voisinsFinDeLigne[j]=num;
			morceau = strtok(NULL, " ");
		}
		itd->nombreNoeudsVoisins[i]=c;
		//printf("%d\n",c);
		itd->voisins[i]=allouerTabInt(c);
		for(int j=0; j<c; j++){
			itd->voisins[i][j]=voisinsFinDeLigne[j];//le tableau créé sera de taille immense car ce sont des pointeurs. SURTOUT QUAND ON LE PARCOURT NE PAS FAIRE WHILE !=0 OU QUELQUE CHOSE DE SIMILAIRE.
		}
		if(contientDoubleInt(itd->voisins[i],itd->nombreNoeudsVoisins[i])){
			printf("Le fichier ITD n'est pas valide... Il y a deux fois le même noeud dans les voisins du noeud %d.\n",i);
			return false;
		}
	}
	

	/*printf("\n\n\n");	//debug
	//printf("%ld\n\n",sizeof(voisins[0]));
	for(int i=0; i<itd->nombreNoeuds; i++){
		for(int j=0; j<itd->nombreNoeudsVoisins[i]; j++)
			printf("%d\n", itd->voisins[i][j]);
		//printf("%ld\n",sizeof(voisins[i])/sizeof(int));
	}*/

	//printf("%d\n",voisins[1][2]);
	
	for(int i=0; i<nombreNoeuds; i++){//On vérifie que les voisins indiqués existent bien.
		for(int j=0; j<itd->nombreNoeudsVoisins[i]; j++){
			c=0;
			for(int k=0; k<nombreNoeuds; k++){
				if(itd->voisins[i][j]==itd->indices[k]){
					if(itd->voisins[i][j]==itd->indices[i]){
						printf("Le fichier ITD n'est pas valide...Au noeud %d, il a comme voisin lui-même...\n",itd->indices[i]);
						return false;
					}
					c=1;
				}
			}
			if(c==0){
				printf("Le fichier ITD n'est pas valide... Au moins un voisin est indiqué au noeud %d alors qu'ils n'existent pas.\n", itd->indices[i]);
				return false;
			}
		}
	}
	
	for(int i=0; i<nombreNoeuds; i++){//On vérifie que les coudes ont bien DEUX voisins seulement, et que les intersections en ont au moins DEUX.
		if((itd->types[i]==3 && itd->nombreNoeudsVoisins[i]!=2) || (itd->types[i]==1 && itd->nombreNoeudsVoisins[i]<1) || (itd->types[i]==2 && itd->nombreNoeudsVoisins[i]<1) || (itd->types[i]==4 && itd->nombreNoeudsVoisins[i]<2)){
			if(itd->types[i]==1)printf("Le fichier ITD n'est pas valide... Au noeud numéro %d, c'est une zone d'entrée : il doit y avoir au moins un voisin.\n",itd->indices[i]);
			if(itd->types[i]==2)printf("Le fichier ITD n'est pas valide... Au noeud numéro %d, c'est une zone de sortie : il doit y avoir au moins un voisin.",itd->indices[i]);
			if(itd->types[i]==3)printf("Le fichier ITD n'est pas valide... Au noeud numéro %d, c'est un coude : il doit y avoir strictement deux noeuds voisins.\n",itd->indices[i]);
			if(itd->types[i]==4)printf("Le fichier ITD n'est pas valide... Au noeud numéro %d, c'est une intersection : il doit y avoir au moins deux noeuds voisins.\n",itd->indices[i]);
			return false;
		}	
	}

	for(int i=0; i<nombreNoeuds; i++){//On vérifie que les voisins sont bien cohérents entre chaque noeud.
		for(int j=0; j<nombreNoeuds; j++){
			for(int k=0; k<itd->nombreNoeudsVoisins[j]; k++){
				if(itd->indices[i]==itd->voisins[j][k]){
					if(!appartientAuTabInt(itd->indices[j], itd->voisins[i],itd->nombreNoeudsVoisins[i])){
						printf("Le fichier ITD n'est pas valide... Le noeud %d n'a pas le noeud %d comme voisin mais le noeud %d a pour voisin %d...",itd->indices[i],itd->indices[j],itd->indices[j],itd->indices[i]);
						return false;
					}
				}
			}
		}
	}
	
	if(fgets(chaine,TAILLE_MAX,myFile)!=NULL){
		printf("Il y a plus de noeuds qu'indiqué...\n");
		return false;
	}
	printf("Le fichier ITD est valide !\n");
	itd->dejaScanne = false;
	return true;

}

// int main(int argc, char const *argv[])
// {
// 	ITD itd;
// 	scanITD("map1.itd",&itd);
// 	/*printf("\n%d\n",itd.types[0]);
// 	printf("\n%d\n\n",itd.nombreNoeudsVoisins[0]);
// 	int valeur;
// 	printf("%d\n",sscanf("22^kkkjkl3","%d",&valeur));
// 	printf("%d\n",valeur);

// 	int num = atoi("00973");
// 	printf("%d\n",num);
// 	//printf("long = %d\n",longueurChaine("PPmezkoekz"));
// 	int nombre;
// 	printf("%d\n",stringInInt("277572",&nombre));
// 	printf("%d\n",nombre);*/
// 	//printf("%d ",contientCaractere("coco\0",' '));
// 	for(int i=0; i<4; i++){
// 		for(int j=0; j<itd.nombreNoeudsVoisins[i];j++)
// 			printf("%d\n ",itd.voisins[i][j]);
// 	}
// 	char * espace ="Coucou";
// 	char * str = malloc(longueurChaine(espace)*sizeof(char));
// 	if(str == NULL){
// 		printf("Echec d'allocation dynamique.\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	memset(str, '\0', sizeof(str));
// 	strcpy(str,espace);
// 	str[2]='y';
// 	printf("%s\n",str);
// 	printf("chaine : %s\n",retirerDernierCaractereTabChar("Salut"));

// 	return 0;
// }