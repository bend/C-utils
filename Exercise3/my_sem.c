#include "my_sem.h"
#include <stdio.h>


my_sem*  my_sem_init( unsigned int val){
  	my_sem* sem;
  	sem = malloc(sizeof(my_sem));
  	sem->mutex = malloc(sizeof(pthread_mutex_t*));
	sem->waiting = malloc(sizeof(pthread_mutex_t*));
	pthread_mutex_init(sem->mutex, NULL);
	pthread_mutex_init(sem->waiting,NULL);
	pthread_mutex_unlock(sem->mutex);
	sem->c=val;
	return sem;
}

void my_sem_wait(my_sem* sem){
  	pthread_mutex_lock(sem->mutex);
	sem->c--;
	if(sem->c<0){
		pthread_mutex_unlock(sem->mutex);
		pthread_mutex_lock(sem->waiting);
	}
	pthread_mutex_unlock(sem->mutex);
}

void my_sem_post(my_sem* sem){
	pthread_mutex_lock(sem->mutex);
	sem->c++;
	if(sem->c<=0){
		pthread_mutex_unlock(sem->waiting);
	}else{
		pthread_mutex_unlock(sem->mutex);
	}
}

void my_sem_close(my_sem* sem){
	pthread_mutex_destroy(sem->waiting);
	pthread_mutex_destroy(sem->mutex);
	free(sem->mutex);
	free(sem->waiting);
	free(sem);
}
	
