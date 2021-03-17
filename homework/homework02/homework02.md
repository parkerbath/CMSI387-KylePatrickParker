# Problems for Assignment #2

1.  In the mutex-locking pseudocode of Figure 4.10 on page 111, there are two consecutive steps that remove the current thread from the runnable threads and then unlock the spinlock. Because spinlocks should be held as briefly as possible, we ought to consider whether these steps could be reversed, as shown in Figure 4.28 [on page 148]. Explain why reversing them would be a bad idea by giving an example sequence of events where the reversed version malfunctions.

#### Answer:

    The issue with reversing the steps is that it unlocks the spin lock before removing the current thread which can result in the thread running more than once.       
    This is dangerous because if the thread isn’t removed before unlocking the mutex, the thread will be caught in an infinite loop.


2.  Suppose the first three lines of the audit method in Figure 4.27 on page 144 were replaced by the following two lines:
    ![prob2](./Images/prob2.png)

    - Explain why this would be a bug: <br>
      - State snapshot = state.get() makes sure that getSeatsRemaining() and getCashonhand is referencing the same state. By removing snapshot, the bug will occur because when the state objects are called such as state.get().getSeatsRemaining() and state.get().getCashOnHand() may possibly be updated, which will then lead to different values returned from getSeatsRemaining() and getCashonHand().

3.  **IN JAVA:** Write a test program in Java for the BoundedBuffer class of Figure 4.17 on page 119 of the textbook. <br>

```
 Refer to BoundedBufferTest.java
```

4. **IN JAVA:** Modify the BoundedBuffer class of Figure 4.17 [page 119] to call notifyAll() only when inserting into an empty buffer or retrieving from a full buffer. Test that the program still works using your test program from the previous exercise. <br>

```
Refer to BoundedBuffer.java
```

5. Suppose T1 writes new values into x and y and T2 reads the values of both x and y. Is it possible for T2 to see the old value of x but the new value of y? Answer this question three times: once assuming the use of two-phase locking, once assuming the read committed isolation level is used and is implemented with short read locks, and once assuming snapshot isolation. In each case, justify your answer.<br>

#### Answer:

    A) In the first case it’s not possible because in two phase locking, there’s an expanding phase where locks are acquired however none are released. The 
    opposite occurs during a shrinking phase. T2 will only be able to read the values of T1 after T1 has written new ones and the lock’s been released.
    B) It is possible in the second case though where T2 is able to read older values as well as newer values (like x and y) because read committed leads the 
    write transactions to be exclusively locked whereas the read transactions use a shared lock which is received before each read and released right after.
    C) It is also possible in the snapshot isolation instance that a read action can read an older version rather than a newer one  because each time a new value 
    is involved, the write action stores that new value as an entity in a different location.

6. Assume a page size of 4 KB and the page mapping shown in Figure 6.10 on page 225. What are the virtual addresses of the first and last 4-byte words in page 6? What physical addresses do these translate into?<br>
   
#### Answer:
    The first 4 byte word would have a virtual address of 12,288, since page 6 maps to page frame 3 and 4096 multiplied by 3 is 12,288. This virtual address translates to the     physical address of 24,576 since that is 4096 multiplied by 6, which is the page number coresponding to page frame 3. The last 4 byte word would have a virtual address of     16,380. That is because we need to add 4092 to the original virtual address of 12,288 to get the last 4 byte word instead of 4096 because it is the end of the block so we     need to subtract 4. The corresponding physical address can be calculated the same way by adding 4092 to the original physical address to get 28,668.
   

7. At the lower right of Figure 6.13 on page 236 are page numbers 1047552 and 1047553. Explain how these page numbers were calculated.<br>
   `ANSWER HERE`

8. Write a program that loops many times, each time using an inner loop to access every 4096th element of a large array of bytes. Time how long your program takes per array access. Do this with varying array sizes. Are there any array sizes when the average time suddenly changes? Write a report in which you explain what you did, and the hardware and software system context in which you did it, carefully enough that someone could replicate your results.<br>

```c
    #include <stdio.h>
    #include <time.h>
    int main() {
     char bytes[20480];
     size_t sizeOfArray = sizeof(bytes);
     clock_t t; 
     t = clock();
     int j;
      for (size_t j = 0; j < 200; j++) {
        for(int i = 4095; i < sizeOfArray; i += 4096) {
          bytes[i];
       }
     }
     t = clock() - t; 
     double time = ((double)t)/CLOCKS_PER_SEC;
     printf("took %f seconds to execute loop \n", time);
     return 0; 
    }
```

#### Answer:

    In MacOS using VSCode, I created an array of chars representing the bytes and created a variable storing the size of the array. Then created an outer loop 
    that runs as many times as you want. Within that for loop is another for loop which starts at the 4096th byte of the array and continues to access each 
    successive 4096th byte. What I found out was that the time it took to access the array was pretty much instantaneous and change in array size made minuscule 
    to no change in time. This is all because array access is in constant time. 

9. Figure 7.20 [page 324] contains a simple C program that loops three times, each time calling the fork() system call. Afterward it sleeps for 30 seconds. Compile and run this program, and while it is in its 30-second sleep, use the ps command in a second terminal window to get a listing of processes. How many processes are shown running the program? Explain by drawing a family tree of the processes, with one box for each process and a line connecting each (except the first one) to its parent.<br>
   `ANSWER HERE`
