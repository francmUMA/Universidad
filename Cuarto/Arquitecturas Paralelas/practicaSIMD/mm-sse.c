#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <smmintrin.h>

#define N 1024

double gettime(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + 1e-6*tv.tv_usec;
}

int main(int argc, char *argv[]) 
{
    // float a[N][N], b[N][N], c[N][N];
    float **a, **b, **c;
    int i,j,k;
    float sum = 0.0;
    double dtime;

    // Allocate matrices
    a = (float **) malloc (N*sizeof(float **));
    posix_memalign((void **)&a[0], 16, N*N*sizeof(float **));
    for (i=1; i<N; i++) a[i] = a[i-1] + N;
    b = (float **) malloc (N*sizeof(float **));
    posix_memalign((void **)&b[0], 16, N*N*sizeof(float **));
    for (i=1; i<N; i++) b[i] = b[i-1] + N;
    c = (float **) malloc (N*sizeof(float **));
    posix_memalign((void **)&c[0], 16, N*N*sizeof(float **));
    for (i=1; i<N; i++) c[i] = c[i-1] + N;

    // Initialize input matrices
    for (i = 0; i < N; i++)
       for (j = 0; j < N; j++)
       {
          a[i][j] = b[i][j] = 3.14;
          c[i][j] = 0.0;
       }

    // Matrix multiplication (Original)
    /*
    for (i = 0; i < N; i++) 
       for (k = 0; k < N; k++) 
          for (j = 0; j < N; j++) 
             c[i][j] = c[i][j] + a[i][k]*b[k][j];

    // Matrix multiplication (Desenrrollado)
    for (i = 0; i < N; i++) 
       for (k = 0; k < N; k++) 
          for (j = 0; j < N; j+=4) 
          {
             c[i][j]   = c[i][j]   + a[i][k]*b[k][j];
             c[i][j+1] = c[i][j+1] + a[i][k]*b[k][j+1];
             c[i][j+2] = c[i][j+2] + a[i][k]*b[k][j+2];
             c[i][j+3] = c[i][j+3] + a[i][k]*b[k][j+3];
	  }
    */

    // Matrix multiplication (SIMD)
    dtime = gettime();

    for (i = 0; i < N; i++) 
       for (k = 0; k < N; k++) 
          for (j = 0; j < N; j+=4) 
          {
             __m128 bv = _mm_load_ps(&b[k][j]);
             __m128 av = _mm_set1_ps(a[i][k]);
             __m128 cv = _mm_load_ps(&c[i][j]);
             __m128 tmp = _mm_add_ps(cv,_mm_mul_ps(av,bv));
             _mm_store_ps(&c[i][j],tmp);
             //c[i][j] = c[i][j] + a[i][k]*b[k][j];
	  }

    dtime = gettime() - dtime;

    for (i = 0; i < N; i++)
       for (j = 0; j < N; j++)
          sum += c[i][j];

    // Print results
    printf("Sum for matrix C: %12.4f\n",sum);
    printf("Exec time: %9.5f sec.\n",dtime); 
}
