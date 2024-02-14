/*
 *  libprocesslab.c
 */


#include "libprocesslab.h"

struct seg_t * pseg;

struct seg_t* allocateSharedMemory(long size)
{
    int fd = shm_open("a", O_RDWR|O_CREAT, 0600 );  // créer un segment
    if (fd==-1) { _exit(1); }
    off_t taille = sizeof(struct seg_t) * size;
    ftruncate(fd, taille);
    // rattacher le segment à l’espace d’adressage du processus appelant
    struct seg_t *pa = (struct seg_t *) mmap(NULL, taille,PROT_READ|PROT_WRITE, MAP_SHARED, fd,0);
    close(fd);
    if(pa==NULL) { _exit(1);}
    for(fd=0; fd<size; fd++) {pa[fd].procLevel = 0; pa[fd].procNum=0; pa[fd].pid=0; pa[fd].ppid=0;}
    return pa;
}

void registerProc(pid_t pid, pid_t ppid, int procLevel, int procNum)
{       int i;
        if(procLevel<0 || procLevel>_LEVELS) return;
        if(procLevel==1 && (procNum<1 || procNum>_NB_1)) return;
        if(procLevel==2 && (procNum<1 || procNum>_NB_2)) return;
        if(procLevel==0)
        { pseg= allocateSharedMemory(_ALL);i=0;}
        if(procLevel==1) i=procNum;
        if(procLevel==2) i=_NB_1+procNum;
        if(pseg==NULL) return;
        pseg[i].procLevel = procLevel; pseg[i].procNum=procNum; pseg[i].pid=pid; pseg[i].ppid=ppid;
}


void printProcRegistrations()
{  int i;
        for(i=0; i<_ALL; i++)
    printf("procLevel=%d, procNum=%d,  pid=%d, ppid=%d \n", pseg[i].procLevel,  pseg[i].procNum, pseg[i].pid, pseg[i].ppid);
    munmap(pseg, _ALL*sizeof(struct seg_t));
}

