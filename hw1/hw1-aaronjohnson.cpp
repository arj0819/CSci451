//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
#include <stdio.h>
#include <cstdlib>
#include <string.h>

int main(int argc, char *argv []) 
{
    for (int i = 1; i < argc; i++) {
        char unixCommand[1000];
        strcpy(unixCommand, argv[i]);
        strcat(unixCommand, " >> output.txt");
        system(unixCommand);
    }
    return 0;
}