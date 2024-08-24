//
// Created by mathi on 27/05/2024.
//
#ifndef PROJET_PAVAGE_INITIALISATIONS_H
#define PROJET_PAVAGE_INITIALISATIONS_H
#include "structs.h"
void choisir_nombre_joueurs(partie* partie);                                                         //On entre le nombre de joueurs (1 ou 2)
void choisir_difficulte(partie* partie);                                                              //On entre la difficulte
void choisir_dimension(partie* partie);                                                               //On entre les dimensions du tableau
void initialiser_grille(partie* partie);                                                              //Initialise la grille
void initialiser_joueurs(partie* partie);                                                             //Creer les 5 tuiles initiales des joueurs
void tirage_au_sort(partie* partie);                                                                   //Determine le joueur qui commence la partie.
void demander_noms(partie* partie);        //Demande le nom des joueurs, appelée uniquement en cas de partie multijoueur
#endif //PROJET_PAVAGE_INITIALISATIONS_H
