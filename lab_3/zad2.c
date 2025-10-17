#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

void * thread_fun (void * arg_wsk)
{
    sleep(1);
    int t_id = *( (int*)arg_wsk );
    printf("arg: %d\nphtead_self: %d\n", 
        (int)(t_id), 
        (int)(pthread_self())
    );

    sleep(1);
}

int main()
{
    const int thread_number = 10;
    pthread_t t_ids[thread_number];
    // pthread_t t_id;

    for(int i = 0; i < thread_number; i++){
        pthread_create(&t_ids[i], NULL, thread_fun, &i);
    }
    for(int i = 0; i < thread_number; i++){
        pthread_join(t_ids[i], NULL);
    }

}

    