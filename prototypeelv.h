/******** prototypes functions structure adherent **********/
void afficher(Adherent unePers);
void obtenir(char *pt);
void demander( Adherent *ptr );
void lire(FILE * donnees, Adherent *P);
void visualiser( pointeur liste);
void creerFIFO(pointeur * L);
void inserer(pointeur * P, Adherent unePers, pointeur avant);
void find(int aChercher, pointeur liste, pointeur * av, pointeur * cl);
void inverser( pointeur * L );
void chercher(pointeur liste);
void eliminer( pointeur * P, pointeur avant, pointeur cestLui);
void supprimer(pointeur * P);
void ajouter(pointeur * P);
void modifier(pointeur * P);
void traiter( char choix, pointeur * L );
void viderBuffer();
void viderBuffered(int n, char chaine[]);
