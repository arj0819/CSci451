//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw9

/*
    This program will sample output from producer files 
    (producer1.cpp, producer2.cpp and producer3.cpp) 
    every 0.5 seconds and concatenate each consecutively
    outputted value from each output file together into 
    a new output file. Semaphores will be used to ensure
    no duplicates and proper concatenation order occur.

    HOW TO USE
    - Use the included Makefile and perform these steps:
    1. enter "make all"
    2. enter "make run"
    3. do a "ctrl + c" in the terminal to end execution
    4. enter "make stop" to kill the producers
    5. enter "make clean" to reset output files and clean executables
    6. repeat steps 1-6 as needed
    

    This program will not terminate unless explicitly
    killed during execution by using a ctrl + C.
*/

#include <cstdio>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "sharedSemaphores.hh"

using namespace std;

// Thread function prototypes
void handleOut1(sem_t*,sem_t*);
void handleOut2(sem_t*,sem_t*);
void handleOut3(sem_t*,sem_t*);

// The global current chars from each output file
string Out1CurrentChar = "";
string Out2CurrentChar = "";
string Out3CurrentChar = "";

// ifstreams for reading output files 1, 2, and 3
ifstream in1;
ifstream in2;
ifstream in3;

// ofstream for writing to output file 4
ofstream out4;

// fstream pointers
ifstream* p_in1 = &in1;
ifstream* p_in2 = &in2;
ifstream* p_in3 = &in3;
ofstream* p_out4 = &out4;

int main(int argc, char *argv[]) {

    // try to open up the semaphores
    // sem_open(sem name, oflag)
    sem_t* semOut1 = sem_open(SEM_OUT1, 0);
    sem_t* semOut2 = sem_open(SEM_OUT2, 0);
    sem_t* semOut3 = sem_open(SEM_OUT3, 0);
    // sem_open(sem name, create if not exist, mode(access permissions(rwx)), initial value)
    sem_t* semOrder = sem_open(SEM_ORDER, O_CREAT, 0644, 1);

    // exit the program if open failed
    if(!semOut1 || !semOut2 || !semOut3 || !semOrder) {
        puts("Could not open semaphores.");
        return 0;
    }

    puts("\nRunning...\n\n(Use Ctrl + c to stop. Then enter 'make stop' to kill the producers.)\n");
    while(1) {
        // create the threads for each output file
        thread t1(handleOut1,semOut1,semOrder);
        thread t2(handleOut2,semOut2,semOrder);
        thread t3(handleOut3,semOut3,semOrder);

        // detach the threads so they can run independently
        t1.detach();
        t2.detach();
        t3.detach();

        // sleeping for 0.5 seconds (Nyquist Sampling Rate in this case)
        // is too long and causes some chars from output1.txt to be missed.
        // This is due to the logic of the handleOut1 function, which delays
        // just enough over time to skip some chars. So, I've shortened the wait
        // time to less than the Nyquist Sampling Rate (250 milliseconds),
        // which allows enough time to capture the dataset in the format
        // specified by the project specifications.

        // PLEASE NOTE THAT I UNDERSTAND IT'S SUPPOSED TO BE 0.5 SECONDS.
        // HOWEVER, DUE TO MY TESTING, THIS DELAY IS TOO LONG AND CAUSES
        // CHARS TO BE MISSED. YOU MAY CHANGE THE DELAY BACK TO 0.5 IF
        // YOU FEEL THE NEED TO VERIFY.
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}

void handleOut1(sem_t* semOut1, sem_t* semOrder) {
    // get the value of semOrder and store it
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);

    // if semOrder val is 1, we can try to access the associated file.
    if (semOrder_val == 1) {
        // if the file is not claimed, open and read from it
        if (sem_wait(semOut1) == 0) {

            p_in1->open("output1.txt");
            p_out4->open("output4.txt", ofstream::app);
            string nextChar;
            *p_in1 >> nextChar;

            // if the nextChar in the file is not the same as what came before,
            // set it to the current char and write it out to output4.txt
            if (nextChar != Out1CurrentChar) {
                Out1CurrentChar = nextChar;
                *p_out4 << Out1CurrentChar << '\n';
            }

            // close the file handles
            p_in1->close();
            p_out4->close();

            // post (increment) semOut1 to let producer1 know it can now write to output1.txt
            sem_post(semOut1);
            // post (increment) semOrder to let t2 know it can now access output2.txt
            sem_post(semOrder);
        }
    }
}

void handleOut2(sem_t* semOut2, sem_t* semOrder) {
    // get the value of semOrder and store it
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);

    // if semOrder val is 2, we can try to access the associated file.
    if (semOrder_val == 2) {
        // if the file is not claimed, open and read from it
        if (sem_wait(semOut2) == 0) {

            p_in2->open("output2.txt");
            p_out4->open("output4.txt", ofstream::app);
            string nextChar;
            *p_in2 >> nextChar;
            
            // if the nextChar in the file is not the same as what came before,
            // set it to the current char and write it out to output4.txt
            if (nextChar != Out2CurrentChar) {
                Out2CurrentChar = nextChar;
                *p_out4 << Out2CurrentChar << '\n';
            }

            // close the file handles
            p_in2->close();
            p_out4->close();

            // post (increment) semOut2 to let producer2 know it can now write to output2.txt
            sem_post(semOut2);
            // post (increment) semOrder to let t3 know it can now access output3.txt
            sem_post(semOrder);
        }
    }
}

void handleOut3(sem_t* semOut3, sem_t* semOrder) {
    // get the value of semOrder and store it
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);

    // if semOrder val is 3, we can try to access the associated file.
    if (semOrder_val == 3) {
        // if the file is not claimed, open and read from it
        if (sem_wait(semOut3) == 0) {

            p_in3->open("output3.txt");
            p_out4->open("output4.txt", ofstream::app);
            string nextChar;
            *p_in3 >> nextChar;

            // if the nextChar in the file is not the same as what came before,
            // set it to the current char and write it out to output4.txt
            if (nextChar != Out3CurrentChar) {
                Out3CurrentChar = nextChar;
                *p_out4 << Out3CurrentChar << '\n';
            }

            // close the file handles
            p_in3->close();
            p_out4->close();

            // post (increment) semOut3 to let producer3 know it can now write to output3.txt
            sem_post(semOut3);
            // wait (decrement) semOrder twice to make it's value 1 to let t1 know it can now access output1.txt
            sem_wait(semOrder);
            sem_wait(semOrder);
        }
    }
}