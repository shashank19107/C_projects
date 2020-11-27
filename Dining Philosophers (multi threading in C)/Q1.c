
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>

int main(){
	int pipe1[2];
	int pipe2[2];

	char input[500];
	pid_t pid;
	if(pipe(pipe1)==-1){
		return -1;
	}
	if(pipe(pipe2)==-1){
		return -1;
	}
	scanf("%[^\n]%*c", input);
	pid = fork();
	if(pid<0){
		return -1;
	}
	else if(pid==0){
		char received_Str[500];
		close(pipe1[1]); 		//closing writing end of first pipe
		read(pipe1[0], received_Str, 500);
		int i =0;
		for(i=0; received_Str[i]!='\0';i++){
			if(received_Str[i]>=97 && received_Str[i]<=122){
				received_Str[i] = received_Str[i] - 32;
			}
		}
		close(pipe1[0]);			//Closing all piipes
		close(pipe2[0]);
		write(pipe2[1], received_Str, i +1);
		close(pipe2[1]);
		return 0;
	}
	else{
			char received_Str[500];
			close(pipe1[0]);
			write(pipe1[1], input, 500);
			close(pipe1[1]);
			wait(NULL);

			close(pipe2[1]);
			read(pipe2[0], received_Str, 500);
			printf("The string returned by the child is %s\n", received_Str );
			// int i=0;
			// while(received_Str[i]!='\0'){
			// 	printf("%c", received_Str[i]);
			// 	i++;
			// }
			return 0;

	}

}
