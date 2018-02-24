#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INF 100000000.0
double **graph;//edge weight matrix

//function to print the matrix
void print(int n)
{
	int i,j;
	for(i=1;i<n+1;i++)
		{
			for(j=1;j<n+1;j++)
				printf(" %.3lf ",graph[i][j]);
			printf("\n\n");
		}
}
//function to print the shortest path
void printParent(int parent[],int v)
{
	//printf("%d printParent visited\n",v);
	if(parent[v]==-1)
		return;
	printParent(parent,parent[v]);
	printf("%d->",v);
}
//auxiliary function to help extract the next minimum from the graph
int minimumDistance(double d[],int spt[],int u,int n)
{
	int i,index;
	double min=INF;
	for(i=1;i<n+1;i++)
	{
		if(spt[i]==0 && d[i]<min)
		{
			min=d[i];
			index=i;
		}
	}
	return index;
}
//function to run the dijkstra algorithm
void dijkstra(int n,int u,int v)
{
	//printf("Entered dijkstra\n");
	double d[n+1];//stores the distance between two vertices
	int sptSet[n+1];//set storing the status of the vertices-included or not in the shortest path
	int parent[n+1];//array storing the parent of all the vertices
	int i,j;
	for(i=1;i<n+1;i++)
	{
		d[i] = INF;//initial distance set to zero
		sptSet[i] = 0;
		parent[i]=0;
	}
	//printf("array d and sptSet initialized\n");
	d[u] = 0.0;//initial distance of source vertex set to 0
	parent[u] = -1;//parent of source vertex is itself
	//running the dijkstra algorithm
	for(i=1;i<n;i++)
	{
		//printf("Entered first for loop\n");
		int u=minimumDistance(d,sptSet,u,n);
		//printf("u discovered\n");
		sptSet[u] = 1;
		for(j=1;j<n+1;j++)
		{
			if(!sptSet[j] && graph[u][j] && d[u]+graph[u][j]<d[j] && d[u]!=INF)
			{
				parent[j]=u;
				d[j]=d[u]+graph[u][j];
			}
		}
	}
	//printf("parent array\n");
	printf("\n\nMOST RELIABLE PATH:\n");
	printf("%d->",u);
	printParent(parent,v);
	printf("\n");
}

void main()
{
	printf("Enter these one by one(separated by spaces\n");
	printf("Enter the number of vertices\nEnter u(source vertex)\nEnter v(final vertex)\nEnter the number of edges\n");
	int n,u,v,e;	
	scanf("%d %d %d %d",&n,&u,&v,&e);
	int i,j;
	graph = (double **)malloc((n+1) * sizeof(double *));//2-D matrix to store the probablity of a particular path
	//printf("Enter the weight of edges of graph between 0 and 1\n"); 
	for(i=1;i<n+1;i++)
		{
			graph[i] = (double *)malloc((n+1) * (sizeof(double)));
		}
	printf("Enter the connected vertices for the directed graph and the weight of the edge-\nsample input:1 2 .55\n");
	//accepting the probabilities,with end points of the vertices
	for(i=1;i<=e;i++)
	{
		int a,b;
		double weight;
		scanf("%d %d %lf",&a,&b,&weight);
		graph[a][b]=weight;
	}
	printf("Original matrix\n");
	print(n);
	printf("Matrix of logarithm\n");
	//taking the logarithm in order to run dijkstra algorithm on the given edge weight matrix
	for(i=1;i<n+1;i++)
		{
			for(j=1;j<n+1;j++)
				{
					if(graph[i][j]!=0)
						{
							double p = -log(graph[i][j]);
							graph[i][j] = p;
						}
				}
		}
	print(n);
	dijkstra(n,u,v);
	return;
}