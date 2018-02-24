#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INF 1000000000

char **name,**name1;
int *ascii;
int **adj,**dist,**path,**adj1;

//function to find the minimum of two numbers
int min(int a,int b)
	{
		if(a>b)
			return b;
		else
			return a;
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
//function to print the path between two localities
void printPath(int *parent,int n,int src)
{
	if(parent[src]==-1)
	{
		printf("%s(city no. %d)->",name[src],src);
		return;
	}
	printPath(parent,n,parent[src]);
	printf("%s(city no. %d)->",name[src],src);
}
//to find the distance between any two pairs of localities by taking the difference character by character
int distance(char *a,char *b,int l1,int l2)
{
	int i,j,k,sum=0;
	int minlen=min(l1,l2);
	for(i=0;i<minlen;i++)
	{
		//the difference is taken according to the ascii value of the characters
		if(a[i]>b[i])
			sum+=(int)(a[i]-b[i]);
		else if(a[i]<b[i])
			sum+=(int)(b[i]-a[i]);
	}
	//if one of the two words is shorter then simply the ascii value of the characters is taken 
	if(l1>l2)
	{
		for(i=l2;i<l1;i++)
			sum+=(int)a[i];
	}
	else if(l1<l2)
	{
		for(i=l1;i<l2;i++)
			sum+=(int)b[i];
	}
	return sum;//the final sum is returned
}
//to find the next minimum in the set of vertices not yet included
int extractMin(int *dist,int *sptSet,int n)
{
	int min=INF,index=0,i;
	for(i=1;i<n+1;i++)
		{
			if(sptSet[i]==0 && dist[i]<=min)
			{
				min=dist[i];
				index=i;
			}
		}
	return index;//the index of the same vertex is returned
}
//function to find the shortest path between the given source and destination
void dijkstra(int n,int src,int dest)
{
	int *sptSet,*parent,*dist;
	sptSet=(int *)malloc((n+1)*sizeof(int));//array to store the status of vertices already included and the ones yet to be included
	parent=(int *)malloc((n+1)*sizeof(int));//array to store the parent array
	dist=(int *)malloc((n+1)*sizeof(int));//array to store the distance of the vertices from the source
	int i,j;
	//initializing the various arrays 
	for(i=1;i<n+1;i++)
	{
		parent[i]=0;
		sptSet[i]=0;
		dist[i]=INF;
	}
	//initializing the array values for the source vertex
	parent[src]=-1;
	dist[src]=0;
	//executing dijkstra on the given input
	for(i=1;i<n;i++)
	{
		//extracting the vertex to be included in the shortest path set
		int u=extractMin(dist,sptSet,n);
		sptSet[u]=1;//updating it's status
		for(j=1;j<n+1;j++)
		{
			//if the vertex has not yet been discovered and its an adjacent vertex then 
			if(sptSet[j]==0 && adj[u][j]!=INF && adj[u][j]!=0 && dist[j]>adj[u][j]+dist[u] && dist[u]!=INF)
			{
				//updating the parent
				parent[j]=u;
				//updating the distance
				dist[j]=adj[u][j]+dist[u];
			}
		}
	}
	printf("The path array is \n");
	for(i=1;i<n+1;i++)
		printf("parent:%d dist:%d\n",parent[i],dist[i]);
	//if the value of the dist matrix not yet discovered then there does not exist a path 
	if(dist[dest]==INF)
		{
			printf("No such path exists\n");
			exit(0);
		}
	else//else execute this
		{
			printf("\n\n\nTHE PATH IS :\n");
			printPath(parent,n,dest);
		}

}
void main()
{
	srand(time(NULL));
	printf("Enter N(number of localities\n");//N is the number of verices(houses)
		int N;
		scanf("%d",&N);
		name=(char **)malloc((N+1) * sizeof(char *));//name array to store the names all in small
		name1=(char **)malloc((N+1) * sizeof(char *));
		int i,j,k;
		printf("Enter the names(FIRST LETTER CAPITAL) \n");//accepting the names
		for(i=1;i<N+1;i++)
			{
				name[i]=(char *)malloc(100*sizeof(char));
				name1[i]=(char *)malloc(100*sizeof(char));
				scanf("%s",name1[i]);
				strcpy(name[i],name1[i]);
				for(j=0;j<strlen(name[i]);j++)
				{
					if(name[i][j]>=65 && name[i][j]<=90)
						name[i][j]=name[i][j]+32;
				}
			}
		adj=(int **)malloc((N+1)*sizeof(int *));//making the edge weight matrix
		//allocating memory to adj and adj1 matrices 
		for(i=0;i<N+1;i++)
			{
				adj[i]=(int *)malloc((N+1)*sizeof(int));
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
								int d=distance(name[i],name[j],strlen(name[i]),strlen(name[j]));
								//printf("count : %d\n",count);
								int diff=strlen(name[j])-strlen(name[i]);
								//printf("distance : %d\n",d);
								//allocating the values to the edge-weight matrix
								//if there exist an edge with positive slope give ith value of d
								//else assign it 0
								if(diff==0)
									adj[i][j]=0;
								else if(count>=1 && diff==1)
									adj[i][j]=d;
								else if(count>=1 && diff==-1)
									adj[i][j]=INF;
								else if(count>=2 && diff==2)
									adj[i][j]=d;
								else if(count>=2 && diff==-2)
									adj[i][j]=INF;
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
		printMatrix(adj,N);
		//randomly selecting the home and the office
		int p,q;
		/*p=1+rand()%N;
		q=1+rand()%N;
		while(p==q)
		{
			q=1+rand()%N;
		}
		printf("(HOME)p:%d  (OFFICE)q:%d\n",p,q);
		dijkstra(N,p,q);*/
		printf("Enter the string for home and that for office\n(F");
		char s1[100],s2[100];
		scanf("%s %s",s1,s2);
		for(i=1;i<N+1;i++)
		{
			for(j=0;j<strlen(s1);j++)
				{
					if(s1[j]>=65 && s1[j]<=90)
						s1[j]=s1[j]+32;
				}
			for(j=0;j<strlen(s2);j++)
				{
					if(s2[j]>=65 && s2[j]<=90)
						s2[j]=s2[j]+32;
				}
			if(strcmp(s1,name[i])==0 || strcmp(s1,name1[i])==0)
				p=i;
			if(strcmp(s2,name[i])==0 || strcmp(s2,name1[i])==0)
				q=i;
		}
		dijkstra(N,p,q);
	return;
}