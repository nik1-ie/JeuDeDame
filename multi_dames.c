#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ----- Définition des structures de données

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
    int statut; // 1 si en cours, 0 sinon
    int nb_joueurs;
    // int joueurs_actifs[MAX_JOUEURS]; // 1 si actif, 0 sinon
    int joueur_courant;
    int tour;
    int pion_est_saisi; // 1 si un pion est saisi, 0 sinon
    int pion_i, pion_j; // la ligne et colonne du pion saisi (0 sinon)
} Jeu;


// ---------------------------------------------------------------------------
// Fonctions utilitaires et de vérification
// ---------------------------------------------------------------------------


// Fonction vérfiant si une position désigne une case dans le plateau et non à l’extérieur
int case_est_valide(int i, int j) {
    return i >= 0 && i < TAILLE && j >= 0 && j < TAILLE;
}

// pour vérifier si un pion peut sauter.
int plateau_pion_peut_sauter(Plateau *plateau, int i, int j){
    if (!case_est_valide(i,j) || plateau->pion[i][j] == 0){
        return 0; // Si la case n'est même pas dans le plateau ou si elle est vide, return 0 directement.
    }
    // Vérifier toutes les directions possibles
    // uniquement les sauts où la distance est de +/-2
    int directions[][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
    for (int d = 0; d < 8; d++) {
        int di = directions[d][0], dj = directions[d][1];
        // Vérifier si la case de destination est valide et vide
        int dest_i = i + 2 * di;
        int dest_j = j + 2 * dj;
        if (case_est_valide(dest_i, dest_j) && plateau->pion[dest_i][dest_j] == 0) {
            // Vérifier s'il y a un pion à sauter
            int saut_i = i + di;
            int saut_j = j + dj;
            if (plateau->pion[saut_i][saut_j] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// Le joueur courant capture la pièce se trouvant à la ligne i et la colonne j (numéroté entre 0 et 7) 
// arg(Jeu * jeu) : pointeur vers la structure Jeu
// Return 0 si la capture s'est bien passée, -1 sinon
int jeu_capturer(Jeu *jeu, int i, int j){
    Plateau * pl = &(jeu->plateau);
    Joueur * player = &(jeu->joueur[jeu->joueur_courant]);
    switch(pl->pion[i][j]){
        case 1:
            // printf("Le joueur %d a capturé un pion blanc ! \n", jeu->joueur_courant + 1);
            player->score += 1;
            break;
        case 2:
            // printf("Le joueur %d a capturé un pion rouge ! \n", jeu->joueur_courant + 1);
            player->score += 5;
            break;
        case 3:
            // printf("Le joueur %d a capturé un pion noir ! \n", jeu->joueur_courant + 1);
            player->score += 8;
            break;
        case 0:
            // printf("Erreur : il n'y a pas de pion à capturer en (%d,%d) ! \n", i, j);
            return -1;
            break;
    }
    pl->pion[i][j] = 0; // La case devient vide
    return 0;
}

int jeu_sauter_vers(Jeu * jeu, int i, int j){
    if (!jeu->pion_est_saisi || !case_est_valide(i, j) || jeu->plateau.pion[i][j] != 0) {
        return 0;
    }

    int di = i - jeu->pion_i;
    int dj = j - jeu->pion_j;

    // Vérifier si le mouvement est un saut valide (distance de 2)
    // Autoriser uniquement les sauts où la distance est de +/-2
    int adi = abs(di);
    int adj = abs(dj);
    if (!((adi == 2 && (adj == 0 || adj == 2)) || (adj == 2 && adi == 0))) {
        return 0;
    }

    // calculer la position du pion sauté
    int saut_i = jeu->pion_i + di/2;
    int saut_j = jeu->pion_j + dj/2;

    if (!case_est_valide(saut_i, saut_j) || jeu->plateau.pion[saut_i][saut_j] == 0) {
        return 0;
    }

    // capturer le pion sauté
    jeu_capturer(jeu, saut_i, saut_j);

    // déplacer le pion
    jeu->plateau.pion[i][j] = jeu->plateau.pion[jeu->pion_i][jeu->pion_j];
    jeu->plateau.pion[jeu->pion_i][jeu->pion_j] = 0;

    // mettre à jour la position du pion saisi
    jeu->pion_i = i;
    jeu->pion_j = j;
    // jeu->pion_est_saisi = 0;
    // jeu->pion_i = -1;
    // jeu->pion_j = -1;
    return 1;
}

// utilisée en début de tour pour saisir le pion permettant de faire des saut (par le joueur courant)
// arg(Jeu * jeu) : pointeur vers la structure Jeu
// Return 1 si le pion est saisi, 0 sinon
int jeu_saisir_pion(Jeu *jeu, int i, int j){
    // printf("Joueur %d, choisissez un pion (ligne colonne) : ", jeu->joueur_courant + 1);
    scanf("%d %d", &i, &j);
    do {
        // printf("Position invalide. Choisissez un autre pion (ligne colonne) : ");
        scanf("%d %d", &i, &j);
    } while (jeu->tour > 1 && !plateau_pion_peut_sauter(&jeu->plateau, i, j));
    
    // printf("Vous avez saisi le pion (%d,%d) \n", i, j);
    jeu->pion_est_saisi = 1;
    jeu->pion_i = i;
    jeu->pion_j = j;
     
    jeu_sauter_vers(jeu, i, j);
    return 1;
}

// Trouve toutes les positions possibles. S'il y en a qu'une seule, sauter automatiquement.
// Sinon, offrir le choix au joueur courant.
void gestion_sauts(Jeu *jeu, int li, int colonne){
    while (plateau_pion_peut_sauter(&jeu->plateau, jeu->pion_i, jeu->pion_j)) {
         
        // printf("Sauts possibles : ");
        
        // Trouver tous les sauts possibles
        int nb_sauts = 0;
        int saut_auto_i = -1, saut_auto_j = -1;

        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if (abs(i - jeu->pion_i) <= 2 && abs(j - jeu->pion_j) <= 2) {
                    int di = i - jeu->pion_i;
                    int dj = j - jeu->pion_j;
                    if ((abs(di) == 2 || abs(dj) == 2) && 
                        jeu->plateau.pion[i][j] == 0 && 
                        jeu->plateau.pion[jeu->pion_i + di/2][jeu->pion_j + dj/2] != 0) {
                        // printf("%d %d, ", i, j);
                        nb_sauts++;
                        saut_auto_i = i;
                        saut_auto_j = j;
                    }
                }
            }
        }
        
        // Si un seul saut possible, l'effectuer automatiquement
        if (nb_sauts == 1) {
            // printf("\nSaut automatique vers %d %d\n", saut_auto_i, saut_auto_j);
            jeu_sauter_vers(jeu, saut_auto_i, saut_auto_j);
        } else {
            // printf("\nEntrer un saut: ");
            scanf("%d %d", &li, &colonne);
            if (!jeu_sauter_vers(jeu, li, colonne)) {
                // printf("Saut invalide !\n");
            }
        }
    }
}

// Utilisée en début de tour pour arrêter de jouer (tant que le joueur courant n’est pas le dernier joueur)
// arg(Jeu * jeu) : pointeur vers la structure Jeu
// Return 1 si le joueur courant arrête de jouer, 0 sinon. - Fonctionnelle en théorie
int jeu_arreter(Jeu *jeu){
    Joueur * players = jeu->joueur;
    int count = 0;
    for (int i = 0; i < jeu->nb_joueurs; i++){
        if (players[i].etat == 1){
            count +=1; 
        }
    }
    if (count >=2){
        char reponse;
        // printf("Joueur %d, voulez-vous arrêter de jouer ? (o/n) : ", jeu->joueur_courant + 1);
        scanf(" %c", &reponse);
        if (reponse == 'o' || reponse == 'O'){
            jeu->joueur[jeu->joueur_courant].etat = 0;
            // printf("Le joueur %d a arrêté de jouer. \n", jeu->joueur_courant +1);
            return 1;
        }
        // printf("Il reste %d joueurs actifs. La partie continue. \n\n", count);
    } else {
        // printf("Il ne reste qu'un seul joueur actif. La partie continue. \n\n");
        return 0;
    }
    return 0;
}

// Passe au joueur suivant. Si le joueur courant décide d'arrêter de jouer, on passe au joueur suivant.
// arg(Jeu * jeu) : pointeur vers la structure Jeu
// (Fonctionnelle en théorie.)
int jeu_joueur_suivant(Jeu *jeu){
    if (jeu->joueur_courant < jeu->nb_joueurs){
        jeu->joueur_courant += 1;
    };
    if (jeu->joueur_courant == jeu->nb_joueurs){
        jeu->joueur_courant = 0;
    }
    jeu->tour += 1;
    jeu->pion_est_saisi = 0;
    jeu->pion_i = -1;
    jeu->pion_j = -1;
    if(jeu_arreter(jeu)){
        jeu->tour -= 1; 
    }else{
        return 0;
    } // Si le joueur courant veut arrêter de jouer.
    return 0;
}


// ---------------------------------------------------------------------------
// Fonctions d'initialisation
// ---------------------------------------------------------------------------

// Fonction d'initialisation du plateau : arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser 
// (Attention : ne fonctionne qu'avec les plateaux 8x8 pour le moment. La disposition des pions est aléatoire - à modifier.)
// void initialiser_plateau(Jeu * jeu){
//     Plateau * plateau = &(jeu->plateau);
// J'ai changé l'argument parce que de toute façon on appelle plateau après
void initialiser_plateau(Plateau *plateau) {
    int blancs = 34;
    int rouges = 20;
    int noirs = 10;

    srand(time(NULL)); // (TP 4) assure que le mélange est différent à chaque exécution
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            int total = blancs + rouges + noirs;
            int r = rand() % total;
            if (r < noirs) {
                plateau->pion[i][j] = 3;
                noirs--;
            } else if (r < noirs + rouges) {
                plateau->pion[i][j] = 2;
                rouges--;
            } else {
                plateau->pion[i][j] = 1;
                blancs--;
            }
        }
    }
}

// Fonction d'initialisation de la partie : arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser
void intialiser_partie(Jeu * jeu){
    jeu->joueur_courant = 0;
    jeu->tour = 1;
    jeu->pion_est_saisi = 0;
    jeu->pion_i = jeu->pion_j = 0;
    // printf("Bienvenue dans le " RED "Jeu de Dame!\n" RESET);

    // Définition du nombre de joueurs;
    jeu->nb_joueurs=0;
    do {
        // printf("Combien de joueurs sont prêts à jouer ? : ");
        scanf("%d", &(jeu->nb_joueurs));
        // printf(" \nNombre de joueurs choisi : %d \n", jeu->nb_joueurs);
        if (jeu->nb_joueurs < 1 || jeu->nb_joueurs > MAX_JOUEURS){
            // printf("Nombre de joueurs invalide ! Veuillez choisir entre 1 et %d\n", MAX_JOUEURS);
        }
    } while(jeu->nb_joueurs < 1 || jeu->nb_joueurs > MAX_JOUEURS);

    for (int i = 0; i < MAX_JOUEURS; i++) {
        jeu->joueur[i].etat = (i < jeu->nb_joueurs) ? 1 : 0;
        jeu->joueur[i].score = 0;
    }
    // init plateau, lancement jeu ??
    initialiser_plateau(&jeu->plateau);
    // printf("Initialisation terminée. Bienvenue aux %d joueurs. \n", jeu->nb_joueurs);
    return;
}

// Fonction vérifiant si la partie est finie ou non.
// arg(Jeu * jeu) : pointeur vers la structure Jeu
int endgame(Jeu * jeu){
    // Vérifie s'il y a des options de saut restantes.
    Plateau * pl = &(jeu->plateau);
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (plateau_pion_peut_sauter(pl, i, j)){
                // printf(RED "DEBUG - Il reste des sauts possibles sur le plateau!! \n" RESET);
                return 0; // Il reste un saut possible, la partie continue.
            }
        }
    }
    // Vérifie s'il reste un pion sur le plateau
    int score_total = 34 + 20 * 5 + 10 * 8;
    int joueurs_total = jeu->joueur->score;
    for (int i = 0; i < jeu->nb_joueurs; i++){
        joueurs_total += jeu->joueur[i].score;
    }
    if (joueurs_total >= score_total){
        // printf("La partie est terminée ! \n");
        for (int i = 0; i < jeu->nb_joueurs; i++){
            // printf("Joueur %d : %d points \n", i + 1, jeu->joueur[i].score);
        }
        return 1;
    }
    return 0;
}

