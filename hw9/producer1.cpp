//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw9

/*
    This program will generate an even value
    onve every second.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sharedSemaphores.hh"

int main(void) {
    int i;
    char number;
    FILE *output;

    int semOut1_val;
    sem_t* semOut1 = sem_open(SEM_OUT1, O_CREAT, 0644, 1);
    // exit the program if open failed
    if(!semOut1) {
        puts("Could not open semOut1.");
        return 0;
    }
    sem_getvalue(semOut1,&semOut1_val);

    while (1) {
       for (i = 0; i < 10; i+=2) {
           sem_wait(semOut1);
           output = fopen("./output1.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
           sem_post(semOut1);
           sleep(1);
       }
    }
    return 1;
}