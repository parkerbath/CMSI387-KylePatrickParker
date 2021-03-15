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
