#define INF 1000000000
#include <stdio.h>
#include <stdlib.h>
/*auxiliary function for memoized top to down approach*/
//V:denomination array
//C:subproblem array
//s is the total sum 
//n is the total number of denominations
int findMinimumNumberOfCoinsMemoized(int *V,int n,int *C,int s)
	{
		//printf("Entered the auxiliary function\n");
		//subproblem returned if it was already calculated and is finite in value
		if(C[s]<INF)
			return C[s];
		else
			{
				int q=INF,i;//initializing q to INF(large value)  to help it store minimum
				for(i=0;i<n;i++)
					{
						if(V[i]<=s)//only executed if the denomination value is lesser than the current sum value
							{	
								int min=1+findMinimumNumberOfCoinsMemoized(V,n,C,s-V[i]);/*from the recursive definition,will find the minimum number of a particular denomination required*/
								if(min<q)//storing the minimum number of coins of a particular denomination required in q
									q=min;
							}	
					}
				C[s]=q;//storing the result of the subproblem in array C
			}
		return C[s];
	}
//backtracking function to find the number of denominations of a particular kind
void numberOfDenominations(int *V,int n,int s,int *C,int *p)
	{
		int i;
		for(i=0;i<n;i++)
			{
				if((1+findMinimumNumberOfCoinsMemoized(V,n,C,s-V[i]))==C[s])/*if the solution of a subproblem matches with that of the corresponding value in the subproblem array C then the correct denomination is encountered*/
					{
						p[V[i]]++;//p array to store the number of coins of a V[i]th denomination
						numberOfDenominations(V,n,s-V[i],C,p);
						break;
					}
			}
	}
//function to call the memoized top to down function
int findMinimumNumberOfCoins(int *V,int n,int s)
	{
		//printf("Entered the first recursive function\n");
		int *C;
		C=(int *)malloc((s+1)*sizeof(int));
		C[0]=0;
		int i;
		for(i=1;i<s+1;i++)
			C[i]=INF;
		int min=findMinimumNumberOfCoinsMemoized(V,n,C,s);
		int *p=(int *)malloc((V[n-1]+1)*sizeof(int));
		//number of elements in array p will be equal to 1+(value of the last denomination)
		for(i=0;i<V[n-1]+1;i++)
			p[i]=0;
		numberOfDenominations(V,n,s,C,p);
		//printing the number of coins of a particular denomination
		for(i=0;i<V[n-1]+1;i++)
			{
				if(p[i]!=0)
					{
						printf("Number of coins of denomination %d are %d\n",i,p[i]);
					}
			}
		return min;
	}
void main()
	{
		printf("Enter the number of coins\n");
		int n;
		scanf("%d",&n);
		int *v;
		v=(int *)malloc(sizeof(int)*n);
		int i;
		for(i=0;i<n;i++)
			{
				printf("Enter the unique denominations\n");
				scanf("%d",&v[i]);
			}
		printf("Enter the total sum s\n");
		int s;
		scanf("%d",&s);
		/*if the enetered sum is less than the smallest denomination then exit*/
		if(s<v[0])
			{
				printf("\nNot possible\n");
				return;
			}
		int p=findMinimumNumberOfCoins(v,n,s);
		/*if the function call returns INF then the sum cannot be expressed in terms of the given denomination*/
		if(p==INF)
			{
				printf("\nNot possible\n");
				return;
			}
		printf("\nThe minimum number of coins is %d \n",p);	
		return;
	}
