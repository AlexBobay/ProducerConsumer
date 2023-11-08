#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>

#include "sharedMem.h"
int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);

#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

int buffer[10];
int count = 0;

int main(int argc, char* argv[]) {
    int fd;
    char           *shmpath;
    struct shmbuf  *shmp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    shmpath = argv[1];

    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);

    fd = shm_open(shmpath, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd == -1)
        errExit("shm_open"); // checks to see if there is an fd there
    
    shmp = mmap(NULL, shmp->cnt, PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    for (int i = 0; i < THREAD_NUM; i++) {
        if (i < 0) {
            int y;

            // Remove from the buffer
            sem_wait(&shmp->semFull);
            pthread_mutex_lock(&mutexBuffer);
            y = buffer[count - 1];
            count--;
            pthread_mutex_unlock(&mutexBuffer);
            sem_post(&shmp->semEmpty);

            // Consume
            printf("Got %d\n", y);
            sleep(1);
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    shm_unlink(shmpath);
    exit(EXIT_SUCCESS);
}
