#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int **adj,**radj,**flow,**G,**cf;
char **name,**name1;
int *parent;
int front,rear;
//function to find the minimum of two numbers 
int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
//function to print matrix 
void printMatrix(int **m,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
				printf("%d\t",m[i][j]);
		}
		printf("\n");
	}
}
//function to check if the queue is empty or not
int isEmpty()
{
	if(front>rear)
		return 1;
	else
		return 0;
}
//function to run bfs on the given graph
int bfs(int n,int s,int t)
{
	int *queue=(int *)malloc((n)*sizeof(int));
	int *visited=(int *)malloc((n)*sizeof(int));
	int i;
	for(i=0;i<n;i++)
		visited[i]=0;
	queue[++rear]=s;
	visited[s]=1;
	parent[s]=-1;
	while(!isEmpty())
	{
		int p=queue[++front];
		for(i=0;i<n;i++)
		{
			if(visited[i]==0 && radj[p][i]>0)
			{
				queue[++rear]=i;
				parent[i]=p;
				visited[i]=1;
			}
		}
	}
	return (visited[t]==1);
}
//function to run the ford fulkerson algorithm
int fordFulkerson(int n)
{
	radj=(int **)malloc((n)*sizeof(int *));//matrix to store the residual graph 
	int i,j;
	for(i=0;i<n;i++)
	{
		radj[i]=(int *)malloc((n)*sizeof(int *));
		for(j=0;j<n;j++)
		{
			radj[i][j]=adj[i][j];//initially the residual graph is equal to the original graph
		}
	}
	parent=(int *)malloc((n)*sizeof(int));//array to store the parent of the vertices in the shortest path
	int max_flow=0;
	rear=front=-1;//setting the initial values of rear and front variables
	//finding the augmenting paths to find the maximum flow 
	while(bfs(n,0,n-1))
	{
		int pathflow=INF;
		rear=front=-1;
		//finding the minimum of the residual capacities in the given path
		for(i=n-1;i!=0;i=parent[i])
		{
			if(pathflow>radj[parent[i]][i])
				pathflow=radj[parent[i]][i];
		}
		//modifying the flows in the for the residual graph
		for(i=n-1;i!=0;i=parent[i])
		{
			radj[parent[i]][i]-=pathflow;
			radj[i][parent[i]]+=pathflow;
		}
		max_flow+=pathflow;//modifying the maximum flow
	}
	return max_flow;
}

void main()
{
	//accepting the number of cities
	printf("Enter the number of cities\n");
	int n;
	scanf("%d",&n);
	adj=(int **)malloc(n*sizeof(int *));
	G=(int **)malloc(n*sizeof(int *));
	cf=(int **)malloc(n*sizeof(int *));
	int i,j,k;
	for(i=0;i<n;i++)
		{
			adj[i]=(int *)malloc(n*sizeof(int));
			G[i]=(int *)malloc(n*sizeof(int));
			cf[i]=(int *)malloc(n*sizeof(int));
		}
		//accepting the names of the cities
	printf("Enter the names of the cities\n");
	name=(char **)malloc(n*sizeof(char *));
	name1=(char **)malloc(n*sizeof(char *));
	for(i=0;i<n;i++)
		{
			name[i]=(char *)malloc(n*sizeof(char));	
			name1[i]=(char *)malloc(n*sizeof(char));
			scanf("%s",name[i]);
			strcpy(name1[i],name[i]);
			for(j=0;j<strlen(name[i]);j++)
				{
					if(name[i][j]>=65 && name[i][j]<=90)
						name[i][j]=name[i][j]+32;
				}
		}
		//setting the source and the sink
	for(i=0;i<n;i++)
		{
			if(strcmp(name[i],"goa")==0)
				{
					char s1[100],s2[100];
					strcpy(s1,name1[i]);
					strcpy(name1[i],name1[0]);
					strcpy(name1[0],s1);
					strcpy(s2,name[i]);
					strcpy(name[i],name[0]);
					strcpy(name[0],s2);
				}
			if(strcmp(name[i],"thiruvananthapuram")==0)
				{
					char s1[100],s2[100];
					strcpy(s1,name1[i]);
					strcpy(name1[i],name1[n-1]);
					strcpy(name1[n-1],s1);
					strcpy(s2,name[i]);
					strcpy(name[i],name[n-1]);
					strcpy(name[n-1],s2);
				}
		}
		//building the adjacency matrix
	int *ch1=(int *)malloc(26*sizeof(int));
	int *ch2=(int *)malloc(26*sizeof(int));
	for(i=0;i<26;i++)
		{
			ch1[i]=0;
			ch2[i]=0;
		}
	for(i=1;i<n-1;i++)
		{
			for(j=0;j<strlen(name[i]);j++)
				{
					int q=(int)name[i][j];
					int p=(int)(q-97);
					//printf("p:(ch1)%d   ",p);
					ch1[p]++;
				}
			
			for(k=1;k<n-1;k++)
				{
					if(k!=i)
						{
							for(j=0;j<strlen(name[k]);j++)
						{
							int q=(int)name[k][j];
							int p=(int)(q-97);
							//printf("p:(ch2)%d     ",p);
							ch2[p]++;
						}
					/*for(j=0;j<26;j++)
						printf("%d ",ch1[j]);
					printf("\n");*/
					int count=0;
					/*for(j=0;j<26;j++)
						printf("%d ",ch2[j]);*/
					for(j=0;j<26;j++)
						{
							if(ch1[j]>0 && ch2[j]>0)
								{
									if(ch1[j]==ch2[j])
										count=count+ch1[j];
									else if(ch1[j]!=ch2[j])
										{
											int p=min(ch1[j],ch2[j]);
											count=count+p;
											ch2[j]=ch2[j]-p;
										}
								}
						}
					/*printf("between %s and %s is count : %d\n",name[i],name[k],count);*/
					if(strlen(name[k])-strlen(name[i])==1 && count>=1 && i!=k)
						{
							adj[i][k]=2*count;
							G[i][k]=k;
						}
					for(j=0;j<26;j++)
						ch2[j]=0;
						}
					if(i==k)
						adj[i][k]=0;
				}
			for(j=0;j<26;j++)
				ch1[j]=0;
		}
		//looking after the connections of the source and the sink
	for(i=1;i<n-1;i++)
		{
			int count1=0,count2=0;
			for(j=1;j<n-1;j++)
			{
				if(adj[j][i]==0)
					count1++;
				if(adj[i][j]==0)
					count2++;
			}
			if(count1==n-2)
				{
					adj[0][i]=20;
					G[0][i]=i;
				}
			if(count2==n-2)
				{
					G[i][n-1]=n-1;
					adj[i][n-1]=20;
				}
		}
	printMatrix(adj,n);
	int max_flow=fordFulkerson(n);
	printf("\n\n");
	printMatrix(radj,n);
	printf("\n\nmaximum flow : %d\n",max_flow);
	
	return;
}