//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
    This program is the first of three programs in this homework.
	It reads in the text from input.data and outputs it in a one
	word per line format into temp1.data which is used by program2.
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
#include <thread>
#include <fstream>
#include <sys/shm.h>

using namespace std;

int main(int argc, char *argv[]) {

	puts("Made it to Program 1");

	key_t key; //unique key for shared memory segment
	int shmid; //shared memory ID
	int* data;
	
	key = 1234;	
	if((shmid = shmget(key,100,0666| IPC_CREAT)) == -1)
	{
		perror("Shared memory creation failed.");
		exit(1);
	}
	data = (int *) shmat(shmid, NULL, 0);
	if(data == (void *)(-1))
	{
		perror("pointer to shared memory failed.\n");
		exit(1);
	}
	int wordTypeValues[] = {data[0], data[1]};
	printf("Shared memory data[0]: %d\n",wordTypeValues[0]);
	printf("Shared memory data[1]: %d\n",wordTypeValues[1]);
	shmdt(data);
	shmctl(shmid,IPC_RMID, NULL);

	ifstream inFile;
	ofstream outFile;
	string fileWord;

	inFile.open("input.data");
	if (!inFile) {
		puts("Could not open input.data. Exiting...");
		exit(0);
	}

	outFile.open("temp1.data");
	while (inFile >> fileWord) {
		outFile << fileWord << endl;
	}

	inFile.close();
	outFile.close();
	
	return 0;
}
