#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000
//function to find the minimum of two numbers 
int b[100],y=0;	
int min(int a,int b)
	{
		if(a<b)
			return a;
		else
			return b;
	}
/*function to find two subsets such that the difference between the two sets is minimum using dynamic programming top-down approach*/
//a is the integer array
//n is the size of array a
//sumTotal is the total sum of all the elements
//c is the array to store the solutions to the subproblems
int findMinimum(int *a,int n,int sumTotal,int **c)
	{
		//printf("\nEntered findMinimum\n");
		//base condition
		if(sumTotal>=0 && n<0){
			return sumTotal;
		}
		if((sumTotal-(2*a[n-1]))<0){
				c[n][sumTotal]=sumTotal;
				return sumTotal;}
		/*if the value of the an element of array c is greater than -1 then return the solution of that subproblem*/
		if(c[n][sumTotal]!=-1) 
			return c[n][sumTotal];
	
		else
			{
/*printf("findMinimum(a,%d,%d,c): \t%d ,\t\tfindMinimum(a,%d,%d,c) :\t%d \n",n-1,sumTotal-(2*a[n]),findMinimum(a,n-1,sumTotal-(2*a[n]),c),n-1,sumTotal,findMinimum(a,n-1,sumTotal,c));*/
				//finding the subsets using the recursion	
				//findMinimum(a,n-1,sumTotal-(2*a[n]),c) : finds the total sum without the current element
				/*findMinimum(a,n-1,sumTotal,c) : finds the total sum with the current element and ultimately stores the difference*/
				c[n][sumTotal]= min(findMinimum(a,n-1,sumTotal-(2*a[n-1]),c),findMinimum(a,n-1,sumTotal,c));
			}
		return c[n][sumTotal];	
	}
//function to find the two subsets individually
void backtrackPath(int *a,int n,int sumTotal,int **c,int p)
	{
		printf("Entered backtrack path\n");
		int i=0,k=n,j=0;
				while(sumTotal!=p && sumTotal>=0)
					{	
						for(i=k;i>=0;i--)
							{
								if(c[i+1][sumTotal]==c[i][sumTotal-(2*a[i])])
									{
										b[y]=a[i];
										k=i-1;
										y++;
										break;
									}
								
							}
						sumTotal=sumTotal-(2*a[i]);
					}
	}
//auxiliary function to make function calls
int findMinimumOfTWoSubsets(int *a,int n)
	{
		int i,j,sumTotal=0;
		int **c;
		//finding total sum of all the elements
		for(i=0;i<n;i++)
			sumTotal+=a[i];
		//c is array of subproblems
		c=(int **)malloc((n+1)*(sizeof(int *)));
		for(i=0;i<n+1;i++)
			c[i]=(int *)malloc((sumTotal+1)*(sizeof(int)));
		/*initializing each element in array c to be -1*/	
		for(i=0;i<n+1;i++)
			{
				for(j=0;j<sumTotal+1;j++)
					c[i][j]=-1;
			}
		//p gives the difference between two subsets
		int p=findMinimum(a,n,sumTotal,c);
		for(i=0;i<n+1;i++)
			{
				for(j=0;j<sumTotal+1;j++)
					{
						if(c[i][j]!=-1)
						printf("\"%d\"\t",c[i][j]);
						else
						printf("%d\t",c[i][j]);
					}
				printf("\n");
			}
		//helps to find the two subsets
		backtrackPath(a,n-1,sumTotal,c,p);
		for(i=0;i<y;i++)
			printf("%d\n",b[i]);
		return p;
	}
int main()
	{
		int n;
		printf("Enter the value of n\n");
		scanf("%d",&n);
		int *a;
		a=(int *)malloc(n*sizeof(int));
		int i,j;
		for(i=0;i<n;i++)
			{
				printf("Enter the elements\n");
				scanf("%d",&a[i]);
			}
		//p will give the minimum between the two subsets
		int p=findMinimumOfTWoSubsets(a,n);
		printf("p: %d\n",p);
		return 0;
	}
