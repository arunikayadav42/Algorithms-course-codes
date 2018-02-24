#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int **matrixDivide(int n,int **A,int i,int j)
{
	int **R;
	int k,l;
	R=(int **)malloc(sizeof(int)*n);
	for(k=0;k<n;k++)
	{
		R[k]=(int *)malloc(sizeof(int)*n);
	}
	for(k=0;k<n;k++)
	{
		for(l=0;l<n;l++)
		R[k][l]=A[i+k][j+l];
	}
		for(k=0;k<n;k++)
	{
		for(l=0;l<n;l++)
		printf("\nR[k][l] : %d \n",R[k][l]);
	}
	return R;
}
int **matrixAdd(int n,int **A,int **B)
	{
		int i,j;
		int **C;
		int k;
		printf("\nEntered matrix add\nmatrix A : \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",A[i][j]);
			}
			printf("\n");
		}
		printf("Matrix B : \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",B[i][j]);
			}
			printf("\n");
		}
		
		C=(int **)malloc(sizeof(int)*n);
		for(k=0;k<n;k++)
			{
				C[k]=(int *)malloc(sizeof(int)*n);
			}
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				C[i][j]=A[i][j]+B[i][j];
			}
			}	
			printf("The addition matrix is \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",C[i][j]);
			}
		}
		
		return C;
	}
int **matrixsubtract(int n,int **A,int **B)
	{
		printf("Entered matrix subtract\n");
		int i,j;
		int k;
		int **C;
		C=(int **)malloc(sizeof(int)*n);
		for(k=0;k<n;k++)
			{
				C[k]=(int *)malloc(sizeof(int)*n);
			}
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				C[i][j]=A[i][j]-B[i][j];
			}
			}
			printf("The subtraction matrix is \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",C[i][j]);
			}
		}	
		return C;
	}
