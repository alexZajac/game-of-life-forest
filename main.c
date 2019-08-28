#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "foret.h"


// ######################### PROTOTYPES DES FONCTIONS DU MAIN ####################################


/* Fonction qui affiche une forêt 
 * Paramètre Foret : un accès mémoire (pointeur) vers la forêt
 */
void affiche_foret(foret* Foret);

/* Fonction qui affiche une forêt en montrant le type pour chaque case 
 * Paramètre Foret : un accès mémoire (pointeur) vers la forêt
 */
void affiche_foret_type(foret* Foret);

/* Fonction qui affiche un caractère pour une cellule donnée
 * Paramètre type_cellule : type de la cellule à afficher
 * Paramètre état : etat de la cellule à afficher
 */
void afficher_caractere(type type_cellule, int etat);

/* Fonction qui affiche une forêt en montrant l'etat pour chaque case 
 * Paramètre Foret : un accès mémoire (pointeur) vers la forêt
 */
void affiche_foret_etat(foret* Foret);

/* Fonction qui affiche une forêt en montrant le degre pour chaque case 
 * Paramètre Foret : un accès mémoire (pointeur) vers la forêt
 */
void affiche_foret_degre(foret* Foret);

/* Fonction qui affiche le menu général au lancement
 */
void menu();

/* Fonction qui laisse choisir a l'utilisateur une option de menu
 * Retour : entier representant le choix parmi les options du menu
 */
int choix_menu();

/* Fonction qui laisse choisir a l'utilisateur une option de type de case au moment de la creation de foret (ni cendres ni cendres eteintes car cette fonction sert d'initilaisation pour la foret)
 * Paramètre ligne : ligne de la case en concernée
 * Paramètre colonne : colonne de la case en concernée
 * Retour : entier representant le choix parmi les options de types de cases
 */
int choix_type_case(int ligne, int colonne);

/* Fonction qui laisse choisir a l'utilisateur une option qui est soir oui, soit non
 * Retour : entier representant le choix (oui ou non)
 */
int choix_binaire();

/* Fonction qui laisse choisir a l'utilisateur une option de changer soit le type, soit le degre soit l'etat d'une case
 * Retour : entier representant le choix parmi les options type, etat et degre
 */
int choix_interrompre_changer();

/* Fonction qui laisse choisir a l'utilisateur une option parmi tous les types de cases
 * Retour : entier representant le choix parmi les options de types de cases
 */
int choix_parmi_types();

/* Fonction qui laisse choisir a l'utilisateur une option parmi tous les etats de cases (0 ou 1)
 * Retour : entier representant le choix parmi les options allumé et éteint
 */
int choix_parmi_etats();

/* Fonction qui laisse choisir a l'utilisateur une option parmi tous les types de degrés
 * Retour : entier representant le choix parmi les options de degrés (0,1,2,3,4,5)
 */
int choix_parmi_degres();

/* Fonction qui permet un remplissage manuel de la Foret
 * Paramètre Foret : un accès mémoire vers la foret
 */
void remplissage_manuel(foret* Foret);

/* Fonction qui permet un remplissage manuel de la Foret
 * Paramètre Foret : un accès mémoire vers la foret
 */
void simulation(foret* Foret);

/* Fonction qui permet à l'utilisateur de placer un point de démarrage du feu dans la forêt
 * Paramètre Foret : un accès mémoire vers la foret
 */
void initialise_feu_utilisateur(foret* Foret);

/* Fonction qui propage l'incendie en fonction des règles dans la forêt apres avoir choisi un nombre de tours, et un point de déclenchement (appellée dans la fonction simulation)
 * Paramètre Foret : un accès mémoire vers la foret
 * Paramètre tours : nombre de tours de propagation du feu
 */
void simulation_incendie(foret* Foret, int tours);

/* Fonction qui permet à l'utilisateur d'interrompre et changer une caractéristiques de la forêt
 * Paramètre Foret : un accès mémoire vers la foret
 */
void interrompre_changer(foret* Foret);
 


//######################### FONCTION CONTENANT DE L'AFFICHAGE ####################################



