// test program to readin a a matrix from an external file`

#define N 3

#include <stdio.h>

int main()
{
	FILE *fp = fopen("MatrixTest.txt", "r");

	int i = 0, j = 0;
	double a[N][N];		// a 3x3 matrix of doubles expected

	for (i=0; i<N; i++)
	 for (j=0; j<N; j++)
	 {
		fscanf(fp, "%lf", &a[i][j]);
	 }
	fclose(fp);

        for (i=0; i<N; i++)
	{
         for (j=0; j<N; j++)
         {      
                printf("%lf\t", a[i][j]);
         }
	 printf("\n");
	}

	return 0;
}
