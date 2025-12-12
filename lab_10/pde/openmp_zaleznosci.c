#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<math.h>

#define N 1000000
// kompilacja
// gcc -fopenmp openmp_zaleznosci.c -lm -o openmp_zaleznosci
//
// debug
// gcc -g -O0 -fopenmp openmp_zaleznosci.c -lm -o openmp_zaleznosci
//
int main(){

  int i;
  double* A = malloc((N+2)*sizeof(double));
  double* B = malloc((N+2)*sizeof(double));
  double suma;

  for(i=0;i<N+2;i++) A[i] = (double)i/N;
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;

  double t1 = omp_get_wtime();
  for(i=0; i<N; i++){
    // WAR A[i+2] l:26
    A[i] += A[i+2] + sin(B[i]);
  }
  t1 = omp_get_wtime() - t1;

  suma = 0.0;
  for(i=0;i<N+2;i++) suma+=A[i];
  // WAR suma l:31

  printf("suma %lf, czas obliczen %lf\n", suma, t1);



  for(i=0;i<N+2;i++) A[i] = (double)i/N;
  for(i=0;i<N+2;i++) B[i] = 1.0 - (double)i/N;

  double* A_tmp = malloc((N+2)*sizeof(double));
  for(i=0;i<N+2;i++) A_tmp[i] = A[i];


  t1 = omp_get_wtime();

  #pragma omp paraller for default(none)
  // wersja równoległa
  for(i=0; i<N; i++){
    // WAR A[i+2] l:26
    A[i] += A_tmp[i+2] + sin(B[i]);
  }

  t1 = omp_get_wtime() - t1;

  suma = 0.0;
  for(i=0;i<N+2;i++) suma+=A[i];
  printf("suma %lf, czas obliczen rownoleglych %lf\n", suma, t1);


}
