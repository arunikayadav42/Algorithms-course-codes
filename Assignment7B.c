#include <stdio.h>
#include <stdlib.h>
//to print the pair of elements in the final pair list
void backtrack(int *a,int *dp,int n)
{
	int sum=dp[n-1];
	int i;
	for(i=n-1;i>=1;i--)
	{
		if(dp[i]==sum && dp[i]!=dp[i-1])
		{
			printf("%d %d\n",a[i-1],a[i]);
			sum=sum-(a[i]+a[i-1]);
		}
	}
}
//to find the maximum sum and the dynamic programming array using bottom up approach
int maxSumDynamic(int *a,int n,int m)
{
	int i,j;
	int *dp;
	dp=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		dp[i]=0;
	dp[1]=a[0]+a[1];
	for(i=1;i<n-1;i++)//the nth element will not have an element after it to pair
	{
		if(a[i+1]-a[i]>m)/*if the difference between two consecutive numbers is greater than m then the sum remains the same*/
		{
			dp[i+1]=dp[i];
		}
		else if(a[i+1]-a[i]<=m)/*if the difference is less than m*/
		{
			if(a[i]-a[i-1]>m)/*if the difference here is greater than m then*/
			{
				dp[i+1]=dp[i]+a[i]+a[i+1];/*the sum at i+1 th position can include the current element and the i+1 th element*/
			}
			else if(a[i]-a[i-1]<=m)/*if the difference here is lesser than m*/
			{
				dp[i+1]=dp[i-1]+a[i]+a[i+1];/*then the sum at i+1 th position will inlcude the sum at i-1 th position and the i+1 th position*/
			}
		}
	}
	printf("Maximum Pair List : \n");
	backtrack(a,dp,n);
	return dp[n-1];
}
/*auxiliary function for quicksort*/
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
void main()
{
	int n,m;
	printf("Enter the number of elements\n");
	scanf("%d",&n);
	printf("Enter the value of m\n");
	scanf("%d",&m);
	int i,j;
	int *a;
	a=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		printf("Enter elements\n");
		scanf("%d",&a[i]);
	}
	//printf("array b made \n");
	/*sorting the array*/
	qsort(a, n, sizeof(int), cmpfunc);
	/*for(i=0;i<n;i++)
	{
		printf("%d \n",a[i]);
	}*/
	printf("Maximum Sum is : %d \n",maxSumDynamic(a,n,m));
	return;
}