put homework answers here
# Problem 1
```c
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>

#define PHILNUMBER 5

//semaphors and mutex idea found from http://faculty.cs.niu.edu/~hutchins/csci480/semaphor.htm

sem_t s[5];
int state[PHILNUMBER]={0};	//0 = think, 1 = hungry, 2 = eating 

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
```
# Problem 2
---
This program is immune to deadlock because of the use of threads and locks. In order to make sure threads that are dependent on each other do not run at the same time, this program locks certain threads from executing until other threads have run. This way there can never be a situation where a philospher is in deadlock trying to eat and think at the same time. The same goes for all other threads; the program will locks certain threads and then unlocks them in a timely way in order to constantly generate actions for the philosophers with no stops.

# Problem 3
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>

//to run: 
//gcc file-processes.c     and then    ./a.out </etc/passwd
int main() {
  pid_t returnedValue = fork();
  if (returnedValue < 0) {
    perror("error forking");
    return -1;
  } else if (returnedValue == 0) {
    execlp("tr", "tr", "a-z", "A-Z", NULL);
    return -1;
  } else {
      if (waitpid(returnedValue, 0, 0) < 0) {
        perror("error waiting for child");
        return -1;
      };
    }
 }
```

#
 Problem 4
---
Refer to nmap.c - to test file, run command ```./a.out test.txt ```

# Problem 5
---
The bounded buffer class would be appropriate to use for the holding area. The TopicServer's recieve method will not return to its caller until after all of the subscribers have recieved the message. However, with the bounded buffer class acting as an immediate storage, we won't need to wait for all the messages.
