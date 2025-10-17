// orginał i kopia

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

struct Odcinek{
    double a;
    double b;
    double srodek;
};

void * thread_fun_ref (void * arg_wsk)
{
    // tworzymy kopie
    // struct Odcinek odc = *((struct Odcinek*)arg_wsk);
    struct Odcinek* odc = (struct Odcinek*)arg_wsk;

    odc->srodek = (odc->b - odc->a) / 2.0 + odc->a;
    // printf("Srodek: %lf\n", odc->srodek);

    return NULL;
}

void * thread_fun_copy (void * arg_wsk)
{
    // tworzymy kopie
    struct Odcinek odc = *((struct Odcinek*)arg_wsk);
    // struct Odcinek* odc = (struct Odcinek*)arg_wsk;

    odc.srodek = (odc.b - odc.a) / 2.0 + odc.a;
    // printf("Srodek: %lf\n", odc->srodek);

    return NULL;
}


int main()
{
    // const int thread_number = 10;
    const int ilosc_podzialow = 10;
    const double caly_a = 0;
    const double caly_b = 100;
    const double dlugosc_odcinka = caly_b - caly_a;


    pthread_t t_ids[ilosc_podzialow];

    struct Odcinek pododcinki[ilosc_podzialow];

    // 0: 5
    // 9: 50

    // (55+5)*5

    // pthread_t t_id;

    for(int i = 0; i < ilosc_podzialow; i++){
        pododcinki[i].a = (dlugosc_odcinka / ilosc_podzialow)*i;
        pododcinki[i].b = (dlugosc_odcinka / ilosc_podzialow)*(i+1);
        pododcinki[i].srodek = 0;
        pthread_create(&t_ids[i], NULL, thread_fun_ref, &pododcinki[i]);
    }

    double suma = 0;
    for(int i = 0; i < ilosc_podzialow; i++){
        pthread_join(t_ids[i], NULL);
        suma += pododcinki[i].srodek;
    }

    printf("Suma środków: %lf\n", suma);
}

    