#include<stdio.h>
#include<pthread.h>
#include<math.h>

double funkcja ( double x );

double calka_sekw(double a, double b, double dx);

double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w);

void* calka_podobszar_w(void* arg_wsk);

struct podobszar
{
  double a;
  double b;
  double dx;
  double id;
  double wynik;
};


double calka_dekompozycja_obszaru(double a, double b, double dx, int l_w){


  //printf("a %lf, b %lf, dx %lf\n", a, b, dx);

  double calka_suma_local = 0.0;

  // tworzenie struktur danych do obsługi wielowątkowości
  struct podobszar arr[l_w];
  double dlugosc_podobszaru = (b-a)/l_w;

  for(int i = 0; i < l_w; i++){
    arr[i].a = dlugosc_podobszaru * i;
    arr[i].b = dlugosc_podobszaru * (i+1);
    arr[i].dx = dx;
  }

  pthread_t t_ids[l_w];

  //* tworzenie wątków
  for(int i = 0; i < l_w; i++){
    arr[i].id = i;
    pthread_create( &t_ids[i], NULL, calka_podobszar_w, (void *) &arr[i] );
  }


  //* oczekiwanie na zakończenie pracy wątków
  for(int i = 0; i < l_w; i++){
    pthread_join(t_ids[i], NULL);
  }

  for(int i = 0; i < l_w; i++){
    calka_suma_local += arr[i].wynik;
  }

  return(calka_suma_local);
}



void* calka_podobszar_w(void* arg_wsk){
  struct podobszar* obszar = (struct podobszar*)arg_wsk;
  double a_local, b_local, dx;
  a_local = obszar->a;
  b_local = obszar->b;
  dx = obszar->dx;
  // rozpakowanie danych przesłanych do wątku

  int my_id; // skąd pobierany?
  my_id = obszar->id;
  printf("\nWątek %d: a_local %lf, b_local %lf, dx %lf\n", 
	 my_id, a_local, b_local, dx);
  // wywołanie zadania do wykonania: całkowanie w zadanym przedziale 
  double calka = calka_sekw(a_local, b_local, dx);

  obszar->wynik = calka;
}

double calka_sekw(double a, double b, double dx){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);
  int i;
  double calka = 0.0;
  for(i=0; i<N; i++){

    double x1 = a + i*dx_adjust;
    calka += 0.5*dx_adjust*(funkcja(x1)+funkcja(x1+dx_adjust));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);

  }

  return(calka);
}