int **matrixMultiplyRecursively(int n,int **A,int **B)
	{
		printf("\nentered matrixMultiplyRecursively\n");
		int **C,i,j,p=n/2;
		printf("\nAllocating memory for atrix C\n");
		C=(int **)malloc(sizeof(int *)*n);
		for(i=0;i<n;i++)
		{
			C[i]=(int *)malloc(sizeof(int)*n);
		}
		printf("Matrix A at the start of matrixMultiplyRec is \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				printf("%d\t",A[i][j]);
			printf("\n");
		}
		printf("Matrix B at the start of matrixMultiplyRec is \n");
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				printf("%d\t",B[i][j]);
			printf("\n");
		}
		if(n==0)
			return;
		if(n==1)
		{
			C[0][0]=A[0][0]*B[0][0];
			return C;	
		}
		int **A11,**A12,**A21,**A22;
		int **B11,**B12,**B21,**B22;
		int **C11,**C12,**C21,**C22;
		int **M1,**M2,**M3,**M4,**M5,**M6,**M7;
		A11=(int **)malloc(sizeof(int *)*n);
		A12=(int **)malloc(sizeof(int *)*n);
		A21=(int **)malloc(sizeof(int *)*n);
		A22=(int **)malloc(sizeof(int *)*n);
		B11=(int **)malloc(sizeof(int *)*n);
		B12=(int **)malloc(sizeof(int *)*n);
		B21=(int **)malloc(sizeof(int *)*n);
		B22=(int **)malloc(sizeof(int *)*n);
		C11=(int **)malloc(sizeof(int *)*n);
		C12=(int **)malloc(sizeof(int *)*n);
		C21=(int **)malloc(sizeof(int *)*n);
		C22=(int **)malloc(sizeof(int *)*n);
		M1=(int **)malloc(sizeof(int *)*n);
		M2=(int **)malloc(sizeof(int *)*n);
		M3=(int **)malloc(sizeof(int *)*n);
		M4=(int **)malloc(sizeof(int *)*n);
		M5=(int **)malloc(sizeof(int *)*n);
		M6=(int **)malloc(sizeof(int *)*n);
		M7=(int **)malloc(sizeof(int *)*n);
			for(i=0;i<p;i++)
		{
			A11[i]=(int *)malloc(sizeof(int)*p);
			A12[i]=(int *)malloc(sizeof(int)*p);
			A21[i]=(int *)malloc(sizeof(int)*p);
			A22[i]=(int *)malloc(sizeof(int)*p);
			B11[i]=(int *)malloc(sizeof(int)*p);
			B12[i]=(int *)malloc(sizeof(int)*p);
			B21[i]=(int *)malloc(sizeof(int)*p);
			B22[i]=(int *)malloc(sizeof(int)*p);
			C11[i]=(int *)malloc(sizeof(int)*p);
			C12[i]=(int *)malloc(sizeof(int)*p);
			C21[i]=(int *)malloc(sizeof(int)*p);
			C22[i]=(int *)malloc(sizeof(int)*p);
			M1[i]=(int *)malloc(sizeof(int)*p);
			M2[i]=(int *)malloc(sizeof(int)*p);
			M3[i]=(int *)malloc(sizeof(int)*p);
			M4[i]=(int *)malloc(sizeof(int)*p);
			M5[i]=(int *)malloc(sizeof(int)*p);
			M6[i]=(int *)malloc(sizeof(int)*p);
			M7[i]=(int *)malloc(sizeof(int)*p);
		}
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				C[i][j]=0;
			}
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A11[i][j]=0;
			}
			
		}
		A11=matrixDivide(n/2,A,0,0);
		printf("\nA11 is formed\n");
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
				{
						printf("%d\t",A11[i][j]);
				}
			printf("\n");
		}
			for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A12[i][j]=0;
			}
			
		}
		printf("\n A12 is formed \n");
		A12=matrixDivide(n/2,A,0,n/2);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A21[i][j]=0;
			}
			
		}
		printf("\n A21 is formed \n");
		A21=matrixDivide(n/2,A,n/2,0);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A22[i][j]=0;
			}
			
		}
			printf("\n A22 is formed \n");
		A22=matrixDivide(n/2,A,n/2,n/2);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B11[i][j]=0;
			}
			
		}
		printf("\n B11 is formed \n");
		B11=matrixDivide(n/2,B,0,0);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B12[i][j]=0;
			}
			
		}
		printf("\n B12 is formed \n");
		B12=matrixDivide(n/2,B,0,n/2);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B21[i][j]=0;
			}
			
		}
		printf("\n B21 is formed \n");
		B21=matrixDivide(n/2,B,n/2,0);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				printf("%d\t",B21[i][j]);
			}
			printf("\n");
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B22[i][j]=0;
			}
			
		}
		
		B22=matrixDivide(n/2,B,n/2,n/2);
		printf("\n B22 is formed \n");
			for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				printf("%d\t",B22[i][j]);
			}
			printf("\n");
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C11[i][j]=0;
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M1[i][j]=0;
				printf("M1 : %d\n",M1[i][j]);
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M2[i][j]=0;
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M3[i][j]=0;
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M4[i][j]=0;
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M5[i][j]=0;
			}
			
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M6[i][j]=0;
			}
			
		}
		printf("M7 is formed\n");
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				M7[i][j]=0;
			}
		}
		M1=matrixMultiplyRecursively(n/2,(matrixAdd(n/2,A11,A22)),(matrixAdd(n/2,B11,B22)));
		M2=matrixMultiplyRecursively(n/2,((matrixAdd(n/2,A21,A22))),((B11)));
		M3=matrixMultiplyRecursively(n/2,(A11),((matrixsubtract(n/2,B12,B22))));
		M4=matrixMultiplyRecursively(n/2,(A22),((matrixsubtract(n/2,B21,B11))));
		M5=matrixMultiplyRecursively(n/2,((matrixAdd(n/2,A11,A12))),(B22));
		M6=matrixMultiplyRecursively(n/2,(matrixsubtract(n/2,A21,A11)),(matrixAdd(n/2,B11,B12)));
		M7=matrixMultiplyRecursively(n/2,(matrixsubtract(n/2,A12,A22)),(matrixAdd(n/2,B21,B22)));
		printf("Calculating C11\n");
		C11=matrixsubtract(n/2,matrixAdd(n/2,matrixAdd(n/2,M1,M4),M7),M5);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i][j]=C11[i][j];
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C12[i][j]=0;
			}
			
		}
		C12=matrixAdd(n/2,M3,M5);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i+n/2][j]=C12[i][j];
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C21[i][j]=0;
			}
			
		}
		C21=matrixAdd(n/2,M2,M4);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i][j+n/2]=C21[i][j];
		}
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C22[i][j]=0;
			}
			
		}
		C22=matrixsubtract(n/2,matrixAdd(n/2,matrixAdd(n/2,M1,M3),M6),M2);
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i+n/2][j+n/2]=C22[i][j];
		}
		return C;
	}
main()
        {
                int k;
                printf("Enter the value of power of 2\n");
                scanf("%d",&k);
                int i,j;
                int p=(int)(pow(2,k));
                 int **a,**b;
                a=(int **)malloc(sizeof(int *)*p);
                b=(int **)malloc(sizeof(int *)*p);
                for(i=0;i<p;i++)
                {
                	a[i]=(int *)malloc(sizeof(int)*p);
                	b[i]=(int *)malloc(sizeof(int)*p);
				}
				for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                        	a[i][j]=0;
                                        	b[i][j]=0;
                                    	}
                    	}
                for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                                printf("Enter the elements of the first matrix\n");
                                                scanf("%d",&a[i][j]);
                                        }
                        }
                for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                                printf("Enter the elements of the second matrix\n");
                                                scanf("%d",&b[i][j]);
                                        }
                        }
            int **c=matrixMultiplyRecursively(p,a,b);
			for(i=0;i<p;i++)
            {
            	for(j=0;j<p;j++)
            	{
            		printf("%d \t",c[i][j]);
				}
				printf("\n");
			}
        }

