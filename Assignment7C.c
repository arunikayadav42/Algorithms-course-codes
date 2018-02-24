#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000
/*to find the minimum of two numbers*/
int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
/*to reduce the number to 1 using top-down manner*/
int reducenumbermemoizedaux(int n,int c[])
	{
		//printf("\nEntered dynamic\n");
		if(c[n]!=INF)/*if the subproblem already solved return the solution*/
			return c[n];
		if(n==1)
			return 0;//if number becomes 1 number of further steps required is 0	
					int a,b,cc,d,e;
							//calculating the number of steps for each type
							if(n%2==0)
								a=1+reducenumbermemoizedaux(n/2,c);
							else
								a=INF;
							if(n%3==0)
								b=1+reducenumbermemoizedaux(n/3,c);
							else
								b=INF;
							if(n%5==0)
								cc=1+reducenumbermemoizedaux(n/5,c);
							else 
								cc=INF;
							if(n%7==0)
								d=1+reducenumbermemoizedaux(n/7,c);
							else
								d=INF;
							if(n>1)
								e=1+reducenumbermemoizedaux(n-1,c);
							else
								e=INF;
				//printf("a:%d , b : %d, cc: %d,d: %d,e :%d\n",a,b,cc,d,e);					
				c[n]=min(a,min(b,min(cc,min(d,e))));/*finding the minimum number of steps*/
				//printf("c[%d] = %d\n",n,c[n]);
		return c[n];/*returning the number of steps*/
	}
	/*function to make the auxiliary array and print the minimum number of steps*/
void reducenumbermemoized(int n)
	{
		int *c=(int *)malloc((n+1)*sizeof(int));
		c[0]=0;
		c[1]=0;
		int i;
		for(i=1;i<n+1;i++)
			c[i]=INF;
		int p=reducenumbermemoizedaux(n,c);
		printf("minimum number of steps = %d",p);
	}
void main()
	{
		int n;
		printf("Enter n\n");
		scanf("%d",&n);
		reducenumbermemoized(n);
	}
