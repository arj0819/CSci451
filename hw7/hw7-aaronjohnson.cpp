//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw6

/*
    This is program 1 of 4 for this assignment. This program
    will always be executed first and will create a set of
    semaphores for the rest of the programs to use.
*/

#include <cstdio>
#include <thread>
#include <fstream>
#include <mutex>
#include <cstdlib>
#include <iostream>

using namespace std;

void accessDrive1();
void accessDrive2();
void accessDrive3();
void accessDrive4();
void accessDrive5();
void garbageCollector();
void accessMemoryPage(int pageIndex, int randAccess, int pid);

const int NUM_PAGES = 5000;

struct MemoryPage {
    int modPID = 0;
    int R_bit = 0;
    int M_bit = 0;
    int isClaimed = 0;
};
MemoryPage memoryPages[NUM_PAGES]; 

mutex driveMutex;
array <string, 5> driveChars = {string("a"),
                                string("b"),
                                string("c"),
                                string("d"),
                                string("e")};
string dataBlock;

int main(int argc, char *argv[]) 
{
    // while(1) {
    //     thread d1(accessDrive1);
    //     thread d2(accessDrive2);
    //     thread d3(accessDrive3);
    //     thread d4(accessDrive4);
    //     thread d5(accessDrive5);

    //     d1.join();
    //     d2.join();
    //     d3.join();
    //     d4.join();
    //     d5.join();

        for (const auto& driveChar : driveChars) {
            dataBlock.append(driveChar);
        }
        cout << dataBlock << endl;
    // }

    return 0;
}

void accessDrive1() {
    int pid = 100;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void accessDrive2() {
    int pid = 200;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void accessDrive3() {
    int pid = 300;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void accessDrive4() {
    int pid = 300;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void accessDrive5() {
    int pid = 300;
    int randPage = rand() % NUM_PAGES;
    int randAccess = rand() % 2;
    accessMemoryPage(randPage,randAccess,pid);
}

void garbageCollector() {
    // for (int i = 0; i < NUM_PAGES; i++) {
    //     int sleepRequired = 0;
    //     if (memoryPages[i].isClaimed) {
    //         // pageMutex.lock();
    //         if (memoryPages[i].M_bit == 1) {
    //             memoryPages[i].R_bit = 0;
    //             memoryPages[i].M_bit = 0;
    //             sleepRequired = 1;
    //         } else {
    //             memoryPages[i].R_bit = 0;
    //         }
    //         // pageMutex.unlock();
    //         if (sleepRequired) {
    //             this_thread::sleep_for(chrono::milliseconds(500));
    //         }
    //     }
    // }
}

void accessMemoryPage(int pageIndex, int randAccess, int pid) {
    // if (!memoryPages[pageIndex].isClaimed || memoryPages[pageIndex].modPID == pid) {
    //     if(pageMutex.try_lock()) {
    //         memoryPages[pageIndex].isClaimed = 1;
    //         int r_bit = 0;
    //         int m_bit = 0;
    //         if (randAccess == 1) {
    //             r_bit = 1;
    //             m_bit = 1;
    //         } else {
    //             r_bit = 1;
    //         }
    //         memoryPages[pageIndex].R_bit = r_bit;
    //         memoryPages[pageIndex].M_bit = m_bit;
    //         memoryPages[pageIndex].modPID = pid;
    //         pageMutex.unlock();
    //     } else {
    //         return;
    //     }
    // } else {
    //     printf("Page Fault: %d\n", pageIndex);
    // }
}