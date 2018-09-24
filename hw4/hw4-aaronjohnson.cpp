//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw3

//NOTE: Please compile with the following command:

//      g++ -std=c++11 hw3-aaronjohnson.cpp -l pthread -o hw3-aaronjohnson

//      This program requires at least -std=c++0x and linking to the
//      pthread library to implement std::thread.

/*
    This program downloads a text file, loads the text of the file 
    into the program dynamically using C++ std::string class, lowers
    the case of each word in the file, then parses through it with 
    two threads, one to count the # of occurrences of the word 
    "easy", and the other to count the # of occurrences of the word
    "polar". 
*/

#include <cstdio>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void downloadNewFile();
void lookForPolar(const std::string fileText);
void lookForEasy(const std::string fileText);

int main(int argc, char *argv[]) 
{
    int wordCount = 0;
    downloadNewFile();

    ifstream inFile;

    inFile.open("hw3-data.txt");
    if (!inFile) {
        cerr << "Couldn't open the file. Exiting...";
        exit(1);
    }

    string fileWord;
    string fileText;

    do {
        if(!(inFile >> fileWord)) { break;}
        transform(fileWord.begin(), fileWord.end(), fileWord.begin(), ::tolower);
        fileText.append(fileWord + " ");
        wordCount++;
    }
    while (!inFile.eof());
    inFile.close();

    thread polarThread(lookForPolar, fileText);
    thread easyThread(lookForEasy, fileText);

    polarThread.join();
    easyThread.join();
    
    return 0;
}

void downloadNewFile() {
    if (FILE *file = fopen("hw3-data.txt", "r")) {
        fclose(file);
        system("rm hw3-data.txt");
    }
    system("wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt");
}

void lookForPolar(const std::string fileText) {
    puts("Hello from PolarThread!");

    int polarCount = 0;
    string target ("polar");

    size_t position = fileText.find(target);
    while (position != string::npos) {
        position = fileText.find(target,position + 1);
        polarCount++;
    }

    printf("PolarThread found %d instances of the word \"polar\"!\n", polarCount);
}

void lookForEasy(const std::string fileText) {
    puts("Hello from EasyThread!");

    int easyCount = 0;
    string target ("easy");

    size_t position = fileText.find(target);
    while (position != string::npos) {
        position = fileText.find(target,position + 1);
        easyCount++;
    }

    printf("EasyThread found %d instances of the word \"easy\"!\n", easyCount);
}