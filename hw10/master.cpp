//Author:     Aaron Johnson
//Email:      aaron.r.johnson@und.edu
//Course:     CSci451
//Instructor: Dr. Ronald Marsh
//Assignment: hw10

/*
    This program is the master program that forks 3 child processes,
	passes appropriate arguments to each child process, and terminates
	once the child processes have finished.

	!!! --- HOW TO USE --- !!!

	1. Use the included Makefile to "make all".
	2. Use the included Makefile to "make run".
	3. Use the included Makefile to "make run".
		A. If at any point "make run" hangs, please use a Ctrl + C
		   to kill the process, then run "./reset" before proceeding.
	4. (Optional) Use the included Makefile to run "make clean".
	5. Repeat this process as needed.

	!!! --- Important Notes --- !!!

	This system of programs isn't always 100% complete when transferring words
	between the pipes and occasionally hangs up for an unknown reason at this
	point. After it hangs, the Type 1 and Type 2 vals are almost always 0 on the
	execution immediately following the hang. I was unable to find a solution to
	these issues before the due date.
*/

#include <iostream>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

//semaphores in global space
sem_t* sem1;
sem_t* sem2;

int main(int argc, char *argv[])
{
	pid_t forkedProcessIDs[3];
	key_t key = 451;
	int pipe1[2];
	int pipe2[2];
	int childProcessStatus;

	if(argc != 3) {
		puts("Invald args.\nUseage: ./master input.data temp3.data\n");
		return 1;
	} else {
		sem1 = sem_open("/sem1", O_CREAT, 0644, 0);
		sem2 = sem_open("/sem2", O_CREAT, 0644, 0);
		if(!sem1 || !sem2) {
			puts("Failed to open semaphores.\nPlease make clean, make all, and make run");
			exit(1);
		}

		if(pipe(pipe1) == -1)
		{
			puts("Pipe 1 couldn't open.\nPlease make clean, make all, and make run");
			exit(1);
		}
		if(pipe(pipe2) == -1)
		{
			puts("Pipe 2 couldn't open.\nPlease make clean, make all, and make run");
			exit(1);
		}

		forkedProcessIDs[0] = fork();
		forkedProcessIDs[1] = fork();
		forkedProcessIDs[2] = fork();

		if(forkedProcessIDs[0] == -1 || forkedProcessIDs[1] == -1 || forkedProcessIDs[2] == -1) {
			puts("Couldn't fork.\nPlease make clean, make all, and make run");
			exit(1);
		}
		if(forkedProcessIDs[0] == 0 && forkedProcessIDs[1] > 0 && forkedProcessIDs[2] > 0) {
		   	char* program1 = (char *) "./program1";
			char* prog1Args[4];
			char pipe1Write[20];
			snprintf(pipe1Write, sizeof(pipe1Write), "%d", pipe1[1]);
			close(pipe1[0]);

    		prog1Args[0] = argv[1];
    		prog1Args[1] = pipe1Write;
    		prog1Args[2] = (char *) "/sem1";
			prog1Args[3] = NULL;
    		if(execvp(program1, prog1Args) == -1) {
				puts("Error running Program1.\nPlease make clean, make all, and make run");
				printf("Error: %s\n", strerror(errno));
			}
		} else if (forkedProcessIDs[0] > 0 && forkedProcessIDs[1] == 0 && forkedProcessIDs[2] > 0) {
		   	char* program2 = (char *) "./program2";				
   			char* prog2Args[6];
			char pipe1Read[20];
			char pipe2Write[20];
			char sharedMemKey[20];
			snprintf(pipe1Read, sizeof(pipe1Read), "%d", pipe1[0]);
			snprintf(pipe2Write, sizeof(pipe2Write), "%d", pipe2[1]);
			sprintf(sharedMemKey, "%d", key);
			close(pipe1[1]);
			close(pipe2[0]);

    		prog2Args[0] = (char *) pipe1Read;
			prog2Args[1] = (char *) pipe2Write;
    		prog2Args[2] = (char *) "/sem1";
    		prog2Args[3] = (char *) "/sem2";
    		prog2Args[4] = sharedMemKey;
    		prog2Args[5] = NULL;
    		if(execvp(program2, prog2Args) == -1 ) {
				puts("Error running Program2.\nPlease make clean, make all, and make run");
				printf("Error: %s\n", strerror(errno));
			}
		} else if (forkedProcessIDs[0] > 0 && forkedProcessIDs[1] > 0 && forkedProcessIDs[2] == 0) {
		   	char* program3 = (char *) "./program3";
   			char* prog3Args[5];
			char pipe2Read[20];
			char sharedMemKey[20];
			snprintf(pipe2Read, sizeof(pipe2Read), "%d", pipe2[0]);
			sprintf(sharedMemKey, "%d", key);
			close(pipe2[1]);

    		prog3Args[0] = argv[2];
    		prog3Args[1] = pipe2Read;
    		prog3Args[2] = (char *) "/sem2";
    		prog3Args[3] = sharedMemKey;
    		prog3Args[4] = NULL;
    		if(execvp(program3, prog3Args) == -1) {
				puts("Error running Program3.\nPlease make clean, make all, and make run");
				printf("Error: %s\n", strerror(errno));
			}
		}

		waitpid(forkedProcessIDs[0], &childProcessStatus, 0);
		waitpid(forkedProcessIDs[1], &childProcessStatus, 0);
		waitpid(forkedProcessIDs[2], &childProcessStatus, 0);

		return 0;
	}
}
