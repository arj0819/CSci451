/************************************************/
/* Produces a character once every 120 seconds. */
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

    int semOut3_val;
    sem_t* semOut3 = sem_open(SEM_OUT3, O_CREAT, 0644, 1);
    // exit the program if open failed
    if(!semOut3) {
        puts("Could not open semOut3.");
        return 0;
    }
    sem_getvalue(semOut3,&semOut3_val);

    while (1) {
       for (i = 58; i < 127; i++) {
           sem_wait(semOut3);
           output = fopen("./output3.txt", "w");
           fprintf(output, "%c\n", i);
           fclose(output);
           sem_post(semOut3);
           sleep(30);
       }
    }
    return 1;
}