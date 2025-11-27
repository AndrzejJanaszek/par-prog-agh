#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

// chce czytac
int my_read_lock_lock(cz_t* cz_p){
  while(cz_p->l_p > 0 || cz_p->waiting_pisarze > 0){
    cz_p->waiting_czytelnicy++;
    printf("🟡CZYTAĆ \t\t🟥czekam\n");
    pthread_cond_wait(&cz_p->czytelnicy_cond, &cz_p->mutex);
    printf("🟡CZYTAĆ \t\t🟢NIEczekam\n");
    cz_p->waiting_czytelnicy--;
  }

  cz_p->l_c++;
  pthread_cond_signal(&cz_p->czytelnicy_cond);
}

// koniec czytania
int my_read_lock_unlock(cz_t* cz_p){
   
  cz_p->l_c--;

  if(cz_p->l_c == 0)
    pthread_cond_signal(&cz_p->pisarze_cond);

}

// chce pisac
int my_write_lock_lock(cz_t* cz_p){
  while(cz_p->l_c + cz_p->l_p > 0){
    cz_p->waiting_pisarze++;
    printf("🔵PISAĆ \t\t🟥czekam\n");
    pthread_cond_wait(&cz_p->pisarze_cond, &cz_p->mutex);
    printf("🔵PISAĆ \t\t🟢NIEczekam\n");
    cz_p->waiting_pisarze--;
  }

  cz_p->l_p++;
}

// koniec pisania
int my_write_lock_unlock(cz_t* cz_p){
  cz_p->l_p--;

  if(cz_p->waiting_czytelnicy > 0){
    pthread_cond_signal(&cz_p->czytelnicy_cond);
  }
  else{
    pthread_cond_signal(&cz_p->pisarze_cond);
  }
  
}

void inicjuj(cz_t* cz_p){

  cz_p->l_p = 0;
  cz_p->l_c = 0;  

  cz_p->waiting_czytelnicy = 0;
  cz_p->waiting_pisarze = 0;

  pthread_mutex_init(&cz_p->mutex, NULL);
  pthread_cond_init(&cz_p->pisarze_cond, NULL);
  pthread_cond_init(&cz_p->czytelnicy_cond, NULL);

}

void czytam(cz_t* cz_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tczytam:  l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
// warunek:
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    printf("lp: %d; lcz: %d\n", cz_p->l_p, cz_p->l_c);
    exit(0);
  }

    usleep(rand()%3000000);
}

void pisze(cz_t* cz_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
  printf("\t\t\t\t\tpisze:   l_c %d, l_p %d\n", cz_p->l_c, cz_p->l_p); 
// sprawdzenie warunku poprawności i ewentualny exit
  if( cz_p->l_p>1 || (cz_p->l_p==1 && cz_p->l_c>0) || cz_p->l_p<0 || cz_p->l_c<0 ) {
    printf("Blad: ....\n");
    printf("lp: %d; lcz: %d\n", cz_p->l_p, cz_p->l_c);
    exit(0);
  }

    usleep(rand()%3000000);
}


