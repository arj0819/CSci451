/*
Name:Tyler Clark
Email: tyler.w.clark@und.edu
HW#: Homework #8
Class: CSCI 451
Instructions: use provided makefile to compile the files and run the associated file generated (e.g. ./prog1)
*/

#include <stdlib.h>
#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ifstream inFile("temp2.data");
	ifstream inType1("shared1.dat");
	ifstream inType2("shared2.dat");
	ofstream outFile("temp3.data");

	if(!inFile || !inType1 || !inType2) {
		cout << "One or more files missing; exiting\n";
		exit(0);
	}
	
	int x;
	//Writes the number of type 1 and type 2 instances to the terminal
	while(inType1 >> x)
		cout << "Type 1: " << x << '\n';
	while(inType2 >> x)
		cout << "Type 2: " << x << '\n';
	
	//Writes the new sentence to a file
	string s;
	while(inFile >> s) 
		outFile << s << " ";

	puts("Hi from Prog3!");
	return 0;
}
