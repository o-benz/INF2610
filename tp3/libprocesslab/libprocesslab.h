/*
 * libprocesslab.h
*/

#ifndef _LIBPROCESSLAB_H
#define _LIBPROCESSLAB_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#define _NB_1 3
#define _NB_2 6
#define _ALL 10
#define _LEVELS 2
struct seg_t { int procLevel; int procNum; pid_t pid; pid_t ppid; };
struct seg_t* allocateSharedMemory(long size);
void registerProc( pid_t pid, pid_t ppid, int procLevel, int procNum);
void printProcRegistrations();
#endif
