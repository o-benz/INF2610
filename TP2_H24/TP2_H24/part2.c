/*
 * Ecole polytechnique de Montreal - GIGL
 * Hiver  2024
 * Initlab - part2.c
 *
 * ajoutez vos noms, prénoms et matricules
*/

#include <stdio.h>
#include <stdlib.h>
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
// TODO

// -------------------------------------------------
void part21 ()
{
 // TODO
}

void part22 ()
{
 // TODO
}

int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}
