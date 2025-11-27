// #include<stdlib.h>
// #include<stdio.h>
// #include<pthread.h>


// struct Bariera
// {
//     pthread_mutex_t mutex;
//     pthread_cond_t warunek;
//     int liczba_wejsc;
//     int liczba_watkow;
// };


// pthread_mutex_t mutex;
// pthread_cond_t warunek;
// int liczba_wejsc = 0;
// int liczba_watkow = 0;

// void bariera_init(int nt, struct Bariera *bariera){
//     bariera->liczba_watkow = nt;
//     bariera->liczba_wejsc = 0;
//     pthread_mutex_init(&bariera->mutex, NULL);
//     pthread_cond_init(&bariera->warunek, NULL);
// }

// void bariera(struct Bariera *bariera){ 
//     pthread_mutex_lock(&bariera->mutex);

//     bariera->liczba_wejsc++;

//     if(bariera->liczba_wejsc == bariera->liczba_watkow){
//         bariera->liczba_wejsc = 0;
//         pthread_cond_broadcast(&bariera->warunek);
//     }else{
//         pthread_cond_wait(&bariera->warunek, &bariera->mutex);
//     }
    
//     pthread_mutex_unlock(&bariera->mutex);
// };