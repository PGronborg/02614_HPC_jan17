
void matadd_nat(int m,int k,double **A,double **B,double **C);
void matsub_nat(int m,int k,double **A,double **B,double **C);
double sum_mat(int m,int k,double **A);
void matmul_nat(int m,int n,int k,double **A,double **B,double **C);
void matmul_blk(int m,int n,int k,double **A,double **B,double **C,int blksize);
void printMat(int m, int n, double **A);
void init_mat(int m, int k, double **A, double val);