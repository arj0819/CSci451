//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw8

/*
    This program is the third of three programs in this homework.
	It reads in the text from temp2.data and reconstructs the 
	messange into its original single line format. It also outputs
	the determined quantity of each word type.
*/

#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

	ifstream temp2;
	ifstream shared1;
	ifstream shared2;
	ofstream outFile;

	temp2.open("temp2.data");
	shared1.open("shared1.dat");
	shared2.open("shared2.dat");

	if(!temp2 || !shared1 || !shared2) {
		puts("Could not open files. Exiting...");
		exit(0);
	}
	outFile.open("temp3.data");
	
	int type1WordsCount;
	int type2WordsCount;

	while(shared1 >> type1WordsCount) {
		printf("Type 1: %d\n", type1WordsCount);
	}
	while(shared2 >> type2WordsCount) {
		printf("Type 2: %d\n", type2WordsCount);
	}
	
	string fileWord;
	while(temp2 >> fileWord) {
		outFile << fileWord + " ";
	}

	temp2.close();
	shared1.close();
	shared2.close();
	outFile.close();

	return 0;
}
