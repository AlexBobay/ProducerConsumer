#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

#define TABLE_SIZE 2

struct shmbuf {
    sem_t  semFull;            /* POSIX unnamed semaphore */
    sem_t  semEmpty;            /* POSIX unnamed semaphore */
    size_t cnt;             /* Number of bytes used in 'buf' */
    char   buf[TABLE_SIZE];   /* Data being transferred */
};
