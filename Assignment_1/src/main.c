#include <stdio.h>
#include <stdlib.h>
#include "matoper.h"
#include "datatools.h"
#include <time.h>

#define NREPEAT 1		/* repeat count for the experiment loop */

#define mytimer clock
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)


void matrixMultiplication(int,int,int,int);
void matrixMultiplication_blk(int, int, int, int, int);

int
main(int argc, char *argv[]) {
	int runs = NREPEAT;
	int i;
	printf("Number of input arguments is: %i\n",argc);
	for (i = 0; i < argc; i++)
		printf("Arg %i is: %s\n",i,argv[i]);
	
	int m = 40, n = 1000, k = 5,blksize = 10;
	if (argc > 1)
		m = strtol(argv[1],NULL,10);
	if (argc > 2)
		n = strtol(argv[2],NULL,10);
	if (argc > 3)
		k = strtol(argv[3],NULL,10);
	if (argc > 4)
		blksize = strtol(argv[4],NULL,10);
	if (argc > 5)
		printf("Cannot handle more than 4 arguments\n");
		
	printf("Sizes (m,n,k) = (%i,%i,%i)\n",m,n,k);
	
	clock_t t1, t2;
	t1 = mytimer();
	matrixMultiplication(runs,m,n,k);
	t2 = mytimer();
	double tcpu = delta_t(t1,t2)/runs/1000;
	
	printf("\nTesting took %lf sec.\n",tcpu);
	
	t1 = mytimer();
	matrixMultiplication_blk(runs,m,n,k,blksize);
	t2 = mytimer();
	tcpu = delta_t(t1,t2)/runs/1000;
	printf("\nTesting took %lf sec. with matmul_blk\n",tcpu);
    return(0);
}

void matrixMultiplication(int runs, int m, int n, int k){
	int i;
	
	printf("Matrix multiplication");
	for (i = 0; i < runs; i++){
		double **A;
		double **B;
		double **C;
		
		/* Allocate memory */
		A = malloc_2d(m, k);
		B = malloc_2d(k, n);
		C = malloc_2d(m, n);
		if (A == NULL || B == NULL || C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}
		
		//init_mat(m,k,A,1.0);
		//init_mat(k,m,B,2.0);
		printf("Before giving initial values\n");
		int r,s;
		for (r = 0; r < m; r++)
			for (s = 0; s <k; s++)
				A[r][s] = 10.0*r+s;
		
		for (r = 0; r < k; r++)
			for (s = 0; s <n; s++)
				B[r][s] = 20.0*r+s;
			
		init_mat(m,n,C,0.0);
		/* *
		printMat(m,k,A);
		printf("\n\n");
		
		printMat(k,n,B);
		//printf("\n\n");*/
		printf("Before mat multiplication\n");
		matmult_nat(m,n,k,A,B,C);
		//printMat(m,n,C);
		//printf("Freeing memory\n");
		free_2d(A);
		free_2d(B);
		free_2d(C);
	}
}

void matrixMultiplication_blk(int runs, int m, int n, int k,int blksize){
	int i;
	
	printf("Matrix multiplication");
	for (i = 0; i < runs; i++){
		double **A;
		double **B;
		double **C;
		
		/* Allocate memory */
		A = malloc_2d(m, k);
		B = malloc_2d(k, n);
		C = malloc_2d(m, n);
		if (A == NULL || B == NULL || C == NULL) {
			fprintf(stderr, "Memory allocation error...\n");
			exit(EXIT_FAILURE);
		}
		
		//init_mat(m,k,A,1.0);
		//init_mat(k,m,B,2.0);
		printf("Before giving initial values\n");
		int r,s;
		for (r = 0; r < m; r++)
			for (s = 0; s <k; s++)
				A[r][s] = 10.0*r+s;
		
		for (r = 0; r < k; r++)
			for (s = 0; s <n; s++)
				B[r][s] = 20.0*r+s;
		/* *
		printMat(m,k,A);
		printf("\n\n");
		
		printMat(k,n,B);
		//printf("\n\n");*/
		printf("Before mat multiplication\n");
		init_mat(m,n,C,0.0);
		matmult_blk(m,n,k,A,B,C,blksize);
		//printMat(m,n,C);
		printf("Freeing memory\n");
		free_2d(A);
		free_2d(B);
		free_2d(C);
	}
}
