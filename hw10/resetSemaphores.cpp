//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
    This program resets the semaphores for the rest of the system.
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <semaphore.h>

int main(int argc, char *argv[]) {
    
	//Opens the semaphores
    sem_t* semOut1 = sem_open("/sem1", 0);
    sem_t* semOut2 = sem_open("/sem2", 0);

    //Terminate if semaphores failed to open
    if(!semOut1 || !semOut2) {
        puts("Could not open semaphores.\nPlease make clean, make all, ane make run");
        return 0;
    }

	//Unlinks the semaphores
    sem_unlink("/sem1");
    sem_unlink("/sem2");

    return 0;
}
