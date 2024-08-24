//
// Created by mathi on 09/06/2024.
//
#include "initialisations.h"
#include "structs.h"
#include "tuiles.h"
#include "save.h"
#include "affichages.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "manager.h"
#include "functions.h"

/**
 * La fonction permet de créer, et gérer une nouvelle partie.
 */
void creer_nouvelle_partie(){
    partie nouvelle_partie;                                                       //Creer une nouvelle partie
    choisir_nombre_joueurs(&nouvelle_partie);                                //Determine le mode (solo ou multi)
    if (nouvelle_partie.mode==2){                                                 //Determine les parametres exclusifs au mode multi
        demander_noms(&nouvelle_partie);
        tirage_au_sort(&nouvelle_partie);
    }else{                                                                        //Determine les parametres exclusifs au mode solo
        (nouvelle_partie).joueur_qui_joue=1;
    }
    choisir_difficulte(&nouvelle_partie);                                                           //Determine les parametres communs aux deux modes
    choisir_dimension(&nouvelle_partie);
    initialiser_grille(&nouvelle_partie);
    initialiser_joueurs(&nouvelle_partie);
    int end=0;
    if (nouvelle_partie.mode==2){
        while ((nouvelle_partie.joueur1.abandon==0 || nouvelle_partie.joueur2.abandon==0) && end==0){
            afficher_grille(&nouvelle_partie);                                                         //Affiche la grille vide
            if (nouvelle_partie.joueur_qui_joue == 1){                                                      //Tout le If s occupe du mode solo
                if (nouvelle_partie.joueur1.abandon==0) {                                                   //Le joueur joue tant que il n a pas abandonne
                    printf("C'est au tour de %s\n", nouvelle_partie.joueur1.nom);
                    afficher_tuiles(&(nouvelle_partie.joueur1));                                       //Affiche les cinq tuiles du joueur

                    int a = placer_tuile(&nouvelle_partie);                                            //
                    while (a == 1) {                                                                        //Le joueur n a
                        afficher_grille(&nouvelle_partie);
                        afficher_tuiles(&(nouvelle_partie.joueur1));
                        a = placer_tuile(&nouvelle_partie);
                    };
                    if (a == 0) {
                        printf("C'est placé !\n");
                        nouvelle_partie.joueur1.score++;
                    } else {
                        if (a==2) {//S occupe de la partie abandon
                            printf("Vous avez abandonné ! Votre partie est terminée !\n");
                            nouvelle_partie.joueur1.abandon = 1;
                        } else { //A est égal à 3 donc sauvegarde
                            end=1;
                            sauvegarder(&nouvelle_partie);
                        }
                    }

                }else{
                    printf("%s passe son tour car il a abandonné !\n",nouvelle_partie.joueur1.nom);
                }
                (nouvelle_partie.joueur_qui_joue) = 2;
            }else{                                                                                          //Tout le else s occupe du mode multi
                if (nouvelle_partie.joueur2.abandon==0) {                                                   //Le joueur joue tant que il n a pas abandonne
                    printf("C'est au tour de %s\n", nouvelle_partie.joueur2.nom);
                    afficher_tuiles(&(nouvelle_partie.joueur2));                                       //Affiche les cinq tuiles du joueur

                    int a = placer_tuile(&nouvelle_partie);                                            //
                    while (a == 1) {                                                                        //Le joueur n a
                        afficher_grille(&nouvelle_partie);
                        afficher_tuiles(&(nouvelle_partie.joueur2));
                        a = placer_tuile(&nouvelle_partie);
                    };
                    if (a == 0) {
                        printf("C'est placé !\n");
                        nouvelle_partie.joueur2.score++;
                    } else {
                        if (a==2) {//S occupe de la partie abandon
                            printf("Vous avez abandonné ! Votre partie est terminée !\n");
                            nouvelle_partie.joueur2.abandon = 1;
                        } else { //A est égal à 3 donc sauvegarde
                            end=1;
                            sauvegarder(&nouvelle_partie);
                        }
                    }

                }else{
                    printf("%s passe son tour car il a abandonné !\n",nouvelle_partie.joueur2.nom);
                }
                (nouvelle_partie.joueur_qui_joue) = 1;
            }
            sleep(5);
        }
        system("cls");
        if (end==0) {
            if (nouvelle_partie.joueur1.score > nouvelle_partie.joueur2.score) {
                printf("%s a gagné la partie contre %s !\n", nouvelle_partie.joueur1.nom,
                       nouvelle_partie.joueur2.nom);
            } else {
                if (nouvelle_partie.joueur1.score == nouvelle_partie.joueur2.score) {
                    printf("Il n'y a pas de vainqueur pour cette partie !\n");
                } else {
                    printf("%s a gagné la partie contre %s !\n", nouvelle_partie.joueur2.nom,
                           nouvelle_partie.joueur1.nom);
                }
            }
            printf("SCORES:\n");
            printf("%s: %d tuile(s) posée(s)\n", nouvelle_partie.joueur1.nom, nouvelle_partie.joueur1.score);
            printf("%s: %d tuile(s) posée(s)\n", nouvelle_partie.joueur2.nom, nouvelle_partie.joueur2.score);
        }

    }else{
        while (nouvelle_partie.joueur1.abandon==0 && end==0){
            afficher_grille(&nouvelle_partie);                                                         //Affiche la grille vide
            afficher_tuiles(&(nouvelle_partie.joueur1));                                       //Affiche les cinq tuiles du joueur

            int a = placer_tuile(&nouvelle_partie);                                            //
            while (a == 1) {                                                                        //Le joueur n a
                afficher_grille(&nouvelle_partie);
                afficher_tuiles(&(nouvelle_partie.joueur1));
                a = placer_tuile(&nouvelle_partie);
            };
            if (a == 0) {
                printf("C'est placé !\n");
                nouvelle_partie.joueur1.score++;
            } else {
                if (a==2) {//S occupe de la partie abandon
                    printf("Vous avez abandonné ! Votre partie est terminée !\n");
                    nouvelle_partie.joueur1.abandon = 1;
                } else { //A est égal à 3 donc sauvegarde
                    end=1;
                    sauvegarder(&nouvelle_partie);
                }
            }
            sleep(5);
        }
        system("cls");
        if (end == 0){
            printf("SCORE:\n");
            printf("%d   tuile(s) posée(s)\n",nouvelle_partie.joueur1.score);
        }
    }
}
/**
 * La fonction permet de charger, et gérer la partie.
 * @param nom_sauvegarde Le nom de la sauvegarde que l'on souhaite charger est passé en paramètre
 */
