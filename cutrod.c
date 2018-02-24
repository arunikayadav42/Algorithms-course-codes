#define INF -1000000000
#include <stdio.h>
#include <stdlib.h>
int cutRodMemoizedAux(int *p,int n,int *r)
	{
		int q;
		if(r[n]!=INF)
			return r[n];
		
		else
			{
				int i;
				for(i=1;i<n+1;i++)
					{
						q=INF;
						int m=p[i]+cutRodMemoizedAux(p,n-i,r);
						if(q<m)
							q=m;
						
					}
				r[n]=q;
				return r[n];	
			}
		
	}
int cutRodMemoized(int *p,int n)
	{
		int *r;
		r=(int *)malloc((sizeof(int))*n);
		int i;
		r[0]=0;
		for(i=1;i<n;i++)
			r[i]=INF;
		return cutRodMemoizedAux(p,n-1,r);
	}
int cutRodBottomUp(int *p,int n)
	{
		int *r,*s;
		r=(int *)malloc((sizeof(int))*n);
		s=(int *)malloc((sizeof(int))*n);
		int i;
		r[0]=0;
		for(i=0;i<n;i++)
			{
				int q=INF,j;
				for(j=0;j<=i;j++)
					{
						if(q<(p[i]+r[i-j]))
							{
								q=p[i]+r[i-j];
								s[i]=j;
							}
					}
				r[i]=q;
			}
		for(i=0;i<n;i++)
			printf("%d\n",r[i]);
		return r[n-2];
	}
int main()
	{
		int tl;
		printf("Enter total length of the rod\n");
		scanf("%d",&tl);
		int *p;
		p=(int *)malloc((tl+1)*(sizeof(int)));
		printf("Enter the lengthwise price for cutting the rod\n");
		int i;
		for(i=0;i<tl+1;i++)
			{
				p[i]=0;
			}
		for(i=1;i<tl+1;i++)
			{
				printf("Enter the price\n");
				scanf("%d",&p[i]);
			}
		int q=cutRodMemoized(p,tl+1);
		printf("q top-down : %d\n",q);
		q=cutRodBottomUp(p,tl+1);
		printf("q bottom-up : %d\n",q);
		return 0;
	}
