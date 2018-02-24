#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **name,**name1;
int **adj;
int *matchR;
//function to find the minimum of two numbers 
int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
//function to print the matrix
void printMatrix(int m,int n)
{
	int i,j;
	for(i=1;i<m+1;i++)
	{
		for(j=1;j<n+1;j++)
			printf("%d\t",adj[i][j]);
		printf("\n");
	}
}
//function to print the result of the number of bipartite matchings
void printResult(int n)
{
	int i;
	for(i=1;i<n+1;i++)
	{
		if(matchR[i]>0 && matchR[i]!=-1)
		printf("%s is placed in %s\n",name1[matchR[i]],name[i]);
	}
}
//function to find the bipartite matching
int bpm(int m,int n,int *visited,int *matchR,int u)
{
	int i;
	for(i=1;i<n+1;i++)
	{
		if(adj[u][i] && !visited[i])
		{
			visited[i]=1;
			if(matchR[i]<0 || bpm(m,n,visited,matchR,matchR[i]))
			{
				matchR[i]=u;
				return 1;
			}
		}
	}
	return 0;
}
//function to find the maximum number of bipartite matchings
int maxBipartiteMatching(int m,int n)
{
	matchR=(int *)malloc((n+1)*sizeof(int));
	int i,j;
	for(i=1;i<n+1;i++)
		matchR[i]=-1;
	int result=0;
	for(i=1;i<m+1;i++)
	{
		int *visited=(int *)malloc((n+1)*sizeof(int));
		for(j=1;j<n+1;j++)
			visited[j]=0;
		if(bpm(m,n,visited,matchR,i))
			result++;
	}
	/*printf("Result calculated\n");*/
	printResult(n);
	return result;
}

void main()
{
	printf("Enter N(number of companies) and ");//N is the number of vertices(companies)
	printf("Enter the number of students\n");
		int N,M;
		scanf("%d %d",&N,&M);
		name=(char **)malloc((N+1) * sizeof(char *));//name array to store the names of companies
		name1=(char **)malloc((M+1) * sizeof(char *));//name1 array to store the names of the students
		adj=(int **)malloc((M+1)*sizeof(int *));
		int i,j,k;
		printf("Enter the names of the companies\n");//accepting the names
		for(i=1;i<M+1;i++)
		{
			adj[i]=(int *)malloc((N+1)*sizeof(int));
		}
		for(i=1;i<N+1;i++)
			{
				name[i]=(char *)malloc(100*sizeof(char));
				scanf("%s",name[i]);
				for(j=0;j<strlen(name[i]);j++)
				{
					if(name[i][j]>=65 && name[i][j]<=90)
						name[i][j]=name[i][j]+32;//converting the names into lower case letters
				}
			}
		printf("Enter the names of the students\n");
		for(i=1;i<M+1;i++)
		{
			name1[i]=(char *)malloc(100*sizeof(char));
				scanf("%s",name1[i]);
				for(j=0;j<strlen(name1[i]);j++)
				{
					if(name1[i][j]>=65 && name1[i][j]<=90)
						name1[i][j]=name1[i][j]+32;//converting the names into lower case letters
				}
		}
		//character arrays to form the adjacency matrix
		int *ch1=(int *)malloc(26*sizeof(int));
		int *ch2=(int *)malloc(26*sizeof(int));
		for(i=1;i<N+1;i++)
		{
			ch1[i]=0;
			ch2[i]=0;
		}
		//building the adhjacency matrix
		for(i=1;i<M+1;i++)
		{
			for(k=0;k<strlen(name1[i]);k++)
				{
					char ch=name1[i][k];
					int p=(int)(ch-97);
					ch1[p]++;
				}
			for(j=1;j<N+1;j++)
			{
				int count=0;
				for(k=0;k<strlen(name[j]);k++)
				{
					char ch=name[j][k];
					int p=(int)(ch-97);
					ch2[p]++;
				}
				for(k=0;k<26;k++)
				{
					if(ch1[k]>0 && ch2[k]>0)
								{
									if(ch1[k]==ch2[k])
										count=count+ch1[k];
									else if(ch1[k]!=ch2[k])
										{
											int p=min(ch1[k],ch2[k]);
											count=count+p;
										}
								}
						}
				if(count>=2)
					adj[i][j]=1;
				else
					adj[i][j]=0;
				for(k=0;k<26;k++)
					ch2[k]=0;
			}
			for(k=0;k<26;k++)
				ch1[k]=0;
		}
		//calling the printmatrix function
		printMatrix(M,N);
		//p stores the maximum number of bipartite matchings
		int p=maxBipartiteMatching(M,N);
		printf("\nThe maximum number of bipartite matchings = %d",p);
}