#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define N 16777216

double a[N], b[N], c[N];
double d = 4.0;

double gettime(void)
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

int main()
{
  int i, k;
  double dtime;

  // Initialise arrays with values
  for (i=0; i<N; i++)
  {
     a[i] = 0.0;
     b[i] = (double) i;
     c[i] = 2.0;
  }

  dtime = gettime();

  for(k=0; k<50; k++) 
     for(i=0; i<N; i++) 
     {
        a[i] = b[i] + d*c[i];
     }

  dtime = gettime() - dtime;

  printf("Exec time: %9.5f sec.\n",dtime);
}
