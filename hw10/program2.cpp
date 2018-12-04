//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
	This program takes words from pipe 1, converts them to Pig Latin,
	then feeds them to pipe 2, all regulated by semaphores.
*/

#include <fstream>
#include <string>
#include <vector>
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
#include <ctype.h>

using namespace std;

//semaphores in global space
sem_t* sem1;
sem_t* sem2;

int main(int argc, char *argv[]) {

	ifstream temp1;
	ofstream outFile;

	int sem1Value;
	int sem2Value;

	int pipe1 = atoi(argv[0]);
	int pipe2 = atoi(argv[1]);
	sem1 = sem_open(argv[2], 0);
	sem2 = sem_open(argv[3], 0);

	temp1.open("temp1.data");
	if (!temp1) {
		puts("Could not open temp1.data. Exiting...");
		exit(0);
	}
	outFile.open("temp2.data");

	sleep(0.25);
	string vowels = "aeiou";
	vector<string> fileWords;
	vector<string> parsedWords;
	string currentWord;
	int type1WordsCount = 0;
	int type2WordsCount = 0;

	char pipe1ReadBuffer[256];
	string word;
    sem_getvalue(sem1,&sem1Value);
	while(sem1Value < 2) {
	    sem_getvalue(sem1,&sem1Value);
		while(sem1Value == 0) {
			sem_getvalue(sem1,&sem1Value);
		}
		sem_wait(sem1);
		read(pipe1, pipe1ReadBuffer, sizeof(pipe1ReadBuffer));
		word = pipe1ReadBuffer;
		string::size_type delimiterPosition = word.find('|');
		word = word.substr(0, delimiterPosition);
		fileWords.push_back(word);
	    sem_getvalue(sem1,&sem1Value);
	}
	sem_wait(sem1);
	sem_wait(sem1);
	sem_wait(sem1);

	for (int i = 0; i < fileWords.size(); i++) {
		currentWord = fileWords[i];
		char firstChar = currentWord.front();
		char lastChar = currentWord.back();
		string suffix = "";

		if (vowels.find(tolower(firstChar)) == string::npos) {
			type2WordsCount++;
			currentWord.erase(0,1);
			suffix = suffix + firstChar + "ay";
		} else {
			type1WordsCount++;
			suffix = "ray";
		}

		if(ispunct(lastChar)) {
			currentWord.insert((currentWord.size() - 1), suffix);
		} else {
			currentWord.append(suffix);
		}

		parsedWords.push_back(currentWord);
	}	

	for (int i = 0; i < parsedWords.size(); i++) {
		outFile << parsedWords[i] << endl;
	}

	string pigLatinWord;
	sem_getvalue(sem2,&sem2Value);
	for(int i = 0; i < parsedWords.size(); i++) {
		while(sem2Value == 1) {
			sem_getvalue(sem2,&sem2Value);
		}
		sem_post(sem2);
		pigLatinWord = parsedWords[i];
		pigLatinWord.append("|");
		write(pipe2, pigLatinWord.c_str(), (strlen(pigLatinWord.c_str())));
		sem_getvalue(sem2,&sem2Value);
	}
	sem_post(sem2);
	sem_post(sem2);
	sem_post(sem2);

	key_t key;
	int shmid;
	int* sharedData;
	int wordTypeValues[] = {type1WordsCount,type2WordsCount};

	key = atoi(argv[4]);
	if((shmid = shmget(key,100,0666| IPC_CREAT)) == -1)
	{
		perror("Couldn't create shared memory segment.");
		exit(1);
	}
	sharedData = (int *) shmat(shmid, NULL, 0);
	if(sharedData == (void *)(-1)) {
		perror("Prog2, pointer to shared memory failed.\n");
		exit(1);
	}
	sharedData[0] = wordTypeValues[0];
	sharedData[1] = wordTypeValues[1];
	shmdt(sharedData);

	temp1.close();
	outFile.close();

	return 0;
}
