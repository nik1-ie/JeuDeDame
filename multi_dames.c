#include <stdio.h>

// Définitions de codes ANSI pour les couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"
#define BLACK   "\033[90m"

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
// (Selection d'un pion à tester)
void jeu_afficher(Jeu * jeu){
    Plateau * pl = &(jeu->plateau);
    printf("  ");
    for(int i = 0; i < TAILLE; i++){
        printf(" %d ", i);
    };
    printf("\n  ");
    for(int i = 0; i < TAILLE; i++){
        printf(" _ ");
    };
    printf("\n");
    for (int i = 0; i < TAILLE; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAILLE; j++) {
            switch (pl->pion[i][j]) {
                switch (i = jeu->pion_i, j = jeu->pion_j, jeu->pion_est_saisi){
                    case 1: printf(WHITE "[o]" RESET); break;
                    case 2: printf(RED "[x]" RESET); break;
                    case 3: printf(BLACK "[+]" RESET); break;
                }
                case 0: printf(" . "); break;
                case 1: printf(WHITE " o " RESET); break;
                case 2: printf(RED " x " RESET); break;
                case 3: printf(BLACK " + " RESET); break;
            }
        }
        printf("\n");
    }
    return;
}

// Fonction d'initialisation du plateau : arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser 
// (Attention : ne fonctionne qu'avec les plateaux 8x8 pour le moment. La disposition des pions est aléatoire - à modifier.)
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
    switch (jeu->nb_joueurs){
        case 1:
            jeu->joueur[0].etat = 1;
            break;
        case 2:
            jeu->joueur[0].etat = 1;
            jeu->joueur[1].etat = 1;
            break;
        case 3:
            jeu->joueur[0].etat = 1;
            jeu->joueur[1].etat = 1;
            jeu->joueur[2].etat = 1;
            break;
        case 4:
            jeu->joueur[0].etat = 1;
            jeu->joueur[1].etat = 1;
            jeu->joueur[2].etat = 1;
            jeu->joueur[3].etat = 1;
            break;
    } // c'est un peu long, mais bon...
    jeu->joueur_courant = 0;
    jeu->tour = 1;
    // init plateau, lancement jeu ??
    initialiser_plateau(jeu);
    printf("Initialisation terminée. Bienvenue aux %d joueurs.", jeu->nb_joueurs);
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

// Passe au joueur suivant.
// (Fonctionnelle en théorie.)
int jeu_joueur_suivant(Jeu *jeu){
    if (jeu->joueur_courant < jeu->nb_joueurs){
        jeu->joueur_courant += 1;
    };
    if (jeu->joueur_courant == jeu->nb_joueurs){
        jeu->joueur_courant = 0;
    }
    jeu->tour += 1;
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
    int i,j; //i et j stockent les coordonnées saisies par l'utilisateur
    return 0;


    // scanf("%d%d", &i, &j);
    // if (!jeu_sauter_vers(&jeu, i, j)){
    //     printf("Actionimpossible\n");
    // }
    // jeu_ecrire(&jeu);
}