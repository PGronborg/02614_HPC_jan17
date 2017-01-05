#include "matoper.h"
#include <stdio.h>
#include <cblas.h>

void matadd_nat(int m,int k,double **A,double **B,double **C){
	int i,j;
	for (i = 0; i < m; i++){
		for (j = 0; j < k; j++){
			C[i][j] = A[i][j]+B[i][j];
		}
	}
}

void matsub_nat(int m,int k,double **A,double **B,double **C){
	int i,j;
	for (i = 0; i < m; i++){
		for (j = 0; j < k; j++){
			C[i][j] = A[i][j]-B[i][j];
		}
	}
}

double sum_mat(int m,int k,double **A){
	int i,j;
	double sum=0;
	for (i = 0; i < m; i++){
		for (j = 0; j < k; j++){
			sum += A[i][j];
		}
	}
	return(sum);
}

void matmul_nat(int m,int n,int k,double **A,double **B,double **C){
	int i,j,l;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			for (l = 0; l < k; l++)
				C[i][j] += A[i][l]*B[l][j];
				
}

void matmul_blk(int m,int n,int k,double **A,double **B,double **C,int blksize){
	int i0,j0,l0,i,j,l;
	for (i0=0; i0 < m; i0+=blksize)
		for (j0=0; j0 < n; j0+=blksize)
			for (l0=0; l0 < k; l0+=blksize)
				for (i = i0; (i < i0+blksize) & (i < m); i++)
					for (j = j0; (j < j0+blksize) & (j < n); j++)
						for (l = l0; (l < (l0+blksize)) & (l< k); l++)
							C[i][j] += A[i][l]*B[l][j];
							
}

void printMat(int m, int n, double **A){
	int i,j;
	
	for ( i = 0; i < m; i++){
		for (j = 0; j < n-1; j++){
			printf("%lf, ",A[i][j]);
		}
		printf("%lf \n",A[i][j]);
	}
}

void init_mat(int m, int k, double **A, double val){
	int i,j;
	for (i = 0; i < m; i++)
	for (j = 0; j < k; j++)
		A[i][j] = val;
		
}

void matmult_lib(int m, int n, int k, double **A, double **B, double **C){

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,m, n, k, 1.0, *A, k, *B, n, 0.0, *C, n);

}
