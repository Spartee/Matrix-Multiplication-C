
// Program for Parallel Matrix Multiplication. Uses OpenMp to access multple threads.
// Program loops through input size and processor count for data collection purposes. 
// Prints to a txt file. 


#include <math.h>
#include <omp.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "cur_time.h"



int main(void) {

  double matrixMultiply(int x, int N, int nthreads) {

    FILE *fp;
    
    if(x==2) {
      fp = fopen("Matrix2.txt","r");
    }
    else if(x==3) {
      fp = fopen("Matrix3.txt","r");
    }
    else {
      fp = fopen("Matrix4.txt","r");
      }

    int i,j,k;
    double sum;            // init helper variables for matrix calculation 
    double **a, **b;


    // Memory Allocation 
    a = (double**)malloc(N*sizeof(*a));
    b = (double**)malloc(N*sizeof(*b));

    // Memory Allocation 
    for (i=0; i<N; i++) {
      a[i] = malloc(N*sizeof(*a[i]));
      b[i] = malloc(N*sizeof(*b[i]));
    }    

    // read in the file 
    double read_start = cur_time(); // varaible linked to helper program 
    for (i=0; i<N; i++) {           // for time calculation 
      for (j=0; j<N; j++) {
        fscanf(fp, "%lf", &a[i][j]);
      }
    }

    // calculate read time and print to file 
    double read_time = 1.0 * cur_time() - read_start;
    printf("File read \n");
    printf("Time taken for reading file: %f\n",read_time);
    fclose(fp);
    
    
    // variable for calucation of time complexity
    double start_multiply_time = cur_time();

    // set omp variables
    omp_set_dynamic(0); //disable dynamic allocation
    omp_set_num_threads(nthreads); //use the specified number of threads

// omp parallel section starts    
#pragma omp parallel private(i,j,k,sum)
    {
#pragma omp for
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        sum = 0;
        for (k=0; k<N; k++) {
          sum += a[i][k] * a[k][j];
          }
        b[i][j] = sum;
      }
    }
    }

    // free up memory space for re-allocation. 
    for (i=0; i<N; i++){
      free(a[i]);
      free(b[i]);
    }
    free(a);
    free(b);

    //variable for complexity calculations. 
    double multiplication_complexity = 1.0 * cur_time() - start_multiply_time; 
    printf("Execution time (sec): %f\n",multiplication_complexity);
    FILE *times;
    times = fopen("paralleltimes.txt","a");
    fprintf(times, "%d%s%f%s%f%s",N,"\t", read_time, "\t",multiplication_complexity,"\n");
    fclose(times);//returns 0;
    
  }
  
  // remove old file
  remove("paralleltimes.txt");
  FILE *times;

  //open new file and print results. 
  times = fopen("paralleltimes.txt","w");
  fprintf(times,"N\tRead Time(seconds)\tMultiply Time(seconds)\n");
  fclose(times);
  
  
  int x, y, p; // helper variables for data collection 
  for(x=2; x<=3; x++) {
    int N = (int)pow((double)10,(double)x); // n = 100, 1000, 10000

    // loop through number of threads
    for (p=2; p<=4; p++) {

      // print five trials of results of the program. 
      for (y=1; y<=5; y++) {
        matrixMultiply(x,N, p);
      }
      printf("N = %d\n",N);                 // Print N 
      printf("num_threads = %d\n",p);          // print Number of threads. 
    } 
  }
  return 0;
}
