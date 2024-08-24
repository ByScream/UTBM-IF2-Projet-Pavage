//
// Created by mathi on 27/05/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "affichages.h"
/**
 * La fonction permet de régénérer une nouvelle tuile pour un joueur
 * @param partie La partie est passée en paramètre
 * @param tuile Numéro de la tuile à regénérer
 */
void regenerer_nouvelle_tuile(partie* partie, int tuile){
    int joueur=(*partie).joueur_qui_joue;
    int nbCaracteres=1, nbNombres;
    if ((*partie).difficulte==1){
        nbNombres=rand()%3+1;
    } else {
        nbCaracteres=2;
        nbNombres=rand()%3+2;
    }

    if (joueur==1){
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
/**
 * La fonction permet de vérifier si le joueur peut bien poser une tuile
 * @param tuile La tuile en question
 * @param partie La partie en cours
 * @param coordC La coordonnée de la colonne dans la grille
 * @param coordL La coordonnée de la ligne dans la grille
 */
int joueur_peut_poser_tuile(char tuile[3][3],partie partie, int coordC, int coordL){
    int ret=0;
    int coordCMax = partie.dimensionC, coordLMax = partie.dimensionL;
    for (int L=0; L<3; L++){
        for (int C=0; C<3; C++){
            if (tuile[C][L]=='X' || tuile[C][L]=='Y' || tuile[C][L]=='A' || tuile[C][L]=='B'){
                if ((coordC+C)<0 || (coordC+C)>= coordCMax || (coordL+L)<0 || (coordL+L)>= coordLMax){
                    ret = 1;
                }
                if (partie.grille[coordC+C][coordL+L]=='X' || partie.grille[coordC+C][coordL+L]=='Y' || partie.grille[coordC+C][coordL+L]=='A' || partie.grille[coordC+C][coordL+L]=='B'){
                    ret = 2;
                }
                if (partie.joueur_qui_joue==1){
                    if (partie.joueur1.score!=0 && (partie.grille[coordC+C][coordL+L]==0 || partie.grille[coordC+C][coordL+L]==' ')){
                        ret = 3;
                    }
                }else{
                    if (partie.joueur2.score!=0 && (partie.grille[coordC+C][coordL+L]==0 || partie.grille[coordC+C][coordL+L]==' ')){
                        ret = 3;
                    }
                }

            }
        }
    }
    return ret;
}
/**
 * La fonction permet de trouver la position colonne dans la tuile d'un caractère
 * @param tuile La tuile en question
 * @param caractere Le caractère en question
 */
int trouver_positionX(char tuile[3][3], char caractere){
    int X;
    for (int L=0; L<3; L++){
        for (int C=0; C<3; C++){
            if (tuile[C][L]==caractere){
                X=C;
            }
        }
    }
    return X;
}/**
 * La fonction permet de trouver la position ligne dans la tuile d'un caractère
 * @param tuile La tuile en question
 * @param caractere Le caractère en question
 */

int trouver_positionY(char tuile[3][3], char caractere){
    int Y;
    for (int L=0; L<3; L++){
        for (int C=0; C<3; C++){
            if (tuile[C][L]==caractere){
                Y=L;
            }
        }
    }
    return Y;
}
/**
 * La fonction permet de gérer le placement des tuiles pour les joueurs
 * Appelée à chaque tour
 * @param partie La partie est passée en paramètre
 */
int placer_tuile(partie* partie){
    int ret=0;
    int tuile_a_poser = 0;
    while (tuile_a_poser<1 || tuile_a_poser > 7){
        printf("----------------------------\n");
        printf("Choisissez la tuile que vous souhaitez poser\n");
        printf("Donnez le numéro de la tuile (Entre 1 et 5)\n");
        printf("Saisissez 6 si vous souhaitez abandonner !\n");
        printf("Saisissez 7 si vous souhaitez sauvegarder et quitter la partie !\n");
        printf("----------------------------\n");
        scanf("%d",&tuile_a_poser);
        if (tuile_a_poser<1 || tuile_a_poser > 7){
            printf("Erreur ! Mauvaise réponse, le choix possible est entre 1 et 5 !\n");
        }
    }
    if (tuile_a_poser==6){
        ret=2;
    }else if (tuile_a_poser==7){
        ret=3;
    }else{
        afficher_grille(partie);
        joueur joueur=(*partie).joueur1;
        if ((*partie).joueur_qui_joue == 2){
            joueur=(*partie).joueur2;
        }

        for (int ligne=0;ligne<7;ligne++){

            if (ligne==0){
                printf("┌──┬──┬──┐ ");
            }
            if (ligne==1 || ligne==3 || ligne == 5){

                for (int C=0;C<3;C++){
                    printf("│");
                    if(((joueur).tuiles[tuile_a_poser-1][C][ligne/2])<32){
                        if(((joueur).tuiles[tuile_a_poser-1][C][ligne/2])>=0) {
                            printf(" ");
                        }
                        printf("%d",(joueur).tuiles[tuile_a_poser-1][C][ligne/2]);
                    }else{
                        printf(" %c",(joueur).tuiles[tuile_a_poser-1][C][ligne/2]);

                    }
                }
                printf("│ ");

            }
            if (ligne==2 || ligne==4){
                printf("├──┼──┼──┤ ");
            }
            if (ligne==6){
                printf("└──┴──┴──┘ ");
            }

            printf("\n");
        }
        int coordCMax = (*partie).dimensionC, coordLMax = (*partie).dimensionL, coordC=0, coordL=0;
        char carac='X';
        if ((*partie).joueur_qui_joue == 2){
            carac='A';
        }
        while (coordC<1 || coordC > coordCMax){
            printf("----------------------------\n");
            printf("Dans quelle colonne de la grille souhaitez-vous placer le caractère %c ?\n",carac);
            printf("Donnez le numéro de la colonne (Entre 1 et %d)\n",coordCMax);
            printf("----------------------------\n");
            scanf("%d",&coordC);
            if (coordC<1 || coordC > coordCMax){
                printf("Erreur ! Mauvaise réponse, le choix possible est entre 1 et %d !\n",coordCMax);
            }
        }
        while (coordL<1 || coordL > coordLMax){
            printf("----------------------------\n");
            printf("Dans quelle ligne de la grille souhaitez-vous placer le caractère %c ?\n",carac);
            printf("Donnez le numéro de la ligne (Entre 1 et %d)\n",coordLMax);
            printf("----------------------------\n");
            scanf("%d",&coordL);
            if (coordL<1 || coordL > coordLMax){
                printf("Erreur ! Mauvaise réponse, le choix possible est entre 1 et %d !\n",coordLMax);
            }
        }
        int posC_carac=trouver_positionX(joueur.tuiles[tuile_a_poser-1],carac);
        int posL_carac=trouver_positionY(joueur.tuiles[tuile_a_poser-1],carac);
        int coordC_tuile = coordC-posC_carac-1;
        int coordL_tuile = coordL-posL_carac-1;


        int type=joueur_peut_poser_tuile(joueur.tuiles[tuile_a_poser-1],(*partie), coordC_tuile, coordL_tuile);
        switch (type){
            case 1:
                printf("Erreur ! Un des caractères sort de la grille !\n");
                int res2=0;
                while (res2<1 || res2>2){
                    printf("----------------------------\n");
                    printf("Que souhaitez-vous faire ?\n");
                    printf("1 - Retenter\n");
                    printf("2 - Abandonner\n");
                    printf("----------------------------\n");
                    scanf("%d",&res2);
                    if (res2<1 || res2>2){
                        printf("Erreur ! Mauvaise réponse, le choix possible est 1 ou 2 !\n");
                    }
                }
                if (res2==1){
                    ret=1;
                }else{
                    ret=2;
                }
                break;
            case 2:
                printf("Erreur ! Un des caractères se pose sur un autre caractère !\n");
                int res=0;
                while (res<1 || res>2){
                    printf("----------------------------\n");
                    printf("Que souhaitez-vous faire ?\n");
                    printf("1 - Retenter\n");
                    printf("2 - Abandonner\n");
                    printf("----------------------------\n");
                    scanf("%d",&res);
                    if (res<1 || res>2){
                        printf("Erreur ! Mauvaise réponse, le choix possible est 1 ou 2 !\n");
                    }
                }
                if (res==1){
                    ret=1;
                }else{
                    ret=2;
                }
                break;
            case 3:
                printf("Erreur ! Un des caractères n'est pas sur un numéro !\n");
                int res3=0;
                while (res3<1 || res3>2){
                    printf("----------------------------\n");
                    printf("Que souhaitez-vous faire ?\n");
                    printf("1 - Retenter\n");
                    printf("2 - Abandonner\n");
                    printf("----------------------------\n");
                    scanf("%d",&res3);
                    if (res3<1 || res3>2){
                        printf("Erreur ! Mauvaise réponse, le choix possible est 1 ou 2 !\n");
                    }
                }
                if (res3==1){
                    ret=1;
                }else{
                    ret=2;
                }
                break;
            default:
                for (int L=0; L<3; L++){
                    for (int C=0; C<3; C++){
                        if (joueur.tuiles[tuile_a_poser-1][C][L]<32){
                            if ((*partie).grille[coordC_tuile+C][coordL_tuile+L]==32){
                                (*partie).grille[coordC_tuile+C][coordL_tuile+L]=joueur.tuiles[tuile_a_poser-1][C][L];
                            }else{
                                if ((*partie).grille[coordC_tuile+C][coordL_tuile+L]<32){
                                    (*partie).grille[coordC_tuile+C][coordL_tuile+L]=(*partie).grille[coordC_tuile+C][coordL_tuile+L] + joueur.tuiles[tuile_a_poser-1][C][L];
                                }
                            }

                        }else{
                            if (joueur.tuiles[tuile_a_poser-1][C][L]!=32) {
                                (*partie).grille[coordC_tuile + C][coordL_tuile + L] = joueur.tuiles[tuile_a_poser -1][C][L];
                            }
                        }
                    }
                }
                regenerer_nouvelle_tuile(partie, tuile_a_poser-1);
        }
    }

    return ret;
}