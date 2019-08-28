#include "cellule.h"

type conversion_type(int rang){
	type resultat = 0;
	switch(rang){
		case 1: resultat = herbe;
		break;
		case 2: resultat = arbre;
		break;
		case 3: resultat = terrain;
		break;
		case 4: resultat = feuille;
		break;
		case 5: resultat = eau;
		break;
		case 6: resultat = rocher;
		break;
		case 7: resultat = cendres;
		break;
		case 8: resultat = cendres_eteintes;
		break;
	}
	return resultat;
}

int type_to_degre(type type_case){
	int resultat = 0;
	switch(type_case){
		//On ne traite que les cas ou degre != 0 car on a initilaisé le resultat à 0
		case arbre: resultat = 4;
		break;
		case feuille: resultat = 2;
		break;
		case rocher: resultat = 5;
		break;
		case herbe: resultat = 3;
		break;
		case cendres: resultat = 1;
		break;
	}
	return resultat;
}

// Le corps de la focntion afficher_caractère n'est pas codé ici mais dans le main car il s'agit d'une fonction d'affichage

