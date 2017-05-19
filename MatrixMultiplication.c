

// Sequential verison of Matric Multiplication program. Runs on a single thread 
// Prints to a text file. 

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "cur_time.h"

int main(void) {

  double matrixMultiply(int x, int N) {


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
    int i,j,k; //variables for matrix for loops

    
    // Memory Allocation 
    double **a, **b; // a and b are pointers 
    a = (double**)malloc(N*sizeof(*a));
    b = (double**)malloc(N*sizeof(*b));

    // Memory Allocation 
    for (i=0; i<N; i++) {
      a[i] = malloc(N*sizeof(*a[i]));
      b[i] = malloc(N*sizeof(*b[i]));
    }

    // Calcualate read_time 
    double start_read_time = cur_time();
     for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        fscanf(fp, "%lf", &a[i][j]);//read file element by element
      }
    }
    double read_time = 1.0 * cur_time() - start_read_time;
    printf("File read \n");
    printf("Time taken for reading file: %f\n",read_time);
    fclose(fp);
    

    // actual matrix Multiplication calculation
    double start_time = cur_time();
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++) {
        double sum = 0;
        for (k=0; k<N; k++) {
          sum += a[i][k] * a[k][j];
          }
        b[i][j] = sum;
        }
      }
      

    // free up memory space for re-allocation
    for (i=0; i<N; i++){
      free(a[i]);
      free(b[i]);
    }
    free(a);
    free(b);

    // calculates multiply time 
    double multiply_time = 1.0 * cur_time() - start_time;
    printf("Execution time in seconds: %f\n",multiply_time);//tell user what the execution time was
    

    // prints the results to a text file for data collection 
    FILE *times;
    times = fopen("sequentialtimes.txt","a");
    fprintf(times, "%d%s%f%s%f%s",N,"\t",read_time, "\t",multiply_time,"\n");
    fclose(times);//returns 0;
    
  }
  
  remove("sequentialtimes.txt");
  FILE *times;
  times = fopen("sequentialtimes.txt","w");
  fprintf(times,"N\tRead Time(seconds)\tMultiply Time(seconds)\n");
  fclose(times);
  
  int x, y; // helper variables for data collection
  for(x=2; x<=3; x++) {

    int N = (int)pow((double)10,(double)x); // n = 100, 1000, 10000
    printf("N = %d\n",N);     // prints N 

    for (y=1; y<=5; y++) {    // prints 5 trials 
      matrixMultiply(x,N);
    }
  }
  return 0;

}