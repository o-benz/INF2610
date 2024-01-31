/*
 * Ecole polytechnique de Montreal - GIGL
 * Hiver  2024
 * Initlab - part1.c
 * 
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 * Michaud, Maël
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------

   #include <fcntl.h>

   int open(const char *path, int oflags);
// -------------------------------------------------

int main () {
    // TODO
    int fileOpen = open("./output2.txt", O_TRUNC);
    if (fileOpen < 0) {
        printf("Appel système open a échoué");
        return 1;
    }
    printf("Saisissez votre texte suivi de CTRL-D :\n");
    

    return 0;
}
