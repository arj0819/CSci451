//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv []) 
{

    if (argc > 5) {
        printf("Invalid arguments.\nUsage: ./hw1-aaronjohnson <UNIXcommands>\nArgs: <UNIXcommands> - any UNIX commands you'd like to execute. You may use up to 4 command line args.\n");
        exit(0);
    }

    system("ls -ls >> output.txt");

    cout << "Hello, World!\n";
    return 0;
}