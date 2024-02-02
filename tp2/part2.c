#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void part21() {
    char message[] = "77dbcb01f571f1c32e196c3a7d26f62e (printed using printf)";
    for (int i = 0; i < sizeof(message); i++) {
        printf("%c" ,message[i]);
    }
        write(0, "77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n", 56);
}

void part22() {
    setvbuf(stdout, NULL, _IONBF, 0); // Désactiver le buffering pour stdout
        char message[] = "77dbcb01f571f1c32e196c3a7d26f62e (printed using printf)";
    for (int i = 0; i < sizeof(message); i++) {
        printf("%c" ,message[i]);
    }
        write(0, "77dbcb01f571f1c32e196c3a7d26f62e (printed using write)\n", 56);
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
