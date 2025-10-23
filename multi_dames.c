#include <stdio.h>

// Définitions de codes ANSI pour les couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"

#define TAILLE 8
typedef struct {
    // 0 si vide, 1 si blanc, 2 si rouge et 3 si noir
    int pion[TAILLE][TAILLE];
} Plateau;

typedef struct {
    int etat; // 1 si dans la partie, 0 sinon
    int score;
} Joueur;

#define MAX_JOUEURS 4
typedef struct {
    Plateau plateau;
    Joueur joueur[MAX_JOUEURS];
    int nb_joueurs;
    int joueur_courant;
    int tour;
    int pion_est_saisi; // 1 si un pion est saisi, 0 sinon
    int pion_i, pion_j; // la ligne et colonne du pion saisi (0 sinon)
} Jeu;


int jeu_capturer(Jeu *jeu, int i, int j){
    // le joueur courant capture la pièce se trouvant à la ligne i et la colonne j (numéroté entre 0 et 7) 
    // (par exemple lors du premier tour de jeu ou lors d’un saut)
}

int jeu_saisir_pion(Jeu *jeu, int i, int j){
    // utilisée en début de tour pour saisir le pion permettant de faire des saut (par le joueur courant)
}

int jeu_sauter_vers(Jeu *jeu, int i, int j){
    // fait sauter le pion saisi vers la case (vide) en position (i,j)
    // en capturant le pion entre les deux positions au passage
}

int jeu_arreter(Jeu *jeu){
    // utilisée en début de tour pour arrêter de jouer (tant que le joueur courant n’est pas le dernier joueur)
}

int jeu_joueur_suivant(Jeu *jeu){
    // passe au joueur suivant
}

void jeu_charger(Jeu *jeu){
    // fonctions pour les tests présentés dans la section suivante
}

void jeu_ecrire(Jeu *jeu){
    // fonctions pour les tests présentés dans la section suivante
}

int plateau_pion_peut_sauter(Plateau *plateau, int i, int j){
    // pour vérifier si un pion peut sauter.
}

int case_est_valide(int i, int j){
    // pour vérfier si une position désigne un case dans le plateau et non à l’extérieur
}

void jeu_afficher(Jeu *jeu){
    // pour afficher le plateau à l’utilisateur
}

void jeu_table_flip(Jeu *jeu){
    // pour que le joueur courant puisse faire un table flip
}

int main(void){
    Jeu jeu;
    int i,j;
    jeu_charger(&jeu);
    scanf("%d%d", &i, &j);
    if (!jeu_sauter_vers(&jeu, i, j)){
        printf("Actionimpossible\n");
    }
    jeu_ecrire(&jeu);
    return 0;
}