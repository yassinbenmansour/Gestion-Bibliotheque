/******** prototypes functions structure adherent **********/
void afficherss(Emprunt emprunt);
void obtenirss(char *pt);
void demanderss(Emprunt *emp);
void liress(FILE * donnees, Emprunt *P);
void visualiserss( pointeurs liste);
void creerFIFOss(pointeurs * L);
void insererss(pointeurs * P, Emprunt unePers, pointeurs avant);
void findss(int aChercher, pointeurs liste, pointeurs * av, pointeurs * cl);
void inverserss( pointeurs * L );
void chercherss(pointeurs liste);
void eliminerss( pointeurs * P, pointeurs avant, pointeurs cestLui);
void supprimerss(pointeurs * P);
void ajouterss(pointeurs * P);
void modifierss(pointeurs * P);
void traiterss( char choix, pointeurs * L );
