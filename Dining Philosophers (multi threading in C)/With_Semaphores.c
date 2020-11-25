#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include <sys/sem.h>

sem_t table, spoons[5];  //Semophore ffor table will allow only 4 philosphers at once


void * philospher(int i){
	sem_wait(&table);  // to limit the total number of philosphers to be 4.
	if((i+1)%2==0){
		sleep(1);
	}
	sem_wait(&spoons[(i+1)%5]);
	sem_wait(&spoons[i]);
	
	printf("Philospher %d acquired both the spoons %d , %d\n",i+1, i+1, (i+1)%5 +1 );
	printf("Philospher %d is currently eating.\n",i+1 );
	printf("Philospher %d has finished eating.\n",i+1 );
	sem_post(&spoons[(i+1)%5]);
	sem_post(&spoons[i]);
	sem_post(&table);

}

void main(){
		pthread_t thread[5];
		sem_init(&table, 0, 4);			//To allow only 4 philosphers on the table at once.
		int i=0;
		while(i<5){
			sem_init(&spoons[i],0,1);	//To allow only one philospher on a spoon at once.
			i++;
		}
		int j=0;
		printf("%s\n","Creating 5 philosphers" );
		while(j<5){
			pthread_create(&thread[j], NULL, philospher, j);
			j++;
		}
		j =0;
		while(j<5){
			pthread_join(thread[j], NULL);
			j++;
		}
		printf("%s\n","Dinner Finished" );


}
