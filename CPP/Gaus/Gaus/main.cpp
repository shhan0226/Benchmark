#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 500
#define ERROR 1.0e-10

int CopyArray2D(double *source, double *target);
int InverseMatrix(double *work, double *result);

int main() {

 

   int i, j;
   double x1[500][500];
   srand(time(NULL));
   for(i = 0; i<500; i++)
   {
	for(j =0; j<500; j++)
	{
	   x1[i][j] = rand()%10;
	}

   }

    double res[500][500];

    clock_t t_begin, t_end, t_elap;
    long    time_elapsed;
    printf( "start..\n" );
    t_begin =   clock();


   InverseMatrix(&x1[0][0], &res[0][0]);


    t_end   =   clock();
    printf( "end..\n" );
    t_elap  =  t_end - t_begin;


    time_elapsed    =   ( ( t_elap / CLOCKS_PER_SEC ) * 1000 ) +
                        ( ( t_elap % CLOCKS_PER_SEC ) * 1000 / CLOCKS_PER_SEC );
    printf( "%ld milliseconds elapsed\n", time_elapsed );


    return (0);
}


int InverseMatrix(double *work, double *result) {
   int i, j, k;
   double constant;
   double tmpWork[500][500];

   CopyArray2D(work, &tmpWork[0][0]);
   
   for (i=0; i<500; i++)
      for (j=0; j<500; j++)
         result[i*500+j] = (i == j) ? 1 : 0;

   for (i=0; i<500; i++)
      if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR) {
         for (k=0; k<500; k++) {
            if (-ERROR < tmpWork[k][i] && tmpWork[k][i] < ERROR) continue;
            for (j=0; j<500; j++) {
               tmpWork[i][j] += tmpWork[k][j];
               result[i*500+j] += result[k*500+j];
            }
            break;
         }
         if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR) return 0;
      }

	
   for (i=0; i<500; i++) {
      constant = tmpWork[i][i];   
      for (j=0; j<500; j++) {
         tmpWork[i][j] /= constant;   
         result[i*500+j] /= constant; 
		 
      }

      for (k=0; k<500; k++) {
         if (k == i) continue;      
         if (tmpWork[k][i] == 0) continue;  

         constant = tmpWork[k][i];
         for (j=0; j<500; j++) {
            tmpWork[k][j] = tmpWork[k][j] - tmpWork[i][j] * constant;
            result[k*500+j] = result[k*500+j] - result[i*500+j] * constant;
         }
      }
   }

   return (0);
}

int CopyArray2D(double *source, double *target) {
   if ((500*500) < 1) return (-1);

   int i;
   for (i=0; i<(500*500); i++)
       target[i] = source[i];

   return (0); 
}
