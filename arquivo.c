#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>


long int p_num = 5000000;
long int contagem = 0;
pthread_mutex_t mutex1, mutex2;

void *t_1(){
	long int i;
	long int aux;
	int cont;

	while (p_num > 1){
		pthread_mutex_lock(&mutex1);
		
		aux = p_num;
		p_num--;

		pthread_mutex_unlock(&mutex1);

		for(i=2; i <= (sqrt(aux)); i++){
			if(aux % i == 0){
				cont++;
				break;
			}
		}
		if(cont == 0){
			//printf("%li e primo \n",aux);
			pthread_mutex_lock(&mutex2);
			contagem++;
			pthread_mutex_unlock(&mutex2);
		}
		else
			cont = 0;
	}
	pthread_exit(0);
}

int main(){
	int i;
	time_t inicio, fim;
	pthread_t t1[4];
	
	inicio = time(NULL);
	
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	for(i=0; i < 4; i++)
		(void) pthread_create(&(t1[i]),NULL,t_1,NULL);

	for(i=0; i < 4;i++)
		(void) pthread_join(t1[i],NULL);

	printf("Foram encontrados %li numeros primos!!! \n",contagem);
	fim = time(NULL);
	printf("Duraçao de execução: %f", difftime(fim,inicio));
	return 0;
}


