//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw5

//NOTE: Please compile with the following command:

//      g++ -std=c++11 hw5-aaronjohnson.cpp -l pthread -o hw5-aaronjohnson

//      This program requires at least -std=c++0x and linking to the
//      pthread library to implement std::thread.

/*
    This program will use the PTHREAD library to create
    four std::pthreads and a mutex to synchronize them.
    These threads will be used to manipulate the memory
    pages using an NRU (not recently used) algorithm.
    The first three threads will continuously generate
    random numbers between 0-4999 using the same seed,
    1492. They will also generate a random coin flip,
    either a 0 or a 1. The first random number will be
    used to indicate what memory page to manipulate. 
    The second random value (zero or one) will be used 
    to indicate how to manipulate this memory page:
        0 - read from the page (Set the R bit)
        1 - write to the page (Set the R and M bits)
    This program basically simulates a memory paging
    scheme that uses an NRU page replacement algorithm
    to swap memory pages in and out of faster memory.
*/

#include <cstdio>
#include <thread>
#include <iostream>
#include <fstream>
#include <mutex>

using namespace std;

void openForReading(ifstream* inFile);
void writeToFile(ofstream* outFile, ifstream* inFile);

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

void openForReading(ifstream* inFile) {
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

void writeToFile(ofstream* outFile, ifstream* inFile) {
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