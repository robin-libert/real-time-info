#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
	int pid_fils_gauche;
	int pid_fils_droit;
	printf("Je suis le pere %d\n", getpid());
	pid_fils_gauche = fork();
	if(pid_fils_gauche == 0){
		printf("Je suis le fils gauche %d %d\n", getpid(), getppid());
		exit(0);
	}else{	
	pid_fils_droit = fork();
	if(pid_fils_droit == 0){
		printf("Je suis le fils droit %d %d\n", getpid(), getppid());
		exit(0);
	}
	wait(NULL);
	wait(NULL);
	return 0;
}
