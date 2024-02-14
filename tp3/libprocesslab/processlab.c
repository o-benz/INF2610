// processlab.c

#include "libprocesslab.h"
#include "part1.h"
#include "part2.h"


int main(int argc, char*argv[])
{
    if(argc!=2)
    { printf("Ligne de commande attendue : ./processlab n, avec n = 1 ou 2 \n");
      _exit(1);
    }
    switch (atoi(argv[1])) {
        case 1:
            question1();
            break;
        case 2:
            question2();
            break;
        default :
            printf("Ligne de commande attendue : ./processlab n, avec n = 1 ou 2 \n");
            _exit(1);
    }
  return 0;

}
