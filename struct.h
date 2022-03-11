//definition des structures du projet
typedef struct Adherent Adherent;
typedef struct Livre Livre;
typedef struct Emprunt Emprunt;
typedef struct Date Date;

typedef struct Element Element;
typedef struct Elements Elements;
typedef struct Liste Liste;
/*déclaration de type pointeur vers les élèments de la liste*/
typedef Element *pointeur;
typedef Elements *pointeurs;
typedef Liste *pointeux;
/*
 *structure type Date
 *@param année
 *@param mois
 *@param jour
 *@param heure
 *@param minute
 */
struct Date{
	int annee;
	int mois;
	int jour;
	int heure;
	int minute;
	int seconde;
};
/*
 *structure type adherent
 *@param int index
 *@param char*
 *@param char*
 *@param int
 *@param int
 */

struct Adherent{
	int index;
	char nom[50];
	char prenom[50];
	int NbEmprunts;
	Date date; 
};
/*
 *structure type Element (structure de controle de la structure adherent)
 *déclaration de type element pour  chaque element de la liste
 *@param type Adherent 
 *@param type Element*
 */
struct Element{
	Adherent pers;
	Element *suivant; 
};
/*
 *structure type adherent
 *@param int index
 *@param char*
 *@param char*
 *@param int
 *@param int
 */

struct Livre{
	int index;
	char Titre[100];
	char Auteur[100];
	int disponible;
	int stock;
};
/*
 *structure type Element (structure de controle de la structure adherent)
 *@param type Livre 
 *@param type Liste*
 */
struct Liste{
	Livre liv;
	Liste *suivant;
};
/*
 *structure type Emprunt
 *@param int index
 *@param char*
 *@param char*
 *@param char*
 *@param date
 *@param date
 */

struct Emprunt{
	int index;
	int id;
	char nom[100];
	char Titre[100];
	char Auteur[100];
	Date date;
	Date retour;
};
/*
 *structure type Elements (structure de controle de la structure adherent)
 *@param type Emprunt 
 *@param type Elements *
 */
struct Elements{
	Emprunt emp;
	Elements *suivant;
};

void menu();
