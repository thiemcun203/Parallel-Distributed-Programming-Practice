#include <omp.h>
#include <stdio.h>
// gcc -fopenmp -o runfile exercise1.c
// ./runfile
int main(){
omp_set_num_threads(20);
#pragma omp parallel

  {
  int threadnumber = omp_get_num_threads();
  int threadID = omp_get_thread_num();
  printf("Hello from thread %d, nthreads %d\n", threadID, threadnumber);
  }
}


