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
    - Start by using the Makefile and run "make all" 
    in the terminal. 
    

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

void handleOut1(sem_t*,sem_t*);
void handleOut2(sem_t*,sem_t*);
void handleOut3(sem_t*,sem_t*);

// prepare ints for semaphore values to be held in
//int semOut1_val;
//int semOut2_val;
//int semOut3_val;
//int semOrder_val;

// The global current chars from each output file
string Out1CurrentChar = "";
string Out2CurrentChar = "";
string Out3CurrentChar = "";
// The global current consecutive chars from each output file
string currentConsecutiveOutChars = "";

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
        // This is due to the logic below that writes the concatenation of
        // each output file char to output4.txt. So, I've shortened the wait
        // time to less than the Nyquist Sampling Rate to 250 milliseconds,
        // which allows enough time to capture the dataset in the format
        // specified by the project specifications.
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        string nextConsecutiveOutChars = "";
        nextConsecutiveOutChars = Out1CurrentChar + Out2CurrentChar + Out3CurrentChar;
        if (nextConsecutiveOutChars != currentConsecutiveOutChars) {
            if (Out3CurrentChar != "") {
                currentConsecutiveOutChars = nextConsecutiveOutChars;
                p_out4->open("output4.txt", std::ios_base::app);
                *p_out4 << currentConsecutiveOutChars << endl;
                p_out4->close();
            }
        }
    }

    return 0;
}

void handleOut1(sem_t* semOut1, sem_t* semOrder) {
    puts("handleOut1");
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);
    //printf("SemOrder = %d\n",semOrder_val);

    if (semOrder_val == 1) {
        puts("SemOrder = 1");
        if (sem_wait(semOut1) == 0) {
            puts("semOut 1 is ready");

            p_in1->open("output1.txt");
            string nextChar;
            *p_in1 >> nextChar;
            if (nextChar != Out1CurrentChar) {
                Out1CurrentChar = nextChar;
            }
            p_in1->close();

            sem_post(semOut1);
            sem_post(semOrder);
        }
    }
}

void handleOut2(sem_t* semOut2, sem_t* semOrder) {
    puts("handleOut2");
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);
    //printf("SemOrder = %d\n",semOrder_val);

    if (semOrder_val == 2) {
        puts("SemOrder = 2");
        if (sem_wait(semOut2) == 0) {
            puts("semOut 2 is ready");

            p_in2->open("output2.txt");
            string nextChar;
            *p_in2 >> nextChar;
            if (nextChar != Out2CurrentChar) {
                Out2CurrentChar = nextChar;
            }
            p_in2->close();

            sem_post(semOut2);
            sem_post(semOrder);
        }
    }
}

void handleOut3(sem_t* semOut3, sem_t* semOrder) {
    puts("handleOut3");
    int semOrder_val;
    sem_getvalue(semOrder,&semOrder_val);
    //printf("SemOrder = %d\n",semOrder_val);

    if (semOrder_val == 3) {
        puts("SemOrder = 3");
        if (sem_wait(semOut3) == 0) {
            puts("semOut 3 is ready");

            p_in3->open("output3.txt");
            string nextChar;
            *p_in3 >> nextChar;
            if (nextChar != Out3CurrentChar) {
                Out3CurrentChar = nextChar;
            }
            p_in3->close();

            sem_post(semOut3);
            sem_wait(semOrder);
            sem_wait(semOrder);
        }
    }
}