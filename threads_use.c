#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex1;
int compteur = 0;

void thread_0(){
	pthread_mutex_lock(&mutex);
	sleep(1);
	while(compteur < 10){
		compteur += 1;
		printf("%d\n", compteur);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

void thread_1(){
	printf("Début du temps impartis\n");
	pthread_mutex_lock(&mutex);
	printf("Fin du temps impartis\n");
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(){
	pthread_t thread0;
	pthread_t thread1;
	
	if(pthread_create(&thread0, NULL, (void*)&thread_0, NULL)){
		perror("thread create0");
		return 0;
	}
	
	if(pthread_create(&thread1, NULL, (void*)&thread_1, NULL)){
		perror("thread create1");
		return 0;
	}
	
	if(pthread_join(thread0, NULL)){
		perror("join0");
		return 0;
	}
	
	if(pthread_join(thread1, NULL)){
		perror("join1");
		return 0;
	}
	
	return 0;
}
