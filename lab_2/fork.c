#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include"../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna=0;

int main(){
  
  int pid, wynik, i;

  // inicjuj_czas();
    
  pid = fork(); 			
  
  if(pid==0){ 			
    
    zmienna_globalna++;

    // char arg1[] = "/bin/ls";
    // char arg2[] = ".";
    char str[40];
    sprintf(str, "%d", pid);

    char *const args[] = {"program", "Andrzej Janaszek", str, NULL};
    // char* arg[] = {"/bin/ls",".",NULL};
    // wynik=execv("/bin/ls",arg); 
    wynik=execv("./program", args); 
    if(wynik==-1)
      printf("Proces potomny nie wykonal programu\n");

    exit(0);
    
  } else {					
    wait(NULL);
  }
    

  // drukuj_czas();
  
}

  
