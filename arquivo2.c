#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>				 // usado para o calculo de tempo de execucao do programa
#define THREADS 4				 // numero de threads a serem criadas

/*NOME: Vitor Henrique Spader Turma: GR86006-00021 RA: 1918176*/

long int p_num = 5000000;			 // numero final do range
long int i_num = 2;				 // numero inicial do range
long int contagem = 0;				 // contagem dos numeros primos 

pthread_mutex_t mutex1, mutex2;

void *t_1(){
	long int i;
	long int aux;
	int cont=0;

	while (i_num <= p_num){
		pthread_mutex_lock(&mutex1);	 // area critica
		
		aux = i_num;
		i_num++;

		pthread_mutex_unlock(&mutex1);

		for(i=2; i <= sqrt(aux); i++){  // verifica se o divisor e menor que a raiz quadrada do numero testado 
			if(aux % i == 0){	// verifica se o numero possui divisores diferentes de 1 e dele mesmo
				cont++;
				break;
			}
		}
		if(cont == 0){				// OBS: numero 2 ignora for e acessa diretamente o if
			//printf("%li - primo \n",aux); // linha de codigo para teste
			pthread_mutex_lock(&mutex2);	// area critica
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
	pthread_t t1[THREADS];
	
	inicio = time(NULL);
	
	printf("\n Procurando por numeros primos... \n");

	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);
	for(i=0; i < THREADS; i++)			
		(void) pthread_create(&(t1[i]),NULL,t_1,NULL);

	for(i=0; i < THREADS;i++)
		(void) pthread_join(t1[i],NULL);

	printf("Foram encontrados %li numeros primos!!! \n",contagem);

	fim = time(NULL);

	printf("Duraçao de execução: %.2f \n", difftime(fim,inicio));
	return 0;
}


