#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//function to divide the matrix into submatrix

int **matrixDivide(int n,int **A,int i,int j)
{
	
	int **R;//R to make the submatrix
	int k,l;
	R=(int **)malloc(sizeof(int *)*n);//allocating memory to R
	for(k=0;k<n;k++)
		{
			R[k]=(int *)malloc(sizeof(int)*n);
		}
	for(k=0;k<n;k++)
	{
		for(l=0;l<n;l++)
		{
			R[k][l]=0;//initializing the elements of R
		}
	}
	for(k=0;k<n;k++)
	{
		for(l=0;l<n;l++)
			R[k][l]=A[i+k][j+l];//forming the submatrix
	}
	return R;
}

//function to add two matrices
int **matrixAdd(int n,int **A,int **B)
	{
		int i,j;
		int **C;//matrix C to hold the sum elements of two matrices
		int k;
		C=(int **)malloc(sizeof(int *)*n);//allocating memory to C
		for(i=k=0;k<n;k++)
			{
				C[k]=(int *)malloc(sizeof(int)*n);
			}
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				C[i][j]=A[i][j]+B[i][j];//addition of elements of two matrices
			}
		}	
		return C;//returning the matrix
	}

//function to multiply two matrices recursively
int **matrixMultiplyRecursively(int n,int **A,int **B)
	{

		int **C,i,j,p=n/2;//matrix C to store the multiplication of two matrices
		C=(int **)malloc(sizeof(int *)*n);//allocating memory to C
		for(i=0;i<n;i++)
		{
			C[i]=(int *)malloc(sizeof(int)*n);
		}
		if(n==0)
		 return;
		 //base case
		if(n==1)//if n=1 then only one element present in the matrix
		{
			C[0][0]=A[0][0]*B[0][0];
			return C;
		}
		//declaring the sub matrices each for matrices A,B and C
		int **A11,**A12,**A21,**A22;
		int **B11,**B12,**B21,**B22;
		int **C11,**C12,**C21,**C22;
		//allocating memory to each
		A11=(int **)malloc(sizeof(int *)*p);
		A12=(int **)malloc(sizeof(int *)*p);
		A21=(int **)malloc(sizeof(int *)*p);
		A22=(int **)malloc(sizeof(int *)*p);
		B11=(int **)malloc(sizeof(int *)*p);
		B12=(int **)malloc(sizeof(int *)*p);
		B21=(int **)malloc(sizeof(int *)*p);
		B22=(int **)malloc(sizeof(int *)*p);
		C11=(int **)malloc(sizeof(int *)*p);
		C12=(int **)malloc(sizeof(int *)*p);
		C21=(int **)malloc(sizeof(int *)*p);
		C22=(int **)malloc(sizeof(int *)*p);
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
		}
		
		//initializing all the elements to zero
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				C[i][j]=0;
			}
		}
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A11[i][j]=0;
			}
			
		}
		//forming the submatrix
		A11=matrixDivide(n/2,A,0,0);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A12[i][j]=0;
			}
			
		}
		//forming the submatrix
		A12=matrixDivide(n/2,A,0,n/2);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A21[i][j]=0;
			}
			
		}
		//forming the submatrix
		A21=matrixDivide(n/2,A,n/2,0);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				A22[i][j]=0;
			}
			
		}
		//forming the submatrix
		A22=matrixDivide(n/2,A,n/2,n/2);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B11[i][j]=0;
			}
			
		}
		//forming the submatrix
		B11=matrixDivide(n/2,B,0,0);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B12[i][j]=0;
			}
			
		}
		//forming the submatrix
		B12=matrixDivide(n/2,B,0,n/2);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B21[i][j]=0;
			}
			
		}
		//forming the submatrix
		B21=matrixDivide(n/2,B,n/2,0);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				B22[i][j]=0;
			}
			
		}
		//forming the submatrix
		B22=matrixDivide(n/2,B,n/2,n/2);
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C11[i][j]=0;
			}
			
		}
		//forming the submatrix
		C11=matrixAdd(n/2,matrixMultiplyRecursively(n/2,A11,B11),matrixMultiplyRecursively(n/2,A12,B21));
		//Building the C matrix from the submatrix
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i][j]=C11[i][j];
		}
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C12[i][j]=0;
			}
			
		}
		//forming the submatrix
		C12=matrixAdd(n/2,matrixMultiplyRecursively(n/2,A11,B12),matrixMultiplyRecursively(n/2,A12,B22));
		//Building the C matrix from the submatrix
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i][j+n/2]=C12[i][j];
		}
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C21[i][j]=0;
			}
			
		}
		//forming the submatrix
		C21=matrixAdd(n/2,matrixMultiplyRecursively(n/2,A21,B11),matrixMultiplyRecursively(n/2,A22,B21));
		//Building the C matrix from the submatrix
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i+n/2][j]=C21[i][j];
		}
		//initializing all the elements to zero
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				C22[i][j]=0;
			}
			
		}
		//forming the submatrix
		C22=matrixAdd(n/2,matrixMultiplyRecursively(n/2,A21,B12),matrixMultiplyRecursively(n/2,A22,B22));
		//Building the C matrix from the submatrix
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			C[i+n/2][j+n/2]=C22[i][j];
		}
		return C;
	}
//main funtion
main()
        {
                int k;
                printf("Enter the value of power of 2\n");
                scanf("%d",&k);
                int i,j;
                int p=(int)(pow(2,k));//p contains the order of the matrix
                int **a,**b;
                //forming the matrices a and b
                a=(int **)malloc(sizeof(int *)*p);
                b=(int **)malloc(sizeof(int *)*p);
                for(i=0;i<p;i++)
                {
                	a[i]=(int *)malloc(sizeof(int)*p);
                	b[i]=(int *)malloc(sizeof(int)*p);
				}
				//intitializing the elements to zero
				for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                        	a[i][j]=0;
                                        	b[i][j]=0;
                                    	}
                    	}
                    	//accepting the elements of the first matrix
                for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                                printf("Enter the elements of the first matrix\n");
                                                scanf("%d",&a[i][j]);
                                        }
                        }
                        //accepting the elements of the second matrix
                for(i=0;i<p;i++)
                        {
                                for(j=0;j<p;j++)
                                        {
                                                printf("Enter the elements of the second matrix\n");
                                                scanf("%d",&b[i][j]);
                                        }
                        }
            int **c=matrixMultiplyRecursively(p,a,b);
            //printing the final matrix obtained after multiplication
            printf("The final matrix is \n");
            for(i=0;i<p;i++)
            {
            	for(j=0;j<p;j++)
            	{
            		printf("%d \t",c[i][j]);
				}
				printf("\n");
			}

        }