void charger_nouvelle_partie(char nom_sauvegarde[]){
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.csv", nom_sauvegarde);
    FILE* file = fopen(filename,"r");
    partie nouvelle_partie;
    char buffer[100];
    (nouvelle_partie).mode= atoi(fgets(buffer,100,file));
    (nouvelle_partie).difficulte=atoi(fgets(buffer,100,file));
    (nouvelle_partie).dimensionC=atoi(fgets(buffer,100,file));
    (nouvelle_partie).dimensionL=atoi(fgets(buffer,100,file));
    for (int L=0; L<(nouvelle_partie).dimensionL;L++){
        for (int C=0; C<(nouvelle_partie).dimensionC;C++){
            nouvelle_partie.grille[C][L]=atoi(fgets(buffer,100,file));
        }
    }
    fgets(buffer,100,file);
    trim_newline(buffer);
    strcpy((nouvelle_partie).joueur1.nom,buffer);
    for (int tuile=0; tuile<5;tuile++) {
        for (int L = 0; L < 3; L++) {
            for (int C = 0; C < 3; C++) {
                nouvelle_partie.joueur1.tuiles[tuile][C][L] = atoi(fgets(buffer, 100, file));
            }
        }
    }
    nouvelle_partie.joueur1.score=atoi(fgets(buffer,100,file));
    nouvelle_partie.joueur1.abandon=atoi(fgets(buffer,100,file));

    int end=0;
    if (nouvelle_partie.mode==2){
        fgets(buffer,100,file);
        trim_newline(buffer);
        strcpy((nouvelle_partie).joueur2.nom,buffer);
        for (int tuile=0; tuile<5;tuile++) {
            for (int L = 0; L < 3; L++) {
                for (int C = 0; C < 3; C++) {
                    nouvelle_partie.joueur2.tuiles[tuile][C][L] = atoi(fgets(buffer, 100, file));
                }
            }
        }
        nouvelle_partie.joueur2.score=atoi(fgets(buffer,100,file));
        nouvelle_partie.joueur2.abandon=atoi(fgets(buffer,100,file));

        nouvelle_partie.joueur_qui_joue=atoi(fgets(buffer,100,file));

        while ((nouvelle_partie.joueur1.abandon==0 || nouvelle_partie.joueur2.abandon==0) && end==0){
            afficher_grille(&nouvelle_partie);                                                         //Affiche la grille vide
            if (nouvelle_partie.joueur_qui_joue == 1){                                                      //Tout le If s occupe du mode solo
                if (nouvelle_partie.joueur1.abandon==0) {                                                   //Le joueur joue tant que il n a pas abandonne
                    printf("C'est au tour de %s\n", nouvelle_partie.joueur1.nom);
                    afficher_tuiles(&(nouvelle_partie.joueur1));                                       //Affiche les cinq tuiles du joueur

                    int a = placer_tuile(&nouvelle_partie);                                            //
                    while (a == 1) {                                                                        //Le joueur n a
                        afficher_grille(&nouvelle_partie);
                        afficher_tuiles(&(nouvelle_partie.joueur1));
                        a = placer_tuile(&nouvelle_partie);
                    };
                    if (a == 0) {
                        printf("C'est placé !\n");
                        nouvelle_partie.joueur1.score++;
                    } else {
                        if (a==2) {//S occupe de la partie abandon
                            printf("Vous avez abandonné ! Votre partie est terminée !\n");
                            nouvelle_partie.joueur1.abandon = 1;
                        } else { //A est égal à 3 donc sauvegarde
                            end=1;
                            sauvegarder(&nouvelle_partie);
                        }
                    }

                }else{
                    printf("%s passe son tour car il a abandonné !\n",nouvelle_partie.joueur1.nom);
                }
                (nouvelle_partie.joueur_qui_joue) = 2;
            }else{                                                                                          //Tout le else s occupe du mode multi
                if (nouvelle_partie.joueur2.abandon==0) {                                                   //Le joueur joue tant que il n a pas abandonne
                    printf("C'est au tour de %s\n", nouvelle_partie.joueur2.nom);
                    afficher_tuiles(&(nouvelle_partie.joueur2));                                       //Affiche les cinq tuiles du joueur

                    int a = placer_tuile(&nouvelle_partie);                                            //
                    while (a == 1) {                                                                        //Le joueur n a
                        afficher_grille(&nouvelle_partie);
                        afficher_tuiles(&(nouvelle_partie.joueur2));
                        a = placer_tuile(&nouvelle_partie);
                    };
                    if (a == 0) {
                        printf("C'est placé !\n");
                        nouvelle_partie.joueur2.score++;
                    } else {
                        if (a==2) {//S occupe de la partie abandon
                            printf("Vous avez abandonné ! Votre partie est terminée !\n");
                            nouvelle_partie.joueur2.abandon = 1;
                        } else { //A est égal à 3 donc sauvegarde
                            end=1;
                            sauvegarder(&nouvelle_partie);
                        }
                    }

                }else{
                    printf("%s passe son tour car il a abandonné !\n",nouvelle_partie.joueur2.nom);
                }
                (nouvelle_partie.joueur_qui_joue) = 1;
            }
            sleep(5);
        }
        system("cls");
        if (end==0) {
            if (nouvelle_partie.joueur1.score > nouvelle_partie.joueur2.score) {
                printf("%s a gagné la partie contre %s !\n", nouvelle_partie.joueur1.nom,
                       nouvelle_partie.joueur2.nom);
            } else {
                if (nouvelle_partie.joueur1.score == nouvelle_partie.joueur2.score) {
                    printf("Il n'y a pas de vainqueur pour cette partie !\n");
                } else {
                    printf("%s a gagné la partie contre %s !\n", nouvelle_partie.joueur2.nom,
                           nouvelle_partie.joueur1.nom);
                }
            }
            printf("SCORES:\n");
            printf("%s: %d tuile(s) posée(s)\n", nouvelle_partie.joueur1.nom, nouvelle_partie.joueur1.score);
            printf("%s: %d tuile(s) posée(s)\n", nouvelle_partie.joueur2.nom, nouvelle_partie.joueur2.score);
        }

    }else{
        while (nouvelle_partie.joueur1.abandon==0 && end==0){
            afficher_grille(&nouvelle_partie);                                                         //Affiche la grille vide
            afficher_tuiles(&(nouvelle_partie.joueur1));                                       //Affiche les cinq tuiles du joueur

            int a = placer_tuile(&nouvelle_partie);                                            //
            while (a == 1) {                                                                        //Le joueur n a
                afficher_grille(&nouvelle_partie);
                afficher_tuiles(&(nouvelle_partie.joueur1));
                a = placer_tuile(&nouvelle_partie);
            };
            if (a == 0) {
                printf("C'est placé !\n");
                nouvelle_partie.joueur1.score++;
            } else {
                if (a==2) {//S occupe de la partie abandon
                    printf("Vous avez abandonné ! Votre partie est terminée !\n");
                    nouvelle_partie.joueur1.abandon = 1;
                } else { //A est égal à 3 donc sauvegarde
                    end=1;
                    sauvegarder(&nouvelle_partie);
                }
            }
            sleep(5);
        }
        system("cls");
        if (end == 0){
            printf("SCORE:\n");
            printf("%d   tuile(s) posée(s)\n",nouvelle_partie.joueur1.score);
        }
    }
}