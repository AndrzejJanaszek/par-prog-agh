#include<stdio.h>
#include<math.h>
#include"pomiar_czasu.h"

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif


double funkcja ( double x );

double funkcja ( double x ){ return( sin(x) ); }

double calka_sekw(double a, double b, double dx);

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);


int main( int argc, char *argv[] ){

  int i; 

  double t1,t2,t3;

  double a, b, dx, calka;

  printf("\nProgram obliczania całki z funkcji (sinus) metodą trapezów.\n");

  a = 0.0;
  //printf("\nPodaj lewy kraniec przedziału całkowania: "); scanf("%lf", &a);

  b = M_PI;
  //printf("\nPodaj prawy kraniec przedziału całkowania: "); scanf("%lf", &b);

  printf("\nPodaj wysokość pojedynczego trapezu:  "); scanf("%lf", &dx);

  int l_w=0;
  printf("\nPodaj liczbę wątków:  "); scanf("%d", &l_w);

  // ########################### 
  // ####### SEKWENCYJNE ####### 
  // ########################### 

  printf("\nPoczatek obliczeń sekwencyjnych\n");
  t1 = czas_zegara();

  calka = calka_sekw(a, b, dx);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen sekwencyjnych\n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

  // ########################### 
  // ####### RÓWNOLEGŁE ####### 
  // ########################### 

  printf("\nPoczatek obliczeń równoległych (zrównoleglenie pętli)\n");
  t1 = czas_zegara();

  calka = calka_zrownoleglenie_petli(a, b, dx, l_w);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  równoległych (zrównoleglenie pętli) \n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

  // ############################
  // ####### DEKOM OBSZAR ####### 
  // ############################ 

  printf("\nPoczatek obliczeń równoległych (dekompozycja obszaru)\n");
  t1 = czas_zegara();

  calka = calka_dekompozycja_obszaru(a, b, dx, l_w);

  t1 = czas_zegara() - t1;
  printf("\nKoniec obliczen  równoległych (dekompozycja obszaru) \n");
  printf("\tCzas wykonania %lf. \tObliczona całka = %.15lf\n", t1, calka);

}