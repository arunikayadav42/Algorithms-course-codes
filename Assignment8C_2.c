#include <stdio.h>
#include <stdlib.h>

int edges;

struct node{
	int vertex;
	struct node *next;
};

struct graph{
	int numVertices;
	int *visited;
	struct node **adjLists;
};

struct node* createNode(int v)
{
	struct node* p = (struct node *)malloc(sizeof(struct node));
	p->vertex = v;
	p->next = NULL;
	return p;
}

struct graph* createGraph(int numOfVertices)
{
	struct graph* graph1 = (struct graph*)malloc(sizeof(struct graph));
	graph1->numVertices = numOfVertices;
	graph1->visited = (int *)malloc((numOfVertices+1) * sizeof(int));
	graph1->adjLists = (struct node**)malloc((numOfVertices+1) * sizeof(struct node * ));
	int i;   
	for(i=1;i<numOfVertices+1;i++)
	{
		graph1->visited[i] = 0;
		graph1->adjLists[i]=NULL;
	}
	return graph1;
}

void addEdge(struct graph *graph1,int start,int end)
	{
		struct node *p = createNode(end);
		p->next = graph1->adjLists[start];
		graph1->adjLists[start] = p;

		struct node *q=createNode(start);
		q->next = graph1->adjLists[end];
		graph1->adjLists[end] = q;
	}
 
void DFS(struct graph* graph1,int vertex)
	{
		//if(graph->visited[vertex]==1)
		//	return;
		printf("Reached DFS\n");
		struct node* p = graph1->adjLists[vertex];
		struct node* temp = p;
		graph1->visited[vertex] = 1;
		while(temp)
		{
			int adjVertex = temp->vertex;
			edges++;
			printf("edges : %d",edges);
			if(graph1->visited[vertex]==0)
			{
				DFS(graph1,adjVertex);
			}
			temp = temp->next;
		}
	}

void printGraph(struct graph* graph1)
{
    int v;
    for (v = 1; v < graph1->numVertices+1; v++)
    {
        struct node* temp = graph1->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void main()
	{
		int N,M;
		printf("Enter the number of edges and the number of vertices\n");
		scanf("%d %d",&N,&M);
		struct graph* graph1 = createGraph(N);
		int i;
		for(i=0;i<M;i++)
		{
			printf("Enter the unordered pair of vertices with an edge\n");
			int a,b;
			scanf("%d %d",&a,&b);
			addEdge(graph1,a,b);
		}
		int max=-1000,edges = 0;
		printGraph(graph1);
		for(i=1;i<N+1;i++)
	{
		printf("%d\n",graph1->visited[i]);
	}
		for(i=1;i<N+1;i++)
		{
			printf("Entered for towards DFS\n");
			if(graph1->visited[i]==0)
			{
				printf("About to reach DFS\n");
				DFS(graph1,i);
				printf("edges : %d\n",edges);
				if(max<edges)
					max = edges;
				edges = 0;
			}
		}
		printf("The maximum number of edges %d",max);
		return;
	}
