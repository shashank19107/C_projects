#include<string.h>
#include <stdio.h> 
#include <dirent.h> 

  
int main(int argc, char *argv[]) 
{ 
    struct dirent *de;  // Pointer for directory entry 
  
  
    DIR *dr = opendir(argv[0]); 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  


    //with -i flag
    if(strcmp(argv[1], "-i")==0)
    while ((de = readdir(dr)) != NULL) {
            printf(" %ld %s\n",de->d_ino, de->d_name); 
        }
  

    // wihtout -i flag
    else if(strcmp(argv[1], "-a")==0)
        while ((de = readdir(dr)) != NULL) {
            printf(" %s\n", de->d_name); 
        }
    else{
        while ((de = readdir(dr)) != NULL) {
            printf(" %s\n", de->d_name); 
        }

    }
    closedir(dr);     
    return 0; 
}
