#include "foret.h"
#include <stdlib.h>

foret* creation_foret(int longueur, int largeur){
	foret* Foret = NULL;
	//Allocation de l'espace global pour une forêt
	Foret = (foret*)malloc(sizeof(foret));
	
	//si l'allocation en mémoire a réussie
	if(Foret != NULL){
		
		//On affecte la longueur et largeur passée en patramètre a la forêt
		Foret -> longueur = longueur;
		Foret -> largeur = largeur;
		
		//On affecte l'espace mémoire pour la matrice de cases constituant les parcelles
		Foret -> cases = (Cellule**)malloc(longueur * sizeof(Cellule*));
		
		//on parcourt chaque ligne pour allouer de l'espace mémoire à chaque colonne
		for(int i = 0; i < longueur; i++){
			Foret -> cases[i] = (Cellule*)malloc(largeur * sizeof(Cellule));
		}
	}
	return Foret;
}

int generation_alea_int(int valeur_max){
	int alea = 0;
	do{
		alea = 1 + rand() / (RAND_MAX / valeur_max);
	} while(alea > valeur_max);
	return alea;
}

void choix_alea(foret* Foret, int ligne, int colonne){
	
	//on vérifie que le pointeur sur la foret existe
	if(Foret != NULL){
		//on stocke la longueur et la largeur dans des variables pour plus de lisibilité
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		//On verifie que les lignes et colonne rentrées en paramètre sont valides
		if(ligne >= 0 && ligne < lignes_foret && colonne >= 0 && colonne < colonnes_foret){
			
			//On génère un nombre aléatoire entre 1 et 6 (car on ne peut pas mettre de cendres et de cendres eteintes au départ)
			int nombre_aleatoire = generation_alea_int(6);
			
			//On determine le type avec ce nombre aléatoire
			type nouveau_type = conversion_type(nombre_aleatoire);
			//On determine le degre avec le type
			int nouveau_degre = type_to_degre(nouveau_type);
			//le nouveau etat vaut tout le temps 0
			int nouveau_etat = 0;
			
			//On l'affecte dans la case considérée
			Foret -> cases[ligne][colonne].type_case = nouveau_type;
			Foret -> cases[ligne][colonne].etat = nouveau_etat;
			Foret -> cases[ligne][colonne].degre = nouveau_degre;
		}
	}
}

void remplissage_aleatoire_foret(foret* Foret){
	if(Foret != NULL){
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		//On remplit les cases en parcourant lignes et colonnes
		for(int i = 0; i < lignes_foret; i++){
			for(int j = 0; j < colonnes_foret; j++){
				choix_alea(Foret, i, j);
			}
		}
	}
}

void initialise_feu(foret* Foret){
	if(Foret != NULL){
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		//On génère un emplacement aléatoire parmi les cases de la forêt
		int index_l_alea = generation_alea_int(lignes_foret) - 1; //entre (1 et valeur_max) - 1 soit 0 et valeur_max - 1
		int index_c_alea = generation_alea_int(colonnes_foret) - 1;
		
		//on cherhce une case qui n'est ni de l'eau ni du terrain
		while(Foret -> cases[index_l_alea][index_c_alea].type_case == eau || Foret -> cases[index_l_alea][index_c_alea].type_case == terrain){
			index_l_alea = generation_alea_int(lignes_foret) - 1;
			index_c_alea = generation_alea_int(colonnes_foret) - 1;
		}
		
		//On mets la case en feu en modifiant son etat (si et seulement si le type n'est ni un terrain ni de l'eau, son type reste inchangé et son degré changera plus tard
		if(Foret -> cases[index_l_alea][index_c_alea].type_case != terrain && Foret -> cases[index_l_alea][index_c_alea].type_case != eau && Foret -> cases[index_l_alea][index_c_alea].type_case != cendres_eteintes){
			Foret -> cases[index_l_alea][index_c_alea].etat = 1;
		}
	}
}

int nb_voisins_feu(foret* Foret, int indL, int indC){
	int resultat = 0;
	if(Foret != NULL){
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		//On parcours les 8 voisins de la case à indL et indC (soit 2 lignes et 2 colonnes au plus)
		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++){
				//si la case parcourue existe dans la matrice de la forêt 
				if((i + indL) >= 0 && (i + indL) < lignes_foret && (j + indC) >= 0 && (j + indC) < colonnes_foret){
					//si la case est en feu et que il ne s'agit pas de la case en position indL et indC (elle-même)
					if(Foret -> cases[i + indL][j + indC].etat == 1 && !(i == 0 && j == 0)){
						resultat++;
					}
				}
			}
		}
	}
	return resultat;
}

void liberation_foret(foret* Foret){
	if(Foret != NULL){
		//on libère chaque ligne
		for(int i = 0; i < Foret -> longueur; i++){
			free(Foret -> cases[i]);
		}
		//puis on libère tout le contenu de la matrice une foit qu'on s'est assurée que chaque lignes est libérée
		free(Foret -> cases);
	}
	//enfin, on libère l'ensemble de l'espace mémoire occupé par la forêt
	free(Foret);
}

void copier_foret(foret* nouvelle, foret* ancienne){
	//si les deux forets existent (pointeurs alloues)
	if(nouvelle != NULL && ancienne != NULL){
		//si elles ont les mêmes dimensions
		if(nouvelle -> longueur == ancienne -> longueur && nouvelle -> largeur == ancienne -> largeur){
			int longueur = nouvelle -> longueur;
			int largeur = nouvelle -> largeur;
			//On declare les caractéristiques d'une case dans des variables temporaires
			int degre, etat;
			type type_case;
			//on parcourt toutes les cases pour les copier
			for(int i = 0; i < longueur; i++){
				for(int j = 0; j < largeur; j++){
					//on passe par des variables intermediaires afin de ne pas modifier l'ancienne foret
					degre = ancienne -> cases[i][j].degre;
					etat = ancienne -> cases[i][j].etat;
					type_case = ancienne -> cases[i][j].type_case;
					//on affecte les valeurs a la nouvelle foret
					nouvelle -> cases[i][j].degre = degre;
					nouvelle -> cases[i][j].etat = etat;
					nouvelle -> cases[i][j].type_case = type_case;
				}
			}
		}
	}
}