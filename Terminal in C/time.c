#include <stdio.h> 
#include <dirent.h> 
#include<string.h>
#include <time.h>
int main(int argc, char *argv[]) 
{ 
	time_t t;
	time(&t);
	struct tm * ptm;
	ptm = gmtime(&t);
	time_t utc = mktime(ptm);
	if(strcmp(argv[0],"-u")== 0)
		printf("%sUTC \n",ctime(&utc) );
	else 
		printf("%sIST\n",ctime(&t) );
	
	return 0;

}
