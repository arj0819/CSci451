//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw6

/*
    This is program 1 of 4 for this assignment. This program
    will always be executed first and will create a set of
    semaphores for the rest of the programs to use.
*/

#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "sharedSemaphores.hh"

using namespace std;

int main(int argc, char *argv[]) {

    // prepare ints for semaphore values to be held in
    int semOrder_val;
    int semOutOfSequence_val;
    int semProcessCounter_val;

    // try to open up the semaphores
    // sem_open(sem name, create if not exist, mode(access permissions(rwx)), initial value)
    sem_t* semOrder = sem_open(SEM_ORDER, O_CREAT, 0644, 0);
    sem_t* semOutOfSequence = sem_open(SEM_OUT_OF_SEQUENCE, O_CREAT, 0644, 0);
    sem_t* semProcessCounter = sem_open(SEM_PROCESS_COUNTER, O_CREAT, 0644, 0);

    // exit the program if open failed
    if(!semOrder || !semOutOfSequence || !semProcessCounter) {
        puts("Could not open semaphores.");
        return 0;
    }

    // get the value of each semaphore and store in previously declared ints
    sem_getvalue(semOrder,&semOrder_val);
    sem_getvalue(semOutOfSequence,&semOutOfSequence_val);
    sem_getvalue(semProcessCounter,&semProcessCounter_val);

    // if we've already executed > 3 processes or not starting from beginning,
    // we close and unlink the semaphores to have the ability to reset them.
    if (semProcessCounter_val > 3 || semOrder_val > 0) {
        sem_close(semOrder);
        sem_close(semOutOfSequence);
        sem_close(semProcessCounter);
        
        sem_unlink(SEM_ORDER);
        sem_unlink(SEM_OUT_OF_SEQUENCE);
        sem_unlink(SEM_PROCESS_COUNTER);
        puts("Semaphores reset. Please initialize them from Program #0.");
        return 0;
    }

    puts("Executing process #0.");

    // increment semProcessCounter and semOrdedr
    sem_post(semProcessCounter);
    sem_post(semOrder);

    // if we've already done one process, increment 
    // semOutOfSequence if we haven't already
    if (semProcessCounter_val > 1) {
        if (semOutOfSequence_val < 1) {
            sem_post(semOutOfSequence);
        }
    }

    // optional debugging printouts
    // sem_getvalue(semOutOfSequence,&semOutOfSequence_val);
    // printf("Value of semOrder:          %d\n", semOrder_val);
    // printf("Value of semOutOfSequence:  %d\n", semOutOfSequence_val);
    // printf("Value of semProcessCounter: %d\n", semProcessCounter_val);

    return 0;
}