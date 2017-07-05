#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/*
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m4 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m5 = PTHREAD_MUTEX_INITIALIZER;
*/

pthread_mutex_t m[5];

struct model{
	int shop[5];
	int buyer[3];
};


void buyer1(struct model *tranz){
	int sh = 0, i;
	while(tranz->buyer[0]>0){
		for(i=0; i<5; i++){
			pthread_mutex_trylock(&m[i]);
				sh = rand()%500;
				if(tranz->buyer[0] > 0){
					tranz->shop[i]=tranz->shop[i]-sh;
					tranz->buyer[0] = tranz->buyer[0]-sh;
					printf("\n++++++++++++++++++++\nNumber shop - %d\nNumber buyer - %d\nBuy summ - %d\nBalance shop - %d\nBalance buyer1 - %d\n++++++++++++++++++++\n", i, 1, sh, tranz->shop[i], tranz->buyer[0]);
				}
			pthread_mutex_unlock(&m[i]);
			if (sh != 0){
	                        sleep(4);
	                        sh = 0;
		        }
		}
	}
}

void buyer2(struct model *tranz){
	int sh = 0, i;
	while(tranz->buyer[1]>0){
	        for(i=0; i<5; i++){
                        pthread_mutex_trylock(&m[i]);
                                sh = rand()%500;
				if(tranz->buyer[1] > 0){
	                                tranz->shop[i]=tranz->shop[i]-sh;
	                                tranz->buyer[1] = tranz->buyer[1]-sh;
	                                printf("\n++++++++++++++++++++\nNumber shop - %d\nNumber buyer - %d\nBuy summ - %d\nBalance shop - %d\nBalance buyer2 - %d\n++++++++++++++++++++\n", i, 2, sh, tranz->shop[i], tranz->buyer[1]);
				}
                        pthread_mutex_unlock(&m[i]);
                        if (sh != 0){
                                sleep(4);
                                sh = 0;
                        }
                }

	}
}

void buyer3(struct model *tranz){
	int sh = 0, i;
	while(tranz->buyer[2]>0){
	        for(i=0; i<5; i++){
                        pthread_mutex_trylock(&m[i]);
                                sh = rand()%500;
				if(tranz->buyer[2] > 0){
        	                        tranz->shop[i]=tranz->shop[i]-sh;
	                                tranz->buyer[2] = tranz->buyer[2]-sh;
	                                printf("\n++++++++++++++++++++\nNumber shop - %d\nNumber buyer - %d\nBuy summ - %d\nBalance shop - %d\nBalance buyer3 - %d\n++++++++++++++++++++\n", i, 2, sh, tranz->shop[i], tranz->buyer[2]);
				}
                        pthread_mutex_unlock(&m[i]);
                        if (sh != 0){
                                sleep(4);
                                sh = 0;
                        }
                }
	}
}


void Loader(struct model *tranz){
	int i, sh, k;
	while(1){
		for(i=0; i<5; i++){
/*			k = rand()%4;
*/		        pthread_mutex_trylock(&m[i]);
				sh = rand()%300;
				tranz->shop[i] = tranz->shop[i]+sh;
				printf("\n----------\nNumber shop - %d\nLoad - %d\nBalance shop - %d\n----------\n", i, sh, tranz->shop[i]);
		        pthread_mutex_unlock(&m[i]);
        	        if (sh != 0){
        	                sleep(2);
        	                sh = 0;
	                }
		}
	}
}


int main(){
	int **shop, *buyer, i;
	struct model *tranz;
	pthread_t tid[4];
/*	pthread_mutex_t m[5];
*/	srand(time(NULL));
	for(i=0; i<5; i++)
		pthread_mutex_init(&m[i], NULL);
	tranz = malloc(sizeof(struct model));
/*	tranz->shop = malloc(sizeof(int)*5);
	tranz->buyer = malloc(sizeof(int)*3);
*/
	for(i=0; i<5; i++){
		tranz->shop[i] = (rand()%100-50)+1000;
	}

	for(i=0; i<3; i++){
                tranz->buyer[i] = (rand()%200-100)+3000;
        }
	printf("Papap\n");
	pthread_create(&tid[0], NULL, buyer1, (void*)tranz);
	pthread_create(&tid[1], NULL, buyer2, (void*)tranz);
	pthread_create(&tid[2], NULL, buyer3, (void*)tranz);
	pthread_create(&tid[3], NULL, Loader, (void*)tranz);

	for(i=0; i<3; i++){
		pthread_join(tid[i], NULL);
	}
	pthread_cancel(tid[3]);

	exit(0);
}
