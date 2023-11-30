#include <stdio.h>
#include <sys/time.h>

double gettime(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec + 1e-6*tv.tv_usec;
}

int main()
{
   static long num_steps = 100000000;
   double step;
   int i;
   double x, pi, sum=0.0;
   double dtime;

   step = 1.0/(double) num_steps;

   // pi calculation
   dtime = gettime();

   for (i=0; i<num_steps; i++)
   {
      x = (i-0.5)*step;
      sum = sum + 4.0/(1.0+x*x);
   }

   pi = step*sum;

   dtime = gettime() - dtime;

   printf("pi with %ld steps is %lf\n", num_steps, pi);
   printf("Exec time: %9.5f sec.\n",dtime);
}
