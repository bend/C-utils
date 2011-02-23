#include <pthread.h>
#include <stdlib.h>
struct my_sem{
	pthread_mutex_t *mutex;
	pthread_mutex_t *waiting;
	int c;
};
typedef struct my_sem my_sem;


my_sem* my_sem_init( unsigned int val);

void my_sem_wait(my_sem* sem);

void my_sem_post(my_sem* sem);

void my_sem_close(my_sem* sem);