void phase_initiale(Jeu * jeu){
    // Phase initiale : chaque joueur retire un pion blanc et l'ajoute à son score.
    // printf("Phase initiale...");
    for (int p = 0; p < jeu->nb_joueurs; p++) {
        jeu->joueur_courant = p;
         

        int li, colonne;
        // printf("Joueur %d, choisissez un pion blanc à retirer (ligne colonne) : ", p + 1);
        while (scanf("%d %d", &li, &colonne) == 2) { // l'utilisateur a bien saisi deux entiers

            if (case_est_valide(li, colonne) && jeu->plateau.pion[li][colonne] == 1) {
                jeu_capturer(jeu, li, colonne);
                break;
            }
            // printf("Position invalide. Choisissez un pion blanc (ligne colonne) : ");
        }
    }
}

// Fonction sauvegardant une partie dans un fichier. 
void jeu_ecrire(Jeu *jeu) {
    printf("%d %d %d\n", jeu->nb_joueurs, jeu->tour, jeu->joueur_courant);

    for (int i = 0; i < jeu->nb_joueurs; i++) {
        printf("%d %d\n", jeu->joueur[i].etat, jeu->joueur[i].score);
    }

    printf("%d %d %d\n", jeu->pion_est_saisi, jeu->pion_i, jeu->pion_j);

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            printf("%d", jeu->plateau.pion[i][j]);
            if (j < TAILLE - 1) printf(" ");
        }
        printf("\n");
    }
}

