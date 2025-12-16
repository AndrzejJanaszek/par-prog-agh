#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

#include <unistd.h>

int main( int argc, char** argv ){ 
  
  int rank, ranksent, size, source, dest, tag, i; 
  MPI_Status status;

  int kreatywna_nazwa = 0;

  // char hostname[256];
  
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  // gethostname(hostname, 256);

  int prev_p = 0;
  int next_p = 0;
  
  if(size>1){
    while(1){
      if(rank == 0 ){
        printf("poczatek\n");
        
        // pierwszy
        next_p = 1;
  
        kreatywna_nazwa++;
        printf("Proces rank: %d, prev_value: %d, value: %d\n", rank, kreatywna_nazwa-1, kreatywna_nazwa);
        
        MPI_Send( &kreatywna_nazwa, 1, MPI_INT, next_p, tag, MPI_COMM_WORLD );
  
        // -----
        MPI_Recv( &kreatywna_nazwa, 1, MPI_INT, size-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
  
      }
      else if(rank == size-1){
        // ostatni
        next_p = 0;
        prev_p = rank-1;
  
        MPI_Recv( &kreatywna_nazwa, 1, MPI_INT, prev_p, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
        
        kreatywna_nazwa++;
        printf("Proces rank: %d, prev_value: %d, value: %d\n", rank, kreatywna_nazwa-1, kreatywna_nazwa);
        
        printf("koniec\n");
        MPI_Send( &kreatywna_nazwa, 1, MPI_INT, 0, tag, MPI_COMM_WORLD );
      }
      else{

    }
      // pozostałe
      next_p = rank+1;
      prev_p = rank-1;
      
      MPI_Recv( &kreatywna_nazwa, 1, MPI_INT, prev_p, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
      
      kreatywna_nazwa++;
      printf("Proces rank: %d, prev_value: %d, value: %d\n", rank, kreatywna_nazwa-1, kreatywna_nazwa);

      MPI_Send( &kreatywna_nazwa, 1, MPI_INT, next_p, tag, MPI_COMM_WORLD );
    }

    
  }
  else{
	printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  
  MPI_Finalize(); 
  
  return(0);

}

