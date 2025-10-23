#include <stdio.h>

// Définitions de codes ANSI pour les couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

int main() {
    // Affichage de texte en différentes couleurs
    printf(RED "Texte en rouge\n" RESET);
    printf(GREEN "Texte en vert\n" RESET);
    printf(YELLOW "Texte en jaune\n" RESET);
    printf(BLUE "Texte en bleu\n" RESET);
    printf(MAGENTA "Texte en magenta\n" RESET);
    printf(CYAN "Texte en cyan\n" RESET);
    printf(WHITE "Texte en blanc\n" RESET);

    // Exemple avec texte en gras et couleur
    printf("\033[1;31mTexte en rouge gras\033[0m\n");

    return 0;
}

// Explications
// - \033 (ou \x1B) est le caractère d’échappement ANSI.
// - [31m : code pour le rouge (32 = vert, 33 = jaune, etc.).
// - [0m : réinitialise la couleur et le style.
// - On peut combiner plusieurs attributs, par exemple :
//      \033[1;34m → bleu en gras
//      \033[4;32m → vert souligné