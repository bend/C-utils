#include "cracker.h"
#include <string.h>
void*
crack_password(void* arg){
  	params* p;
	buffer* buf;
	char* pass;
	struct zip_archive * archive;
		p =(params*)arg;
		buf = p->buf;
		printf("consumer buffer name%s\n",buf->name);
		printf("%d\n",&buf);
		if ((archive = zip_load_archive(p->filename)) == NULL) {
			printf("Unable to open archive %s\n", p->filename);
			exit(-1);
		 }
		sleep(5);
		printf("here\n");
		do{	
			printf("consumer_wait\n");
			//sem_wait(p->full);
			//pthread_mutex_lock(p->mutex);
			pass = bounded_buffer_get(buf);
			printf("testing %s\n",pass);
			if(zip_test_password(archive, pass) == 0) {
					printf("Password is: %s\n", pass);
					free(pass);
					bounded_buffer_free(buf);
					free(p->filename);
					free(p);
					exit(0);
			}
			//pthread_mutex_unlock(p->mutex);
			//sem_post(p->empty);
			printf("conusmer ++\n");
		}while(pass != NULL);

		pthread_exit(NULL);

}


void*
fill_buffer(void* arg){
	params* p;
	buffer* buf;
	int i;
	char* temp;
	FILE* file;
		p=(params*)arg;
		buf=p->buf;
		file = open_file(p->filename);    /*            		  Open file        */
		//temp=get_next(file);
		i=0;
		printf("producer buf name %s\n",buf->name);
		/*while(temp!=NULL && i<(int)buf->size){          * first fill of the buffer *
			bounded_buffer_put(buf,temp);
			temp=get_next(file);
			i++;
		}*/

		do{
			printf("producer_wait\n");
			//sem_wait(p->empty);
			//pthread_mutex_lock(p->mutex);
			if(buf->nb_elem < buf->size){
				temp = get_next(file);
				printf("producer  add %s\n",temp);
				bounded_buffer_put(buf, temp);
			}
			//	pthread_mutex_unlock(p->mutex);
		//sem_post(p->full);
			printf("producer_end_put\n");
			sleep(1);
		}while(temp!=NULL);


	pthread_exit(NULL);
}


void 
create_threads(unsigned int nb_threads, buffer* buf, char* file_to_crack, char* dictionary_file){
	pthread_t *threads;										/*Array of threads*/
	int rc;
	int i;
	int pthread_join_res;
	params *crack_params;
	params *fill_params;
	sem_t *full;
	sem_t *empty;
	pthread_mutex_t *mutex;
		

		pthread_mutex_init(mutex, NULL);				/* Create the mutex lock */
	    sem_init(full, 0, 0);							/* Create the full semaphore and initialize to 0 */
	    sem_init(empty, 0, buf->size);					/* Create the empty semaphore and initialize to BUFFER_SIZE */
		
		threads = malloc(sizeof(pthread_t)*nb_threads+1);			/* nb_threads+1 for storing the bounded_buffer thread*/
		if(threads == NULL){
			perror("malloc failed");
			bounded_buffer_free(buf);
			exit(-1);
		}
		
		crack_params = malloc(sizeof(params*));
		if(crack_params == NULL){
			perror("malloc failed");
			free(threads);
			bounded_buffer_free(buf);
			exit(-1);
		}
		crack_params->filename = file_to_crack;
		crack_params->empty = empty;
		crack_params->full = full;
		crack_params->mutex = mutex;
		crack_params->buf = buf;
		printf("$$$ %s\n",crack_params->buf->name);
		for(i=0; i<nb_threads; i++){						/* create crack threads */
			rc = pthread_create(&threads[i],NULL,crack_password,(void*)crack_params);   /*Creating thread*/
			if (rc){
				printf("ERROR; return code from pthread_create() is %d\n", rc);
			    free(threads);
				bounded_buffer_free(buf);
				free(crack_params);
			    exit(-1);
			}
		}

		printf("$$$ %s\n",crack_params->buf->name);

		
		fill_params = malloc(sizeof(params*));
		if(fill_params == NULL){
			perror("malloc failed");
			bounded_buffer_free(buf);
			free(threads);
			free(crack_params);
			exit(-1);
		}
		fill_params->buf = buf;
		fill_params->filename = dictionary_file;
		fill_params->full = full;
		fill_params->empty = empty;
		fill_params->mutex = mutex;
		rc =pthread_create(&threads[nb_threads+1],NULL,fill_buffer,(void*)fill_params);
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
            free(threads);
			bounded_buffer_free(buf);
			free(crack_params);
			free(fill_params);
			exit(-1);
		}
		for(i=0; i<nb_threads+1; i++)
			pthread_join_res = pthread_join(threads[i], NULL);
		
		bounded_buffer_free(buf);
		free(crack_params);
		free(fill_params);
		free(threads);
}


void create_process(unsigned int nb_process, buffer* buff, char* file_to_crack, char* dictionary_file){
		/* TODO implement */
	;
}


void start_cracking(char tp, unsigned int nb_pt, char* file_to_crack, char* dictionary_file){
	buffer* buf;
		buf=bounded_buffer_new(10);
		buf->name = "ben";
		if(tp=='p')
			create_process(nb_pt, buf,file_to_crack, dictionary_file);
		else
			create_threads(nb_pt,buf, file_to_crack, dictionary_file);
}
