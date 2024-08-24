//
// Created by mathi on 27/05/2024.
//

#ifndef PROJET_PAVAGE_STRUCTS_H
#define PROJET_PAVAGE_STRUCTS_H
typedef struct {                                             //La structure joueur associe a chacun un nom, un score ainsi que ses cinq tuiles de trois par trois
    /**
     * Nom du joueur
     */
    char nom[30];
    /**
     * Tuiles du joueur
     */
    char tuiles[5][3][3];
    /**
     * Score du joueur
     */
    int score;
    /**
     * Si le joueur a abandonné
     */
    int abandon;
} joueur;
typedef struct {                                             //La structure partie va permettre de diminuer drastiquement le nombre de parametres dans les fonctions.
    /**
     * Mode de jeu de la partie
     */
    int mode;                                                //De plus, elle permet de sauvegarder les parties, et d y rejouer plus tard.
    /**
     * Difficulté de la partie
     */
    int difficulte;                                          // Elle definit tous les parametres propre à une fonction et entré par l'utilisateur.
    /**
     * Nombre de lignes de la grille
     */
    int dimensionL;
    /**
     * Nombre de colonnes de la grille
     */
    int dimensionC;
    /**
     * Grille de la partie
     */
    char grille[999][999];
    /**
     * Joueur 1 de la partie
     */
    joueur joueur1;
    /**
     * Joueur 2 de la partie
     */
    joueur joueur2;
    /**
     * Le joueur qui doit jouer
     */
    int joueur_qui_joue;
} partie;
#endif //PROJET_PAVAGE_STRUCTS_H
