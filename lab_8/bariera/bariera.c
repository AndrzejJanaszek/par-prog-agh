#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

pthread_mutex_t mutex;
pthread_cond_t warunek;
int liczba_wejsc = 0;
int liczba_watkow = 0;

void bariera_init(int nt){
    liczba_watkow = nt;
    liczba_wejsc = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&warunek, NULL);
};

void bariera(void){ 
    pthread_mutex_lock(&mutex);

    liczba_wejsc++;

    // 
    if(liczba_wejsc == liczba_watkow){
        liczba_wejsc = 0;
        pthread_cond_broadcast(&warunek);
    }else{
        pthread_cond_wait(&warunek, &mutex);
    }
    
    pthread_mutex_unlock(&mutex);
};