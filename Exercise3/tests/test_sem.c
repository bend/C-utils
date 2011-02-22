#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t *sem;

void* 
producer(void* arg){
	while(1){
		sem = sem_open("MySemaphore", (O_CREAT|O_EXCL), S_IRWXU, 0) ;
		printf("Im thread %d\n",1);
		sem_unlink(sem);
		sem_close(sem);
	}
	return NULL;

}



void*
consumer(void* arg){
	while(1){
		sem_wait(sem);
		printf("Im thread %d\n",2);
		sem_post(sem);
	}
	return NULL;
}



int main(){
	pthread_t prod, cons, prod2,cons2;


	pthread_create(&prod, NULL, producer,(void*)1);
	sleep(1);
	pthread_create(&cons, NULL, producer,(void*)2);

	pthread_join(prod, NULL);
	
	pthread_join(cons, NULL);


	return 1;
}