int moteur_principal(Jeu * jeu){
    // jeu_charger(&jeu);
    if (jeu->tour <= 1) {
        intialiser_partie(jeu);
        phase_initiale(jeu);
    }
    // Après que tous les joueurs ont retiré leur pion blanc, on passe au tour 2
    // printf("Phase initiale terminée. Que la partie commence ! \n");
    jeu_joueur_suivant(jeu);
    int i = -1;
    int j = -1;
    // boucle principale du jeu
    while (!endgame(jeu)) {
        jeu_saisir_pion(jeu, i, j);
        gestion_sauts(jeu, i, j);
         
        jeu_joueur_suivant(jeu);
    }
    return 0;
    jeu_ecrire(jeu);
}

// ----- Fonctions de sauvegarde et chargement (Tests Platon)

// Fonction chargant une partie depuis une classe Jeu.  
// arg(Jeu * jeu) : pointeur vers la structure Jeu à initialiser
void jeu_charger(Jeu *jeu) {
    scanf("%d %d %d", &jeu->nb_joueurs, &jeu->tour, &jeu->joueur_courant);

    for (int i = 0; i < jeu->nb_joueurs; i++) {
        scanf("%d %d", &jeu->joueur[i].etat, &jeu->joueur[i].score);
    }

    scanf("%d %d %d", &jeu->pion_est_saisi, &jeu->pion_i, &jeu->pion_j);

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            scanf("%d", &jeu->plateau.pion[i][j]);
        }
    }
    moteur_principal(jeu);
}

int main(void) {
    Jeu jeu;
    int i, j;
    jeu_charger(&jeu);
    scanf("%d%d", &i, &j);
    if (!jeu_sauter_vers(&jeu, i, j)) {
        printf("Saut impossible\n");
    }
    jeu_ecrire(&jeu);
    return 0;
}