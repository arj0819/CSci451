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
#include <vector>
#include <ctype.h>
#include "global.h"

using namespace std;


int main(int argc, char *argv[]) {
	vector<char> vowels{'a', 'e', 'i', 'o', 'u'};
	//sem_t* s1 = sem_open(argv[1], 0);
	char buf[80];
	int pp = atoi(argv[0]);
	//char *p;
	//long int pp = strtol(argv[0], &p, 10);
	//sem_wait(s1);
	while(counter != 2) {
		cout << counter << " yes\n";
		while(counter != 1) {
			//cout << counter << " yes\n";
		}
		cout << counter << " yes\n";
		int b = read(pp, buf, sizeof(buf));
		cout << "Reading: " << buf << "\n";
		counter -= 1;
	}

	ifstream inFile("temp1.data");
	ofstream outFile("temp2.data");
	ofstream shared1("shared1.dat");
	ofstream shared2("shared2.dat");
	if(!inFile) {
		cout << "temp1.data is missing; exiting\n";
		exit(0);
	}
	

	vector<string> temp1;
	string s;
	//Inserts words from the file into the vector
	while(inFile >> s)
		temp1.push_back(s);	

	vector<string> temp2;
	int vows = 0;
	int cons = 0;
	//Loops through the size of the vector
	for(int i = 0; i < temp1.size(); i++) {
		bool hasVowel = false;
		char c = temp1[i].at(0);
		//Basically checks to see if a vowel is present at the beginning
		//and if so performs the necessary translation to pig latin
		for(int j = 0; j < vowels.size(); j++) {
			if(char(tolower(c)) == vowels[j]) {
				hasVowel = true;
				//Vowels
				s = temp1[i];
				vows++;
				//Tells if punctuation is present
				if(ispunct(temp1[i].back())) {
					s.insert((s.size() - 1), "ray");
					temp2.push_back(s);
				} else {
					s.append("ray");
					temp2.push_back(s);
				}			
			}	
		}
		//Performs the necessary translation to pig latin for consonants
		if(!hasVowel) {
			//Consonants
			s = temp1[i];
			cons++;
			if(ispunct(temp1[i].back())) {
				string tmp = "";
				s.erase(0,1);
				tmp = tmp + c + "ay";
				s.insert((s.size() - 1), tmp);
				temp2.push_back(s);
			} else {
				string tmp = "";
				s.erase(0,1);
				tmp = tmp + c + "ay";
				s.append(tmp);
				temp2.push_back(s);
			}
		}
	}	

	//Writes the contnets of the newly translated words to a file	
	for(int i = 0; i < temp2.size(); i++)
		outFile << temp2[i] << '\n';

	shared1 << vows;
	shared2 << cons;

	puts("Hi from Prog2!");
	return 0;
}
