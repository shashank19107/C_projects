#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>

int main(int argc, char *argv[]) {

	//printf("All the best\n");

	FILE *fp;
	// for(int i=0; i<argc;i++)
	// printf("%s\n",argv[i]);
	//printf("%s\n",argv[1]);
	//printf("%s\n",argv[2]);
	fp = fopen(argv[0], "r");
	if(fp == NULL){
		printf("%s\n","FAiled to open the file" );
	}
	else{
		//printf("%s\n", "The contents of the file are:" );
		char arr[10240];
		int c=0;
		if(strcmp(argv[1],"-E")==0 && strcmp(argv[2],"-n")==0){
				printf("%s\n","here" );
				c++;
					while(!feof(fp)){
					    fscanf(fp, "%[^\n]\n", arr);
					    printf("%d %s\n",c, arr);
					}
		}

		else if(strcmp(argv[2],"-n")==0){
				printf("%s\n","Here 2" );

				while(!feof(fp)){
					c++;
					    fscanf(fp, "%[^\n]\n", arr);
					    printf("%d %s\n",c, arr);
					}

			}

		else if (strcmp(argv[1],"-E")==0){
				printf("%s\n","Here 3" );
				while(!feof(fp)){
					    fscanf(fp, "%[^\n]\n", arr);
					    printf("$ %s\n", arr);
					}
			}

		else{
				printf("%s\n","Here 4" );
				while(!feof(fp)){
					    fscanf(fp, "%[^\n]\n", arr);
					    printf("%s\n", arr);
					}
			}

	}
	fclose(fp);
	exit(0);


}