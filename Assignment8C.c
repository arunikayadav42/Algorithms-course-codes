#include <stdio.h>
#include <stdlib.h>

int **v;
int *vis;
int edges;
//function to find the maximum of a and b
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

//function to execute dfs on the adjacency matrix
void dfs(int vertex,int n)
{
	//the current vertex becomes visited hence store 1
	vis[vertex]=1;
	int i;
	//exploring the adjacent vertices of vertex 'vertex'
	for(i=1;i<n+1;i++)
	{
		if(v[vertex][i])/*if there exist an edge between vertices 'vertex' and 'i' then there exists an edge between them*/
			edges++;
		if(vis[v[vertex][i]]==0)//if the adjacent vertex has not been visited perform visit it and perform dfs
		{
			dfs(v[vertex][i],n);
		}
	}
}
void main()
	{
		int N,M;
		printf("Enter N -No of vertices\n");
		scanf("%d",&N);
		printf("Enter M -No of edges\n");
		scanf("%d",&M);
		int i;
		/*matrix v stores the vertices which have an edge between each other*/
		v = (int **)malloc((N+1) * sizeof(int *));

		for(i=0;i<N+1;i++)
		{
			v[i] = (int *)malloc((N+1) * sizeof(int));
		}
		printf("Enter the unordered pair of vertices with an edge,the index of vertices starts from 1\n");
		for(i=0;i<M;i++)
		{
			/*(a,b) stores the connected set of vertices*/
			
			int a,b;
			scanf("%d %d",&a,&b);
			v[a][b] = b;
			v[b][a] = a;
		}
		/*maxe stores the maximum number of edges in found in a connected component so far*/
		int j,maxe = -1000;
		edges = 0;
		vis = (int *)malloc((N+1)*sizeof(int));/*stores the status of the vertices already visited*/
		for(i=1;i<N+1;i++)
			vis[i] = 0;
		/*running dfs for all the n vertices if they are not visited yet*/
		for(i=1;i<N+1;i++)
		{
			if(!vis[i])
				dfs(i,N);
			//printf("%d\n",edges/2);
			/*edges/2 because in a particular run of a dfs each vertex is visited twice*/
			maxe=max(maxe,edges/2);
			edges=0;/*after calculating the edges for a particular component set the edges to 0*/
		}

		/*for(i=1;i<N+1;i++)
		{
			for(j=1;j<N+1;j++)
			{
				printf("%d\t",v[i][j]);
			}
			printf("\n");
		}*/
		//printing the maximum number of edges
		printf("The maximum number of edges are %d \n",maxe);
		return;
	}