#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void part21() {
    printf("77dbcb01f571f1c32e196c3a7d26f62e (printed using printf)\n");
    int fileOpen = open("./output3.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fileOpen < 0) {
        perror("Appel système open a échoué");
        exit(1);
    }
    write(fileOpen, "77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n", 58);
    close(fileOpen);
}

void part22() {
    setvbuf(stdout, NULL, _IONBF, 0); // Désactiver le buffering pour stdout
    printf("77dbcb01f571f1c32e196c3a7d26f62e (printed using printf)\n");
    int fileOpen = open("./output4.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fileOpen < 0) {
        perror("Appel système open a échoué");
        exit(1);
    }
    write(fileOpen, "77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n", 58);
    close(fileOpen);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <mode>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);

    if (mode == 1) {
        part21();
    } else if (mode == 2) {
        part22();
    } else {
        fprintf(stderr, "Mode non reconnu\n");
        return 1;
    }

    return 0;
}
