#include<stdio.h>
#include<time.h>
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
        
        
        // success = 0;
        // do{
        //     if(pthread_mutex_trylock(&mutex_kran) == 0){
        //         // nalej piwa
        //         success = 1;
        //         usleep(1000);
        //     }
        //     else{
        //         praca++;
        //     }
        //     pthread_mutex_unlock(&mutex_kran);
        // }while(success == 0);
        
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
            // pthread_mutex_unlock(&mutex_kufle);
        }while(success == 0);
        // pthread_mutex_lock(&mutex_kufle);
        // p->liczba_kufli+=1;
        // pthread_mutex_unlock(&mutex_kufle);
    }

    printf("Praca %llu\n", praca);
    return NULL;
}

int main(int argc, char const *argv[])
{
    const int liczba_kufli_start = 100;
    struct Pub pub;
    pub.liczba_kufli = liczba_kufli_start;
    pub.liczba_klientow = 500;
    pub.ile_litrow_per_klient = 100;

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
    pthread_mutex_destroy(&mutex_kran);
    
    return 0;
}
