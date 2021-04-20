#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>

#define PHILNUMBER 5

//semaphors and mutex idea found from http://faculty.cs.niu.edu/~hutchins/csci480/semaphor.htm

sem_t s[5];
int state[PHILNUMBER]={0}; //0 = think, 1 = hungry, 2 = eating

pthread_mutex_t mutex;

void *philosopher(void* nPhilosopher);
void eating();
void thinking();
void pick_up_forks(int);
void put_down_forks(int);
void check(int);

void *philosopher(void* nPhilosopher)
{
    int i, j=0;
    while(j<5)
        {
            i=(int)nPhilosopher;
            printf("\nPhilosopher %d is Thinking!!\n", i);
            thinking();
            printf("\nPhilosopher %d is Hungry!!\n", i);
            pick_up_forks(i);
            printf("\nPhilosopher %d is Eating!!\n", i);
            eating();
            printf("\nPhilosopher %d has Finished Eating and has Put down the fork!!\n", i);
            put_down_forks(i);
            j++;
        }
}

void eating()
{
    sleep(3);
}

void thinking()
{
    sleep(3);
}

void pick_up_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i]=1;
    check(i);
    pthread_mutex_unlock(&mutex);
    sem_wait(&s[i]);
}

void put_down_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i]=0;
    printf("Fork %d and %d are dropped!!\n",(i+(PHILNUMBER-1))%PHILNUMBER, i);
    check((i+(PHILNUMBER-1))%PHILNUMBER);
    check((i+1)%PHILNUMBER);
    pthread_mutex_unlock(&mutex);
}

void check(int i)
{
    if(state[i]==1 && state[(i+(PHILNUMBER-1))%PHILNUMBER]!=2 && state[(i+1)%PHILNUMBER]!= 2)
    {
        state[i]=2;
        printf("\nPhilosopher %d has picked up forks: %d and %d!!\n",i, (i+(PHILNUMBER-1))%PHILNUMBER, i);
        sem_post(&s[i]);
    }
}

int main()
{
    int i;
    pthread_t thread_Id[PHILNUMBER];
    for(i=0; i<PHILNUMBER; i++)
        sem_init(&s[i], 0, 0);
    for(i=0; i<PHILNUMBER ; i++)
        pthread_create(&thread_Id[i], NULL, philosopher, (void*)i);
    for(i=0; i<PHILNUMBER; i++)
        pthread_join(thread_Id[i], NULL);

    return 0;
}
