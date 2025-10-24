#include<stdio.h>
#include<time.h>
#include<pthread.h>

#define LICZBA_KRANOW 10

struct Pub{
    int liczba_kufli;
    int liczba_klientow;
    int ile_litrow_per_klient;
    int liczba_kranow;
    // int krany[LICZBA_KRANOW];
    pthread_mutex_t mutex_krany[LICZBA_KRANOW];
};
pthread_mutex_t mutex_kufle = PTHREAD_MUTEX_INITIALIZER;
// pthread_mutex_t mutex_kran = PTHREAD_MUTEX_INITIALIZER;

void* funkcja_klient(void * args){
    struct Pub* p = (struct Pub*)args;
    unsigned long long praca = 0;
    
    for(int i = 0; i < p->ile_litrow_per_klient; i++){

        int success = 0;
        do{
            if(pthread_mutex_trylock(&mutex_kufle) == 0){
                if(p->liczba_kufli > 0){
                    p->liczba_kufli -= 1;
                    success = 1;
                    pthread_mutex_unlock(&mutex_kufle);
                }
                else{
                    pthread_mutex_unlock(&mutex_kufle);
                    usleep(rand()%500+1000); 
                }
            }
            else{
                praca++;
            }

        }while(success == 0);
        
        success = 0;

        do{
            for(int i = 0; i < p->liczba_kranow; i++){
                if(pthread_mutex_trylock(&(p->mutex_krany[i])) == 0){
                    success = 1;
                    printf("kran: %d\n", i);
                    usleep(1000);
                    pthread_mutex_unlock(&(p->mutex_krany[i]));
                }  
                else{
                    // praca
                    praca++;
                }
            }
        }while(success == 0);

        
        // wypij piwo
        usleep(300);
        
        success = 0;
        do{
            if(pthread_mutex_trylock(&mutex_kufle) == 0){
                // oddaj kufel
                success = 1;
                p->liczba_kufli += 1;
                pthread_mutex_unlock(&mutex_kufle);
            }
            else{
                praca++;
            }
        }while(success == 0);
    }

    printf("Praca %llu\n", praca);
    return NULL;
}

int main(int argc, char const *argv[])
{
    const int liczba_kufli_start = 100;
    struct Pub pub;
    pub.liczba_kufli = liczba_kufli_start;
    pub.liczba_klientow = 2000;
    pub.ile_litrow_per_klient = 2;
    pub.liczba_kranow = LICZBA_KRANOW;

    for(int i = 0; i < LICZBA_KRANOW; i++){
        pthread_mutex_init(&pub.mutex_krany[i], NULL);
    }

    pthread_t t_id[pub.liczba_klientow];

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_create(&t_id[i], NULL, funkcja_klient, &pub);
    }

    for(int i = 0; i < pub.liczba_klientow; i++){
        pthread_join(t_id[i], NULL);
    }
    
    
    
    printf("Kufle: %d\n", pub.liczba_kufli);
    if(pub.liczba_kufli != liczba_kufli_start){
        printf("!Kwantowe kufle!\n");
    }

    pthread_mutex_destroy(&mutex_kufle);
    // pthread_mutex_destroy(&mutex_kran);
    
    return 0;
}
