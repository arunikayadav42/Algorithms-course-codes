#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *vis;
int **v;
int f;

/*function to find the minimum of two numbers*/
int min(int a,int b)
{
	if(a<b)
		return a;
	else
		return b;
}
//function to run dfs on the adjacency matrix
void dfs1(int vertex,int n)
{
	//the value of array vis is set 1 for the visited array
	vis[vertex] = 1;
	int i;
	//printf("vertex : %d\n",vertex);
	//for(i=1;i<n+1;i++)
		//printf("%d\t",vis[i]);
	//printf("\n");
	//i starts from vertex because it is a directed graph and cannot visit it's parent
	for(i=1;i<n+1;i++)
	{
//if the vertex has already been visited in the path and is not the current vertex then increment flag value
		if(vis[v[vertex][i]]==1 && i!=vertex)
		{
			f++;
		}
		//printf("f : %d\n",f);
		//else run dfs on the matrix
		if(vis[v[vertex][i]]==0 && v[vertex][i])
			dfs1(v[vertex][i],n);
	}
}

void main()
{
	printf("Enter the number of names(vertices)\n");
	int n;
	scanf("%d",&n);
	char **s=(char **)malloc((n+1)*sizeof(char *));
	int i,j;
//vis array stores the status of the visited array
	vis = (int *)malloc((n+1) * sizeof(int));
//v matrix stores the adjacency matrix for the input
	v = (int **)malloc((n+1) * sizeof(int *));
//initializing the vis array to 0
	for(i=1;i<n+1;i++)
	{
		vis[i] = 0;
	}
//initializing the adjacency matrix to zero
	for(i=0;i<n+1;i++)
	{
		v[i] = (int *)malloc((n+1) * sizeof(int));
		for(j=1;j<n+1;j++)
		{
			v[i][j] = 0;
		}
	}
printf("Enter the words\n");

	for(i=1;i<n+1;i++)
		{
			
			s[i]=(char *)malloc(5*sizeof(char));
			scanf(" %s",s[i]);
		}
	/*declaring two arrays for comparing two words at a time and checking if they are connected or not*/
	int *ch1 = (int *)malloc(26 * sizeof(int));
	int *ch2 = (int *)malloc(26 * sizeof(int));
//initializing them to zero
	for(i=0;i<26;i++)
	{
		ch1[i] = 0;
		ch2[i] = 0;
	}

	int k;
	//building the adjacency matrix
	for(i=1;i<n+1;i++)
	{
		//ch1 stores the characters of the current word except the first character
		for(k=1;k<strlen(s[i]);k++)
		{
			char ch = s[i][k];
			int p = (int)(ch-97);
			ch1[p] = ch1[p]+1;
		}

		for(j=1;j<n+1;j++)
		{
			//checking with what words does the current word connected
			if(i!=j)
			{
				for(k=0;k<strlen(s[j]);k++)
				{
					char ch = s[j][k];
					int p = (int)(ch-97);
					ch2[p] = ch2[p]+1;
				}
				//count variable turns 4 means that there is an edge
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
				//printf("count : %d\n",count);
				if(count==4)
				{
					//printf("connected : %s %s\n",s[i],s[j]);
					v[i][j] = j;
				}
				for(k=0;k<26;k++)//ch2 becomes [0] after comparison with every other word
				{
					ch2[k] = 0;
				}
			}
		}
	for(k=0;k<26;k++)//ch1 and ch2 both become zero after comparison with every other word
		{
			ch2[k] = 0;
			ch1[k] = 0;
		}
	}

	/*for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			printf("%d ",v[i][j]);
		}
		printf("\n");
	}*/
	//flag value to check if a graph is cyclic or not
	f=0;
	//running dfs to check if the graph is cyclic or not
	for(i=1;i<n+1;i++)
	{
		if(!vis[i])
			dfs1(i,n);
	}

	printf("\n");

	if(f==0)
		printf("GRAPH IS ACYCLIC\n");
	else
		printf("GRAPH IS CYCLIC\n");

	printf("\n");
	//making vis[] again zero for printing the path matrix
	for(i=1;i<n+1;i++)
	{
		vis[i] = 0;
	}
	//finding if there exists a path for every (i,j)
	int **a;
	a = (int **)malloc((n+1)*sizeof(int *));//a[][] is the path matrix

	for(i=1;i<n+1;i++)
	{
		a[i] = (int *)malloc((n+1) * sizeof(int));
		for(j=1;j<n+1;j++)
			a[i][j] = 0;
	}

	for(i=1;i<n+1;i++)
	{
		dfs1(i,n);
		for(j=1;j<n+1;j++)
		{
			if(vis[j]==1)
				{
					a[i][j] = 1;//if the vertex was visited during the dfs then path exists
					//a[j][i] = 1;
				}
			else
				{
					a[i][j] = 0;//else there does not exist a path
				}
		}
		for(j=1;j<n+1;j++)
			vis[j] = 0;//initializing vis[] to zero for dfs of next vertex 
		
	}
	printf("\n");
	printf("1 indicates existence of path \n");
	printf("0 indicates non-existence of path\n");
	printf("\n");
	//printing the path matrix
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
			{
				printf("%d ",a[i][j]);
			}
			printf("\n");
	}

	/*for(i=0;i<n;i++)
		{
			printf("%s\n",s[i]);
		}*/

	return;
}
