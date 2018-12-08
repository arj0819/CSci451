//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
    This program takes the arguments from master and feeds words
	from the input.data file into pipe1, regulated by a semaphore.
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
sem_t* sem1;

int main(int argc, char *argv[]) {

	ofstream outFile;
	string fileWord;
	
	ifstream inFile(argv[0]);
	if (!inFile) {
		puts("Could not open input.data. Exiting...");
		exit(0);
	}
	int pipe1Write = atoi(argv[1]);
	sem1 = sem_open(argv[2], 0);
	outFile.open("temp1.data");

	int sem1Value;
	while(inFile >> fileWord) {
		sem_getvalue(sem1,&sem1Value);
		while(sem1Value == 1) {
			sem_getvalue(sem1,&sem1Value);
            usleep(1);
		}
		sem_post(sem1);
		fileWord.append("|");
		outFile << fileWord << "\n";
		write(pipe1Write, fileWord.c_str(), (strlen(fileWord.c_str())));
		sem_getvalue(sem1,&sem1Value);
	}
	
	if(inFile.eof()) {
		sem_post(sem1);
		sem_post(sem1);
		sem_post(sem1);
	}

	inFile.close();
	outFile.close();
	
	return 0;
}
