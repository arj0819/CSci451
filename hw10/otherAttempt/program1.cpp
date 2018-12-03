/*
Name:Tyler Clark
Email: tyler.w.clark@und.edu
HW#: Homework #10
Class: CSCI 451
Instructions: use provided makefile to compile the files and run the associated file generated (e.g. ./prog1)
*/

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
#include "global.h"

using namespace std;

int main(int argc, char *argv[]) {
	//sem_t* s1 = sem_open(argv[2], 0);
	int pp = atoi(argv[1]);
	//pipe(pp);
	//long int pp = strtol(argv[1], &p, 10);
	//cout << pp << '\n';
	ifstream inFile(argv[0]);
	ofstream outFile("temp1.data");
	if(!inFile) {
		cout << "Input missing; exiting\n";
		exit(0);
	}

	string s;
	//string t = "dog";
	/*
	//sem_wait(s1);
	write(pp, t.c_str(), (strlen(t.c_str())));
	//sem_post(s1);
	int j = 0;
	while(j != 3) {
		write(pp, t.c_str(), (strlen(t.c_str())));
		t+= to_string(j);
		j++;
	}
	t = "#";
	write(pp, t.c_str(), (strlen(t.c_str())));
	*/
	counter = 0;
	while(inFile >> s) {
		while(counter != 0) {

		}
		//sem_wait(s1);
		outFile << s << "\n";
		write(pp, s.c_str(), (strlen(s.c_str())));
		cout << s << '\n';
		//sem_post(s1);
		counter += 1;
		cout << counter << '\n';
	}
	counter = 2;
	
	if(inFile.eof()) {
		//s = "#";
		//sem_wait(s1);
		//write(p, s, 10)
		//sem_post(s1);
	}
	
	puts("Hi from Prog1!");
	return 0;
}
