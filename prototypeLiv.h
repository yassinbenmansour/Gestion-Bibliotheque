/******** prototypes functions structure adherent **********/
void affichers(Livre unePers);
void obtenirs(char *pt);
void demanders(Livre *ptr );
void lires(FILE * donnees, Livre *P);
void visualisers( pointeux liste);
void creerFIFOs(pointeux *L);
void inserers(pointeux *P, Livre unePers, pointeux avant);
void finds(int aChercher, pointeux liste, pointeux *av, pointeux *cl);
void inversers(pointeux *L);
void cherchers(pointeux liste);
void eliminers(pointeux *P, pointeux avant, pointeux cestLui);
void supprimers(pointeux *P);
void ajouters(pointeux *P);
void modifiers(pointeux *P);
void traiters(char choix, pointeux *L);

