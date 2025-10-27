#include <stdio.h>

// Définitions de codes ANSI pour les couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define GREY "\033[90m"

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

// Fonction affichant le plateau à l’utilisateur. arg(Jeu * jeu) : pointeur vers la structure Jeu à afficher.
// (Selection d'un pion à ajouter.)
void jeu_afficher(Jeu * jeu){
    Plateau * pl = &(jeu->plateau);
    for(int i = 0; i < TAILLE; i++){
        printf("  %d", i);
    };
    printf("\n");
    for(int i = 0; i < TAILLE; i++){
        printf("  _");
    };
    printf("\n");
    for(int j = 0; j < TAILLE; j++){
        printf("%d", j+1);
        for(int k = 0; k < TAILLE; k++){
            if (pl->pion[j][k] == 0){
                printf("  .");
            }
            else if (pl->pion[j][k] == 1){
                printf(WHITE "  +" RESET);
            }
            else if (pl->pion[j][k] == 2){
                printf(RED "  +" RESET);
            }
            else if (pl->pion[j][k] == 3){
                printf(GREY "  +" RESET);
            }
        }
        printf("\n");
    }
}

// Fonction d'initialisation du plateau : arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser 
// (Attention : ne fonctionne qu'avec les plateaux 8x8 pour le moment.)
void initialiser_plateau(Jeu * jeu){
    Plateau * plateau = &(jeu->plateau);
    if (TAILLE == 8){ 
        int tmp[8][8] = {
            {1, 1, 1, 1, 1, 1, 1, 1},      // 8 blancs (total: 8)
            {1, 1, 1, 1, 1, 1, 1, 1},      // 8 blancs (total: 16)
            {1, 1, 1, 1, 1, 1, 1, 1},      // 8 blancs (total: 24)
            {1, 1, 1, 1, 1, 1, 1, 1},      // 8 blancs (total: 32)
            {1, 1, 2, 2, 2, 2, 2, 2},      // 2 blancs (total: 34), 6 rouges (total: 6)
            {2, 2, 2, 2, 2, 2, 2, 2},      // 8 rouges (total: 14)
            {2, 2, 3, 3, 3, 3, 3, 3},      // 2 rouges (total: 16), 6 noirs (total: 6)
            {3, 3, 3, 3, 0, 0, 0, 0}       // 4 noirs (total: 10), 4 vides
        };

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                plateau->pion[i][j] = tmp[i][j];
    }
    jeu_afficher(jeu);
    return;
}

// Fonction d'initialisation de la partie : arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser
void intialiser_partie(Jeu * jeu){
    printf("Bienvenue dans le " RED "Jeu de Dame!" RESET);

    // Définition du nombre de joueurs;
    jeu->nb_joueurs=0;
    do {
        printf("\n Combien de joueurs sont prêts à jouer ? : ");
        scanf("%d", &(jeu->nb_joueurs));
        printf(" \nNombre de joueurs choisi : %d \n", jeu->nb_joueurs);
        if (jeu->nb_joueurs < 1 || jeu->nb_joueurs > MAX_JOUEURS){
            printf("Nombre de joueurs invalide ! Veuillez choisir entre 1 et %d\n", MAX_JOUEURS);
        }
    } while(jeu->nb_joueurs < 1 || jeu->nb_joueurs > MAX_JOUEURS);

    // Création de x joueurs, init de leur état

    // init plateau, lancement jeu ??
    initialiser_plateau(&(jeu->plateau));
    return;
}

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


int main(void){
    Jeu jeu;
    intialiser_partie(&jeu);
    return 0;
    // int i,j;
    // jeu_charger(&jeu);
    // scanf("%d%d", &i, &j);
    // if (!jeu_sauter_vers(&jeu, i, j)){
    //     printf("Actionimpossible\n");
    // }
    // jeu_ecrire(&jeu);
}