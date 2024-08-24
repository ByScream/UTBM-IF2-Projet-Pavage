//
// Created by mathi on 27/05/2024.
//
#include "structs.h"
#ifndef PROJET_PAVAGE_TUILES_H
#define PROJET_PAVAGE_TUILES_H
int trouver_positionX(char tuile[3][3], char caractere);
int trouver_positionY(char tuile[3][3], char caractere);
int placer_tuile(partie* partie);                                                                      //Verifie et place une tuile selectionne par le joueurs
int joueur_peut_poser_tuile(char tuile[3][3],partie partie, int coordC, int coordL);
void regenerer_nouvelle_tuile(partie* partie, int tuile);
#endif //PROJET_PAVAGE_TUILES_H
