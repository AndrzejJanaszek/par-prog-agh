#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>


#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
    int zmienna_lokalna = *(int*)argument;
    
    for(int i = 0; i < 100000; i++){
        (zmienna_lokalna)++;
        zmienna_globalna++;
    }

    printf("WATEK: Wartość zmiennej lokalnej: %d\n", zmienna_lokalna);
    printf("WATEK: Wartość zmiennej globalnej: %d\n", zmienna_globalna);

  /* int wynik; */
  /* wynik=execv("./program",NULL); */
  /* if(wynik==-1) */
  /*   printf("Proces potomny nie wykonal programu\n"); */

  return 0;
}

int main()
{

  void * stos_1;
  void * stos_2;
  pid_t pid_1, pid_2;
  int arg_1 = 0, arg_2 = 0;
  
  stos_1 = malloc( ROZMIAR_STOSU );
  stos_2 = malloc( ROZMIAR_STOSU );
  if (stos_1 == 0 || stos_2 == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

//   inicjuj_czas();

    pid_1 = clone( &funkcja_watku, (void *) stos_1+ROZMIAR_STOSU, 
            CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM,  &arg_1);

    pid_2 = clone( &funkcja_watku, (void *) stos_2+ROZMIAR_STOSU, 
            CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, &arg_2 );

    waitpid(pid_1, NULL, __WCLONE);
    waitpid(pid_2, NULL, __WCLONE);

    printf("MAIN: Wartość zmiennej lokalnej 1: %d\n", arg_1);
    printf("MAIN: Wartość zmiennej lokalnej 2: %d\n", arg_2);
    printf("MAIN: Wartość zmiennej globalnej: %d\n", zmienna_globalna);


  free( stos_1 );
  free( stos_2 );
}

// wynik programu:
// WATEK: Wartość zmiennej lokalnej: 100000
// WATEK: Wartość zmiennej globalnej: 118667
// WATEK: Wartość zmiennej lokalnej: 100000
// WATEK: Wartość zmiennej globalnej: 126960
// MAIN: Wartość zmiennej lokalnej 1: 100000
// MAIN: Wartość zmiennej lokalnej 2: 100000
// MAIN: Wartość zmiennej globalnej: 126960

// lokalne wynosza tyle ile powinny
// a dla zmiennej globalnej występuje konflikt