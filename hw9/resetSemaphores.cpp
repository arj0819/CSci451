#include <cstdio>
#include "sharedSemaphores.hh"

int main(int argc, char *argv[]) {

    // try to open up the semaphores
    // sem_open(sem name, oflag)
    sem_t* semOut1 = sem_open(SEM_OUT1, 0);
    sem_t* semOut2 = sem_open(SEM_OUT2, 0);
    sem_t* semOut3 = sem_open(SEM_OUT3, 0);
    sem_t* semOrder = sem_open(SEM_ORDER, 0);

    // exit the program if open failed
    if(!semOut1 || !semOut2 || !semOut3 || !semOrder) {
        puts("Could not open semaphores.\nPlease initialize them by running the program using\nthe steps outlined in the comments of sampler.cpp.");
        return 0;
    }
    
    // close all semaphores
    sem_close(semOut1);
    sem_close(semOut2);
    sem_close(semOut3);
    sem_close(semOrder);
    
    // unlink them so their values can be reinitialized on make run again
    sem_unlink(SEM_OUT1);
    sem_unlink(SEM_OUT2);
    sem_unlink(SEM_OUT3);
    sem_unlink(SEM_ORDER);

    return 0;
}