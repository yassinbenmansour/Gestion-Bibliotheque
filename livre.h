/*
 *@function obtenir permet d'obtenir le choix de l'usager pour une option du menu 
 *@param char*
 *@return void
 */
void obtenirs(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouveau livre\n");
     	printf("        - M pour Modifier les informations d'un livre\n");
     	printf("        - S pour Supprimer un livre de la liste\n");
     	printf("        - I pour visualiser la liste Inverse \n");
     	printf("        - R pour retourner au menu principal\n");	
	printf("        - N pour Nettoyer l'ecran \n");
	do{
		printf("\n\n");
		printf("Entrez votre choix >>");
		fflush(stdin);
		c = toupper(getchar());
	}while(strchr("QVCAMSIRN", c) == NULL);
	*pt = c;
}
/*
 *@function affiche permet d'afficher les informations d'un livre 
 *@param char*
 *@return void
 */

void affichers(Livre livre){
	printf("\n\ref:	%5d\n",livre.index);
	printf("titre:	%s\n",livre.Titre);
	printf("status:	%d\n",livre.disponible);
}
/*
 *@function demander permet de recuperer les informations d'un usager 
 *@param Adherent*
 *@return void
 */
void demanders(Livre *adh){
	Livre perso;
	printf("Entrez les informations d'un livre (les chaines de caractère doivent être séparer par _ ) : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - Titre :  ");
	scanf("%s",perso.Titre);
	viderBuffer();
	printf(" - Auteur :  ");
	scanf("%s",perso.Auteur);
	printf(" - nombre disponible :   ");
	scanf("%d",&(perso.disponible));
	printf(" - le stock total :   ");
	scanf("%d",&(perso.stock));
	*adh = perso;
}
/*
 *@function visualiser permet de visualiser les informations d'un usager dans la liste chainée 
 *@param liste type pointeur 
 *@return void
 */
void visualisers( pointeux liste){
	const int parEcran = 20 ; /* 20 personnes par écran */
      	int n ;
      	char unCar ; /* pour quitter quand l'usager le désire */

      	n = 0 ;
      	unCar = ' ' ; /* différent à 'T' pour faire démarrer la boucle */
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
           	printf("%3d) %d %s %s %d %d \n",n,(liste->liv).index,(liste->liv).Titre, (liste->liv).Auteur,(liste->liv).disponible,
		(liste->liv).stock);

           	liste = liste->suivant;

           	if ( n % parEcran == 0 || liste == NULL){
			printf("\n\n");
             		printf("Appuyez sur Entrée pour continuer ou T pour terminer ");
             		fflush(stdin);
             		unCar = toupper(getchar());
             		if (  unCar != 'T' && liste != NULL){    
                   		printf("Dans l'ordre : \n");
              		}
           	}
	}
}
/*
 *@function lire permet de lire les informations d'un usager dans un fichier 
 *elle lit une ligne dans le fichier
 *@param FILE *donnees , Adherent *p 
 *@return void
 */
void lires(FILE * donnees, Livre *P){
    	fscanf(donnees,"%d%s%s%d%d \n", &(P->index), P->Titre, P->Auteur, &(P->disponible), &(P->stock));
}

/*
 *@function creerFIFO  
 *@param pointeur *L
 *@return void
 */

void creerFIFOs(pointeux *L){ /* dans l'ordre FIFO */
   /* comme le fichier de données a été trié selon le numéro de personnes,
      cette façon de création permet d'obtenir une liste triée.
   */   
	FILE *donnees ;
     	Livre unePers ;
     	pointeux tempo, Laliste, present ;
     	int tailleOctets = sizeof(Liste) ;
   
     	donnees = fopen("Livre.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeux) malloc (tailleOctets);
         	lires(donnees, &unePers);
         	Laliste->liv = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeux) malloc (tailleOctets);
           		lires(donnees, &unePers);

           		tempo->liv    = unePers ;
           		present->suivant = tempo;
           		present = tempo;
          	}
         	fclose(donnees);
         	present->suivant = NULL; /* mettre la fin de la liste, ici en dehors de la boucle */
     	}
      	*L = Laliste;
}
						
/*
 *@function inverser  
 *@param pointeur *
 *@return void
 */

void inversers (pointeux *L){ 
   
	pointeux aContourner, leSuivant , liste = * L ;
   
     	aContourner = liste ;
     	liste        = NULL  ;
   
     	while (aContourner){
		leSuivant            = aContourner->suivant ;

        	aContourner->suivant = liste ;
        	liste                = aContourner ;

        	aContourner          = leSuivant;
       	}

     	*L = liste ;
}

/*
 *@function find  
 *@param int, pointeur, pointeur *,  pointeur *
 *@return void
 */

