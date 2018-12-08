//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
    This program reads words from pipe 2 and reassembles the original
	input.data translated into Pig Latin, regulated by a semaphore.
*/

#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/shm.h>

using namespace std;

//semaphores in global space
sem_t* sem2;

int main(int argc, char *argv[]) {

	ofstream outFile(argv[0]);
	int pipe2 = atoi(argv[1]);
	sem2 = sem_open(argv[2], 0);

	int sem2Value;
	key_t key;
	int shmid;
	int* sharedData;
	
	sleep(0.5);
	key = atoi(argv[3]);	
	if((shmid = shmget(key,100,0666| IPC_CREAT)) == -1)
	{
		perror("Couldn't create shared memory segment.");
		exit(1);
	}
	sharedData = (int *) shmat(shmid, NULL, 0);
	if(sharedData == (void *)(-1))
	{
		perror("Prog3, pointer to shared memory failed.\n");
		exit(1);
	}
	int wordTypeValues[] = {sharedData[0], sharedData[1]};

	printf("Type 1: %d\n", wordTypeValues[0]);
	printf("Type 2: %d\n", wordTypeValues[1]);

	shmdt(sharedData);
	shmctl(shmid,IPC_RMID,NULL);

	ifstream temp2;
	temp2.open("temp2.data");
	if(!temp2) {
		puts("Could not open temp2.data. Exiting...");
		exit(0);
	}	

	char pipe2ReadBuffer[256];
	string word;
    sem_getvalue(sem2,&sem2Value);

	while(sem2Value < 2) {
	    sem_getvalue(sem2,&sem2Value);

		while(sem2Value == 0) {
			sem_getvalue(sem2,&sem2Value);
            usleep(1);
		}
		sem_wait(sem2);
		read(pipe2, pipe2ReadBuffer, sizeof(pipe2ReadBuffer));
		word = pipe2ReadBuffer;
		string::size_type delimiterPosition = word.find('|');
		word = word.substr(0, delimiterPosition);
		outFile << word << " ";
	    sem_getvalue(sem2,&sem2Value);
	}
	sem_wait(sem2);
	sem_wait(sem2);
	sem_wait(sem2);

	temp2.close();
	outFile.close();

	return 0;
}
