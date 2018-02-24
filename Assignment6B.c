#define INF 1000000000
#include <stdio.h>
#include <stdlib.h>
/*to calculate the minimum of two numbers*/
int min(int x,int y)
	{
		if(x>y)
			return y;
		else
			return x;
	}
/*function to calculate the minimum cost path using dynamic top down approach*/
int minimumRoomCost(int m,int n,int **a,int r,int c,int **p,int cost)
	{
		/*if m exceeds the number of rows then INF cost returned because it will not serve as a valid path*/
		if(m>r)
			return INF;
		/*if n exceeds the number of columns then INF cost returned because it will not serve as a valid path*/
		if(n>c)
			return INF;
		/*if the last cell is reached then we return the cost of previous calls plus the cost of the present cell (r,c)*/	
		if(m==r && n==c)
			return (cost+a[r][c]);
		/*returning the solution to an already solved sub problem*/
		if(p[m][n]!=INF)
			{	
				return p[m][n];
			}
		/*calculating the minimum cost via recursion*/
		else
			{
				int res=min(min(minimumRoomCost(m,n+1,a,r,c,p,cost),minimumRoomCost(m+1,n+1,a,r,c,p,cost)),minimumRoomCost(m+1,n,a,r,c,p,cost))+a[m][n];	
				p[m][n]=res;		
				return p[0][0];//returning the minimum cost of the subarray
			}
	}
/*function to backtrack the minimum cost path in the matrix*/
void backtrackPath(int m,int n,int **a,int r,int c,int **p,int cost)
	{
	/*if the subproblem matrix solution matches with any of the conditions mentioned in if ,else if and else if statements then that particular cell is a part of the minimum path,that element is printed and then the next call is made*/
	if((minimumRoomCost(m,n+1,a,r,c,p,cost)+a[m][n])==p[m][n])
		{
			printf("%d->",a[m][n+1]);
			backtrackPath(m,n+1,a,r,c,p,cost);
		}
	else if((minimumRoomCost(m+1,n+1,a,r,c,p,cost)+a[m][n])==p[m][n])
		{
			printf("%d->",a[m+1][n+1]);
			backtrackPath(m+1,n+1,a,r,c,p,cost);
		}
	else if((minimumRoomCost(m+1,n,a,r,c,p,cost)+a[m][n])==p[m][n])
		{
			printf("%d->",a[m+1][n]);
			backtrackPath(m+1,n,a,r,c,p,cost);
		}	
}
void main()
	{
		int m,n;
		printf("Enter value of m and n\n");
		scanf("%d %d",&m,&n);
		int i,j,c,d;
		int **a,**p;
		a=(int **)malloc(m*sizeof(int *));
		p=(int **)malloc(m*sizeof(int *));
		//a array :array of costs
		for(i=0;i<m;i++)
			a[i]=(int *)malloc(n*sizeof(int));
		//p array of solutions of subproblems
		for(i=0;i<m;i++)
			p[i]=(int *)malloc(n*sizeof(int)*n);
		printf("Enter the coordinates you want to reach\n");
		scanf("%d %d",&c,&d);
		printf("Enter the cost \n");
		for(i=0;i<m;i++)
			{
				
				for(j=0;j<n;j++)
					scanf("%d",&a[i][j]);
			}
		printf("The matrix \n");
		for(i=0;i<m;i++)
			{
				
				for(j=0;j<n;j++)
					printf("%d\t",a[i][j]);
				printf("\n");
			}
		printf("\n");
		/*making each element of array p to be INF to help it store the minimum cost*/
		for(i=0;i<m;i++)
			{
				for(j=0;j<n;j++)
					p[i][j]=INF;
			}
		int cost=0;
		int q=minimumRoomCost(0,0,a,c-1,d-1,p,cost);
		printf("Minimum cost = %d\n\n",q);
		printf("Path : \n");
		printf("%d->",a[0][0]);
		backtrackPath(0,0,a,c-1,d-1,p,cost);
		printf("end\n");
	}
