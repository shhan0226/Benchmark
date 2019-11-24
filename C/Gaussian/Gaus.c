#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define N 500
#define ERROR 1.0e-10

int CopyArray2D(double *source, double *target, int n);
int InverseMatrix(double *work, double *result, int n);
int PrT(double *T);

int main() {


   int i, j, start, stop;
   double x1[N][N];
   srand(time(NULL));
   for(i = 0; i<N; i++)
   {
	for(j =0; j<N; j++)
	{
	   x1[i][j] = rand()%10;
	}

   }


/*
    double x1[N][N] = {
        { 4, 1, 1},
        { 1, 1, 1},
        { 1, 1, 1}
    };
*/
    double res[N][N];

    
//   printf("\nOriginal Matrix\n");
//   PrT(&x1[0][0]);

   start = millisecond();
   InverseMatrix(&x1[0][0], &res[0][0], N);
   stop = millisecond();
   printf("milli? %d\n", stop-start);

//   printf("\nInverse Matrix\n");
//   PrT(&res[0][0]);

    return (0);
}

int PrT(double *T)
{
   int i, j;
   double tmp[N][N];
   CopyArray2D(T, &tmp[0][0], (N*N));
   for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
         printf("%d%d : %f  ", i, j, tmp[i][j]);
      }
      printf("\n");
   }
   return 0;
}

int InverseMatrix(double *work, double *result, int n) {
   int i, j, k;
   double constant;

   // 포인터 work 를 직접 조작하면,
    // 실제 원본 데이터값이 바뀌기 때문에 복사본을 만들어 작업한다. 
    // 복사본으로 작업하기 위한 임시 매트릭스 선언 
   double tmpWork[n][n];

   // 2차원 배열 복사
   CopyArray2D(work, &tmpWork[0][0], (n*n));
   
   // 계산 결과가 저장되는 result 행렬을 단위행렬로 초기화
   for (i=0; i<n; i++)
      for (j=0; j<n; j++)
         result[i*n+j] = (i == j) ? 1 : 0;

   /* 대각 요소를 0 이 아닌 수로 만듦 */
   for (i=0; i<n; i++)
      if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR) {
         for (k=0; k<n; k++) {
            if (-ERROR < tmpWork[k][i] && tmpWork[k][i] < ERROR) continue;
            for (j=0; j<n; j++) {
               tmpWork[i][j] += tmpWork[k][j];
               result[i*n+j] += result[k*n+j];
            }
            break;
         }
         if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR) return 0;
      }

	

   /* Gauss-Jordan elimination */
   for (i=0; i<n; i++) {
      // 대각 요소를 1로 만듦 
      constant = tmpWork[i][i];      // 대각 요소의 값 저장 
      for (j=0; j<n; j++) {
         tmpWork[i][j] /= constant;   // tmpWork[i][i] 를 1 로 만드는 작업 
         result[i*n+j] /= constant;   // i 행 전체를 tmpWork[i][i] 로 나눔
		 
//		printf("1 INIT\n(%d, %d)<%f \n",i,j,constant);
//		PrT(&tmpWork[0][0]);
      }

      // i 행을 제외한 k 행에서 tmpWork[k][i] 를 0 으로 만드는 단계 
      for (k=0; k<n; k++) {
         if (k == i) continue;      // 자기 자신의 행은 건너뜀 
         if (tmpWork[k][i] == 0) continue;   // 이미 0 이 되어 있으면 건너뜀 

         // tmpWork[k][i] 행을 0 으로 만듦 
         constant = tmpWork[k][i];
         for (j=0; j<n; j++) {
            tmpWork[k][j] = tmpWork[k][j] - tmpWork[i][j] * constant;
            result[k*n+j] = result[k*n+j] - result[i*n+j] * constant;
//		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n/(%d, %d)<%f calc !!!\n",k,j,constant);
//		PrT(&tmpWork[0][0]);
         }
      }
   }

   return (0);
}

int CopyArray2D(double *source, double *target, int n) {
   if (n < 1) return (-1);

   int i;
   for (i=0; i<n; i++)
       target[i] = source[i];

   return (0); 
}
