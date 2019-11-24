#include <stdio.h>
#include <stdlib.h>

#define N 50000000
 
void main()
{
   float *A, *B, X, Y;
   long i, j;
   int start, stop, mflops;
   
   A = malloc(sizeof(float)*N);
   B = malloc(sizeof(float)*N);
   
   for(i = 0; i< N; i++)
   {
     A[i] = i;
   }
    
   X = 1.23;
   Y = 2.34;
   
   start = millisecond(); 
   for(i = 0; i<N; i++)
   {
    B[i] = A[i]*X +Y;
   }
   stop = millisecond();
   printf("milli? %d\n", stop-start);
//   mflops = (2*N)/(((float)(stop-start)*1000));
//   printf("MFLOPS? %d\n",mflops); 
   
   free(A);
   free(B);
   
   exit(0);
}
  

