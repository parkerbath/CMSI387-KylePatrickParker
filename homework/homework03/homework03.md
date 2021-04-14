put homework answers here

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



# Problem 5
---
The bounded buffer class would be appropriate to use for the holding area. The TopicServer's recieve method will not return to its caller until after all of the subscribers have recieved the message. However, with the bounded buffer class acting as an immediate storage, we won't need to wait for all the messages.
