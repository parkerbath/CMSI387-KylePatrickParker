
#include <stdio.h>
#include <stdlib.h>
#define MY_SYMBOLIC_CONSTANT 23
int main( int argc, char * argv[] ) {

   int myRA1[10];
   int myRA2[5];

   int i = 0;
   for( i = 0; i < 5; i++ ) {
      myRA2[i] = i + 1;
   }
   for( i = 0; i < 10; i++ ) {
      myRA1[i] = i * 2;
   }
   
   printf( "\n   Hello, world!\n\n" );
   exit( 0 );

}
