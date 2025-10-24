#include<stdio.h>
#include<pthread.h>

struct Pub{
    int liczba_kufli;
    int liczba_klientow;
    int ile_litrow_per_klient;
};

void* funkcja_klient(void * args){
    struct Pub* p = (struct Pub*)args;

    for(int i = 0; i < p->ile_litrow_per_klient; i++){
        // weż kufel
        p->liczba_kufli -= 1;

        usleep(1000);

        // oddaj kufel
        p->liczba_kufli += 1;
    }

    printf("Wychodze z pubu\n");
}

int main(int argc, char const *argv[])
{
    // BRAK mutexow
    // różna liczba kufli na początku i na końcu
    const int liczba_kufli_start = 1000;
    struct Pub pub;
    pub.liczba_kufli = liczba_kufli_start;
    pub.liczba_klientow = 1000;
    pub.ile_litrow_per_klient = 300;

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
    
    return 0;
}
