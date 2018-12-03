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

#define SHM_SIZE 100 //shared memeory size
int main(int argc, char *argv[])
{
	//Variable declarations
	int pipe1[2]; //pipe 1
	int pipe2[2]; //pipe 2
	pid_t idarr[3];
	sem_t* sem1;
	sem_t* sem2;
	int sem1_value;
	int sem2_value;
	key_t key; //unique key for shared memory segment
	int shmid; //shared memory ID
	int *data;
	if(argc < 3 || argc > 3) {
		cout << "Too many or too few arguments\n";
		return 1;

	} else {
		
		//create the pipes
		if(pipe(pipe1) == -1)
		{
			cout << "Pipe 1 failed to open.";
			return 2;
		}
		if(pipe(pipe2) == -1)
		{
			cout << "Pipe 2 failed to open.";
			return 2;
		}
		
		//create the semaphores	
		sem1 = sem_open("/semaphore1", O_CREAT, 0644, 1);
		if(!sem1)
		{
			cout << "Error opening first semaphore!!\n";
			return 3;
		}
		
		sem2 = sem_open("/semaphore2", O_CREAT, 0644, 1);
		if(!sem2)
		{
			cout << "Error opening second semaphore!!\n";
			return 3;
		}

		//create the shared memory space
		if((key = ftok("./master.cpp", 'R')) == -1)
		{
			perror("Key creation failed.\n");
			exit(1);
		}	
		if((shmid = shmget(key, 100, 0644 | IPC_CREAT)) == -1)
		{
			perror("Shared memory creation failed.");
			exit(1);
		}
		data = (int *) shmat (shmid, (void *)0, 0);
		if(data == (int *)(-1))
		{
			perror("pointer to shared memory failed.\n");
			exit(1);
		}
		/*
		idarr[0] = fork();
		idarr[1] = fork();
		idarr[2] = fork();
		
		if(idarr[0] > 0 && idarr[1] > 0 && idarr[2] > 0) {
			//parent

		} else if(idarr[0] == 0 && idarr[1] > 0 && idarr[2] > 0) {
			cout << "Execute Prog1\n";
			cout << getpid() << '\n';
			char pw[20];
			close(pipe1[0]);
		   	char *cmd = (char *) "./prog1";
			char *args[4];								
    		args[0] = argv[1];
			snprintf(pw, sizeof(pw), "%d", pipe1[1]);
    		args[1] = pw;
    		args[2] = (char *) sem1;						
    		args[3] = NULL;
    		execvp(cmd, args);
		
		} else if(idarr[0] > 0 && idarr[1] == 0 && idarr[2] > 0) {
			cout << "Execute Prog2\n";
			cout << getpid() << '\n';
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
    		execvp(cmd, args);

		} else if(idarr[0] > 0 && idarr[1] > 0 && idarr[2] == 0) {
			cout << "Execute Prog3\n";
			cout << getpid() << '\n';
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


		}
		*/

		/*
		if((idarr[0] = fork()) == 0) {
			cout << "Execute Prog1\n";
			char pw[20];
			close(pipe1[0]);
		   	char *cmd = (char *) "./prog1";
			char *args[4];								
    		args[0] = argv[1];
			snprintf(pw, sizeof(pw), "%d", pipe1[1]);
    		args[1] = pw;
    		args[2] = (char *) sem1;						
    		args[3] = NULL;
    		execvp(cmd, args);

		} else {
			int status;
			waitpid(idarr[0], &status, 0);
		}

		if((idarr[1] = fork()) == 0) {
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
    		execvp(cmd, args);
		} else {
			int status;
			waitpid(idarr[1], &status, 0);
		}

		if((idarr[2] = fork()) == 0) {
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
			waitpid(idarr[2], &status, 0);
		}
		*/
		
		for(int i = 0; i < 3; i++) {
			if((idarr[i] = fork()) == 0) {
				if(i == 0) {
					cout << "Execute Prog1\n";
					char pw[20];
					close(pipe1[0]);
				   	char *cmd = (char *) "./program1";
					char *args[4];								
		    		args[0] = argv[1];
    				snprintf(pw, sizeof(pw), "%d", pipe1[1]);
		    		args[1] = pw;
		    		args[2] = (char *) sem1;						
		    		args[3] = NULL;
		    		execvp(cmd, args);
				} else if (i == 1) {
					cout << "Execute Prog2\n";
				   	char *cmd = (char *) "./program2";				
		   			char *args[3];
					char semarg[20];
					char pr[20];
					close(pipe1[1]);
    				snprintf(pr, sizeof(pr), "%d", pipe1[0]);
		    		args[0] = pr;
		    		args[1] = (char *) sem1;
					/*
		    		args[2] = sem1;
		    		args[3] = sem2;
		    		args[4] = (char *) shmid
					*/				
		    		args[2] = NULL;
		    		execvp(cmd, args);
				} else {
					cout << "Execute Prog3\n";
				   	char *cmd = (char *) "./program3";
		   			char *args[1];
					/*
		    		args[0] = argv[2];
		    		args[1] = (char *) pipe2[0];
		    		args[2] = sem2;
		    		args[3] = (char *) shmid
					*/
		    		args[0] = NULL;
		    		execvp(cmd, args);
					//system("./program3 NULL");
				}			
			} else {
				int status;
				waitpid(idarr[i], &status, 0);
			}
		}
		


		return 0;
	}
}
