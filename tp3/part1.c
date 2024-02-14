/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Hiver 2024
 * Benzekri Omar, 244082
 * Michaud Mael, 2209239
*/

#include "libprocesslab/libprocesslab.h"

void question1()
{
    if (fork() == 0) { // level 1.1
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        exit(0);
    }

    if (fork() == 0) { // level 1.2
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        exit(0);
    }

    if (fork() == 0) { // level 1.3
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        exit(0);
    }

    if (fork() == 0) { // level 1.4
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        if(fork() == 0) {
            exit(0);
        }
        wait(NULL);
        exit(0);
    }

}
