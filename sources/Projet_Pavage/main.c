#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "manager.h"
#include "save.h"

int lancement_jeu ();

/*! \mainpage Projet IF2: Pavage
 *
 * Projet créé dans le cadre de l'UE IF2 en TC2, semestre P2024
 *
 * L'ensemble des conditions, obligations, règles, fonctionnement sont écrits dans le document que nous avons reçu:
 * <a href="https://moodle.utbm.fr/pluginfile.php/282346/mod_resource/content/1/Projet%20IF2B%202024%20-%20Pavage.pdf">Document</a>
 *
 * Lien de notre compte-rendu :
 * <a href="https://1drv.ms/b/s!AlVy8DwbZ9TlgdlMmmz_jvTfLFsoeg?e=Xor5MU">Compte-Rendu</a>
 *
 * Réalisé par JOLY Valentin et RICHARD Mathis
 */

int main() {
    system("chcp 65001");
    srand(time(0));
                                                              //Trois choix: commencer, relancer une partie sauvegarder ou quitter
    int end=0;
    while (end==0) {
        int type=lancement_jeu();
        switch (type) {                                                                       //Ce switch permet d'appliquer le choix precedent
            case 1:
                creer_nouvelle_partie();
                break;
            case 2:
                if (afficher_nom_sauvegardes() != 0) {
                    char nom_sauvegarde[21];
                    choisir_sauvegarde(nom_sauvegarde);
                    charger_nouvelle_partie(nom_sauvegarde);
                }
                break;
            default:
                end=1;
        }
    }
    return 0;
}


/**
 * La fonction permet d'afficher le menu principal
 */
int lancement_jeu (){                                                       //Trois choix: commencer, relancer une partie sauvegarder ou quitter
    int res=0;
    while (res<1 || res>3){
        printf("---------- Pavage ----------\n");
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Démarrer une partie\n");
        printf("2 - Reprendre une partie\n");
        printf("3 - Quitter le jeu\n");
        printf("----------------------------\n");
        scanf("%d",&res);
        if (res<1 || res>3){
            printf("Erreur ! Mauvaise réponse, le choix possible est 1, 2 ou 3 !\n");
        }
    }
    return res;
}
