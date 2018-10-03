//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw6

/*
    This is program 3 of 4 for this assignment. This program
    only prints a message if it is executed immediately after
    program 2.
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
    sem_t* semOrder = sem_open(SEM_ORDER, 0);
    sem_t* semOutOfSequence = sem_open(SEM_OUT_OF_SEQUENCE, 0);
    sem_t* semProcessCounter = sem_open(SEM_PROCESS_COUNTER, 0);
    
    // exit the program if open failed
    if(!semOrder || !semOutOfSequence || !semProcessCounter) {
        puts("Could not open semaphores. Please initialize them from Program #0.");
        return 0;
    }
    sem_getvalue(semProcessCounter,&semProcessCounter_val);

    // if we already performed more than 3 processes, close all semaphores and
    // unlink so we can reset them to try again from program 0.
    if (semProcessCounter_val > 3) {
        sem_close(semOrder);
        sem_close(semOutOfSequence);
        sem_close(semProcessCounter);
        
        sem_unlink(SEM_ORDER);
        sem_unlink(SEM_OUT_OF_SEQUENCE);
        sem_unlink(SEM_PROCESS_COUNTER);
        puts("Semaphores reset. Please initialize them from Program #0.");
        return 0;
    }
    // otherwise, increment semProcessCounter
    sem_post(semProcessCounter);

    sem_getvalue(semOrder,&semOrder_val);
    sem_getvalue(semOutOfSequence,&semOutOfSequence_val);

    // if our order is correct and we aren't out of sequence
    if (semOrder_val == 2 && semOutOfSequence_val == 0) {
        // we execute proces 2 and increment semOrder
        puts("Executing process #2.");
        sem_post(semOrder);
    } else {
        // otherwise, increment semOutOfSequence if we haven't already
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