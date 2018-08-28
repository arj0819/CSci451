//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh

//the command that creates the text in my output.txt is as follows:
//        ./hw1-aaronjohnson.cpp whoami date ps df

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