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
    If a page is claimed by the garbage collector and
    a manipulator attempts to access this page, a page
    fault is printed to std out.
*/

#include <cstdio>
#include <thread>
#include <fstream>
#include <mutex>
#include <cstdlib>

using namespace std;

void manipulator1();
void manipulator2();
void manipulator3();
void garbageCollector();
void accessMemoryPage(int pageIndex, int randAccess, int pid);

const int NUM_PAGES = 5000;
const int RAND_SEED = 1492;

struct MemoryPage {
    int modPID = 0;
    int R_bit = 0;
    int M_bit = 0;
    int isClaimed = 0;
};
MemoryPage memoryPages[NUM_PAGES]; 

mutex pageMutex;

int main(int argc, char *argv[]) 
{
    srand(RAND_SEED); // "In 1492, Colombus saild the ocean blue!"

    while(1) {
        thread m1(manipulator1);
        thread m2(manipulator2);
        thread m3(manipulator3);
        thread gc(garbageCollector);

        m1.join();
        m2.join();
        m3.join();
        gc.join();
    }

    return 0;
}

void manipulator1() {
    int pid = 100;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void manipulator2() {
    int pid = 200;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void manipulator3() {
    int pid = 300;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void garbageCollector() {
    for (int i = 0; i < NUM_PAGES; i++) {
        int sleepRequired = 0;
        if (memoryPages[i].isClaimed) {
            pageMutex.lock();
            if (memoryPages[i].M_bit == 1) {
                memoryPages[i].R_bit = 0;
                memoryPages[i].M_bit = 0;
                sleepRequired = 1;
            } else {
                memoryPages[i].R_bit = 0;
            }
            pageMutex.unlock();
            if (sleepRequired) {
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }
    }
}

void accessMemoryPage(int pageIndex, int randAccess, int pid) {
    if (!memoryPages[pageIndex].isClaimed || memoryPages[pageIndex].modPID == pid) {
        if(pageMutex.try_lock()) {
            memoryPages[pageIndex].isClaimed = 1;
            int r_bit = 0;
            int m_bit = 0;
            if (randAccess == 1) {
                r_bit = 1;
                m_bit = 1;
            } else {
                r_bit = 1;
            }
            memoryPages[pageIndex].R_bit = r_bit;
            memoryPages[pageIndex].M_bit = m_bit;
            memoryPages[pageIndex].modPID = pid;
            pageMutex.unlock();
        } else {
            return;
        }
    } else {
        printf("Page Fault: %d\n", pageIndex);
    }
}