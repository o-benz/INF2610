#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fileOpen = open("./output2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fileOpen < 0) {
        perror("Appel système open a échoué");
        return 1;
    }

    printf("Saisissez votre texte suivi de CTRL-D :\n");

    char c;
    while (read(STDIN_FILENO, &c, 1) > 0) {
        if (c == 4)
            break;
        if (write(fileOpen, &c, 1) != 1) {
            perror("Appel système write a échoué");
            close(fileOpen);
            return 1;
        }
    }

    close(fileOpen);\
    return 0;
}
