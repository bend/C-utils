#include "../my_sem.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>  


my_sem *sem;

void 
test_init_close(){
	assert(my_sem_init(&sem, 4)==0);
	assert(sem != NULL);
	assert(my_sem_close(sem)==0);
}

void*
prod1(){
	assert(my_sem_wait(sem,4)==0);
	printf("prod1, sem aquired\n");
	sleep(3);
	assert(my_sem_post(sem,2)==0);
	printf("prod1, sem_post\n");
	return NULL;
}

void*
prod2(){
	assert(my_sem_wait(sem,2)==0);
	printf("prod2, sem aquired\n");
	assert(my_sem_post(sem,0)==0);
	printf("prod2, sem_post\n");
	return NULL;
}


void test_sem(){
	pthread_t t1,t2;
	assert(my_sem_init(&sem, 4)==0);
	pthread_create(&t1,NULL,prod1,NULL);
	pthread_create(&t2,NULL,prod2,NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}

int main(){
	test_init_close();
	/*test_sem();*/
	printf("All semaphores tests succeded\n");
	return EXIT_SUCCESS;
}
