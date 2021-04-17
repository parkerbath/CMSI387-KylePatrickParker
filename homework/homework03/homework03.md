put homework answers here
# Problem 1
```c

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
