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
int pageFaultOccurred = 0;

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
    if (pageFaultOccurred) {
        for (int i = 0; i < NUM_PAGES; i++) {
            if (memoryPages[i].isClaimed) {
                // printf("Garbage Collector is attempting to access Page %d\n\n",i);
                lock_guard <mutex> guard(pageMutex);
                // puts("GARBAGE");
                // printf("Page: %d\nR bit: %d\nM bit: %d\nPID: %d\n",i,memoryPages[i].R_bit,memoryPages[i].M_bit,memoryPages[i].modPID);
                memoryPages[i].isClaimed = 0;
                memoryPages[i].modPID = 0;
                if (memoryPages[i].M_bit == 1) {
                    memoryPages[i].R_bit = 0;
                    memoryPages[i].M_bit = 0;
                    // puts("SLEEP (M_Bit = 1)");
                    this_thread::sleep_for(chrono::milliseconds(500));
                    break;
                // printf("Page: %d\nR bit: %d\nM bit: %d\nPID: %d\n",i,memoryPages[i].R_bit,memoryPages[i].M_bit,memoryPages[i].modPID);
                } else {
                    // puts("NO SLEEP (M_Bit = 0)");
                    memoryPages[i].R_bit = 0;
                }
                // printf("Garbage Collector is releasing Page %d\n\n",i);
            } else {

                // printf("No garbage found on Page %d\n\n",i);
            }
        }
    }
}

void accessMemoryPage(int pageIndex, int randAccess, int pid) {
    if (!memoryPages[pageIndex].isClaimed) {
        // printf("Accessor %d is attempting to access Page %d\n\n",pid,pageIndex);
        lock_guard <mutex> guard(pageMutex);
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
        // puts("ACCESS");
        // printf("Page: %d\nR bit: %d\nM bit: %d\nPID: %d\n\n",pageIndex,r_bit,m_bit,pid);
        // printf("Accessor %d is releasing Page %d\n\n",pid,pageIndex);
    } else {
        printf("Page Fault: %d\n", pageIndex);
        pageFaultOccurred = 1;
        // printf("Accessor %d was denied access to Page %d\n\n",pid,pageIndex);
    }
}