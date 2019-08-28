#include "cellule.h"

//******************************************************************************
// Le type 'foret' contenant des parcelles (de type cellules) :
//******************************************************************************

typedef struct 
{
	int longueur;
	int largeur;
	Cellule** cases;
} foret; 

/* 
	Ici la foret est représentée dans une matrice de dimension longeur x largeur, où chaque élément est une cellule (définie dans cellule.h).
*/


/* ----------------------------RAPPEL DES REGLES------------------------------ : 
 * Pour simuler la propagation de ce feu de forêt, des règles ont été défnies :
 - si une case se trouvant à la ième ligne et jème colonne [i,j], est en feu au tour t de
simulation et son degré est à 2, alors elle devient en cendres au tour d'après t+1
 - si une case [i,j] est en cendres à l'étape t, alors elle devient en cendres éteintes au tour
suivant t+1.
 - si une case [i,j] est un arbre ou un rocher ou de l'herbe ou une feuille et qu'au moins
un de ses 8 voisins est en feu alors la case [i,j] sera en feu à t+1 et son
degré diminue de 1
 - si une case [i,j] est en feu et que son degré est > à 2, alors on le réduit de 1
 - si une case [i,j] contient de l'eau ou du terrain, rien ne se passe.
  */ 
  
  
//******************************************************************************
// La déclaration des fonctions applicables à une foret
// (prototypes des fonctions)
//******************************************************************************

/*
 * Fonction qui créer en mémoire une foret
 * Paramètre longueur : nombre strictement positif de lignes de la matrice Cellule
 * Paramètre largeur : nombre strictement positif de colonnes de la matrice Cellule
 * Retour : accès (à la zone mémoire) à la forêt créée
 */
foret* creation_foret(int longueur, int largeur);

/* Fonction qui génère un nombre aléatoire entre 1 et une valeur maximum
 * Paramètre valeur_max : nombre positif qui définit la borne supérieure de l'intervalle dans lequel va etre crée le nombre aléatoire
 * Retour : nombre aléatoire entre 1 et valeur_max
 */
int generation_alea_int(int valeur_max);

/* Fonction qui permet de sélectionner aléatoirement le type d'une case
 * Paramètre _foret : un accès mémoire (pointeur) vers la forêt
 * Paramètre ligne : ligne de la case où l'on va selectionner un type
 * Paramètre colonne : colonne de la case où l'on va selectionner un type
 */
void choix_alea(foret* _foret, int ligne, int colonne);

/* Fonction qui determine le degre en fonction du type de la cellule
 * Paramètre type_case : le type de la case considérée
 */

/* Fonction qui remplit aléatoirement chaque case de la forêt
 * Paramètre _foret : un accès mémoire (pointeur) vers la forêt
 */
void remplissage_aleatoire_foret(foret* _foret);

/* Fonction qui permet d'initialiser l'incendie dans la forêt en choissant une case de manière aléatoire
 * Paramètre : un accès mémoire (pointeur) vers la forêt
 */
void initialise_feu(foret* _foret);

/* Fonction qui retourne le nombre de voisins en feu au tour d'une case passée en paramètre
 * Paramètre _foret : un accès mémoire (pointeur) vers la forêt
 * Paramètre indL : ligne de la case considérée
 * Paramètre indC :  colonne de la case considérée
 * retour : Nombre de voisins en feu autour de la case
 */
int nb_voisins_feu(foret* _foret, int indL, int indC);

/* Fonction qui libère la zone mémoire occupée par une forêt
 * Paramètre _foret : un accès émoire (pointeur) vers la forêt
 */
void liberation_foret(foret* _foret);

/* Fonction qui copie une foret dans une autre foret
 * Paramètre nouvelle : un accès mémoire (pointeur) vers la forêt a remplir
 * Paramètre ancienne : un accès mémoire (pointeur) vers la forêt dont les valeurs vont être copiées
 */
void copier_foret(foret* nouvelle, foret* ancienne);