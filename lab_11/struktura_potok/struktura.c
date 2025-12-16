#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

#include "mpi.h"

#include <unistd.h>

struct struktura
{
  int n_int;
  double n_double;
  char imie[8];
};


int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;

  char buff[1000]; 
  int position = 0;


  int kreatywna_nazwa = 0;

  // char hostname[256];
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  // gethostname(hostname, 256);
  struct struktura dane;
  strcpy(dane.imie, "Andrzej\0");

  dane.n_int = 0;
  dane.n_double = 0;

  MPI_Datatype typek_elegancki;

  int dlugosci_blokow[3] = {1,1,8};
  MPI_Datatype tab_typow[3] = { MPI_INT, MPI_DOUBLE, MPI_CHAR };

  MPI_Aint ofsety[3], base;

  MPI_Get_address( &dane.n_int, &ofsety[0] );
  MPI_Get_address( &dane.n_double, &ofsety[1] );
  MPI_Get_address( &dane.imie, &ofsety[2] );

  base = ofsety[0];

  for(int i = 0; i < 3; i++){
    ofsety[i] -= base;
  }

  MPI_Type_create_struct( 3, dlugosci_blokow, ofsety, tab_typow, &typek_elegancki);
  MPI_Type_commit(&typek_elegancki);


  int prev_p = 0;
  int next_p = 0;
  
  if(size>1){
    if(rank == 0 ){
      printf("poczatek\n");
      // pierwszy
      next_p = 1;

      printf("Proces rank: %d, nint: %d, ndouble: %lf, imie: %s\n", rank, dane.n_int, dane.n_double, dane.imie);
      
      position = 0;
      MPI_Pack(&dane.n_int, 1, MPI_INT, buff, 1000, &position, MPI_COMM_WORLD);
      MPI_Pack(&dane.n_double, 1, MPI_DOUBLE, buff, 1000, &position, MPI_COMM_WORLD);
      MPI_Pack(dane.imie, 8, MPI_CHAR, buff, 1000, &position, MPI_COMM_WORLD);

      MPI_Send( buff, position, MPI_PACKED, next_p, tag, MPI_COMM_WORLD); 

    }
    else if(rank == size-1){
      // ostatni
      next_p = 0;
      prev_p = rank-1;

      // MPI_Recv( buff, 1, MPI_INT, prev_p, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
      MPI_Recv( buff, 1000, MPI_PACKED, prev_p, MPI_ANY_TAG,MPI_COMM_WORLD, &status); 

      position = 0;
      MPI_Unpack(buff, 1000, &position, &dane.n_int, 1, MPI_INT, MPI_COMM_WORLD); 
      MPI_Unpack(buff, 1000, &position, &dane.n_double, 1, MPI_DOUBLE, MPI_COMM_WORLD); 
      MPI_Unpack(buff, 1000, &position, dane.imie, 1, MPI_CHAR, MPI_COMM_WORLD); 

      dane.n_int+=1;
      dane.n_double+=1.1;
      printf("Proces rank: %d, nint: %d, ndouble: %lf, imie: %s\n", rank, dane.n_int, dane.n_double, dane.imie);
      // printf("Proces rank: %d, nint: %d, ndouble: %lf, imie: %s\n", rank, dane.n_int, dane.n_double, dane.imie);
      
      printf("koniec\n");
    }
    else{
      // pozostałe
      next_p = rank+1;
      prev_p = rank-1;
      
      // MPI_Recv( &kreatywna_nazwa, 1, MPI_INT, prev_p, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
      MPI_Recv( buff, 1000, MPI_PACKED, prev_p, MPI_ANY_TAG,MPI_COMM_WORLD, &status); 

      position = 0;
      MPI_Unpack(buff, 1000, &position, &dane.n_int, 1, MPI_INT, MPI_COMM_WORLD); 
      MPI_Unpack(buff, 1000, &position, &dane.n_double, 1, MPI_DOUBLE, MPI_COMM_WORLD); 
      MPI_Unpack(buff, 1000, &position, dane.imie, 1, MPI_CHAR, MPI_COMM_WORLD); 
      
      printf("Proces rank: %d, nint: %d, ndouble: %lf, imie: %s\n", rank, dane.n_int, dane.n_double, dane.imie);
      dane.n_int+=1;
      dane.n_double+=1.1;

      printf("Proces rank: %d, nint: %d, ndouble: %lf, imie: %s\n", rank, dane.n_int, dane.n_double, dane.imie);

      position = 0;
      MPI_Pack(&dane.n_int, 1, MPI_INT, buff, 1000, &position, MPI_COMM_WORLD);
      MPI_Pack(&dane.n_double, 1, MPI_DOUBLE, buff, 1000, &position, MPI_COMM_WORLD);
      MPI_Pack(dane.imie, 8, MPI_CHAR, buff, 1000, &position, MPI_COMM_WORLD);

      MPI_Send( buff, position, MPI_PACKED, next_p, tag, MPI_COMM_WORLD);
      // MPI_Send( &kreatywna_nazwa, 1, MPI_INT, next_p, tag, MPI_COMM_WORLD );
      
    }
    
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

