void viderBuffer(){
	int c = 0;
	while (c != '\n' && c != EOF){
		c = getchar();
	}
}
/*
 *@function obtenir permet d'obtenir le choix de l'usager pour une option du menu 
 *@param char*
 *@return void
 */
void obtenir(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouvel adherent\n");
     	printf("        - M pour Modifier les informations d'un adherent\n");
     	printf("        - S pour Supprimer un adherent de la liste\n");
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
 *@function affiche permet d'afficher les informations d'un usager 
 *@param char*
 *@return void
 */

void afficher(Adherent adherent){
	printf("\n\nindex:	%6d\n",adherent.index);
	printf("nom:	%s\n",adherent.nom);
	printf("prenom:	%s\n",adherent.prenom);
	printf("nombre d'emprunts:	%d\n",adherent.NbEmprunts);
	printf("Date d'inscription:	%d/%d/%d ",adherent.date.annee,adherent.date.mois,adherent.date.jour);

}
/*
 *@function demander permet de recuperer les informations d'un usager 
 *@param Adherent*
 *@return void
 */
void demander(Adherent *adh){
	Adherent perso;
	printf("Entrez les informations de l'adherent : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - nom :  ");
	scanf("%s",perso.nom);
	viderBuffer();
	printf(" - prenom :  ");
	scanf("%s",perso.prenom);
	printf(" - nombre d'emprunts :   ");
	scanf("%d",&(perso.NbEmprunts));
	printf(" - date d'inscription :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.date.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.date.mois));
	printf("\t - année :");
	scanf("%d",&(perso.date.annee));

	*adh = perso;
}
/*
 *@function visualiser permet de visualiser les informations d'un usager dans la liste chainée 
 *@param liste type pointeur 
 *@return void
 */
void visualiser ( pointeur liste){
	const int parEcran = 20 ; /* 20 personnes par écran */
      	int n ;
      	char unCar ; /* pour quitter quand l'usager le désire */

      	n = 0 ;
      	unCar = ' ' ; /* différent à 'T' pour faire démarrer la boucle */
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
           	printf("%3d) %d %s %s %d  %d/%d/%d \n",n,(liste->pers).index,(liste->pers).nom, (liste->pers).prenom,(liste->pers).NbEmprunts,
		(liste->pers).date.annee,(liste->pers).date.mois,(liste->pers).date.jour);

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
void lire (FILE * donnees, Adherent *P){
	Date date;
    	fscanf(donnees,"%d%s%s%d %d%d%d\n", &(P->index), P->nom, P->prenom, &(P->NbEmprunts),&(date.annee),&(date.mois), &(date.jour));
    	P->date  = date;
}

/*
 *@function creerFIFO permet de créer la liste chainée des adhérents  
 *@param pointeur *L
 *@return void
 */

void creerFIFO (pointeur *L){ /* dans l'ordre FIFO */
   /* comme le fichier de données a été trié selon le numéro de personnes,
      cette façon de création permet d'obtenir une liste triée par identifiant.
   */   
	FILE *donnees ;//declaration du fichier
     	Adherent unePers ;//déclaration d'une variable personne de type Adherent
     	pointeur tempo, Laliste, present ;//déclaration de trois variables de type pointeur sur la structure de controle de la liste chainéé
     	int tailleOctets = sizeof(Element) ;
   
     	donnees = fopen("eleve.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeur) malloc (tailleOctets);
         	lire(donnees, &unePers);
         	Laliste->pers = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeur) malloc (tailleOctets);
           		lire(donnees, &unePers);

           		tempo->pers    = unePers ;
           		present->suivant = tempo;
           		present = tempo;
          	}
         	fclose(donnees);
         	present->suivant = NULL; /*on met la fin de la liste, en dehors de la boucle */
     	}
      	*L = Laliste;
}
						
/*
 *@function inverser permet d'inverser la liste chainée 
 *@param pointeur *
 *@return void
 */

void inverser (pointeur *L){ 
   
	pointeur aContourner, leSuivant ,liste = * L ;
   
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
 *@function find permet de rechercher un element dans la liste chainée
 *on donne la valeur a chercher, elle cherche dans la liste et retourne deux pointeurs
 * *cl qui pointe vers l'element a chercher *av qui pointe sur l'element précedant l'élèment a chercher  
 *@param int, pointeur, pointeur *,  pointeur *
 *@return void
 */

void find (int aChercher, pointeur liste, pointeur *av, pointeur *cl){
	pointeur avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->pers).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
      /* si on ne le trouve pas, on met le cestLui à NULL */
      	if (cestLui && (cestLui->pers).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

/*
 *@function chercher  
 *@param pointeur
 *@return void
 */

void chercher (pointeur liste){
	pointeur  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numéro de la personne à chercher ");
        	scanf("%d", &aChercher);
        	find (aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){ /* on le trouve */    
                	printf("\nYOUPI! on l'a trouvé : \n");
                	afficher(cestLui -> pers);
          	}else{
          		printf("Désolé! on ne trouve pas cette personne\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->pers.index);
         	}
		viderBuffer();
         	printf("avez-vous une autre personne à chercher (O/N) ? ");
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

void eliminer ( pointeur *P, pointeur avant, pointeur cestLui){
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

void supprimer (pointeur *P){
	pointeur liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numéro à supprimer ");
       		scanf("%d", &aSupprimer);
       		find(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouvé : \n");
          		afficher(cestLui->pers);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminer ( P, avant, cestLui);}
		}else{
          		printf("Désolé! on ne trouve pas cette personne\n");
         		viderBuffer();
         		printf("avez-vous autre personne à supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}
/*
 *@function inserer  
 *@param pointeur *,Adherent ,pointeur
 *@return void
 */

void inserer (pointeur *P, Adherent unePers, pointeur avant){
	pointeur tempo;

        tempo = (pointeur) malloc(sizeof(Element));
        tempo->pers = unePers ;
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
void ajouter (pointeur * P){
	pointeur liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("eleve.txt","a");
	int aAjouter;
	char reponse ;
      	Adherent unePers ;
	viderBuffer();        	
	printf("Entrez le nouveau numéro de la personne afin de faire une vérification d'existance: ");
        scanf("%d", &aAjouter);
        find (aAjouter, *P, &avant, &cestLui );
        reponse = 'N';
        if (cestLui != NULL){
        	printf("Cet identifiant ou personne existe déjà en: \n");
        	afficher(cestLui->pers);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous ajouter les informations de cette personne avec un autre identifiant ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demander(&unePers);        
		  	inserer (P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d %d %d %d",unePers.index,unePers.nom,unePers.prenom,unePers.NbEmprunts,
			unePers.date.annee,unePers.date.mois,unePers.date.jour);     
		}	
	}else{
          	printf("Cet identifiant n'existe pas\n");
          	printf("Ajoutez les informations de cette personne,Tapez O ?");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demander(&unePers);        
		  	inserer (P, unePers, avant);
		  	fprintf(donnees,"%d %s %s %d %d %d %d",unePers.index,unePers.nom,unePers.prenom,unePers.NbEmprunts,
			unePers.date.annee,unePers.date.mois,unePers.date.jour);     
		}	
	}
}
/*
 *@function modifier  
 *@param pointeur *
 *@return void
 */

void modifier (pointeur * P){
	pointeur  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Adherent nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("eleve.txt","r+");

        do{
	viderBuffer();        	
	printf("Entrez le numéro de la personne à modifier ses informations ");
        scanf("%d", &aModifier);
 
         	find(aModifier, *P, &avant, &cestLui );
//         	reponse = 'N';
        if (cestLui != NULL){
        	printf("On l'a trouvé : \n");
        	afficher(cestLui->pers);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous modifier les informations de cette personne ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demander( &nouvPers);
	                 if ( nouvPers.index == (cestLui->pers).index ){
           		         cestLui->pers = nouvPers;
           		 }else{
                  		eliminer ( P, avant, cestLui);
                  		find ( nouvPers.index, *P, &avant, &cestLui);
                  		inserer(P, nouvPers, avant);
			  	fprintf(donnees,"%d %s %s %d %d %d %d",nouvPers.index,nouvPers.nom,nouvPers.prenom,nouvPers.NbEmprunts,
				nouvPers.date.annee,nouvPers.date.mois,nouvPers.date.jour);     
				viderBuffer();
                 	 }
            	}
		}else{
        	printf("Désolé! on ne trouve pas cette personne\n");
		viderBuffer();
         	printf("avez-vous autre personne à modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      
/*
 *@function traiter  
 *@param char,pointeur *
 *@return void
 */

void traiter ( char choix, pointeur * L ){
   /* Dépendant du choix, il est possible que la liste sera modifiée.
      Pour cette raison, le passage de la liste est par pointeur.   */  
	switch(choix){
 		case 'V' : visualiser( *L );
                 	   break;
		case 'C' : chercher ( *L );
	                   break ;
		case 'S' : supprimer (L);
	                   break;
		case 'A' : ajouter (L);
	                   break;
		case 'M' : modifier(L);
	                   break;
		case 'I' : inverser(L); /* inverser la liste */
	                   visualiser(*L);
          	           inverser(L); /* remettre dans l'ordre FIFO */
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}

