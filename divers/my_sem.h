#ifndef __MY_SEM_H__
#define __MY_SEM_H__

#include <fcntl.h>  /*needed on linux for O_ constants */
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define MUTEX 		"mutex"
#define MUTEX_FREE 	"mutex_free"

struct my_sem{
	int value;
	sem_t *mutex_free;
	sem_t *mutex;
};

typedef struct my_sem my_sem;

/*
 * Create a Semaphore with value nb
 * @param nb : the initial value of the semaphore
 * @param sem: a pointer to the pointer to my_sem descriptor
 * @return 0 if success, -1 otherwise
 */
int 
my_sem_init(my_sem** sem, unsigned int nb);

/*
 * waits on the semaphore and decrement it of nb
 * @param nb: the value of decrementation
 * @param sem: pointer to my_sem descriptor
 * @return 0 if success, -1 otherwise
 */
int 
my_sem_wait(my_sem *sem, unsigned int nb);

/*
 * posts the semaphore and increments it of nb
 * @param nb the value of incrementation
 * @param sem: pointer to my_sem descriptor
 */
int 
my_sem_post(my_sem *sem, unsigned int nb);

/*
 * Closes the semaphore and frees the structure
 * @param sem: a pointer to the sem desciptor
 * @return 0 if success -1 otherwise
 */
int
my_sem_close(my_sem *sem);

#endif
