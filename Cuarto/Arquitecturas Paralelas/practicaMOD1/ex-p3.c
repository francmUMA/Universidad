#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define N 65536

double a[N] __attribute__((aligned(64)));
double b[N] __attribute__((aligned(64)));

double gettime(void)
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

void init(double *u1, double *u2)
{
  int i;

  for (i=0; i<N; i++) {
    u1[i] = (double) i;
    u2[i] = u1[i]*2 ;
  }
}

int main()
{
  int i,j;
  double dtime;

  // Initialise both arrays with values
  init(a, b);

  dtime = gettime();

#pragma omp parallel for schedule(static,8) private(j)
  for(i=0; i<N; i++) {
    for(j=0; j<i; j++) {
      a[i] = a[i] + b[j];
    }
  }

  dtime = gettime() - dtime;

  printf("Exec time: %9.5f sec.\n",dtime);
}
