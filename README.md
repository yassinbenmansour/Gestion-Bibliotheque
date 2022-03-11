# gestion-biblio


Pour effet la compilation de cette programme on utilisera
logiciel Dev-C++.



menu
- A pour sortir de l'application
- B pour les fonctionnalites des eleve
- C pour les fonctionnalites des livres
- D pour les fonctionnalites des emprunts
Default
Erreur, information inexistante...


Choix A   A pour sortir de l'application function permet d'obtenir le choix pour l’option sorti
Desirez vous vraiment quitter l'application (O/N)?:
O pour Quitter
N pour retourner   l'application   menu()
default
ceci n'apparait pas dans la liste de choix...


choix B   B pour les fonctionnalites des eleve
function permet d'obtenir le choix pour l’option fonctionnalites des eleve

choix
Q pour Quitter
V pour Visualiser
C pour Chercher
A pour Ajouter un nouvel eleve
M pour Modifier les informations d'un eleve
S pour Supprimer un eleve de la liste
R pour retourner au menu principal

Suposons on veut visualiser ou bien afficher les informations
function affiche permet d'afficher les informations
void afficher(Eleve elv){
printf("\n\n code: %6d\n",adherent.code);
printf("nom: %s\n",elv.nom);
printf("prenom: %s\n",elv.prenom);
printf("nombre d'emprunts: %d\n",elv.NbEmprunts);
}

Choix C   - C pour les fonctionnalites des livres
function obtenir permet d'obtenir les fonctionnalites des livres

Q pour Quitter
V pour Visualiser
C pour Chercher
A pour Ajouter un nouvel livre
M pour Modifier les informations d'un livre
S pour Supprimer un livre de la liste
R pour retourner au menu principal

fonction affiche permet d'afficher les informations d'un livre

void affichers(Livre livre){
printf("\n\n ref: %d\n",livre.ref);
printf("titre: %s\n",livre.Titre);
printf("nombre d'emprunts: %d\n",livre.disponible);
printf("Liste d'emprunts: %d\n",livre.stock);
}

function lire permet de lire les informations dans le fichier livre.txt
void lires(FILE * donnees, Livre *P){
fscanf(donnees,"%d%s%s%d%d \n", &(P->ref), P->Titre,
&(P->disponible), &(P->stock));
}

Choix D   D pour les fonctionnalites des emprunts
function obtenir permet d'obtenir les fonctionnalites des enprunts
Q pour Quitter
V pour Visualiser
C pour Chercher
A pour Ajouter un nouvel livre
M pour Modifier les informations d'un livre
S pour Supprimer un livre de la liste
R pour retourner au menu principal

function afficherss permet d'afficher les informations sur l'emprunts

void afficherss(Emprunt emprunt){
printf("\n\n code: %6d\n",emprunt.code);
printf("l'identifiant d eleve: %d\n",emprunt.id);
printf("nom eleve : %s\n",emprunt.nom);
printf("Titre de l'ouvrage: %s\n",emprunt.Titre);
printf("Date d'emprunt:%d/%d/%d%d:%d
\n",emprunt.date.annee,emprunt.date.mois,emprunt.date.jour,
emprunt.date.heure,emprunt.date.minute);
printf("Date retour: %d/%d/%d %d:%d
\n",emprunt.retour.annee,emprunt.retour.mois,emprunt.retour.jour
,emprunt.retour.heure,emprunt.retour.minute);
}
function demander permet de recuperer les informations sur
l'emprunt
void demanderss(Emprunt *emp){
Emprunt perso;
printf("Entrez les informations de l'emprunt : \n");
printf(" - ref : ");
scanf("%d",&(perso.ref));
fflush(stdin);
viderBuffer();
printf(" - identifiant deleve: ");
scanf("%d",&(perso.id));
fflush(stdin);
viderBuffer();
printf(" - nom eleve: ");
scanf("%s",perso.nom);
viderBuffer();
printf(" - Titre de l'ouvrage : ");
scanf("%s",perso.Titre);
viderBuffer();
printf(" - date d'emprunt : \n");
printf("\t - jour :");
scanf("%d",&(perso.date.jour));
printf("\t - mois :");
scanf("%d",&(perso.date.mois));
printf("\t - ann e :");
scanf("%d",&(perso.date.annee));
printf("\t - heure :");
scanf("%d",&(perso.date.heure));
printf("\t - minute :");
scanf("%d",&(perso.date.minute));
printf(" - date de retour : \n");
printf("\t - jour :");
scanf("%d",&(perso.retour.jour));
printf("\t - mois :");
scanf("%d",&(perso.retour.mois));
printf("\t - ann e :");
scanf("%d",&(perso.retour.annee));
printf("\t - heure :");
scanf("%d",&(perso.retour.heure));
printf("\t - minute :");
scanf("%d",&(perso.retour.minute));
*emp = perso;
}
Les structure utiliser
Struct.h
struct Date{
int annee;
int mois;
int jour;
int heure;
int minute;
int seconde;
};
struct eleve{
int ref;
char nom[50];
int NbEmprunts;
Date date;
};
struct Livre{
int ref;
char Titre[100];
int disponible;
int stock;
};
struct Emprunt{
int ref;
int id;
char nom[100];
char Titre[100];
Date date;
Date retour;
};
struct Element{
elev pers;
Element *suivant;
};
Pour la cr ation de cet programme on a rencontre de probl me au
niveau de la cr ation de l’application et son ex cution.
Au fur du temps, on a r ussit a r soudre tout le probl me de
l’application gr ce au travail de groupe.
