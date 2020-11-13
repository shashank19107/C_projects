#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define sh_task_info 336

int main(int argv, char * argc[])
{
 // printf("%s %s\n", argc[0], argc[1]);
 if(argv<2){
 	printf("PID as argument not entered\n");
 	return 0;
 }
  int pid = atoi(argc[1]);
  
  if(pid == 0){
  	printf("The entered argument is not a valid PID(Integer>0)\n");
  	printf("Syscall terminated\n");
  	return 0;
  }
  
  
  printf("Making system call with \"%d\".\n", pid);
  long res = syscall(sh_task_info, pid);
  if(res == -1){
  	system("dmesg | tail -n 1");
  }
	else if(res == -2){
		printf("Unable to open the file");
	return -1;
}
  else
  system("dmesg | tail -n 6");
  printf("System call returned %ld.\n", res);
  return res;
}
