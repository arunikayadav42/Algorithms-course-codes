#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000

int s1[100],k1;//to store the elements of subset 1
int s2[100],k2;//to store the elements of subset 2
//function to find the minimum of two numbers 
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
		if((sumTotal-(2*a[n]))<0)
				return sumTotal;
		/*if the value of the an element of array c is greater than -1 then return the solution of that subproblem*/
		if(c[n+1][sumTotal]!=-1) 
			return c[n+1][sumTotal];
	
		else
			{
/*printf("findMinimum(a,%d,%d,c): \t%d ,\t\tfindMinimum(a,%d,%d,c) :\t%d \n",n-1,sumTotal-(2*a[n]),findMinimum(a,n-1,sumTotal-(2*a[n]),c),n-1,sumTotal,findMinimum(a,n-1,sumTotal,c));*/
				//finding the subsets using the recursion	
				//findMinimum(a,n-1,sumTotal-(2*a[n]),c) : finds the total sum without the current element
				/*findMinimum(a,n-1,sumTotal,c) : finds the total sum with the current element and ultimately stores the difference*/
				c[n+1][sumTotal]= min(findMinimum(a,n-1,sumTotal-(2*a[n]),c),findMinimum(a,n-1,sumTotal,c));
			}
		return c[n+1][sumTotal];	
	}
//function to find the two subsets individually after backtracking
void backtrackPath(int *a,int n,int sumTotal,int **c)
	{
		if(n>=0)//if the index becomes less than 0 then that is invalid
		{
			if(findMinimum(a,n-1,sumTotal,c)==c[n+1][sumTotal])
				{
					s1[k1]=a[n];//storing elements of subset 1
					k1++;
					backtrackPath(a,n-1,sumTotal,c);
				}
			else if(findMinimum(a,n-1,sumTotal-(2*a[n]),c)==c[n+1][sumTotal])
				{
					s2[k2++]=a[n];//storing elements of subset 2
					backtrackPath(a,n-1,sumTotal-(2*a[n]),c);
				}
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
		int p=findMinimum(a,n-1,sumTotal,c);
		/*for(i=0;i<n+1;i++)
			{
				for(j=0;j<sumTotal+1;j++)
					{
						if(c[i][j]!=-1)
						printf("\"%d\"\t",c[i][j]);
						else
						printf("%d\t",c[i][j]);
					}
				printf("\n");
			}*/
		//helps to find the two subsets
		k2=0;
		k1=0; 	
		backtrackPath(a,n-1,sumTotal,c);
		printf("Set1 : ");//printing set 1
		for(i=0;i<k1;i++)
			printf("%d ",s1[i]);
		printf("\n");
		printf("Set2 : ");//printing set 2
		for(i=0;i<k2;i++)
			printf("%d ",s2[i]);
		return p;
	}
void main()
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
		printf("\n");
		//p will give the minimum difference between the two subsets
		int p=findMinimumOfTWoSubsets(a,n);
		printf("\n");
		printf("|set1 - set2| : %d\n",p);
		return ;
	}
