#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

// chce czytac
int my_read_lock_lock(cz_t* cz_p){
  pthread_rwlock_rdlock(&cz_p->rw_lock);

  pthread_mutex_lock(&cz_p->mutex_cz);
  cz_p->l_c++;
  pthread_mutex_unlock(&cz_p->mutex_cz);
  
}

// koniec czytania
int my_read_lock_unlock(cz_t* cz_p){
  pthread_mutex_lock(&cz_p->mutex_cz);
  cz_p->l_c--;
  pthread_mutex_unlock(&cz_p->mutex_cz);

  pthread_rwlock_unlock(&cz_p->rw_lock);
}

// chce pisac
int my_write_lock_lock(cz_t* cz_p){
  pthread_rwlock_wrlock(&cz_p->rw_lock);
  
  pthread_mutex_lock(&cz_p->mutex_p);
  cz_p->l_p++;
  pthread_mutex_unlock(&cz_p->mutex_p);
}

// koniec pisania
int my_write_lock_unlock(cz_t* cz_p){
  pthread_rwlock_unlock(&cz_p->rw_lock);
  pthread_mutex_lock(&cz_p->mutex_p);
  cz_p->l_p--;
  pthread_mutex_unlock(&cz_p->mutex_p);
}

void inicjuj(cz_t* cz_p){

  cz_p->l_p = 0;
  cz_p->l_c = 0;  

  cz_p->waiting_czytelnicy = 0;
  cz_p->waiting_pisarze = 0;

  pthread_mutex_init(&cz_p->mutex, NULL);
  pthread_mutex_init(&cz_p->mutex_p, NULL);
  pthread_mutex_init(&cz_p->mutex_cz, NULL);
  pthread_cond_init(&cz_p->pisarze_cond, NULL);
  pthread_cond_init(&cz_p->czytelnicy_cond, NULL);

  pthread_rwlock_init(&cz_p->rw_lock, NULL);

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


