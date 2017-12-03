
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(){
	int n_neg = -1;
	int n_pos = -1;
	int result_gauche;
	int result_droit;

	//creation de 2 tubes car le père va communiquer avec 2 processus
	int descs1[2];
	int descs2[2];
	if(pipe(descs1)){//erreur
		return -1;
	}
	if(pipe(descs2)){//erreur
		return -1;
	}
	
	//creation de 2 processus
	
	int pid_fils_gauche;
	int pid_fils_droit;
	
	pid_fils_gauche = fork();
	if(pid_fils_gauche == 0){
		while(1){
			read(descs1[0], &n_neg, sizeof(int));
			if(n_neg == 0){
				write(descs1[1], &result_gauche, sizeof(int));
				break;
			}else{
				result_gauche = result_gauche + n_neg;
			}
		}
		exit(0);
	}
	
	pid_fils_droit = fork();
	if(pid_fils_droit == 0){
		while(1){
			read(descs2[0], &n_pos, sizeof(int));
			if(n_pos == 0){
				write(descs2[1], &result_droit, sizeof(int));
				break;
			}else{
				result_droit = result_droit + n_pos;
			}
		}
		exit(0);
	}
	int res1, res2;
	while(1){
		int entry;
		printf("Entrez un nombre : \n");
		scanf("%d", &entry);
		if(entry == 0){
			write(descs1[1], &entry, sizeof(int));
			write(descs2[1], &entry, sizeof(int));
			wait(NULL);
			wait(NULL);
			read(descs1[0], &res1, sizeof(int));
			read(descs2[0], &res2, sizeof(int));
			close(descs1[0]);
			close(descs1[1]);
			close(descs2[0]);
			close(descs2[1]);
			break;
		}
		if(entry < 0){
			write(descs1[1], &entry, sizeof(int));
		}else{
			write(descs2[1], &entry, sizeof(int));
		}
	}
	printf("Résultat négatif : %d\n", res1);
	printf("Résultat positif : %d\n", res2);
	
	
	return 0;
}
