#include<stdio.h>
#include<pthread.h>

struct Pub{
    int liczba_kufli;
    int liczba_klientow;
    int ile_litrow_per_klient;
};
pthread_mutex_t mutex_kufle = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_kran = PTHREAD_MUTEX_INITIALIZER;

void* funkcja_klient(void * args){
    struct Pub* p = (struct Pub*)args;
    
    for(int i = 0; i < p->ile_litrow_per_klient; i++){
        pthread_mutex_lock(&mutex_kufle);
        p->liczba_kufli -= 1;
        if(p->liczba_kufli < 0)
            printf("Kufel magiczny! - blad logiki\n");
        pthread_mutex_unlock(&mutex_kufle);
        
        // nalej piwa
        pthread_mutex_lock(&mutex_kran);
        // printf("Leje\n");
        usleep(1000);
        // printf("leje koniec\n");
        pthread_mutex_unlock(&mutex_kran);
        
        // wypij piwo
        // printf("Pije\n");
        usleep(3000);
        // printf("Pije koniec\n");
        
        pthread_mutex_lock(&mutex_kufle);
        // printf("Oddaje\n");
        p->liczba_kufli += 1;
        pthread_mutex_unlock(&mutex_kufle);
    }

    // printf("wychodze z pubu\n");

    return NULL;
}

int main(int argc, char const *argv[])
{
    const int liczba_kufli_start = 1;
    struct Pub pub;
    pub.liczba_kufli = liczba_kufli_start;
    pub.liczba_klientow = 10;
    pub.ile_litrow_per_klient = 3;

    pthread_t t_id[pub.liczba_klientow];

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_create(&t_id[i], NULL, funkcja_klient, &pub);
    }

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_join(t_id[i], NULL);
    }

    
    pthread_mutex_destroy(&mutex_kufle);
    pthread_mutex_destroy(&mutex_kran);

    printf("Kufle: %d\n", pub.liczba_kufli);
    if(pub.liczba_kufli != liczba_kufli_start){
        printf("!Kwantowe kufle!\n");
    }
    
    return 0;
}
