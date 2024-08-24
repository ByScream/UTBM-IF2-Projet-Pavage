//
// Created by mathi on 27/05/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "functions.h"
/**
 * La fonction permet de demander le nom des deux joueurs.
 * Appelée uniquement en mode multi
 *
 * @param partie La partie dont on souhaite demander le nom des deux joueurs est passé en paramètre
 */
void demander_noms(partie* partie){
    fgetchar();
    printf("----------------------------\n");
    printf("Donnez le nom du joueur 1\n");
    printf("----------------------------\n");
    char buffer[100];
    fgets(buffer,30,stdin);
    trim_newline(buffer);
    strcpy((*partie).joueur1.nom,buffer);
    printf("----------------------------\n");
    printf("Donnez le nom du joueur 2\n");
    printf("----------------------------\n");
    fgets(buffer,30,stdin);
    trim_newline(buffer);
    strcpy((*partie).joueur2.nom,buffer);
}
/**
 * La fonction permet de tirer au sort le premier joueur qui commencera.
 * Appelée uniquement en mode multi
 *
 * @param partie La partie dont on souhaite tirer au sort le premier joueur est passé en paramètre
 */
void tirage_au_sort(partie* partie){
    (*partie).joueur_qui_joue=rand()%2+1;
    printf("Tirage au sort du joueur qui commencera...\n");
    sleep(1);
    if ((*partie).joueur_qui_joue == 1){
        printf("Le premier joueur qui commencera sera: %s\n",(*partie).joueur1.nom);
    }else{
        printf("Le premier joueur qui commencera sera: %s\n",(*partie).joueur2.nom);
    }
}
/**
 * La fonction permet d'itinialiser le ou les joueurs de la partie.
 *
 * @param partie La partie dont on souhaite initialiser les joueurs est passé en paramètre
 */
void initialiser_joueurs(partie* partie) {
    int nbJoueurs=(*partie).mode;
    for (int joueur=1;joueur<=nbJoueurs;joueur++){
        for (int tuile=0; tuile<5;tuile++) {
            int nbCaracteres=1, nbNombres;
            if ((*partie).difficulte==1){
                nbNombres=rand()%3+1;
            } else {
                nbCaracteres=2;
                nbNombres=rand()%3+2;
            }

            if (joueur==1){
                (*partie).joueur1.score=0;
                (*partie).joueur1.abandon=0;
                for (int i=0;i<3;i++){
                    for (int ii=0;ii<3;ii++){
                        (*partie).joueur1.tuiles[tuile][i][ii]=' ';
                    }
                }
                for (int a=1;a<=nbCaracteres;a++) {
                    int posY, posX;
                    do {
                        posY = rand() % 3;
                        posX = rand() % 3;

                    } while ((*partie).joueur1.tuiles[tuile][posY][posX] != ' ');
                    if (a==1){
                        (*partie).joueur1.tuiles[tuile][posY][posX]='X';
                    }else{
                        (*partie).joueur1.tuiles[tuile][posY][posX]='Y';
                    }

                }
                for (int a=1;a<=nbNombres;a++) {
                    int posY, posX;
                    do {
                        posY = rand() % 3;
                        posX = rand() % 3;

                    } while ((*partie).joueur1.tuiles[tuile][posY][posX] != ' ');
                    (*partie).joueur1.tuiles[tuile][posY][posX]=(rand()%3+1);
                }
            }else {
                (*partie).joueur2.score=0;
                (*partie).joueur2.abandon=0;
                for (int i=0;i<3;i++){
                    for (int ii=0;ii<3;ii++){
                        (*partie).joueur2.tuiles[tuile][i][ii]=' ';
                    }
                }
                for (int a=1;a<=nbCaracteres;a++) {
                    int posY, posX;
                    do {
                        posY = rand() % 3;
                        posX = rand() % 3;
                    } while ((*partie).joueur2.tuiles[tuile][posY][posX] != ' ');
                    if (a==1){
                        (*partie).joueur2.tuiles[tuile][posY][posX]='A';
                    }else{
                        (*partie).joueur2.tuiles[tuile][posY][posX]='B';
                    }
                }
                for (int a=1;a<=nbNombres;a++) {
                    int posY, posX;
                    do {
                        posY = rand() % 3;
                        posX = rand() % 3;
                    } while ((*partie).joueur2.tuiles[tuile][posY][posX] != ' ');
                    (*partie).joueur2.tuiles[tuile][posY][posX]=-(rand()%3+1);
                }
            }
        }
    }
}
/**
 * La fonction permet de demander choisir la difficulté.
 *
 * @param partie La partie dont on souhaite demander la difficulté est passé en paramètre
 */
void choisir_difficulte(partie* partie){
    int res=0;
    while (res<1 || res>2){
        printf("----------------------------\n");
        printf("Choississez la difficulté:\n");
        printf("1 - Facile\n");
        printf("2 - Difficile\n");
        printf("----------------------------\n");
        scanf("%d",&res);
        if (res<1 || res>2){
            printf("Erreur ! Mauvaise réponse, le choix possible est 1 ou 2 !\n");
        }
    }
    partie->difficulte=res;
}
/**
 * La fonction permet de demander les dimensions de la grille.
 *
 * @param partie La partie dont on souhaite demander les dimensions de la grille est passé en paramètre
 */
void choisir_dimension(partie* partie){
    int res=0;
    while (res<3){
        printf("----------------------------\n");
        printf("Réglage des dimensions de la grille\n");
        printf("Donnez le nombre de lignes (>=3)\n");
        printf("----------------------------\n");
        scanf("%d",&res);
        if (res<3){
            printf("Erreur ! Mauvaise réponse, le choix possible est supérieur ou égal a 3 !\n");
        }

    }
    partie->dimensionL=res;
    res = 0;
    while (res<6){
        printf("----------------------------\n");
        printf("Réglage des dimensions de la grille\n");
        printf("Donnez le nombre de colonnes (>=6)\n");
        printf("----------------------------\n");
        scanf("%d",&res);
        if (res<6){
            printf("Erreur ! Mauvaise réponse, le choix possible est supérieur ou égal a 6 !\n");
        }
    }
    partie->dimensionC=res;
}
/**
 * La fonction permet d'initialiser la grille.
 *
 * @param partie La partie dont on souhaite initialiser la grille est passé en paramètre
 */
void initialiser_grille(partie* partie) {
    int dimensionC=(*partie).dimensionC, dimensionL=(*partie).dimensionL;
    for (int a=0; a<dimensionC;a++){
        for (int b=0; b<dimensionL;b++){
            (*partie).grille[a][b]=' ';
        }
    }
}
/**
 * La fonction permet de demander le nombre de joueurs d'une partie.
 *
 * @param partie La partie dont on souhaite demander le nombre de joueurs est passé en paramètre
 */
void choisir_nombre_joueurs(partie* partie){
    int res=0;
    while (res<1 || res>2){
        printf("----------------------------\n");
        printf("Choississez le mode de jeu:\n");
        printf("1 - Solo\n");
        printf("2 - Multijoueur (2 joueurs)\n");
        printf("----------------------------\n");
        scanf("%d",&res);
        if (res<1 || res>2){
            printf("Erreur ! Mauvaise réponse, le choix possible est 1 ou 2 !\n");
        }
    }
    partie->mode=res;
}



