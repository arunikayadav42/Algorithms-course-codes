#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

int **adj,**radj;
int *parent;
int front,rear;
//function to print matrix 
void printMatrix(int **adj,int n)
{
	int i,j;
	for(i=0;i<n+2;i++)
	{
		for(j=0;j<n+2;j++)
		{
				printf("%d\t",adj[i][j]);
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
	int *queue=(int *)malloc((n+2)*sizeof(int));
	int *visited=(int *)malloc((n+2)*sizeof(int));
	int i;
	for(i=0;i<n+2;i++)
		visited[i]=0;
	queue[++rear]=s;
	visited[s]=1;
	parent[s]=-1;
	while(!isEmpty())
	{
		int p=queue[++front];
		for(i=0;i<n+2;i++)
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
	radj=(int **)malloc((n+2)*sizeof(int *));//matrix to store the residual graph 
	int i,j;
	for(i=0;i<n+2;i++)
	{
		radj[i]=(int *)malloc((n+2)*sizeof(int *));
		for(j=0;j<n+2;j++)
		{
			radj[i][j]=adj[i][j];//initially the residual graph is equal to the original graph
		}
	}
	parent=(int *)malloc((n+2)*sizeof(int));//array to store the parent of the vertices in the shortest path
	int max_flow=0;
	rear=front=-1;//setting the initial values of rear and front variables
	//finding the augmenting paths to find the maximum flow 
	while(bfs(n,0,n+1))
	{
		int pathflow=INF;
		rear=front=-1;
		//finding the minimum of the residual capacities in the given path
		for(i=n+1;i!=0;i=parent[i])
		{
			if(pathflow>radj[parent[i]][i])
				pathflow=radj[parent[i]][i];
		}
		//modifying the flows in the for the residual graph
		for(i=n+1;i!=0;i=parent[i])
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
	int n;
	printf("Enter the number of vertices excluding the source and sink vertices\n");
	scanf("%d",&n);
	adj=(int **)malloc((n+2)*sizeof(int *));
	int i,j;
	//making the adjacency matrix
	for(i=0;i<n+2;i++)
	{
		adj[i]=(int *)malloc((n+2)*sizeof(int));
		for(j=0;j<n+2;j++)
			adj[i][j]=0;
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(i!=j && (j-i)<=3 && (j-i)>0)
			{
				adj[i][j]=i+j;
			} 
		}
	}
	for(i=1;i<=(n/4);i++)
	{
		adj[0][i]=i;
	}
	for(i=3*(n/4);i<=n;i++)
		adj[i][n+1]=i;
	printMatrix(adj,n);
	printf("\n\n");
	
	int max_flow=fordFulkerson(n);
	printMatrix(radj,n);
	printf("\n\nmaximum flow : %d\n",max_flow);
	
	return;
}