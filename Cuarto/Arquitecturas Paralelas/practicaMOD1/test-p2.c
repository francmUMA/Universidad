#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

#define NSTEPS 500
#define NX 1000000

double gettime(void)
{
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec + 1e-6*tv.tv_usec;
}

void init(double *u1, double *u2)
{
  int i;

  for (i=0; i<NX; i++) {
    u1[i] = 0;
    u2[i] = (double) i;
  }
}

int main()
{
  int ii,kk;
  double *uk = malloc(sizeof(double) * NX);
  double *ukp1 = malloc(sizeof(double) * NX);
  double *temp;
  double dx = 1.0/(double)NX;
  double dt = 0.5*dx*dx;
  double dtime;

  // Initialise both arrays with values
  init(uk, ukp1);

  dtime = gettime();

  #pragma omp parallel for schedule(static,8) private(ii)
  for(kk=0; kk<NSTEPS; kk++) {  
    for(ii=1; ii<NX-1; ii++) {
      ukp1[ii] = uk[ii] + (dt/(dx*dx))*(uk[ii+1]-2*uk[ii]+uk[ii-1]);
    }
    temp = ukp1;
    ukp1 = uk;
    uk = temp;
  }

  dtime = gettime() - dtime;

  printf("Exec time: %9.5f sec.\n",dtime);
}
