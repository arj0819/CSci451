//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw2

/*
    This program is a fork bomb that spawns 
    the xeyes program for each fork of the
    parent process.
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void main(int argc, char *argv []) 
{
    int exitCode = 1;
    pid_t PID;
    char *command = "hw2-aaronjohnson";

    PID = fork();
    if (PID == 0) {
        execv(command, NULL);
        exit(exitCode);
    } else {
        system("xeyes");
        waitpid(PID, &exitCode, 0);
    }
}