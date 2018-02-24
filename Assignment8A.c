#include <stdio.h>
#include <stdlib.h>

void main()
	{
		int **a;
		printf("Enter the value of n(number of players) \n");
		int n,i,j;
		scanf("%d",&(n));
		a=(int **)malloc((n+1)*sizeof(int *));//initializing memory to the adjacency matrix
		
		for(i=1;i<n+1;i++)
			{
				a[i]=(int *)malloc((n+1)*sizeof(int));
			}
		
		for(i=1;i<(n+1);i++)
			{
				for(j=0;j<(n+1);j++)
					{
						a[i][j]=0;//inintializing the adjacency matrix
					}
			}

		int p=1;

		while(p)
			{
				printf("Enter the pair which has a rivalry\n");
				scanf("%d %d",&i,&j);
				a[i][j]=1;
				a[j][i]=1;
				printf("Want to enter more pairs?\n");
				scanf("%d",&p);
			}
			//b[] and c[] store two different sets of vertices with no mutual rivalry
		int *b=(int *)malloc((n+1)*(sizeof(int)));
		int *c=(int *)malloc((n+1)*(sizeof(int)));
		/*for(i=1;i<n+1;i++)
			{
				for(j=1;j<n+1;j++)
					printf("%d\t",a[i][j]);
				printf("\n");
			}*/
		//initializing b[] and c[]
		for(i=0;i<n+1;i++)
			{
				b[i]=0;
				c[i]=0;
			}
			//dividing the the vertices into different sets
		for(i=1;i<n+1;i++)
			{
				for(j=1;j<n+1;j++)
					{
						if(a[i][j]==1 && j>i)//considering only the upper half of the matrix
							{
								/*conditions to determine if the given vertex belongs to b[] or it belongs to c[]*/
								if(b[i]==0 && b[j]==0)
									{
					   					if(c[i]==1)
											b[j]=1;
										else if(c[j]==1)
											b[i]=1;
										else
											{
												b[i]=1;
												c[j]=1;
											}
											
									}
								else if(b[i]==0 && b[j]==1)
									{
										c[i]=1;
									}
								else if(b[i]==1 && b[j]==0)
									{
										c[j]=1;
									}
								else if(b[i]==1 && c[j]==0)
									c[j]=1;
							}
					}
			}
			//printing b[]
		for(i=1;i<n+1;i++)
			if(b[i]==1)
				printf("%d ,",i);
		printf("\n");
		//printing c[]
		for(i=1;i<n+1;i++)
			if(c[i]==1)
				printf("%d ,",i);
		//if a vertex is not connected to any vertices then it can be present in both
		for(i=1;i<n+1;i++)
			if(c[i]==0 && b[i]==0)
				printf("%d ,",i);
	return;
		
	}











