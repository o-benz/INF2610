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
    pid_t pid, ppid;
    int level, num, status;
    int total_child = 0;

    // Register level0 process
    pid = getpid();
    ppid = getppid();
    level = 0;
    num = 0;
    
    registerProc(pid, ppid, level, num);

    if ((pid = fork()) == 0) { // level 1.1
        ppid = getppid();
        level = 1;
        num = 1;
        registerProc(pid, ppid, level, num);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 1;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        exit(1);
    }
    wait(&status);
    total_child += WEXITSTATUS(status) + 1;

    if ((pid = fork()) == 0) { // level 1.2
        ppid = getppid();
        level = 1;
        num = 2;
        registerProc(pid, ppid, level, num);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 2;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 3;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        exit(2);
    }
    wait(&status);
    total_child += WEXITSTATUS(status) + 1;

    if ((pid = fork()) == 0) { // level 1.3
        ppid = getppid();
        level = 1;
        num = 3;
        registerProc(pid, ppid, level, num);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 4;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        exit(1);
    }
    wait(&status);
    total_child += WEXITSTATUS(status) + 1;

    if ((pid = fork()) == 0) { // level 1.4
        ppid = getppid();
        level = 1;
        num = 4;
        registerProc(pid, ppid, level, num);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 5;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 6;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        if((pid = fork()) == 0) {
            ppid = getppid();
            level = 2;
            num = 7;
            registerProc(pid, ppid, level, num);
            exit(0);
        }
        wait(NULL);
        exit(3);
    }
    wait(&status);
    total_child += WEXITSTATUS(status) + 1;

    while (wait(NULL) > 0);

    printf("Nombre total de fils crée : %d\n", total_child);
    printProcRegistrations();
}