void finds(int aChercher, pointeux liste, pointeux *av, pointeux *cl){
	pointeux avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->liv).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
      /* si on ne le trouve pas, on met le cestLui à NULL */
      	if (cestLui && (cestLui->liv).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

/*
 *@function chercher  
 *@param pointeur
 *@return void
 */

void cherchers(pointeux liste){
	pointeux  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numéro du livre à chercher ");
        	scanf("%d", &aChercher);
        	finds(aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){ /* on le trouve */    
                	printf("\nYOUPI! on l'a trouvé : \n");
                	affichers(cestLui->liv);
          	}else{
          		printf("Désolé! on ne trouve pas ce livre\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->liv.index);
         	}
		viderBuffer();
         	printf("avez-vous un autre livre à chercher (O/N) ? ");
         	//fflush(stdin);
		//viderBuffer();
		
	}while (toupper(getchar()) != 'N');
	viderBuffer();
}
/*
 *@function eliminer  
 *@param pointeur *,Adherent ,pointeur
 *@return void
 */

void eliminers( pointeux *P, pointeux avant, pointeux cestLui){
	if(avant == NULL){
		/* au début de la liste */
    		*P = (*P)->suivant ; /* on fait avancer la liste */
        }else{
		avant->suivant = cestLui->suivant;
	}
}
/*
 *@function supprimer  
 *@param pointeur *
 *@return void
 */

void supprimers (pointeux *P){
	pointeux liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numéro à supprimer ");
       		scanf("%d", &aSupprimer);
       		finds(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouvé : \n");
          		affichers(cestLui->liv);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminers( P, avant, cestLui);}
		}else{
          		printf("Désolé! on ne trouve pas ce livre\n");
         		viderBuffer();
         		printf("avez-vous autre livre à supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}
/*
 *@function inserer  
 *@param pointeur *,Adherent ,pointeur
 *@return void
 */

void inserers(pointeux *P, Livre unePers, pointeux avant){
	pointeux tempo;

        tempo = (pointeux) malloc(sizeof(Liste));
        tempo->liv = unePers;
        if(avant == NULL){
		tempo->suivant = *P ;
                (*P) = tempo;
        }else{
		tempo->suivant = avant->suivant ;
                avant->suivant= tempo;
              }
}

/*
 *@function ajouter  
 *@param pointeur *
 *@return void
 */
void ajouters(pointeux *P){
	pointeux liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("Livre.txt","a");
	int aAjouter;
	char reponse ;
      	Livre unePers ;
		viderBuffer();        	
		printf("Entrez le nouveau numéro du livre afin de faire une vérification d'existance: ");
         	scanf("%d", &aAjouter);
		printf("blablabala");
         	finds(aAjouter, *P, &avant, &cestLui );
        if (cestLui != NULL){
		printf("blablabala");
		viderBuffer();
        	printf("Cet identifiant ou le livre existe déjà en: \n");
        	affichers(cestLui->liv);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous ajouter les informations de ce livre avec un autre identifiant ?(O/N) ");
                reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demanders(&unePers);        
		  	inserers(P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d%d ",unePers.index,unePers.Titre,unePers.Auteur,unePers.disponible,unePers.stock);     
		}//viderBuffer();	
	}
}
/*
 *@function modifier  
 *@param pointeur *
 *@return void
 */

void modifiers(pointeux *P){
	pointeux  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Livre nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("Livre.txt","r+");
        do{ 
		viderBuffer();        	
		printf("Entrez le numéro du livre à modifier ses informations ");
         	scanf("%d", &aModifier);
         	finds(aModifier, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("On l'a trouvé : \n");
        	affichers(cestLui->liv);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous modifier les informations de ce livre ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demanders( &nouvPers);
	                 if ( nouvPers.index == (cestLui->liv).index ){
           		         cestLui->liv = nouvPers;
           		 }else{
                  		eliminers( P, avant, cestLui);
                  		finds( nouvPers.index, *P, &avant, &cestLui);
                  		inserers(P, nouvPers, avant);
			  	fprintf(donnees,"%d %s %s %d%d ",nouvPers.index,nouvPers.Titre,nouvPers.Auteur,nouvPers.disponible,nouvPers.stock);     

                 	 }
            	}
        }else{
        	printf("Désolé! on ne trouve pas ce livre\n");
		viderBuffer();
         	printf("avez-vous autre livre à modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      
/*
 *@function traiter  
 *@param char,pointeur *
 *@return void
 */

void traiters( char choix, pointeux *L ){
   /* Dépendant du choix, il est possible que la liste sera modifiée.
      Pour cette raison, le passage de la liste est par pointeur.   */  
	switch(choix){
 		case 'V' : visualisers( *L );
                 	   break;
		case 'C' : cherchers( *L );
	                   break ;
		case 'S' : supprimers(L);
	                   break;
		case 'A' : ajouters(L);
	                   break;
		case 'M' : modifiers(L);
	                   break;
		case 'I' : inversers(L); /* inverser la liste */
	                   visualisers(*L);
          	           inversers(L); /* remettre dans l'ordre FIFO */
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}

