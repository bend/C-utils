#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "../my_sem.h" 

my_sem *sem;

pthread_mutex_t mutexsum;
void* 
producer(void* arg){
  			my_sem_wait(sem);
  			printf("I'm producer\n");
			sleep(1);
			my_sem_post(sem);
	return NULL;

}

void*
consumer(void* arg){
  			my_sem_wait(sem);
  			printf("I'm consumer\n");
			sleep(1);
			my_sem_post(sem);
	return NULL;
}



int main(){
		
  
  
  	pthread_t prod, cons, prod2,cons2;

	sem = my_sem_init(1);
	
	pthread_create(&prod, NULL, producer,(void*)1);
	pthread_create(&cons, NULL, consumer,(void*)2);
	
	pthread_create(&cons2, NULL, producer,(void*)2);
	pthread_create(&prod2, NULL, consumer,(void*)2);
	pthread_join(prod, NULL);
	
	pthread_join(cons, NULL);
	pthread_join(cons2, NULL);
	pthread_join(prod2, NULL);
	

	return 1;
}
