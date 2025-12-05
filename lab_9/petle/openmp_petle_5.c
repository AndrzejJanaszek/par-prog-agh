#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10

int main ()
{
  double a[WYMIAR][WYMIAR];

  for(int i=0;i<WYMIAR;i++) for(int j=0;j<WYMIAR;j++) a[i][j]=1.02*i+1.01*j;

  // podwójna pętla - sekwencyjnie
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
    for(int j=0;j<WYMIAR;j++) {
      suma += a[i][j];
    }
  }
  
  printf("Suma wyrazów tablicy: %lf\n", suma);

  omp_set_nested(1);
  // double agregacyjna[WYMIAR*WYMIAR] = {0};
  // double agregacyjna[WYMIAR][WYMIAR] = {0};
  double* agregacyjna[WYMIAR];
  for(int i = 0; i < WYMIAR; i++){
    agregacyjna[i] = malloc(sizeof(double)*WYMIAR);
    for(int j = 0; j < WYMIAR; j++){
      agregacyjna[i][j] = 0;
    }
  }
  // podwójna pętla - docelowo równolegle
  double suma_parallel=0.0; int i,j;
  // wierszowa
  #pragma omp parallel for num_threads(3) default(none) shared(a) shared(agregacyjna) schedule(static, 2) private(j) ordered
  for(j=0;j<WYMIAR;j++) {
    int id_w = omp_get_thread_num();
    // #pragma omp ordered
    #pragma omp parallel for num_threads(4) default(none) shared(a) shared(agregacyjna) schedule(static, 2) firstprivate(j) firstprivate(id_w) ordered
    for(i=0;i<WYMIAR;i++) {
      // suma_parallel += a[i][j];
      agregacyjna[i][j] += a[i][j];
      // agregacyjna[i*WYMIAR + j] += a[i][j];
      // dla dekompozycji 1D
      // printf("(%1d,%1d)-W_%1d ",i,j,omp_get_thread_num()); 
      // dla dekompozycji 2D
      #pragma omp ordered
      printf("(%1d,%1d)-W(%1d,%1d) ",i,j,id_w,omp_get_thread_num()); 
    }
    // #pragma omp ordered
    printf("\n");
  }
  suma_parallel = 0;
  for(int i = 0; i < WYMIAR; i++){
    for(int j = 0; j < WYMIAR; j++){
    suma_parallel += agregacyjna[i][j];
    // suma_parallel += agregacyjna[i*WYMIAR + j];
    }
  }

  printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}