void affiche_foret(foret* Foret){
	//Afficher une foret consiste a afficher ses symboles (representant le type de la case), chaque case est en noir si elle ne brule pas et rouge si elle brule, ensuite, on affiche le degre de chaque case pour pouvoir suivre le déroulement de la simulation 
	affiche_foret_type(Foret);
	affiche_foret_degre(Foret);
}

void affiche_foret_type(foret* Foret){
	if(Foret != NULL){
		
		//on declare deux varaibles contenant les lignes et colonnes de la foret
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		printf("------------------------ TYPE DES CASES -------------------------\n\n");
		
		//On parcourt les lignes et colonnes en affichant les éléments
		for(int i = 0; i < lignes_foret; i++){
			for(int j = 0; j < colonnes_foret; j++){
				//On affiche un caractère en fonction d'un type
				afficher_caractere(Foret -> cases[i][j].type_case, Foret -> cases[i][j].etat);
			}
			//On saute une ligne a la fin de chaque colonne
			printf("\n");
		}
		printf("\n");
	}
}

void afficher_caractere(type type_cellule, int etat){
	
	//on déclare une variable nous permettant de manipuler la console
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//si la case brule
	if(etat == 1){
		//On mets sa couleur de fond a rouge
		SetConsoleTextAttribute(hconsole, BACKGROUND_RED);
	}
	else{
		//on mets sa couleur d'ecriture a blanc (r,g,b)
		SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	switch(type_cellule){
		case herbe: printf("| x |");
		break;
		case arbre: printf("| * |");
		break;
		case terrain: printf("| + |");
		break;
		case feuille: printf("|   |");
		break;
		case eau: printf("| / |");
		break;
		case rocher: printf("| # |");
		break;
		case cendres: printf("| - |");
		break;
		case cendres_eteintes: printf("| . |");
		break;
	}
	//dans tous les cas on remets le texte en blanc après avoir affiché le symbole
	SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void affiche_foret_etat(foret* Foret){
	if(Foret != NULL){
		
		//on declare deux varaibles contenant les lignes et colonnes de la foret
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		printf("-------------------- ETAT DES CASES --------------------\n\n");
		//On parcourt les lignes et colonnes en affichant les éléments
		for(int i = 0; i < lignes_foret; i++){
			for(int j = 0; j < colonnes_foret; j++){
				//On affiche un caractère en fonction d'un type
				printf("| %d |", Foret -> cases[i][j].etat);
			}
			//On saute une ligne a la fin de chaque colonne
			printf("\n");
		}
		printf("\n\n");
	}
}

void affiche_foret_degre(foret* Foret){
	if(Foret != NULL){
		
		//on declare deux varaibles contenant les lignes et colonnes de la foret
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		printf("------------------------ DEGRE DES CASES ------------------------\n\n");
		
		//On parcourt les lignes et colonnes en affichant les éléments
		for(int i = 0; i < lignes_foret; i++){
			for(int j = 0; j < colonnes_foret; j++){
				//On affiche un caractère en fonction d'un type
				printf("| %d |", Foret -> cases[i][j].degre);
			}
			//On saute une ligne a la fin de chaque colonne
			printf("\n");
		}
		printf("\n");
	}
}



//######################### FONCTION DU MENU ET CHOIX ####################################



void menu(){
	//On définit le couleur d'ecriture en blanc pur
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	printf("Bienvenue dans le probleme 1 : La propagation de l'incendie! \n\n");
	//On demande la longueur et largeur de la foret a l'utilisateur
	int longueur, largeur;
	printf("Rentrez une longueur (positive) pour la foret! \n");
	scanf("%d", &longueur);
	printf("Rentrez une largeur (positive) pour la foret! \n");
	scanf("%d", &largeur);
	//on traite les cas ou la longueur et/ou la largeur sont negatives
	if(longueur < 0){
		longueur *= -1;
	}
	if(largeur < 0){
		largeur *= -1;
	}
	//Creation de la foret
	foret* Foret = creation_foret(longueur, largeur);

	//si l'allocation mémoire a fonctionnée
	if(Foret != NULL){
		//il n'y a pas encore de premier choix
		int choix_precedent = -1;
		//on demande un choix parmi les options du menu
		int choix = choix_menu();
		
		while(choix != 5){
			
			switch(choix){
				//CHOIX 1
				case 1: 
					choix_precedent = choix;
					remplissage_aleatoire_foret(Foret);
					affiche_foret(Foret);
					choix = choix_menu();
					break;
				//CHOIX 2
				case 2: 
					choix_precedent = choix;
					remplissage_manuel(Foret);
					affiche_foret(Foret);
					choix = choix_menu();
					break;
				//CHOIX 3
				case 3: 
					if(choix_precedent != -1){
						choix_precedent = choix;
						simulation(Foret);
					}
					else{
						printf("Impossible de interrompre et changer sans avoir rempli la foret!\n");
					}
					choix = choix_menu();
					break;
				//CHOIX 4
				case 4: 
					if(choix_precedent != -1){
						choix_precedent = choix;
						interrompre_changer(Foret);
						affiche_foret(Foret);
					}
					else{
						printf("Impossible de interrompre et changer sans avoir rempli la foret!\n");
					}
					choix = choix_menu();
					break;
				//CHOIX 5
				case 5: 
					liberation_foret(Foret);
					break;
				}
		}
	}
}

int choix_menu(){

	//on affiche le menu
	printf("\n--------------------- MENU ---------------------\n\n");
	printf("1. Remplir aleatoirement la foret.\n");
	printf("2. Remplir manuellement la foret.\n");
	printf("3. Simuler l'incendie.\n");
	printf("4. Interrompre et changer.\n");
	printf("5. Quitter.\n\n");
	printf("------------------------------------------------\n\n");
	printf("Selectionnez votre choix a l'aide d'un numero : \n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 5){
		printf("Choix non valide, reessayez ! \n");
		choix = choix_menu();
	}

	return choix;
}

int choix_type_case(int ligne, int colonne){
	
	//On affiche la case que l'utilisateur est en train de remplir
	printf("Case [%d, %d]: \n", ligne, colonne);
	printf("1. Herbe\n");
	printf("2. Arbre\n");
	printf("3. Terrain\n");
	printf("4. Feuille\n");
	printf("5. Eau\n");
	printf("6. Rocher\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 6){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_type_case(ligne, colonne);
	}

	return choix;
}

int choix_binaire(){
	
	//On affiche la case que l'utilisateur est en train de remplir
	printf("1. Oui\n");
	printf("2. Non\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 2){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_binaire();
	}

	return choix;
}

int choix_interrompre_changer(){
		//On affiche la case que l'utilisateur est en train de remplir
	printf("1. Type\n");
	printf("2. Etat\n");
	printf("2. Degre\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 3){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_interrompre_changer();
	}

	return choix;
}

int choix_parmi_types(){
	//On affiche la case que l'utilisateur est en train de remplir
	printf("1. Herbe\n");
	printf("2. Arbre\n");
	printf("3. Terrain\n");
	printf("4. Feuille\n");
	printf("5. Eau\n");
	printf("6. Rocher\n");
	printf("5. Cendres\n");
	printf("6. Cendres eteintes\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix <= 0 || choix > 8){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_parmi_types();
	}

	return choix;
}

int choix_parmi_etats(){
	//On affiche la case que l'utilisateur est en train de remplir
	printf("Eteindre (tapez 0)\n");
	printf("Allumer (tapez 1)\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix < 0 || choix > 1){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_parmi_etats();
	}

	return choix;
}

int choix_parmi_degres(){
	//On affiche la case que l'utilisateur est en train de remplir
	printf("0\n");
	printf("1\n");
	printf("2\n");
	printf("3\n");
	printf("4\n");
	printf("5\n\n");
	int choix;
	scanf("%d", &choix);
	printf("\n");
	
	//si le choix n'est pas valide on rappelle recursivement la fonction
	if(choix < 0 || choix > 5){
		printf("Choix non valide, reessayez ! \n\n");
		choix = choix_parmi_degres();
	}

	return choix;
}



//######################### CHOIX DU MENU (2, 3, 4) ####################################



//CES FONCTIONS SONT ORGANISEES EN FONCTIONS DES 4 CHOIX POSSIBLES DU MENU (LE 1ER CHOIX EST UNE FONCTION DEJA CODEE DANS LE FORET.C), ET REAFFICHEES A CHAQUE ACTIONS DE L'UTILISATEUR
//CHAQUE PARTIE CONTIENT UNE FONCTION PRINCIPALE (APPELEE DANS LE SWITCH GENERAL DU MENU) ET/OU DES SOUS-FONCTIONS POUR UNE MEILLEUR LISIBILITE

//------------------ Choix: 2 - Remplissage manuel -----------------------------

void remplissage_manuel(foret* Foret){
	
	printf("Vous avez choisi le remplissage manuel : \n\n");
	
	//On vérifie toujours la validité du pointeur sur la Foret en paramètre
	if(Foret != NULL){
		int longueur = Foret -> longueur;
		int largeur = Foret -> largeur;
		//Variable represntant le choix pour chaque case
		int choix_type;
		//tableau de type nous permettant d'acceder directement au type souhaité apres le choix de l'utilisateur (seuls ces types sont initialisables)
		type tab_type[] = {herbe, arbre, terrain, feuille, eau, rocher};
		
		for(int i = 0; i < longueur; i++){
			for(int j = 0; j < largeur; j++){
				
				//On récupère son choix
				choix_type = choix_type_case(i, j);
				//On l'affecte avec le tableau de type precedemment recupéré
				Foret -> cases[i][j].type_case = tab_type[choix_type - 1];
				//L'etat initial est toujours éteint
				Foret -> cases[i][j].etat = 0;
				//Le type est deduit avec la fonction type_to_degre
				Foret -> cases[i][j].degre = type_to_degre(tab_type[choix_type - 1]);
			}
		}
	}
}

//------------------ Choix: 3 - Simulation incendie -----------------------------

void simulation(foret* Foret){
	
	if(Foret != NULL){
		//Afficher un message de debut
		printf("Simulons un incendie !\n\n");
		
		//On demande le nombre de tours
		printf("Combien de tours doit durer la simulation ? \n");
		int tours;
		scanf("%d", &tours);
		
		//On demande a l'utilisateur s'il veut choisir un point de declenchement
		printf("\nPreferez-vous choisir un point de declechement, ou definir ce point aleatoirement ? \n");
		int choix = choix_binaire();
		
		//si oui, on le laisse choisir le point de declenchement
		if(choix == 1){
			initialise_feu_utilisateur(Foret);
		}
		//sinon, on initialise le feu aléatoirement
		else{
			initialise_feu(Foret);
		}
		
		printf("Voici la foret apres initialisation du feu (tour 0) : \n\n");
		affiche_foret(Foret);
		printf("\n");
		//peu importe le mode d'initialisation du feu, on lance la simulation de l'incendie
		simulation_incendie(Foret, tours);
	}
}

void initialise_feu_utilisateur(foret* Foret){
	
	//on se prépare a demander a l'utilisateur la case dans laquelle il veut initialiser le feu
	if(Foret != NULL){
		int lignes_foret = Foret -> longueur;
		int colonnes_foret = Foret -> largeur;
		
		//On demande un emplacement valide parmi les cases de la forêt
		int index_l, index_c; 
		printf("Entrez l'index de la ligne et de la colonne d'ou le feu va demarrer : \n");
		scanf("%d %d", &index_l, &index_c);
		
		//tant que la case rentrée n'est pas valide
		while(index_l < 0 || index_l >= lignes_foret || index_c < 0 || index_c >= colonnes_foret){
			printf("\nPosition non-valide, veuillez entrer une position valide : \n");
			scanf("%d %d", &index_l, &index_c);
		}
		
		//On mets la case en feu en modifiant son etat (si et seulement si le type n'est ni un terrain, ni de l'eau, son type reste inchangé et son degré changera plus tard
		if(Foret -> cases[index_l][index_c].type_case != terrain && Foret -> cases[index_l][index_c].type_case != eau && Foret -> cases[index_l][index_c].type_case != cendres_eteintes){
			Foret -> cases[index_l][index_c].etat = 1;
		}
	}
}

void simulation_incendie(foret* Foret, int tours){
	
	//On crée une forêt temporaire pour stocker le changement des etat/type/degre des cases et les appliquer ensuite au tour t + 1
	int lignes = Foret -> longueur;
	int colonnes = Foret -> largeur;
	foret* tour_suivant = creation_foret(lignes, colonnes);
	
	if(Foret != NULL && tour_suivant != NULL){
		//on propage l'incendie
		int tour_actuel = 1;
		//compteur de condition de stabilité
		int compteur_condition_de_stabilite = 0;
		
		//tant qu'il reste des tours
		while (tour_actuel <= tours){
			
			//on affiche le tour et la foret
			printf("-------------------------- TOUR : %d -----------------------------\n\n", tour_actuel);
			
			//on remet le compteur de stabilite à 0 car on effectue des vérifications sur ce-dernier en fin de tour
			compteur_condition_de_stabilite = 0;
			
			//on parcours toutes les cases pour le traitement
			for(int i = 0; i < lignes; i++){
				for(int j = 0; j < colonnes; j++){
					//On affecte la case de l'ancienne forêt a celle du tour suivant 
					tour_suivant -> cases[i][j] = Foret -> cases[i][j];
					
					//Puis on effectue les verifications de propagations
					//Règle 1
					if(Foret -> cases[i][j].etat == 1 && Foret -> cases[i][j].degre == 2){
						tour_suivant -> cases[i][j].type_case = cendres;
						tour_suivant -> cases[i][j].degre = 1;
					}
					//Règle 2
					else if(Foret -> cases[i][j].type_case == cendres){
						tour_suivant -> cases[i][j].type_case = cendres_eteintes;
						tour_suivant -> cases[i][j].degre = 0;
						tour_suivant -> cases[i][j].etat = 0;
					}
					//Règle 3
					else if((Foret -> cases[i][j].type_case == arbre || Foret -> cases[i][j].type_case == rocher || Foret -> cases[i][j].type_case == herbe || Foret -> cases[i][j].type_case == feuille) && nb_voisins_feu(Foret, i, j) >= 1 ){
						tour_suivant -> cases[i][j].etat = 1;
						//si une feuille brule, on la laisse bruler un tour pour que l'utilisateur la voit, puis elle se transforme en cendres au tout t + 1 (Règle 4)
						if(Foret -> cases[i][j].type_case != feuille){
							tour_suivant -> cases[i][j].degre -= 1;
						}
					}
					//Règle 5
					else if(Foret -> cases[i][j].etat == 1 && Foret -> cases[i][j].degre > 2){
						tour_suivant -> cases[i][j].degre -= 1;
					}
					//CONDITION DE STABILITE
					//si la case est de type eau, terrain, ou cendres_eteintes, on incremente le compteur de stabilité car elle ne pourra plus bruler
					if(tour_suivant -> cases[i][j].degre == 0){
						compteur_condition_de_stabilite++;
					}
				}
			}
			//on copie le contenu du tour suivant dans Foret afin de preparer les prochains tours
			copier_foret(Foret, tour_suivant);
			affiche_foret(Foret);
			printf("\n");
			
			//si le compteur_de_stabilite est égal au nombre de cases, alors le feu ne peu plus se propager
			if(compteur_condition_de_stabilite == lignes * colonnes){
				printf("CONDITION DE STABILITE ATTEINTE AU TOUR %d : La foret ne peut plus bruler. \n\n", tour_actuel);
				//on sort de la boucle 
				tour_actuel = tours + 1;
			}
			//sinon on demande a l'utilisateur s'il veut interrompre et changer
			else{
				printf("Voulez vous interrompre et changer ?\n");
				int choix_changement = choix_binaire();
				//si oui
				if(choix_changement == 1){
					interrompre_changer(Foret);
				}
			}
			//on passe au tour suivant
			tour_actuel++;
		}
		//On libère l'espace occupée par la foret temporaire
		liberation_foret(tour_suivant);
	}
}

//------------------ Choix: 4 -  Interrompre et changer -----------------------------

void interrompre_changer(foret* Foret){
	
	if(Foret != NULL){
		
		//on demande la case a modifier
		printf("Quelle case souhaitez-vous changer (ligne, colonne) : \n");
		int indL, indC;
		scanf("%d %d", &indL, &indC);
		
		int longueur = Foret -> longueur;
		int largeur = Foret -> largeur;
		
		//si elles sont valides
		if(indL >= 0 && indL < longueur && indC >= 0 && indC < largeur){
			
			//on demande quelle caractéristiques de la case il faut changer
			printf("Veuillez selectionner l'information a changer : \n");
			
			//on récupère le choix de changement
			int choix_changement = choix_interrompre_changer();
			
			//si l'utilisateur veut changer le type
			if(choix_changement == 1){
				type tab_type[] = {herbe, arbre, terrain, feuille, eau, rocher, cendres, cendres_eteintes};
				int choix_type = choix_parmi_types();
				//on place le nouveau type dans une variable par soucis de clarté
				type nouveau_type = tab_type[choix_type - 1];
				//on affecte le nouveau type
				Foret -> cases[indL][indC].type_case = nouveau_type;
				//s'il place des cendres_eteintes, de l'eau ou du terrain alors il faut eteindre la case et remettre le degré à 0
				if(nouveau_type == cendres_eteintes || nouveau_type == eau || nouveau_type == terrain){
					Foret -> cases[indL][indC].etat = 0;
					Foret -> cases[indL][indC].degre = 0;
				}
				//on fait corrrespondre le degre avec le nouveau type 
				Foret -> cases[indL][indC].degre = type_to_degre(nouveau_type);
			}
			
			//s'il veut changer l'état
			else if(choix_changement == 2){
				int nouveau_etat = choix_parmi_etats();
				//si il veut allumer la case alors que c'est impossible (eau, terrain, cendres_eteintes)
				if(nouveau_etat == 1 && (Foret -> cases[indL][indC].type_case == cendres_eteintes || Foret -> cases[indL][indC].type_case == eau || Foret -> cases[indL][indC].type_case == terrain)){
					printf("Impossible d'allumer cette case, verifiez son type !\n\n");
				}
				//sinon on effectue son changement
				else{
					Foret -> cases[indL][indC].etat = nouveau_etat;
				}
			}
			
			//s'il veut changer le degré
			else{
				
				//on ne le laisse pas mettre un degré de 0 car il on ne pourrait pas determiner s'il s'agit de cendres_eteintes, d'eau ou de terrain
				int choix_degre = choix_parmi_degres();
				
				//s'il veut mettre un degre de 2 alors que la case ne brule pas (c'est impossible si elle se mets a bruler au tour t + 1 alors elle sera au degré de 1 mais toujours au même type alors qu'elle devrait etre en cendres eteintes
				if(choix_degre == 2 && Foret -> cases[indL][indC].etat == 0){
					printf("Impossible de mettre un degre de 2 sur cette case, les règles ne le permettent pas (elle ne brule pas).\n\n");
				}
				//s'il veut mettre 1 alors automatiquement la case devient des cendres
				else if(choix_degre == 1){
					Foret -> cases[indL][indC].type_case = cendres;
				}
				//s'il choisi de mettre un degre de 0, on place dans la case un type aléatoire entre eau, terrain et rocher, et on eteint la case
				else if(choix_degre == 0){
					int nb_alea = generation_alea_int(3);
					//on utlise pas la fonction choix alea car ici le choxi est restreint a 3 possibilités
					switch(nb_alea){
						case 1: 
							Foret -> cases[indL][indC].type_case = eau;
							break;
						case 2: 
							Foret -> cases[indL][indC].type_case = terrain;
							break;
						case 3: 
							Foret -> cases[indL][indC].type_case = cendres_eteintes;
							break;
					}
					Foret -> cases[indL][indC].etat = 0;
				}
				//sinon on effectue son changement
				else{
					Foret -> cases[indL][indC].degre = choix_degre;
				}
			}
		}
		
		//si l'utilisateur a rentré une case non valide, on le laisse attendre le prochain tour
		else{
			printf("\n\n");
			interrompre_changer(Foret);
		}
	}
}
 


//################################ MAIN ############################################



int main(int argc, char **argv){
	srand(time(NULL)); //initialisation de la graine du générateur aléatoire
	menu();
	return 0;
}
