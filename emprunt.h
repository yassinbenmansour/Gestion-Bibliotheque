/*
 *@function obtenir permet d'obtenir le choix de l'usager pour une option du menu 
 *@param char*
 *@return void
 */
void obtenirss(char *pt){
	char c;
	printf("Tapez : \n");
     	printf("        - Q pour Quitter \n");
     	printf("        - V pour Visualiser \n");
     	printf("        - C pour Chercher\n");
     	printf("        - A pour Ajouter un nouvel emprunt\n");
     	printf("        - M pour Modifier les informations d'un emprunt\n");
     	printf("        - S pour Supprimer un emprunt de la liste\n");
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
 *@function affiche permet d'afficher les informations sur l'emprunts 
 *@param char*
 *@return void
 */

void afficherss(Emprunt emprunt){
	printf("\n\nindex:	%6d\n",emprunt.index);
	printf("l'identifiant de l'adherent:    %d\n",emprunt.id);
	printf("nom eleve:	%s\n",emprunt.nom);
	printf("Titre :	%s\n",emprunt.Titre);
	printf("Auteur :	%s\n",emprunt.Auteur);
	printf("Date d'emprunt:	%d/%d/%d  %d:%d \n",emprunt.date.annee,emprunt.date.mois,emprunt.date.jour,emprunt.date.heure,emprunt.date.minute);
	printf("Date retour:	%d/%d/%d  %d:%d \n",emprunt.retour.annee,emprunt.retour.mois,emprunt.retour.jour,emprunt.retour.heure,emprunt.retour.minute);
}
/*
 *@function demander permet de recuperer les informations sur l'emprunt 
 *@param Emprunt*
 *@return void
 */
void demanderss(Emprunt *emp){
	Emprunt perso;
	printf("Entrez les informations de l'emprunt : \n");
	printf(" - index :  ");
	scanf("%d",&(perso.index));
	fflush(stdin);
	viderBuffer();
	printf(" - identifiant eleve:   ");
	scanf("%d",&(perso.id));
	fflush(stdin);
	viderBuffer();
	printf(" - nom eleve:  ");
	scanf("%s",perso.nom);
	viderBuffer();
	printf(" - Titre  :  ");
	scanf("%s",perso.Titre);
	viderBuffer();
	printf(" - Auteur  :  ");
	scanf("%s",perso.Auteur);
	printf(" - date d'emprunt :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.date.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.date.mois));
	printf("\t - année :");
	scanf("%d",&(perso.date.annee));
	printf("\t - heure :");
	scanf("%d",&(perso.date.heure));
	printf("\t - minute :");
	scanf("%d",&(perso.date.minute));
	printf(" - date de retour :   \n");
	printf("\t - jour :");
	scanf("%d",&(perso.retour.jour));
	printf("\t - mois :");
	scanf("%d",&(perso.retour.mois));
	printf("\t - année :");
	scanf("%d",&(perso.retour.annee));
	printf("\t - heure :");
	scanf("%d",&(perso.retour.heure));
	printf("\t - minute :");
	scanf("%d",&(perso.retour.minute));
	*emp = perso;
}
/*
 *@function visualiser permet de visualiser les informations d'un emprunt dans la liste chainée 
 *@param liste type pointeur 
 *@return void
 */
void visualiserss(pointeurs liste){
	const int parEcran = 20 ; /* 20 personnes par écran */
      	int n ;
      	char unCar ; 

      	n = 0 ;
      	unCar = ' ' ;
      	printf("Dans l'ordre : \n");
      	while ( unCar != 'T' && liste ){
		n++;
		printf("%3d) %d %d %s %s %s   %d/%d/%d %d:%d  %d/%d/%d %d:%d \n",n,(liste->emp).index,(liste->emp).id,(liste->emp).nom, (liste->emp).Titre,(liste->emp).Auteur,
		(liste->emp).date.annee,(liste->emp).date.mois,(liste->emp).date.jour,(liste->emp).date.heure,(liste->emp).date.minute,
		(liste->emp).retour.annee,(liste->emp).retour.mois,(liste->emp).retour.jour,(liste->emp).retour.heure,(liste->emp).retour.minute);

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
 *@function lire permet de lire les informations d'un emprunt dans un fichier elle lit une ligne dans le fichier
 *@param FILE *donnees , Adherent *p 
 *@return void
 */
void liress (FILE * donnees, Emprunt *P){
	Date date;
	Date retour;
    	fscanf(donnees,"%d%d%s%s%s %d%d%d%d%d %d%d%d%d%d\n", &(P->index), &(P->id), P->nom, P->Titre, P->Auteur,&(date.annee),&(date.mois), 
		&(date.jour),&(date.heure),&(date.minute),&(retour.annee),&(retour.mois),&(retour.jour),&(retour.heure),&(retour.minute));
    	P->date  = date;
	P->retour  = retour;
}

/*
 *@function creerFIFO permet de créer la liste chainée First In First Out 
 *@param pointeur *L
 *@return void
 */

void creerFIFOss (pointeurs *L){ /* dans l'ordre FIFO */
   /* comme le fichier de données a été trié selon le numéro de personnes,
      cette façon de création permet d'obtenir une liste triée.
   */   
	FILE *donnees ;
     	Emprunt unePers ;
     	pointeurs tempo, Laliste, present ;
     	int tailleOctets = sizeof(Elements) ;
   
     	donnees = fopen("emprunt.txt","r+");

     	if (feof(donnees))
       		Laliste = NULL ;
     	else{ 
         	Laliste = (pointeurs) malloc (tailleOctets);
         	liress(donnees, &unePers);
         	Laliste->emp = unePers;
         	present = Laliste;
   
         	while (!feof(donnees)){
           		tempo = (pointeurs) malloc (tailleOctets);
           		liress(donnees, &unePers);

           		tempo->emp    = unePers ;
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

void inverserss(pointeurs *L){ 
   
	pointeurs aContourner, leSuivant , liste = * L ;
   
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
 *@function find  permet d'effectuer une recherche dans la liste chainée 
 *la recherche se fait en fonction des index du plus petit au plus grand 
 *@param int, pointeur, pointeur *,  pointeur *
 *@return void
 */

void findss(int aChercher, pointeurs liste, pointeurs *av, pointeurs *cl){
	pointeurs avant, cestLui ;
      	avant = NULL ;
      	cestLui = liste ;
      	while ( cestLui && (cestLui->emp).index < aChercher ){
		avant   = cestLui;
        	cestLui = cestLui->suivant ;
       }
      /* si on ne le trouve pas, on met le cestLui à NULL */
      	if (cestLui && (cestLui->emp).index != aChercher)
      		cestLui = NULL;
      		*av = avant ;
      		*cl = cestLui ;
}

/*
 *@function chercher permet d'appliquer la function find afin de chercher un index dans la liste
 *@param pointeur
 *@return void
 */

void chercherss(pointeurs liste){
	pointeurs  cestLui, avant ;
      	int aChercher;
      	do{ 
		viderBuffer();
        	printf("Entrez le numéro de la personne à chercher ");
        	scanf("%d", &aChercher);
        	findss (aChercher,liste, &avant, &cestLui);

		if (cestLui != NULL){ /* on le trouve */    
                	printf("\nYOUPI! on l'a trouvé : \n");
                	afficherss(cestLui->emp);
          	}else{
          		printf("Désolé! on ne trouve pas cet emprunt\n");
		}
           	if (avant == NULL){
              		printf("\navant vaut NULL\n");
           	}else{
              		printf("\nvaleur avant : %5d\n", avant->emp.index);
         	}
		viderBuffer();
         	printf("avez-vous un autre emprunt à chercher (O/N) ? ");
         	//fflush(stdin);
		//viderBuffer();
		
	}while (toupper(getchar()) != 'N');
	viderBuffer();
}
/*
 *@function eliminer permet la suppression dans la liste chainée
 *@param pointeur *,Adherent ,pointeur
 *@return void
 */

void eliminerss(pointeurs *P, pointeurs avant, pointeurs cestLui){
	if(avant == NULL){
		/* au début de la liste */
    		*P = (*P)->suivant ; /* on fait avancer la liste */
        }else{
		avant->suivant = cestLui->suivant;
	}
}
/*
 *@function supprimer permet d'appliquer la function eliminer pour 
 *supprimer une element en fonction de l'index de cette element
 *@param pointeur *
 *@return void
 */

void supprimerss(pointeurs *P){
	pointeurs liste, cestLui, avant, tempo ;
      	int aSupprimer;
      	char reponse ;
      	do{
         	viderBuffer();
       		printf("\n\nEntrez le numéro à supprimer ");
       		scanf("%d", &aSupprimer);
       		findss(aSupprimer,*P, &avant, &cestLui);
       		reponse = 'N';
       		if (cestLui != NULL){
        		printf("On l'a trouvé : \n");
          		afficherss(cestLui->emp);
			viderBuffer();
          		printf("\nConfirmez-vous la suppression ?(O/N) ");
          		fflush(stdin);
          		reponse = toupper(getchar());   
          		if (reponse == 'O'){ eliminerss( P, avant, cestLui);}
		}else{
          		printf("Désolé! on ne trouve pas cet emprunt\n");
         		viderBuffer();
         		printf("avez-vous autre emprunt à supprimer (O/N) ? ");
        		fflush(stdin);
		}
        }while (toupper(getchar()) != 'N');
}
/*
 *@function inserer permet l'insertion dans la liste chainée
 *@param pointeur *,Adherent ,pointeur
 *@return void
 */

void insererss(pointeurs *P, Emprunt unePers, pointeurs avant){
	pointeurs tempo;

        tempo = (pointeurs) malloc(sizeof(Elements));
        tempo->emp = unePers ;
        if(avant == NULL){
		tempo->suivant = *P ;
                (*P) = tempo;
        }else{
		tempo->suivant = avant->suivant ;
                avant->suivant= tempo;
              }
}

/*
 *@function ajouter applique la function inserer pour inserer des informations sur l'emprunt
 * et insere les informations de la liste chainée dans le fichier emprunt.txt
 *@param pointeur *
 *@return void
 */
void ajouterss(pointeurs * P){
	pointeurs liste,cestLui, avant, tempo ;
	FILE *donnees = NULL;
	donnees = fopen("emprunt.txt","a");
	int aAjouter;
	char reponse ;
      	Emprunt unePers ;
		viderBuffer();        	
		printf("Entrez le nouveau numéro de l'emprunt afin de faire une vérification d'existance: ");
         	scanf("%d", &aAjouter);
         	findss(aAjouter, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("Cet identifiant ou emprunt existe déjà en: \n");
        	afficherss(cestLui->emp);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous ajouter les informations de cet emprunt avec un autre identifiant ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demanderss(&unePers);        
		  	insererss(P, unePers, avant);
		  	fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",unePers.index,unePers.id,unePers.nom,unePers.Titre,unePers.Auteur,
			unePers.date.annee,unePers.date.mois,unePers.date.jour,unePers.date.heure,unePers.date.minute,
			unePers.retour.annee,unePers.retour.mois,unePers.retour.jour,unePers.retour.heure,unePers.retour.minute);     
		}	
	}else{
          	printf("Cet identifiant n'existe pas\n");
          	printf("Tapez O pour l'ajout des informations de cet emprunt");
          	fflush(stdin);
          	reponse = toupper(getchar());
	        if (reponse == 'O' || cestLui == NULL){
			viderBuffer();
	        	demanderss(&unePers);        
		  	insererss(P, unePers, avant);
		  	fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",unePers.index,unePers.id,unePers.nom,unePers.Titre,unePers.Auteur,
			unePers.date.annee,unePers.date.mois,unePers.date.jour,unePers.date.heure,unePers.date.minute,
			unePers.retour.annee,unePers.retour.mois,unePers.retour.jour,unePers.retour.heure,unePers.retour.minute);     
		}
	}
}
/*
 *@function modifier permet de modifier une information dans la liste chainée 
 *et modifie le contenu du fichier emprunt.txt 
 *@param pointeur *
 *@return void
 */

void modifierss(pointeurs * P){
	pointeurs  cestLui, avant, tempo ;
	int aModifier;
	char reponse ;
	Emprunt nouvPers ;
	FILE *donnees = NULL;
	donnees = fopen("emprunt.txt","r+");
        do{ 
		viderBuffer();        	
		printf("Entrez l'identifiant de l'emprunt à modifier ses informations ");
         	scanf("%d", &aModifier);
         	findss(aModifier, *P, &avant, &cestLui );
         	reponse = 'N';
        if (cestLui != NULL){
        	printf("On l'a trouvé : \n");
        	afficherss(cestLui->emp);
          	printf("\n\n");
		viderBuffer();
          	printf("Désirez-vous modifier les informations de cet emprunt ?(O/N) ");
          	fflush(stdin);
          	reponse = toupper(getchar());
          	if (reponse == 'O'){
			 demanderss( &nouvPers);
	                 if ( nouvPers.index == (cestLui->emp).index ){
           		         cestLui->emp = nouvPers;
           		 }else{
                  		eliminerss( P, avant, cestLui);
                  		findss( nouvPers.index, *P, &avant, &cestLui);
                  		insererss(P, nouvPers, avant);
			  	fprintf(donnees,"%d %d %s %s %s  %d %d %d %d %d  %d %d %d %d %d",nouvPers.index,nouvPers.id,nouvPers.nom,nouvPers.Titre,
				nouvPers.Auteur,nouvPers.date.annee,nouvPers.date.mois,nouvPers.date.jour,nouvPers.date.heure,nouvPers.date.minute,
				nouvPers.retour.annee,nouvPers.retour.mois,nouvPers.retour.jour,nouvPers.retour.heure,nouvPers.retour.minute);     

                 	 }
            	}
        }else{
        	printf("Désolé! on ne trouve pas cet emprunt\n");
		viderBuffer();
         	printf("avez-vous autre emprunt à modifier (O/N) ? ");
         	fflush(stdin);
	}
        }while (toupper(getchar()) != 'N');
}      
/*
 *@function traiter permet de traiter le choix de l'utilisateur  
 *@param char,pointeur *
 *@return void
 */
void traiterss( char choix, pointeurs *L){
	switch(choix){
 		case 'V' : visualiserss( *L );
                 	   break;
		case 'C' : chercherss( *L );
	                   break ;
		case 'S' : supprimerss(L);
	                   break;
		case 'A' : ajouterss(L);
	                   break;
		case 'M' : modifierss(L);
	                   break;
		case 'I' : inverserss(L); /* inverser la liste */
	                   visualiserss(*L);
          	           inverserss(L); /* remettre dans l'ordre FIFO */
	                   break;
		case 'R' : menu();
			   break;
		case 'N' : system("clear");
		break;

	}
}

