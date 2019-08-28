//******************************************************************************
// Le type enum 'type' qui regroupe sous un meme ensemble les différents types de cellules possibles : 
//******************************************************************************

typedef enum 
{
	terrain, arbre, feuille, rocher, herbe, eau, cendres, cendres_eteintes
} type;

//******************************************************************************
// Le type 'Cellule' contenant 3 informations : 
// 1. Son type (terrain, arbre, rocher, herbe, eau, cendres, cendres_eteintes)
// 2. Son degre indiquant si elle va bruler rapidement (0, 1, 2, 3, 4 ,5)
// 3. Son etat (en feu : 1 ou pas : 0)
//******************************************************************************

typedef struct 
{
	type type_case;
	unsigned int degre;
	int etat;
} Cellule;


//******************************************************************************
// La déclaration des fonctions applicables à une foret
// (prototypes des fonctions)
//*****************************************************************************


/* Fonction qui retourne le type de la case en fonction d'une valeur entre 1 et 7
 * Paramètre rang : nombre > 0 qui définira le type de la case
 * Retour : type de la case de la forêt
 */
type conversion_type(int rang);

/* Fonction qui determine le degre en fonction du type de la cellule
 * Paramètre type_case : le type de la case considérée
 */
int type_to_degre(type type_case);

/* Fonction qui affiche un caractère d'une foret en fonction de son type 
 * Paramètre type_cellulle : le type de la cellule à afficher
 */
void afficher_caractere(type type_cellule, int etat);