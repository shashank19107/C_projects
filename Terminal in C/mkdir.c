#include<stdio.h> 
#include<string.h> 

int main(int argc, char *argv[]) {

	int file = remove(argv[0]);
	if(file==0){
		if(strcmp(argv[1], "-v")==0){
			printf("rm: Deleted File %s\n",argv[0] );
		}
		if(strcmp(argv[1], "-f")==0){

		}
		else
		printf("%s\n","The file deleted successfully" );
	}
	else{
		printf("Error: Unable to find the file %s\n", argv[0]);
	}

	return 0;


	}