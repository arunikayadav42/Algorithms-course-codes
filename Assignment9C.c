#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

char **name;
double **adj,**dist;//adj and dist arrays are used to store the time values for different pairs of locality
int *visit;
int **path;
//function to find the minimu of two numbers
int min2(int a,int b)
{
	if(a>b)
		return b;
	else
		return a;
}
//function to find the minimum of three numbers
int min3(int a,int b,int c)
{
	return min2(min2(a,b),c);
}
//function to find the edit distance between two pairs of strings using dynamic programming
int editDistance(char *s1,char *s2,int m,int n)
{
	int dp[m+1][n+1];
	int i,j;
	for(i=0;i<m+1;i++)
	{
		for(j=0;j<n+1;j++)
		{
			if(i==0)//if strlen(s1)=0 ,then minimum number of characters equal to j
				dp[i][j]=j;
			else if(j==0)//if strlen(s2)=0 ,then minimum number of characters equal to i
				dp[i][j]=i;
			else if(s1[i-1]==s2[j-1])//if the last character matches,then consider the m-1 and n-1 characters left
				dp[i][j]=dp[i-1][j-1];
			else//
			{
				int p=dp[i][j-1];//insert a character
				int q=dp[i-1][j];//remove a character
				int r=dp[i-1][j-1];//replace a character
				dp[i][j]=1+min2(min2(p,q),r);//selecting the operation with minimum cost
			}
		}
	}
	return dp[m][n];//returning the result
}
//function to print the matrix with type double entries
void printMatrix(double **a,int n)
{
	int i,j;
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			printf("%.3lf ",a[i][j]);
		}
		printf("\n");
	}
}
//function to print matrix with integer entries
void printMatrix1(int **a,int n)
{
	int i,j;
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
}
//function to execute the floyd warshall algorithm to find the all pair shortest path
void floydWarshall(int n)
{
	dist=(double **)malloc((n+1)*sizeof(double *));
	path=(int **)malloc((n+1)*sizeof(int *));
	int i,j,k;
	for(i=1;i<n+1;i++)
	{
		dist[i]=(double *)malloc((n+1)*sizeof(double));
		path[i]=(int *)malloc((n+1)*sizeof(int));
		for(j=1;j<n+1;j++)
		{
			dist[i][j]=adj[i][j];//initializing the dist matrix
		//making the path matrix
		if(i==j)
			path[i][j]=0;
		else if(adj[i][j]!=INF)
			path[i][j]=i;
		else
			path[i][j]=-1;
		}
	}
	//executing the floyd warshall algorithm in O(n(cubed))
	for(k=1;k<n+1;k++)
	{
		for(i=1;i<n+1;i++)
		{
			for(j=1;j<n+1;j++)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])//if we get a shorter path other than i,j via a vertex k then update the vertex
					{
						dist[i][j]=dist[i][k]+dist[k][j];//updating the cost matrix
						path[i][j]=path[k][j];//updating the path matrix
					}
			}
		}
	}
	printMatrix(dist,n);//printing the dist matrix
	printf("The path matrix :\n");
	printMatrix1(path,n);//printing the path matrix
}
//printing the path using the path matrix
void printPath(int n,int src,int dest)
{
	if(path[src][dest]==src)
		{
			printf("%s->",name[src]);
			return;
		}
	printPath(n,src,path[src][dest]);
	printf("%s->",name[path[src][dest]]);
}
//deciding in which locality to set the dominoes 
void maxLocality(int n,int p)
{
	int i,j;
	int index,max=-1000000000;
	int *count=(int *)malloc((n+1)*sizeof(int));
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(visit[j]==0 && dist[i][j]<=30)//if the locality has not yet been covered and it can be covered using the current locality in less than 30 mins then it is inlcuded
				count[i]++;//incrementing the count of number of localities covered by the ith locality
		}
	}
	//using greedy approach to find the locality that covers the maximum number of localities
	for(i=1;i<n+1;i++)
	{
		if(max<count[i])
		{
			index=i;
			max=count[i];
		}
	}
	//updating the status of the visit array accordingly
	for(i=1;i<n+1;i++)//gives the number of localities covered by a particular restaurant
	{
		if(visit[i]==0 && dist[index][i]<=30)
			visit[i]=p;
	}
	visit[index]=-p;//gives the locality where the restaurant is to be set up
}
void main()
{
	int n;
	printf("Enter the number of localities\n");
	scanf(" %d",&n);
	printf("\nEnter the names in small case letters\n");
	printf("Enter the names of the locality\n");
	int i,j;
	name=(char **)malloc((n+1)*sizeof(char *));
	double **traffic=(double **)malloc((n+1)*sizeof(double *));//accepting the traffic b/w two loaclities from the user
	for(i=1;i<=n;i++)
	{
		char w[100];
		scanf(" %s",w);
		name[i] = (char *)malloc((strlen(w)+1)*sizeof(char));
		strcpy(name[i],w);
		//printf("%s %lf",name[i],traffic[i]);
	}
	//initializing the time matrix
	adj=(double **)malloc((n+1)*sizeof(double *));
	for(i=1;i<n+1;i++)
	{
		adj[i]=(double *)malloc((n+1)*sizeof(double));
		traffic[i]=(double *)malloc((n+1)*sizeof(double));
		for(j=1;j<n+1;j++)
		{
			if(i!=j)
				adj[i][j] = INF;
			else
				adj[i][j]=0;
		}
	}
		//accepting the traffic b/w two localities from the user
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(i!=j)
			{
				printf("Enter traffic (lying between 0.5 and 2) between %s and %s\n",name[i],name[j]);
				scanf(" %lf",&traffic[i][j]);
			}
			
		}
	}
	//calculating the edge weights for the various edges and building the edge weight matrix
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			if(j!=i)
				{
					int p=editDistance(name[i],name[j],strlen(name[i]),strlen(name[j]));
					adj[i][j]=p*traffic[i][j];
				}
		}
	}
	printf("\nThe time matrix is \n");
	printMatrix(adj,n);
	printf("\n");
	printf("\nThe all pair shortest path matrix is\n");
	floydWarshall(n);
	visit=(int *)malloc((n+1)*sizeof(int));
	for(i=1;i<n+1;i++)
		visit[i]=0;
	int flag=0;
	for(i=1;i<n+1;i++)
	{
		flag=1;
		maxLocality(n,i);
		for(j=1;j<n+1;j++)
		{
			if(visit[j]==0)
				flag=0;
		}
		if(flag==1)
			break;

	}
	printf("\nThe visit array is\n");
	for(i=1;i<n+1;i++)
		printf("%d ",visit[i]);
	printf("\n");
	//printf("%d\n",p);
	//printing the location of the restaurant and the localities covered by this restaurant
	for(i=1;i<n+1;i++)
	{
		double max=-100000000.0;
		int index=0;
		flag=0;
		
		for(j=1;j<n+1;j++)
			if(visit[j]==-i)
				{
					printf("Dominoes Location:\n");
					printf(" %s\t\t\t",name[j]);
					printf("\nLocalities Covered\n");
					flag=1;
				}
		
		for(j=1;j<n+1;j++)
		{

			if(visit[j]==i)
				printf("%s ,",name[j]);
		}
	}
	printf("\nPath\n");
	/*for(i=1;i<n+1;i++)
	{
		double max=-100000000.0;
		int index=0;
		flag=0;

		
		for(j=1;j<n+1;j++)
			if(visit[j]==i && max<dist[i][j])
			{
				max=dist[i][j];
				index=j;
			}
			if(flag==1)
			{
				if(i!=index && path[i][index]!=-1)
				printPath(n,i,index);
			}
	}*/
	//printing the path to reach every locality under which it is covered
	for(i=1;i<n+1;i++)
	{
		flag=0;
		int index;
		for(j=1;j<n+1;j++)
			if(visit[j]==-i)//finding the locality atwhich there is a dominoes
				{
					flag=1;
					index=j;
					for(j=1;j<n+1;j++)
						{
							if(index!=j && path[index][j]!=-1)//printing the path from this to every other locality that it covers
								{
									printf("\nSHortest path between %s and %s is : ",name[index],name[j]);
									printPath(n,index,j);
									printf("%s\n",name[j]);
								}
						}
				}
	}
	printf("\n");
	return;
}