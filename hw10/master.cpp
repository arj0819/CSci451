#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <thread>
#include <fstream>
#include <sys/shm.h>

using namespace std;

#ifndef SHM_SIZE
#define SHM_SIZE 100 //shared memeory size
#endif

//globals
sem_t sem1;
sem_t sem2;

int main(int argc, char *argv[])
{
	pid_t forkedProcessIDs[3];
	key_t key; //unique key for shared memory segment
	int shmid; //shared memory ID
	int* data;
	int pipe1[2];
	int pipe2[2];

	if(argc != 3) {
		puts("Please include input.data and temp3.data as args in that order.\n");
		return 1;
	} else {
		//init the semaphores
		//puts("Before init semaphores");
		if(sem_init(&sem1, 1, 1) != 0 || sem_init(&sem2, 1, 1) != 0) {
			puts("Failed to initialize semaphores.\nPlease make clean, recompile, and try again.");
		}

		//create the pipes
		//puts("Before pipe creation");
		if(pipe(pipe1) == -1)
		{
			puts("Pipe 1 failed to open.\nPlease make clean, recompile, and try again.");
			return 2;
		}
		if(pipe(pipe2) == -1)
		{
			puts("Pipe 2 failed to open.\nPlease make clean, recompile, and try again.");
			return 2;
		}

		//create the shared memory space
		//puts("Before shared mem creation");
		key = 1234;
		if((shmid = shmget(key,100,0666| IPC_CREAT)) == -1)
		{
			perror("Shared memory creation failed.");
			exit(1);
		}
		data = (int *) shmat(shmid, NULL, 0);
		if(data == (void *)(-1))
		{
			perror("pointer to shared memory failed.\n");
			exit(1);
		}
		*data = 10;
		printf("Shared memory data: %d\n",*data);
		shmdt(data);
		
		//puts("Before forks");
		forkedProcessIDs[0] = fork();
		forkedProcessIDs[1] = fork();
		forkedProcessIDs[2] = fork();

		if(forkedProcessIDs[0] == -1 || forkedProcessIDs[1] == -1 || forkedProcessIDs[2] == -1) {
			puts("One or more of the forks failed.\nPlease make clean, recompile, and try again.");
			exit(1);
		}

		if(forkedProcessIDs[0] == 0 && forkedProcessIDs[1] > 0 && forkedProcessIDs[2] > 0) {
			puts("This is Program 1 child");
		   	char *cmd = (char *) "./program1";
			char *prog1Args[4];

    		prog1Args[0] = argv[1];
    		prog1Args[1] = (char *) &pipe1[1];
    		prog1Args[2] = (char *) &sem1;
			prog1Args[3] = NULL;
    		if(execvp(cmd, prog1Args) == -1) {
				puts("Error running Program1. Please make clean, recompile, and try again.");
				printf("Error: %s\n", strerror(errno));
			}
			//system("./program1");
		
		} else if(forkedProcessIDs[0] > 0 && forkedProcessIDs[1] == 0 && forkedProcessIDs[2] > 0) {
			puts("This is Program 2 child");
		   	char *cmd = (char *) "./program2";				
   			char *prog2Args[6];

    		prog2Args[0] = (char *) &pipe1[0];
			prog2Args[1] = (char *) &pipe2[1];
    		prog2Args[2] = (char *) &sem1;
    		prog2Args[3] = (char *) &sem2;
    		prog2Args[4] = (char *) &shmid;
    		prog2Args[5] = NULL;
    		if(execvp(cmd, prog2Args) == -1 ) {
				puts("Error running Program2. Please make clean, recompile, and try again.");
				printf("Error: %s\n", strerror(errno));
			}
			//system("./program2");

		} else if(forkedProcessIDs[0] > 0 && forkedProcessIDs[1] > 0 && forkedProcessIDs[2] == 0) {
			puts("This is Program 3 child");
		   	char *cmd = (char *) "./program3";
   			char *prog3Args[5];

    		prog3Args[0] = argv[2];
    		prog3Args[1] = (char *) &pipe2[0];
    		prog3Args[2] = (char *) &sem2;
    		prog3Args[3] = (char *) &shmid;
    		prog3Args[4] = NULL;
    		if(execvp(cmd, prog3Args) == -1) {
				puts("Error running Program3. Please make clean, recompile, and try again.");
				printf("Error: %s\n", strerror(errno));
			}
			//system("./program3");

		} else {

		}
		/*
		if((forkedProcessIDs[0] = fork()) == 0) {
			cout << "Execute Prog1\n";
			char pw[20];
			close(pipe1[0]);
		   	char *cmd = (char *) "./prog1";
			char *args[4];								
			system("./pr")
    		args[0] = argv[1];
			snprintf(pw, sizeof(pw), "%d", pipe1[1]);
    		args[1] = pw;
    		args[2] = (char *) sem1;						
    		args[3] = NULL;
    		execvp(cmd, args);

		} else {
			int status;
			waitpid(forkedProcessIDs[0], &status, 0);
		}

		if((forkedProcessIDs[1] = fork()) == 0) {
			cout << "Execute Prog2\n";
		   	char *cmd = (char *) "./prog2";				
   			char *args[3];
			//char semarg[20];
			char pr[20];
			close(pipe1[1]);
			snprintf(pr, sizeof(pr), "%d", pipe1[0]);
    		args[0] = pr;
    		args[1] = (char *) sem1;
			/*
    		args[2] = sem1;
    		args[3] = sem2;
    		args[4] = (char *) shmid		
			/		
    		args[2] = NULL;
    		execvp(cmd, args);init semaphores
		} else {
			int status;
			waitpid(forkedProcessIDs[1], &status, 0);
		}

		if((forkedProcessIDs[2] = fork()) == 0) {
			cout << "Execute Prog3\n";
		   	char *cmd = (char *) "./prog3";
   			char *args[1];
			/*
    		args[0] = argv[2];
    		args[1] = (char *) pipe2[0];
    		args[2] = sem2;
    		args[3] = (char *) shmid
			/
    		args[0] = NULL;
    		execvp(cmd, args);
		} else {
			int status;


			waitpid(forkedProcessIDs[2], &status, 0);
		}
		*/
		
		// for(int i = 0; i < 3; i++) {
		// 	if((forkedProcessIDs[i] = fork()) == 0) {
		// 		if(i == 0) {
		// 			cout << "Execute Prog1\n";
		// 			char pw[20];
		// 			close(pipe1[0]);
		// 		   	char *cmd = (char *) "./program1";
		// 			char *args[4];								
		//     		args[0] = argv[1];
    	// 			snprintf(pw, sizeof(pw), "%d", pipe1[1]);
		//     		args[1] = pw;
		//     		args[2] = (char *) sem1;						
		//     		args[3] = NULL;
		//     		execvp(cmd, args);
		// 		} else if (i == 1) {
		// 			cout << "Execute Prog2\n";
		// 		   	char *cmd = (char *) "./program2";				
		//    			char *args[3];
		// 			char semarg[20];
		// 			char pr[20];
		// 			close(pipe1[1]);


    	// 			snprintf(pr, sizeof(pr), "%d", pipe1[0]);
		//     		args[0] = pr;
		//     		args[1] = (char *) sem1;
		// 			/*
		//     		args[2] = sem1;
		//     		args[3] = sem2;
		//     		args[4] = (char *) shmid
		// 			*/				
		//     		args[2] = NULL;
		//     		execvp(cmd, args);
		// 		} else {


		// 			cout << "Execute Prog3\n";
		// 		   	char *cmd = (char *) "./program3";
		//    			char *args[1];
		// 			/*
		//     		args[0] = argv[2];
		//     		args[1] = (char *) pipe2[0];
		//     		args[2] = sem2;
		//     		args[3] = (char *) shmid
		// 			*/
		//     		args[0] = NULL;
		//     		execvp(cmd, args);
		// 			//system("./program3 NULL");
		// 		}			
		// 	} else {
		// 		int status;
		// 		waitpid(forkedProcessIDs[i], &status, 0);
		// 	}
		// }
		
		return 0;
	}
}
