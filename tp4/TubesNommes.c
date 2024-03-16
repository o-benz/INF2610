#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
    mkfifo("pipe1", 0666);
    mkfifo("pipe2", 0666);

    // P3: diff
    if (fork() == 0) {
        int pipe1 = open("pipe1", O_RDONLY);
        dup2(pipe1, STDIN_FILENO);
        close(pipe1); 
        execlp("diff", "diff", "-", "In.txt", NULL);
        exit(0); 
    }

    int pipe1 = open("pipe1", O_WRONLY);

    // P2: tr
    if (fork() == 0) {
        int pipe2 = open("pipe2", O_RDONLY);
        dup2(pipe2, STDIN_FILENO);
        close(pipe2); 

        dup2(pipe1, STDOUT_FILENO);
        close(pipe1); 

        execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
        exit(0); 
    }

    close(pipe1);

    int pipe2 = open("pipe2", O_WRONLY);

    // P1: cat
    if (fork() == 0) {
        dup2(pipe2, STDOUT_FILENO);
        close(pipe2); 
        execlp("cat", "cat", "In.txt", NULL);
        exit(0); 
    }

    close(pipe2);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    unlink("pipe1");
    unlink("pipe2");

    return 0;
}