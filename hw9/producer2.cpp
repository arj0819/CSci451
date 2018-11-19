/************************************************/
/* Produces an odd value once every 30 seconds. */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sharedSemaphores.hh"

int main(void) {
    int i;
    char number;
    FILE *output;

    int semOut2_val;
    sem_t* semOut2 = sem_open(SEM_OUT2, O_CREAT, 0644, 1);
    // exit the program if open failed
    if(!semOut2) {
        puts("Could not open semOut2.");
        return 0;
    }
    sem_getvalue(semOut2,&semOut2_val);

    while (1) {
       for (i = 1; i < 10; i+=2) {
           sem_wait(semOut2);
           output = fopen("./output2.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           sem_post(semOut2);
           sleep(10);
       }
    }
    return 1;
}