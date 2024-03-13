#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
    mkfifo("pipe1", 0666);
    mkfifo("pipe2", 0666);

    if (fork() == 0) { // P3
        int pipe1 = open("pipe1", O_RDONLY);
        dup2(pipe1, STDIN_FILENO);
        execlp("diff", "diff", "-", "In.txt", NULL);
    }

    int pipe1 = open("pipe1", O_WRONLY);

    if (fork() == 0) { // P2
        int pipe2 = open("pipe2", O_RDONLY);
        dup2(pipe2, STDIN_FILENO);
        dup2(pipe1, STDOUT_FILENO);
        execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
    }

    int pipe2 = open("pipe2", O_WRONLY);

    if (fork() == 0) { // P1
        dup2(pipe2, STDOUT_FILENO);
        execlp("cat", "cat", "In.txt", NULL);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    unlink("pipe1");
    unlink("pipe2");

    return 0;
}