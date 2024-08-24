//
// Created by mathi on 05/06/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#include "structs.h"
#include "functions.h"

/**
 * La fonction permet de vérifier si le nom d'une sauvegarde existe déjà
 * @param file Il s'agit du fichier ou tous les noms des sauvegardes sont enregistrés
 * @param searchWord Nom de la partie dont on souhaite vérifier l'existence
 */
int sauvegarde_existe_deja(FILE* file, char searchWord[]){
    char word[21];
    int lineNumber = 0;
    int found = 0;
    fseek(file, 0, SEEK_SET);
    while (fgets(word, sizeof(word), file)) {
        lineNumber++;
        trim_newline(word);  // Enlever le caractère de nouvelle ligne
        if (strcmp(word, searchWord) == 0) {
            found = 1;
            break;  // Sortir de la boucle après avoir trouvé le mot
        }
    }
    return found;
}
/**
 * La fonction permet de créer le fichier de la sauvegarde, et d'y enregistrer les données
 * @param nom Le nom de la sauvegarde est passée en paramètre
 * @param partie La partie que l'on souhaite sauvegarder est passée en paramètre
 */
void create_file_sauvegarde(char nom[],partie* partie){
    char filename[100];
    snprintf(filename, sizeof(filename), "%s.csv", nom);
    FILE* file= fopen(filename,"w+");
    if (file !=NULL){
        fprintf(file,"%d\n",(*partie).mode);
        fprintf(file,"%d\n",(*partie).difficulte);
        fprintf(file,"%d\n",(*partie).dimensionC);
        fprintf(file,"%d\n",(*partie).dimensionL);
        for (int L=0; L<(*partie).dimensionL;L++){
            for (int C=0; C<(*partie).dimensionC;C++){
                fprintf(file,"%d\n",(*partie).grille[C][L]);
            }
        }
        fprintf(file,"%s\n",(*partie).joueur1.nom);
        for (int tuile=0;tuile<5;tuile++){
            for (int L=0; L<3;L++){
                for (int C=0; C<3;C++){
                    fprintf(file,"%d\n",(*partie).joueur1.tuiles[tuile][C][L]);
                }
            }
        }
        fprintf(file,"%d\n",(*partie).joueur1.score);
        fprintf(file,"%d\n",(*partie).joueur1.abandon);
        if ((*partie).mode==2){
            fprintf(file,"%s\n",(*partie).joueur2.nom);
            for (int tuile=0;tuile<5;tuile++){
                for (int L=0; L<3;L++){
                    for (int C=0; C<3;C++){
                        fprintf(file,"%d\n",(*partie).joueur2.tuiles[tuile][C][L]);
                    }
                }
            }
            fprintf(file,"%d\n",(*partie).joueur2.score);
            fprintf(file,"%d\n",(*partie).joueur2.abandon);

            fprintf(file,"%d\n",(*partie).joueur_qui_joue);
        }
        fclose(file);
    } else {
        printf("Erreur lors de la création de la sauvegarde !\n");
    }
}
/**
 * La fonction permet de sauvegarder une partie en cours.
 * @param partie La partie que l'on souhaite sauvegarder est passée en paramètre
 */
void sauvegarder(partie* partie){
    fgetchar();
    system("cls");
    FILE* file = fopen("saves.csv","r+");
    if (file == NULL){
        file = fopen("saves.csv","w+");
    }
    if (file != NULL){
        char name[21];
        int exist;
        do {
            printf("----------------------------\n");
            printf("Entrez le nom de la partie que vous souhaitez sauvegarder\n");
            printf("20 caractères maximum\n");
            printf("----------------------------\n");
            fgets(name,21,stdin);
            trim_newline(name);
            exist=sauvegarde_existe_deja(file,name);
            if (exist==1){
                printf("Erreur ! Ce nom est déjà pris !\n");
            }
        } while (exist==1);

        printf("Enregistrement des données...\n");
        fprintf(file,"%s\n",name);
        fclose(file);
        create_file_sauvegarde(name,partie);
        printf("Données enregistrées !\n");
    }else{
        printf("Erreur lors de l'ouverture du fichier\n");
    }
}
/**
 * La fonction permet d'afficher toutes les sauvegardes enregistrées.
 */
int afficher_nom_sauvegardes(){
    FILE* file = fopen("saves.csv","r");
    if (file == NULL){
        file = fopen("saves.csv","w+");
    }
    char buffer[21];
    //fseek(file, 0, SEEK_SET);
    printf("----------------------------\n");
    printf("Listes des parties sauvegardées :\n");
    int cpt=0;
    while (fgets(buffer, sizeof(buffer), file)) {
        trim_newline(buffer);  // Enlever le caractère de nouvelle ligne
        printf("- %s\n",buffer);
        cpt++;
    }
    if (cpt==0){
        printf("Il n'y a aucune sauvegarde !\n");
    }
    printf("----------------------------\n");
    fclose(file);
    return cpt;
}

/**
 * La fonction demande au joueur d'entrer le nom de la partie qu'il souhaite charger
 *
 * @param nom Tableau de caractère passé en paramètre, où on y copie le nom de la sauvegarde choisi à la fin de la fonction
 */
void choisir_sauvegarde(char nom[]){
    char name[21];
    int exist=0;
    fgetchar();
    FILE* file = fopen("saves.csv","r");
    if (file == NULL){
        file = fopen("saves.csv","w+");
    }
    do {
        printf("----------------------------\n");
        printf("Entrez le nom de la partie que vous souhaitez charger\n");
        printf("----------------------------\n");
        fgets(name,21,stdin);
        trim_newline(name);
        exist=sauvegarde_existe_deja(file,name);
        if (exist==0){
            printf("Erreur ! Ce nom n'existe pas !\n");
        }
    } while (exist==0);
    fclose(file);
    strcpy(nom,name);
}