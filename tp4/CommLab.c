// Commlab
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {

    // QUESTION 1 --------------------------------------
    // Compile question 1:
    if (!fork()) {
        execlp("gcc", "gcc", "-o", "ansq1", "TubesNommes.c", NULL);
    }
    wait(NULL);
    
    // run the solution
    if (!fork()) {
        execl("./ansq1", "ansq1", NULL);
    }
    
    wait(NULL);
    unlink("ansq1");
    
    // QUESTION 2 --------------------------------------
    // compile question 2
    if (!fork()) {
        execlp("gcc", "gcc", "-o", "ansq2", "TubesAnonymes.c", NULL);
    }
    
    wait(NULL);
    
    // run the solution
    if (!fork()) {
        execl("./ansq2", "ansq2", NULL);
    }
    
    wait(NULL);
    unlink("ansq2");
    // now the python grader will interpret the files
}
