#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"../pomiar_czasu/pomiar_czasu.h"
 
const int liczba = 10000000;
// const int liczba = 100000;

int main(){
  // double day_time_io_start, day_time_io_end, day_time_ar_start, day_time_ar_end= 0;
  double cpu_time_io_start, cpu_time_io_end, cpu_time_ar_start, cpu_time_ar_end= 0;

  double a, b, c;
  int i,j,k,l;

  
  k = -50000;
  // day_time_io_start = czas_zegara();
  cpu_time_io_start = czas_CPU();
  for(i=0;i<liczba;i++){
    
    printf("%d ",k+i);
    
  }
  // day_time_io_end = czas_zegara();
  cpu_time_io_end = czas_CPU();

  printf("\n");

  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",liczba);


  a = 1.000001;
  // day_time_ar_start = czas_zegara();
  cpu_time_ar_start = czas_CPU();
  for(i=0;i<liczba;i++){
    
    a = 1.000001*a+0.000001; 
    
  }
  // day_time_ar_end = czas_zegara();
  cpu_time_ar_end = czas_CPU();

  // double day_io_dif = day_time_ar_end - day_time_ar_start;
  double cpu_io_dif = cpu_time_io_end - cpu_time_io_start;
  double cpu_ar_dif = cpu_time_ar_end - cpu_time_ar_start;

  printf("IO nl AR\n");
  printf("%lf\n", cpu_io_dif);
  printf("%.15lf\n",cpu_ar_dif);

  // IO n AR
  // 0.015891
  // 0.001052

}