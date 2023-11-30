#include <stdio.h>
#include <omp.h>

int main()
{
   static long num_steps = 100000000;
   double step;
   int i;
   double x, pi, sum=0.0;
   double sump[64];
   double dtime;

   step = 1.0/(double) num_steps;

   // pi calculation
   dtime = omp_get_wtime();

   #pragma omp parallel 
   {
      int id = omp_get_thread_num();

      sump[id] = 0;

      #pragma omp for private(i,x)
      for (i=0; i<num_steps; i++)
      {
         x = (i-0.5)*step;
         sump[id] = sump[id] + 4.0/(1.0+x*x);
      }

      #pragma omp master
      for (i=0; i<omp_get_num_threads(); i++)
         sum += sump[i];
   }

   pi = step*sum;

   dtime = omp_get_wtime() - dtime;

   printf("pi with %ld steps is %lf\n", num_steps, pi);
   printf("Exec time: %9.5f sec.\n",dtime);
}
