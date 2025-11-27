#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

// -bariera
struct Bariera
{
    pthread_mutex_t mutex;
    pthread_cond_t warunek;
    int liczba_wejsc;
    int liczba_watkow;
};

void bariera_init(int nt, struct Bariera *bariera){
    bariera->liczba_watkow = nt;
    bariera->liczba_wejsc = 0;
    pthread_mutex_init(&bariera->mutex, NULL);
    pthread_cond_init(&bariera->warunek, NULL);
}

void bariera(struct Bariera *bariera){ 
    pthread_mutex_lock(&bariera->mutex);

    bariera->liczba_wejsc++;

    if(bariera->liczba_wejsc == bariera->liczba_watkow){
        bariera->liczba_wejsc = 0;
        pthread_cond_broadcast(&bariera->warunek);
    }else{
        pthread_cond_wait(&bariera->warunek, &bariera->mutex);
    }
    
    pthread_mutex_unlock(&bariera->mutex);
};


///--------- bariera


#define LICZBA_W 4
//#define LICZBA_W 44

pthread_t watki[LICZBA_W];

void *cokolwiek( void *arg);

struct Bariera bariera1;

int main( int argc, char *argv[] ){

  int i, indeksy[LICZBA_W]; for(i=0;i<LICZBA_W;i++) indeksy[i]=i; 

  // use of pthread_once (once_control, init_routine) ?
  // int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));
  // but init_routine has no arguments...
  bariera_init(LICZBA_W, &bariera1);

  for(i=0; i<LICZBA_W; i++ ) {
    pthread_create( &watki[i], NULL, cokolwiek, (void *) &indeksy[i] );
  }

  for(i=0; i<LICZBA_W; i++ ) pthread_join( watki[i], NULL );

  pthread_exit( NULL);  
}


void *cokolwiek( void *arg){

  int i, moj_id;

  moj_id = *( (int *) arg ); 

  printf("przed bariera 1 - watek %d\n",moj_id);

  bariera(&bariera1);

   printf("przed bariera 2 - watek %d\n",moj_id);

  bariera(&bariera1);

  printf("przed bariera 3 - watek %d\n",moj_id);

  bariera(&bariera1);

  printf("przed bariera 4 - watek %d\n",moj_id);

  bariera(&bariera1);

  printf("po ostatniej barierze - watek %d\n",moj_id);  

  pthread_exit( (void *)0);
}
