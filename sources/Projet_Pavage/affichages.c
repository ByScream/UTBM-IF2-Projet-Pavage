#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
/**
 * La fonction permet d'afficher sur le terminal les 5 tuiles d'un joueur
 *
 * @param joueur Le joueur dont on souhaite afficher les tuiles est passé en paramètre
 */
void afficher_tuiles(joueur* joueur){
    for (int ligne=0;ligne<8;ligne++){
        for (int tuile=0;tuile<5;tuile++){
            if (ligne==0){
                printf("┌──┬──┬──┐ ");
            }
            if (ligne==1 || ligne==3 || ligne == 5){

                for (int C=0;C<3;C++){
                    printf("│");
                    if(((*joueur).tuiles[tuile][C][ligne/2])<32){
                        if(((*joueur).tuiles[tuile][C][ligne/2])>=0) {
                            printf(" ");
                        }
                        printf("%d",(*joueur).tuiles[tuile][C][ligne/2]);
                    }else{
                        printf(" %c",(*joueur).tuiles[tuile][C][ligne/2]);

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
            if (ligne==7){
                printf("    (%d)    ",tuile+1);
            }

        }
        printf("\n");
    }
}
/**
 * La fonction permet d'afficher sur le terminal la grille actuelle
 *
 * @param partie La partie dont on souhaite afficher la grille est passé en paramètre
 */
void afficher_grille(partie* partie) {
    system("cls");

    int dimensionC=(*partie).dimensionC, dimensionL=(*partie).dimensionL;
    if (dimensionL >=10 ){
        printf(" ");
    }
    for(int i=0;i<dimensionC;++i){
        printf("  %d",i+1);
    }
    printf("\n");
    for(int ligne=0;ligne<dimensionL*2+1;++ligne){
        if (ligne==0){
            if (dimensionL >=10 ){
                printf(" ");
            }
            printf(" ┌");
            for (int C=0; C<dimensionC-1;++C){
                printf("──┬");
            }
            printf("──┐\n");
        }else{
            if ((ligne)%2==1){


                if (ligne/2+1 < 10 && dimensionL >=10 ){
                    printf("%d ",(ligne/2)+1);
                }else{
                    printf("%d",(ligne/2)+1);
                }

                for (int C=0; C<dimensionC;++C){
                    printf("│");
                    if ((*partie).grille[C][ligne/2] < 32) {
                        if ((*partie).grille[C][ligne/2] >= 0) {
                            printf(" ");
                        }
                        printf("%d", (*partie).grille[C][ligne/2]);
                    } else {
                        printf(" %c", (*partie).grille[C][ligne/2]);

                    }
                }
                printf("│\n");
            }else{
                if (ligne==(dimensionL*2)){
                    if (dimensionL >=10 ){
                        printf(" ");
                    }
                    printf(" └");
                    for (int C=0; C<dimensionC-1;++C){
                        printf("──┴");
                    }
                    printf("──┘\n");
                }else{
                    if (dimensionL >=10 ){
                        printf(" ");
                    }
                    printf(" ├");
                    for (int C=0; C<dimensionC-1;++C){
                        printf("──┼");
                    }
                    printf("──┤\n");
                }

            }
        }

    }
}