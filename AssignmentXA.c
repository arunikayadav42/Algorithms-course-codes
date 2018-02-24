#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

char **name;
int *ascii;
int **adj,**dist,**path,**adj1;
int flag;
int *visited;

//function to find the minimum of two numbers
int min(int a,int b)
	{
		if(a>b)
			return b;
		else
			return a;
	}

//function to find the maximum of two numbers
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

//function to print the matrix
void printMatrix(int **adj,int n)
{
	int i,j;
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(adj[i][j]!=INF)
				printf("%d\t",adj[i][j]);
			else
				printf("INF\t");
		}
		printf("\n");
	}
}
void printMatrixadj1(int **adj,int n)
{
	int i,j;
	printf("\n");
	printf("\t");
	for(i=1;i<n+1;i++)
	{
		printf("%s   ",name[i]);
	}
	printf("\n");
	for(i=1;i<n+1;i++)
	{
		printf("%s   ",name[i]);
		for(j=1;j<n+1;j++)
		{
				if(adj[i][j]==1 && i!=j)
					printf("%d\t",dist[i][j]);
				else if(i==j)
					printf("0\t");
				else
					printf("INF\t");
		}
		printf("\n");
	}
}
/*function to execute the floyd warshall algorithm in order to find the shortest distance between all pairs of vertices*/
void floydWarshall(int n)
{
	dist=(int **)malloc((n+1)*sizeof(int *));//matrix to store the all pair shortest distances
	int i,j;
	for(i=1;i<n+1;i++)
	{
		dist[i]=(int *)malloc((n+1)*sizeof(int));
		/*path[i]=(int *)malloc((n+1)*sizeof(int));*/
		for(j=1;j<n+1;j++)
		{
			dist[i][j]=adj[i][j];//storing the original distances in the dist matrix
		}
	}
	int k;
	//applying floyd warshall to find the all pair shortest path between any two pairs of vertices
	for(k=1;k<n+1;k++)
	{
		for(i=1;i<n+1;i++)
		{
			for(j=1;j<n+1;j++)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j] && dist[i][k]!=INF && dist[k][j]!=INF)
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					/*path[i][j]=path[k][j];*/
				}
			}
		}
	}
	printf("All pairs shortest distance matrix is :\n");
	printMatrix(dist,n);
	printf("\n");
	/*printf("The path matrix is :\n");
	printMatrix(path,n);*/
}
/*void detectPath(int n,int src,int dest)
{
	if(path[src][dest]==src && src!=dest)
		return;
	else if(path[src][dest]==src && src==dest)
	{
		adj[src][dest]=1;
		return;
	}
	detectPath(n,src,path[src][dest]);
	adj[src][dest]=1;
	
}*/
//to make the graph follow the transitive property as demanded in the question
void transitive(int **adj,int n)
{
	int i,j,k;
	
		for(j=1;j<n+1;j++)
		{
			//building adj1 matrix based on the updated adj matrix 
			for(k=1;k<n+1;k++)
			{
				adj1[j][k]=adj[j][k];
				if(k==j)
					adj1[j][j]=1;
			}
		}
		//checking for transitivity in the current matrix built based on the criteria of shortest distance
	for(k=1;k<n+1;k++)
	{
		for(i=1;i<n+1;i++)
		{
			for(j=1;j<n+1;j++)
				{
					adj1[i][j]=adj1[i][j] || (adj1[i][k] && adj1[k][j]);
				}
		}
	}
	printf("The final adjacency matrix(directed graph) is :\n");
	printf("cost>0 indicates a path exists from i to j :i-->j\n");
	printf("0 represents a self loop\n");
	printf("INF represents no edge between the given pairs and no path exists between the given pairs");
	printMatrixadj1(adj1,n);
}
void main()
	{
		printf("Enter N\n");//N is the number of verices(houses)
		int N;
		scanf("%d",&N);
		name=(char **)malloc((N+1) * sizeof(char *));//name array to store the names all in small
		int i,j,k;
		printf("\nEnter all the names in small case and with no spaces\n");
		printf("Enter the names(ALL IN SMALL)\n");//accepting the names
		for(i=1;i<N+1;i++)
			{
				name[i]=(char *)malloc(5*sizeof(char));
				scanf("%s",name[i]);
			}
		adj=(int **)malloc((N+1)*sizeof(int *));//making the edge weight matrix
		adj1=(int **)malloc((N+1)*sizeof(int *));
		path=(int **)malloc((N+1)*sizeof(int *));//making the second 2-D matrix to store the transitive closure of the current graph
		//allocating memory to adj and adj1 matrices 
		for(i=0;i<N+1;i++)
			{
				adj[i]=(int *)malloc((N+1)*sizeof(int));
				adj1[i]=(int *)malloc((N+1)*sizeof(int));
				path[i]=(int *)malloc((N+1)*sizeof(int));
			}
		/*declaring the matrices ch1 and ch2 in order to establish the edges*/
		int *ch1=(int *)malloc(26*sizeof(int));
		int *ch2=(int *)malloc(26*sizeof(int));
		//initializing the arrays
		for(i=0;i<26;i++)
			{
				ch1[i] = 0;
				ch2[i] = 0;
			}
		//accepting the threshold distances
		printf("ENTER THE VALUE 'd'\n");
		int d;
		scanf("%d",&d);
		//building the adjacency matrix
		int sum1,sum2;
		for(i=1;i<N+1;i++)
			{
				sum1=0;
				//ch1 stores the characters of the current word
				for(k=0;k<strlen(name[i]);k++)
					{
						char ch = name[i][k];
						int p = (int)(ch-97);
						ch1[p] = ch1[p]+1;
						sum1=sum1+name[i][k];//sum1 stores the sum of characters of the first word
					}
				for(j=1;j<N+1;j++)
					{
						sum2=0;
						//checking with what words is the current word connected
						if(j==i)
							adj[i][i]=0;//no self loops
						else
							{
								for(k=0;k<strlen(name[j]);k++)
									{
										char ch = name[j][k];
										int p = (int)(ch-97);
										ch2[p] = ch2[p]+1;
										sum2=sum2+name[j][k];//sum2 stores the sum of characters of the second word
									}
//count variable to see that two nodes get connected only if 4 characters match					
								int count = 0;
								for(k=0;k<26;k++)
									{
										if(ch1[k]>0 && ch2[k]>0)
											{
												if(ch1[k]==ch2[k])
													count=count+ch1[k];
												else//else for repeated letters in the words
													{
														int mini = min(ch1[k],ch2[k]);
														while(mini!=0)
															{
																count++;
																mini--;
															}
													}
											}
									}
										//printf("count : %d minlen:%d",count,minlen);
								if(count==4)//if count=4 then the two houses are neighbours
									{
										if((sum1>sum2))
											{
												adj[i][j]=sum1-sum2;//establishing an edge only if sum1>sum2,i.e,1-->2,i.e, 1 can access 2's account
												adj[j][i]=INF;//the j,i entry will not be an edge as the graph is directed
											}	
									}
					//if the count does not become 4 then no edge betwee the given pair
								if(count!=4)
									{
										//printf("count and minlen not equal\n");
										adj[i][j]=adj[j][i]=INF;
									}
							}
								
					for(k=0;k<26;k++)//ch2 becomes [0] after comparison with every other word
						{
							ch2[k] = 0;
						}	
				}
			for(k=0;k<26;k++)//ch1 and ch2 both become zero after comparison with every other word
				{
						ch2[k] = 0;
						ch1[k] = 0;
				}
		}
		printf("Initial adjacency matrix:\n");
		printMatrix(adj,N);
		printf("\n");
		floydWarshall(N);//calling floyd warshall 
		//reinitializing the adj matrix to store the new adjacency based on 'd'

		for(i=0;i<N+1;i++)
		{
			for(j=0;j<N+1;j++)
				{
					path[i][j]=adj[i][j];
					adj[i][j]=0;
				}
		}
		//storing the new adjacency
		for(i=1;i<N+1;i++)
		{
			for(j=1;j<N+1;j++)
			{
				if(dist[i][j]<=d && i!=j)
					adj[i][j]=1;
			}
		}
		//making the transitive closure of this graph
		transitive(adj,N);
		/*for(i=1;i<N+1;i++)
		{
			printf("%s\t\t",name[i]);
			for(j=1;j<N+1;j++)
			{
				if(adj[i][j]==1)
					printf("%s ",name[j]);
			}
			printf("\n");
		}*/
		//printing the result
		printf("\n \nACCESS STATUS:\n");
		printf("Vertex 'A'\t   'A' Can Access the following\n");
		for(i=1;i<N+1;i++)
		{
			printf("%s\t\t",name[i]);
			for(j=1;j<N+1;j++)
			{
				if(adj1[i][j]==1)
					{
						printf("%s ,",name[j]);
					}
			}
			printf("\n");
		}
	return;
}