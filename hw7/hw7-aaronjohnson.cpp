//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw7

/*
    This program will simulate a RAID 5 drive configuration.
    This is program will create 5 threads, each thread will
    handle its own drive (simulated by a file). The threads
    are synchronized by a mutex such that only one character
    is read from each file at a time. The main thread will
    assemble the data block given the chars read from each
    thread, in order of drive number. The main thread then
    prints the data block.
*/

#include <cstdio>
#include <thread>
#include <fstream>
#include <mutex>
#include <iostream>

using namespace std;

// Function Declarations
void accessDrive1();
void accessDrive2();
void accessDrive3();
void accessDrive4();
void accessDrive5();
string getNextChar(ifstream* p_driveHandle);

// We need a mutex as specified in reqirements!
mutex driveMutex;

// Create global string array to hold the 
// new chars found by each thread
array <string, 5> driveChars = {string(""),
                                string(""),
                                string(""),
                                string(""),
                                string("")};
// The global datablock
string dataBlock;

// RAID - Kills hard drives dead.
ifstream drive1;
ifstream drive2;
ifstream drive3;
ifstream drive4;
ifstream drive5;

// RAID - Kills file pointers dead.
ifstream* p_drive1 = &drive1;
ifstream* p_drive2 = &drive2;
ifstream* p_drive3 = &drive3;
ifstream* p_drive4 = &drive4;
ifstream* p_drive5 = &drive5;

int main(int argc, char *argv[]) 
{
    // open each file
    drive1.open("drive1.data");
    drive2.open("drive2.data");
    drive3.open("drive3.data");
    drive4.open("drive4.data");
    drive5.open("drive5.data");

    // exit if any of them failed to open
    if(!drive1 || !drive2 || !drive3 || !drive4 || !drive5) {
        cerr << "Could not open drives (simulated as files)." << endl;
        exit(1);
    }
    
    // repeat until drive1 has no more chars left.
    // NOTE: This condition is based on Caveat 1
    // in the project specs, stating that all files
    // will be of equal size.
    do  {

        // create the threads for each drive
        thread d1(accessDrive1);
        thread d2(accessDrive2);
        thread d3(accessDrive3);
        thread d4(accessDrive4);
        thread d5(accessDrive5);

        // join them up!
        d1.join();
        d2.join();
        d3.join();
        d4.join();
        d5.join();

        // assemble the dataBlock with each new char found
        for (int i = 0; i < driveChars.size(); i++) {
            dataBlock.append(driveChars[i]);
        }
    } while (!p_drive1->eof());

    // remove the unnecessary chars appended by getNextChar
    for (int i = 0; i < driveChars.size(); i++) {
        dataBlock.pop_back();
    }

    // print out the result
    cout << dataBlock << endl;

    return 0;
}

// Each drive access will simply read the next char
// from the respective drive (file).
void accessDrive1() {
    driveChars[0] = getNextChar(p_drive1);
}

void accessDrive2() {
    driveChars[1] = getNextChar(p_drive2);
}

void accessDrive3() {
    driveChars[2] = getNextChar(p_drive3);
}

void accessDrive4() {
    driveChars[3] = getNextChar(p_drive4);
}

void accessDrive5() {
    driveChars[4] = getNextChar(p_drive5);
}

// use the mutex to ensure only 1 thread can
// return a new char at a time.
string getNextChar(ifstream* p_driveHandle) {
    string nextChar;
    lock_guard<mutex> guard(driveMutex);
    nextChar.push_back(p_driveHandle->get());
    return nextChar;
}