#include<stdio.h>
#include<pthread.h>

struct Pub{
    int liczba_kufli;
    int liczba_klientow;
    int ile_litrow_per_klient;
    pthread_mutex_t mutex;
};

void* funkcja_klient(void * args){
    struct Pub* p = (struct Pub*)args;
    unsigned long long praca = 0;

    for(int i = 0; i < p->ile_litrow_per_klient; i++){
        // weź kufel
        // printf("Biore kufel\n");
        // printf("%d\n", p->liczba_kufli );
        int success = 0;
        do{
            pthread_mutex_lock(&(p->mutex));
            if(p->liczba_kufli > 0){
                if(p->liczba_kufli < 1)
                    printf("za malo\n");
                p->liczba_kufli -= 1;
                pthread_mutex_unlock(&(p->mutex));
                
                // nalej piwa -> sleep
                // printf("Nalewam piwo\n");
                sleep(1);
                
                // // wypij piwo -> sleep
                // printf("Pije piwo\n");
                // sleep(3);
            
                // oddaj kufel
                // printf("Oddaje kufel\n");
                pthread_mutex_lock(&(p->mutex));
                p->liczba_kufli += 1;
                pthread_mutex_unlock(&(p->mutex));
                
                success = 1;
            }
            else{
                pthread_mutex_unlock(&(p->mutex));
                praca++;
            }
        }while(success == 0);
        
    }

    // printf("Wychodze z pubu\n");
    printf("%llu\n", praca);
}

int main(int argc, char const *argv[])
{
    struct Pub pub;
    pub.liczba_kufli = 1000;
    pub.liczba_klientow = 2000;
    pub.ile_litrow_per_klient = 3;

    pthread_mutex_init(&(pub.mutex), NULL);

    pthread_t t_id[pub.liczba_klientow];

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_create(&t_id[i], NULL, funkcja_klient, &pub);
    }

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_join(t_id[i], NULL);
    }


    pthread_mutex_destroy(&(pub.mutex));
    printf("Kufle: %d\n", pub.liczba_kufli);

    return 0;
}
