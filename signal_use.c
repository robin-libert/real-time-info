#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*
Exemple of how I use a signal.
*/

int i = 0;

void handler(int sig){
	printf("%d\n",i);
	i++;
	alarm(1);//SIGALRM -> go to handler
}

int main(){
	
	struct sigaction sa;
	sa.sa_handler = handler;//go to a function I created to do something when my program receive a signal.
	sigfillset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGALRM, &sa, NULL);
	alarm(1);//SIGALRM -> go to handler
	while(1);
	return 0;
}
