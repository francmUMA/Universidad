#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 5000
#define ERR 0.000001

double A[N+2][N+2];
double dif;

/* Inicializacion de la matriz de datos */
void init()
{
   int i,j;

   for (i=0; i<=N+1; i++)
      for (j=0; j<=N+1; j++)
         A[i][j] = (double) (i+j)*(i+j);
}

/* Metodo de resolucion de Gauss-Seidel */
void solve()
{
   int i,j,fin=0;
   double tmp;

   while (!fin)
   {
      dif = 0.0;
      #pragma omp parallel for private(tmp, j)
      for (i=1; i<=N; i+=2)
      {
         for (j=1; j<=N; j+=2)
         {
            tmp = A[i][j];
            A[i][j] = 0.2*(A[i][j]+A[i][j-1]+A[i-1][j]+A[i][j*1]+A[i+1][j]);
            dif += fabs(A[i][j]-tmp);
         }
      }
      
      #pragma omp parallel for private(tmp,j)
      for (i=2; i<=N; i+=2)
      {
         for (j=2; j<=N; j+=2)
         {
            tmp = A[i][j];
            A[i][j] = 0.2*(A[i][j]+A[i][j-1]+A[i-1][j]+A[i][j*1]+A[i+1][j]);
            dif += fabs(A[i][j]-tmp);
         }
      }
      if (dif < ERR) fin = 1;
   } 
}

int main()
{
   double stime, etime, sum=0.0;
   int i,j;
   
   init();

   stime = omp_get_wtime();
   solve();
   etime = omp_get_wtime();

   for (i=1; i<=N; i++)
      for (j=1; j<=N; j++)
         sum += A[i][j];

   printf("Calculo sum(A):%lf, Tiempo: %lf secs.\n", sum, etime-stime);
}
