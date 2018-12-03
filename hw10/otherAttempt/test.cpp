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

int main()
{
	char readbuff[80];

   int pw[2];
   int piped = pipe(pw);

   pid_t pid = fork();


   if(pid == 0)
   {
     close(pw[0]);
     string a = "butt";
     write(pw[1], a.c_str(), (strlen(a.c_str())));
   }
   else
   {
     close(pw[1]);
     string q = "";
	 int size;
     size = read(pw[0], readbuff, sizeof(readbuff));
     
	 //cout << readbuff;
     
   }
 }
