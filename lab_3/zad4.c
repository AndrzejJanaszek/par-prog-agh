// orginał i kopia
#define _GNU_SOURCE
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>


void * thread_fun (void * arg_wsk)
{
    pthread_attr_t attr;
    size_t stacksize;
    // void* stackaddress;
    // 8MB / 4B = 2M
    int arr[2*1024*1024];
    // int arr[100];
    pthread_getattr_np(pthread_self(), &attr);

    pthread_attr_getstacksize(&attr, &stacksize);

    printf("Stacksize: %d\n", stacksize);

    int attachment;
    pthread_attr_getdetachstate(&attr, &attachment);

    if(attachment == PTHREAD_CREATE_JOINABLE){
        printf("Joined thread\n");
        
    }else{
        printf("detached thread\n");
    }

    return NULL;
}


int main()
{
    pthread_t t_ids, t_id2;
    pthread_attr_t attr, attr2;


    pthread_attr_init(&attr);
    size_t rozmiar = 16*1024*1024;
    pthread_attr_setstacksize(&attr, rozmiar);

    pthread_create(&t_ids, &attr, thread_fun, NULL);
    
    pthread_attr_destroy(&attr);
    
    pthread_join(t_ids, NULL);



    pthread_attr_init(&attr2);
    // size_t rozmiar = 16*1024*1024;
    pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_DETACHED);

    pthread_create(&t_id2, &attr2, thread_fun, NULL);
    
    // pthread_join(t_id2, NULL);

    sleep(1);

    return 0;
}

    