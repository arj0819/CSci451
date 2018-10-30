//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw8

/*
    This program is the first of three programs in this homework.
	It reads in the text from input.data and outputs it in a one
	word per line format into temp1.data which is used by program2.
*/

#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

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
