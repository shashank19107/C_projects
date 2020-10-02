#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 


char mkdir[100], ls[100], rm[100], date[100], cat[100], History[100];

void init_shell() 
{ 
	
	char* username = getenv("USER"); 
	printf("You are using as @%s", username); 
	printf("\n"); 
	
} 


void getPwd(){

	char cwd[100];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working directory is: %s\n", cwd);
   } 
   else {
       printf("Directory error");
       
   }

}

void main(){
	init_shell();
	FILE *his = fopen("History.txt", "w+");
	if(his==NULL){
		printf("%s\n","Unable to load history." );
	}
	getPwd();
	//char command[1024];
			char home[100];
			getcwd(home, 100);
			strcat(mkdir,home);
			strcat(mkdir,"/realmkdir");
			strcat(rm,home);
			strcat(rm,"/mkdir");
			strcat(date,home);
			strcat(date,"/time");	
			strcat(cat,home);
			strcat(cat,"/cat");		
			strcat(ls,home);
			strcat(ls,"/pwd");
			strcat(History,home);
			strcat(History,"/History.txt");

	while(1){


			char str[200]; 

			char command[10][100];
			printf(">>>");

		   scanf("%[^\n]%*c", str); 

		   fprintf(his, "%s \n", str );
		   int u=0,v=0;
		   for(int i =0 ; i<strlen(str);i++){
		   		if(str[i]==' '|| str[i]=='\0'){
		   			command[u][v]='\0';
			   			if(strlen(command[u])>0){
			   			u++;
			   			v=0;
			   			}
		   		}
		   		else{
		   			command[u][v]=str[i];
		   			v++;

		   		}
		   }
		   command[u][v]='\0';

		   if(strcmp(command[0], "pwd")==0){
		   		if(u>0)
		   			getPwd();
		   		else{
		   			getPwd();
		   		}
		   }

		   else if(strcmp(command[0], "exit")==0){
		   		printf("%s\n","Thank you for using this shell." );
		   		exit(0);

		   }
		   else if (strcmp(command[0], "history")==0){
		   	fclose(his);

		   		FILE *t = fopen(History,"r");
		   		if(u>0 && (strcmp(command[1],"-c")==0)){
		   			fclose(t);
		   			his = fopen("History.txt", "w+");

		   		}
		   		else{
		   		if(t==NULL){
		   			printf("%s\n","History command error has occured." );
		   		}
		   		else{
		   			char temp[100];
		   			while(!feof(t))
		   			{
						fscanf(t,"%[^\n]%*c\n", temp);
						printf("%s\n",temp);
					}
					fclose(t);
		   		}
		   		
		   		his = fopen("History.txt", "a");
		   	}


		   }
		   else if (strcmp(command[0], "echo")==0){
		   		if((strcmp(command[1], "-n")==0 || strcmp(command[2], "-n")==0 ) && (strcmp(command[1], "-E")==0 || strcmp(command[2], "-E")==0 ))
		   	 		{
		   	 				printf("%s",(str+12) );
		   	 		}

		   	 	else if (strcmp(command[1],"-n")==0){
		   				printf("%s",(str+8) );
		   			}
		   			else if(strcmp(command[1],"-E")==0){
		   				printf("%s\n",(str+8) );
		   			}
		   			else{
		   				printf("%s\n",(str+4) );
		   			}





		   	// 	if(u>2){
		   	// 		if((strcmp(command[1], "-n")==0 || strcmp(command[2], "-n")==0 ) && (strcmp(command[1], "-E")==0 || strcmp(command[2], "-E")==0 ))
		   	// 		{
		   	// 				printf("%s",(str+12) );
		   	// 		}
		   	// 		else{
		   	// 			printf(" %s %s \n",command[1],command[2] );
		   	// 		}
		   	// 	}
		   	// 	else if(u>1){
		   	// 		if(strcmp(command[1],"-n")==0){
		   	// 			printf("%s",(str+8) );
		   	// 		}
		   	// 		else if(strcmp(command[1],"-E")==0){
		   	// 			printf("%s\n",(str+8) );
		   	// 		}
		   	// 		else{
		   	// 			printf("%s\n",(str+4) );
		   	// 		}
		   	// 	}
		   	// 	else{
		   	// 	printf("%s\n",(str+5) );
		   	// }

		   }
		   else if (strcmp(command[0], "cd")==0){
		   	int re =0;
		   		if(strcmp(command[1], "~")==0){
		   			 re = chdir(home);
		   		}
		   		else {
		   		
		   			 re = chdir(command[1]);
		   		}
		   			if(re != 0){
		   				printf("Directory not found!! %s\n",command[2]);
		   			}
		   		

		   }
		   else if (strcmp(command[0], "ls")==0){

		   			pid_t pid;

		   		pid = fork();

		   		if(pid <0){
		   			printf("%s\n","Fork failed" );
		   		}
		   		if(pid == 0){
		   			char filee[100];
		   			getcwd(filee, 100);
		   			//printf("%s\n",filee );

		   			//strcat(filee,"/");

		   			

		   		if(strcmp(command[1],"-i")== 0 ){
		   			//strcat(filee,command[2]);
		   			execl(ls,filee,"-i",  (char*) NULL);
		   		}
		   		else if(strcmp(command[1],"-a")== 0){
		   			//strcat(filee,command[2]);
		   			execl(ls,filee,"-a",  (char*) NULL);
		   		}
		   		else if (u>1){
		   			printf("Invalid Flag for ls %s\n",command[1] );
		   			exit(0);
		   		}
		   		else{
		   			strcat(filee,command[1]);
		   			execl(ls,filee ,"time", (char*) NULL);
		   		}



		   	}
		   	else{
		   		wait(NULL);
		   		continue;
		   	}


		   }

		   else if (strcmp(command[0], "cat")==0){
		   		pid_t pid;

		   		pid = fork();
		   			char filee[100];

		   			getcwd(filee, 100);
		   			//printf("%s\n",filee );

		   			strcat(filee,"/");



		   		if(pid <0){
		   			printf("%s\n","Fork failed" );
		   		}
		   		if(pid == 0){
		   			

		   		if((strcmp(command[1], "-n")==0 || strcmp(command[2], "-n")==0 ) && (strcmp(command[1], "-E")==0 || strcmp(command[2], "-E")==0 )){
		   			strcat(filee,command[3]);
		   			execl(cat,filee, "-E","-n", (char*) NULL);
		   		}
		   		else if (strcmp(command[1],"-n")==0){
		   			strcat(filee,command[2]);
		   			execl(cat,filee, "","-n", (char*) NULL);

		   		}
		   		else if (strcmp(command[1],"-E")==0){
		   			strcat(filee,command[2]);
		   			execl(cat,filee, "-E","", (char*) NULL);

		   		}
		   		else{
		   			strcat(filee,command[1]);
		   			execl(cat,filee, "","", (char*) NULL);
		   		}


		   	}
		   	else{
		   		wait(NULL);
		   		continue;
		   	}

		   }
		   else if (strcmp(command[0], "date")==0){
		   			pid_t pid;

		   		pid = fork();

		   		if(pid <0){
		   			printf("%s\n","Fork failed" );
		   		}
		   		if(pid == 0){
		   		if(strcmp(command[1],"-u")== 0 ){
		   			execl(date,command[1],  (char*) NULL);
		   		}
		   		else if(strcmp(command[1],"--debug")== 0){
		   			execl(date,command[1],  (char*) NULL);
		   		}
		   		else if (u>0){
		   			printf("Invalid Flag for Date %s\n",command[1] );
		   			exit(0);
		   		}
		   		else{
		   			execl(date, "time", (char*) NULL);
		   		}



		   	}
		   	else{
		   		wait(NULL);
		   		continue;
		   	}

		   }

		   else if (strcmp(command[0], "rm")==0){

		   		pid_t pid;

		   		pid = fork();

		   		if(pid <0){
		   			printf("%s\n","Fork failed" );
		   		}
		   		if(pid == 0){
		   			char filee[100];
		   			getcwd(filee, 100);
		   			//printf("%s\n",filee );

		   			strcat(filee,"/");

		   			

		   		if(strcmp(command[1],"-v")== 0 ){
		   			strcat(filee,command[2]);
		   			execl(rm,filee,"-v",  (char*) NULL);
		   		}
		   		else if(strcmp(command[1],"-f")== 0){
		   			strcat(filee,command[2]);
		   			execl(rm,filee,"-f",  (char*) NULL);
		   		}
		   		else if (u>1){
		   			printf("Invalid Flag for rm %s\n",command[1] );
		   			exit(0);
		   		}
		   		else{
		   			strcat(filee,command[1]);
		   			execl(rm,filee ,"time", (char*) NULL);
		   		}



		   	}
		   	else{
		   		wait(NULL);
		   		continue;
		   	}


		   }

		   else if (strcmp(command[0], "mkdir")==0){

		   		pid_t pid;

		   		pid = fork();

		   		if(pid <0){
		   			printf("%s\n","Fork failed" );
		   		}
		   		if(pid == 0){
		   			char filee[100];

		   			getcwd(filee, 100);
		   			//printf("%s\n",filee );

		   			strcat(filee,"/");

		   			

		   		if(strcmp(command[1],"-v")== 0 ){
		   			strcat(filee,command[2]);
		   			execl(mkdir,filee,"-v",  (char*) NULL);
		   		}
		   		else if(strcmp(command[1],"-m")== 0){
		   			strcat(filee,command[2]);
		   			execl(mkdir,filee,"-f",  (char*) NULL);
		   		}
		   		else if (u>1){
		   			printf("Invalid Flag for mkdir %s\n",command[1] );
		   			exit(0);
		   		}
		   		else{
		   			strcat(filee,command[1]);
		   			execl(mkdir,filee ,"time", (char*) NULL);
		   		}



		   	}
		   	else{
		   		wait(NULL);
		   		continue;
		   	}



		   }

		   else{
		   	printf("%s command is not valid please Enter valid command. \n", command[0] );
		   }





	}
	fclose(his);
}
