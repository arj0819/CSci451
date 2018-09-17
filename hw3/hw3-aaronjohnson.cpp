//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw3

/*
    This program downloads a text file, loads the characters of
    the file into the program dynamically, then parses through it
    with two threads, one to count the # of occurrences of the word
    "Easy", and the other to count the # of occurrences of the word
    "Polar", regardless of case. 
*/

#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void downloadNewFile();
void lookForPolar(const std::string fileText);
void lookForEasy(const std::string fileText);

int main(int argc, char *argv[]) 
{
    static int polarCount = 0;
    static int easyCount = 0;

    downloadNewFile();

    ifstream file;

    file.open("hw3-data.txt");
    if (!file) {
        cerr << "Couldn't open the file. Exiting...";
        exit(1);
    }

    string fileText;

    file >> fileText;

    thread polarThread(lookForPolar, fileText);
    thread easyThread(lookForEasy, fileText);

    polarThread.join();
    easyThread.join();

    file.close();
    
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
}

void lookForEasy(const std::string fileText) {
    puts("Hello from EasyThread!");
}