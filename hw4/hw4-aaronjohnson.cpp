//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw4

//NOTE: Please compile with the following command:

//      g++ -std=c++11 hw4-aaronjohnson.cpp -l pthread -o hw4-aaronjohnson

//      This program requires at least -std=c++0x and linking to the
//      pthread library to implement std::thread.

/*
    This program will use the PTHREAD library to create
    two std::pthreads and a mutex to synchronize them.
    This program takes the input file "hw4.in", which is
    in a format provided in the spec sheet "hw4.txt", and
    opens it for reading in one thread. This thread locks
    the mutex, stalling the other thread. The first thread
    simply stored this integer into a global variable, then
    unlocks the mutex. This allows the second thread to lock
    out the first thread and read the global variable. Then,
    the second thread tests to see if this integer is even 
    or odd. If even, it writes the integer out twice. If odd,
    it writes the integer out only once. Then, the second
    thread unlocks the mutex, allowing the next integer to
    be read in by thread 1. This process repeats until eof
    is reached in the inFile handle, which allows the threads
    to join and lets the main thread close the file handles
    and exit the program.
*/

#include <cstdio>
#include <thread>
#include <iostream>
#include <fstream>

using namespace std;

void openForReading(std::ifstream* inFile);
void writeToFile(std::ofstream* outFile, std::ifstream* inFile);

int currentInt;
int currentInt_Mutex = 0;

int main(int argc, char *argv[]) 
{
    ifstream inFile;
    ifstream* p_inFile = &inFile;

    ofstream outFile;
    ofstream* p_outFile = &outFile;
    outFile.open("hw4.out");

    thread readInFile(openForReading, p_inFile);
    thread writeOutFile(writeToFile, p_outFile, p_inFile);

    readInFile.join();
    writeOutFile.join();

    inFile.close();
    outFile.close();
    
    return 0;
}

void openForReading(std::ifstream* inFile) {
    inFile->open("hw4.in");
    if (!*inFile) {
        cerr << "Couldn't open the file. Exiting...";
        exit(1);
    }
    do {
        while(1) {
            if (currentInt_Mutex == 0) {
                break;
            }
        }
        // puts("Mutex locked by THREAD 1");
        if(!(*inFile >> currentInt)) { 
            break;
        }
        // puts("Mutex unlocked by THREAD 1");
        currentInt_Mutex = 1;
    } while (!inFile->eof());
}

void writeToFile(std::ofstream* outFile, std::ifstream* inFile) {
    do {
        while(1) {
            if (currentInt_Mutex == 1) {
                break;
            }
        }
        // puts("Mutex locked by THREAD 2");
        if (currentInt % 2 == 0) {
            *outFile << currentInt << endl;
            *outFile << currentInt << endl;
        } else {
            *outFile << currentInt << endl;
        }
        currentInt_Mutex = 0;
        // puts("Mutex unlocked by THREAD 2");
    } while (!inFile->eof());
}