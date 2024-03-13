#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    if (fork() == 0) {
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("cat", "cat", "In.txt", NULL);
    }

    if (fork() == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("tr", "tr", "[a-z]", "[A-Z]", NULL);
    }

    close(pipe1[0]);
    close(pipe1[1]);

    if (fork() == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        int fd = open("Out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0660);
        dup2(fd, STDOUT_FILENO);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("diff", "diff", "-", "In.txt", NULL);
    }

    close(pipe2[0]);
    close(pipe2[1]);

    while (wait(NULL) > 0);

    return 0;
}