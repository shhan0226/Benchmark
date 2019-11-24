#include <stdio.h>
#include <math.h>

#define ROW 3
#define COL 3
#define ERROR 1.0e-10

int CopyArray2D(double *source, double *target, int n);
int InverseMatrix(double *work, double *result, int n);
int PrT(double *T);

int main() {
   int i, j;

    double x1[ROW][COL] = {
        { 1, 1, 1},
        { 2, 3, 1},
        { 1, 3, 1},
    };

    double res[ROW][COL];

    
   printf("\nOriginal Matrix\n");
   for (i=0; i<ROW; i++) {
      for (j=0; j<COL; j++) {
         printf("%d%d : %f  ", i, j, x1[i][j]);
      }
      printf("\n");
   }

   InverseMatrix(&x1[0][0], &res[0][0], ROW);
   printf("\nInverse Matrix\n");
   PrT(&res[0][0]);
/*   for (i=0; i<ROW; i++) {
      for (j=0; j<COL; j++) {
         printf("%d%d : %f  ", i, j, res[i][j]);
      }
      printf("\n");
   }
*/

    return (0);
}

int PrT(double *T)
{
   int i, j;
   double tmp[ROW][COL];
   CopyArray2D(T, &tmp[0][0], (ROW*COL));
   for (i=0; i<ROW; i++) {
      for (j=0; j<COL; j++) {
         printf("%d%d : %f  ", i, j, tmp[i][j]);
      }
      printf("\n");
   }
   return 0;
}

/*******************************************
* FUNCTION NAME : PURPOSE
*   InverseMatrix() 함수 : 가우스-조던 소거법을 이용하여 역행렬 구하는 함수 
*
* DESCRIPTION OF PARAMETERS
*   double *work : 역행렬로 바꿀 행렬을 가리키는 포인터 
*   double *result : 역행렬로 변환된 값이 저장될 행렬을 가리키는 포인터 
*   int n : 행/열의 개수 
*
* REMARKS
*   double 형 데이터를 가지는
*   2차원 배열에서만 사용할 수 있음 
*
* SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED
*   CopyArray2D() 함수 : 2차원 배열을 복사하는 함수 
*******************************************/
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
         }
      }
   }

   return (0);
}

/*******************************************
* FUNCTION NAME : PURPOSE
*   CopyArray2D() 함수 : 2차원 배열을 복사하는 함수 
*
* DESCRIPTION OF PARAMETERS
*   double *source : 소스 행렬 (복사 원본) 
*   double *target : 결과 행렬 (복사 사본) 
*   int n : 데이터의 개수 (행 x 열) 
*
* REMARKS
*   double 형 데이터를 가지는
*   2차원 배열에서만 사용할 수 있음 
*   복사되는 곳의 크기를 검증하는 루틴 없음. 
*
* SUBROUTINES AND FUNCTION SUBPROGRAMS REQUIRED
*   NONE 
*******************************************/
int CopyArray2D(double *source, double *target, int n) {
   if (n < 1) return (-1);

   int i;
   for (i=0; i<n; i++)
       target[i] = source[i];

   return (0); 
}
