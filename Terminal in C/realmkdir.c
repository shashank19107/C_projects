#include<stdio.h> 
#include<string.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
		int al = -1;
	if(strcmp(argv[1],"-v")== 0){
		al = mkdir(argv[0], 0777);
		printf("%s","mkdir: " );
	}
	else if((strcmp(argv[1],"-m")== 0)){
		al = mkdir(argv[0], 0777);
	}
	else{
		al =  mkdir(argv[0],0777);
	}

	 if (al == -1) 
        printf("%s\n","unable to create a directory: Error occured" );
  
    else
        printf("%s\n","Directory created" );


	return 0;
}