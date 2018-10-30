//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw8

/*
    This program is the second of three programs in this homework.
	It reads in the text from temp1.data and creates a Pig Latin
	version that is stored in temp2.data, which is used by program3
	to write out the text in its original single line format. It also
	determines the count of each word type and outputs them into
	shared1.dat and shared2.dat.
*/

#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

	ifstream temp1;
	ofstream outFile;
	ofstream shared1;
	ofstream shared2;

	temp1.open("temp1.data");
	if (!temp1) {
		puts("Could not open temp1.data. Exiting...");
		exit(0);
	}

	outFile.open("temp2.data");
	shared1.open("shared1.dat");
	shared2.open("shared2.dat");

	string vowels = "aeiou";
	vector<string> fileWords;
	vector<string> parsedWords;
	string currentWord;
	int type1WordsCount = 0;
	int type2WordsCount = 0;

	while (temp1 >> currentWord) {
		fileWords.push_back(currentWord);	
	}

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

	shared1 << type1WordsCount;
	shared2 << type2WordsCount;

	temp1.close();
	outFile.close();
	shared1.close();
	shared2.close();

	return 0;
}
