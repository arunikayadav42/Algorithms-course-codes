#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000
//name array to store the names of the houses
char **name;
char **nameCapital;
double *w1;

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
void printMatrix(double **adj,int n)
{
	int i,j;
	for(i=1;i<n+1;i++)
	{
		for(j=1;j<n+1;j++)
		{
			printf("%.3lf ",adj[i][j]);
		}
		printf("\n");
	}
}
//function to calulate the vertex weights
double *makeArrayW(int n,char **name)
	{
		double *w=(double *)malloc((n+1)*sizeof(double));
		int i;
		for(i=1;i<n+1;i++)
			{
				int j;
				double count=0;
				//counting the sum of ascii codes of all the characters in the name
				for(j=0;j<strlen(name[i]);j++)
					{
						int p=(int)name[i][j];
						count+=(double)p;
					}
				//w[i] stores the average value 
				w[i]=count/strlen(name[i]);
				//printf("count : %d\n",w[i]);
			}
		return w;
	}
	//function to extract the vertex with minimum vertex weight 
int minKey(double key[],int mstSet[],int n)
{
	double mini=INF;
	int index=0,i;
	for(i=1;i<n+1;i++)
	{
		if(mstSet[i]==0 && key[i]<mini)
			{
				mini=key[i];
				index=i;
			}
	}
	return index;
}
//function to print the final solution of the minimum spanning tree
void printMST(int parent[],double **adj,int n)
{
	printf("Connection          	COST\n");
	int i;
	double count=0;
	for(i=1;i<n+1;i++)
	{
		//borewell exists at the vertex
		if(parent[i]==i)
			{
				printf("%s-%s          %.3lf\n",nameCapital[0],nameCapital[i],adj[i][0]);
				count+=adj[i][0];
			}
		else//else the vertex shares a pipeline from it's neighbour
			{
				printf("%s-%s         %.3lf\n",nameCapital[parent[i]],nameCapital[i],adj[i][parent[i]]);
				count+=adj[i][parent[i]];
			}	
	}
	printf("\nTotal Cost : %.3lf\n",count);
}
//function to run the prims algorithm on the given input,adj matrix is the matrix of edge weights
void primMST(double **adj,int n)
{
	int parent[n+1];//stores the parent of the vertex
	double key[n+1];//stores the key for each vertex
	int mstSet[n+1];//stores the vertices already included in the minimum spanning tree	
	int i,j;
	double mini=1000000.0;
	int index=0;//mini to store the vertex with least cost for using the borewell,works as the source vertex
	for(i=1;i<n+1;i++)
	{
		key[i]=w1[i];//initializing keys with the self-cost
		mstSet[i]=0;//initially no vertex is present in the MST
		parent[i]=i;//assigning borewell to all initially
	}
	//finding the minimum cost borewell from the set of N houses,
	for(i=1;i<n+1;i++)
	{
		if(mini>w1[i])
			{
				mini=w1[i];
				index=i;
			}
	}
	key[index]=w1[index];//the vertex at the index acts as the source
//running prims algorithm on all the vertices
	for(i=1;i<n;i++)
	{
		int u=minKey(key,mstSet,n);
		mstSet[u]=1;
		for(j=1;j<n+1;j++)
		{
			if(adj[u][j] && mstSet[j]==0 && adj[u][j]<key[j])
				parent[j]=u,key[j]=adj[u][j];
		}
	}
	printMST(parent,adj,n);//printing the solution
}
void main()
	{
		printf("Enter N\n");//N is the number of verices(houses)
		int N;
		scanf("%d",&N);
		name=(char **)malloc((N+1) * sizeof(char *));//name array to store the names all in small
		nameCapital=(char **)malloc((N+1) * sizeof(char *));//name array to store the original names
		int i,j,k;
		name[0]=(char *)malloc((20)*sizeof(char));
		nameCapital[0]=(char *)malloc((20)*sizeof(char));
		printf("\nEnter all the names in small case and with no spaces\n");
		printf("Enter the names(ALL IN SMALL)\n");//accepting the names
		for(i=1;i<N+1;i++)
			{
				char s[100];
				scanf("%s",s);
				name[i]=(char *)malloc((strlen(s)+1)*sizeof(char));
				nameCapital[i]=(char *)malloc((strlen(s)+1)*sizeof(char));
				strcpy(nameCapital[i],s);
				if(s[0]>=65 && s[0]<=90)
				s[0]=s[0]+32;
				strcpy(name[i],s);
			}
		strcpy(name[0],"borewell");
		strcpy(nameCapital[0],"borewell");
			//printf("%s %s\n",name[1],name1[1]);
		w1=makeArrayW(N,name);//making the self-weight array
		//convertIntoSmallLetters();
		//printf("adj declared\n");
		printf("\nName\t\tCost of borewell :\n");
		for(i=1;i<N+1;i++)
		{
			printf("%s\t\t\t%.3lf\n",name[i],w1[i]);
		}
		double **adj=(double **)malloc((N+1)*sizeof(double *));//making the edge weight matrix
		for(i=0;i<N+1;i++)
			{
				adj[i]=(double *)malloc((N+1)*sizeof(double));
			}
			//printf("adj declared\n");
			//assigning self cost 
		for(i=1;i<N+1;i++)
			adj[i][0]=adj[0][i]=w1[i];
		//printf("self cost given\n");
		//character arrays to help determine that edges exist between which two vertices
		int *ch1=(int *)malloc(26*sizeof(int));
		int *ch2=(int *)malloc(26*sizeof(int));
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
			sum1=sum1+name[i][k];//sum2 stores the sum of characters of the second word
		}

										/*printf("%s\n",name[i]);
										for(k=0;k<26;k++)
										{
											if(ch1[k]>0)
												printf("ch2[%d] = %d\n",k,ch1[k]);
										}*/
		for(j=1;j<N+1;j++)
		{
			sum2=0;
			//checking with what words does the current word connected
			if(j==i)
				adj[i][i]=0.0;//no self loops
			else
				{
					int minlen=min(strlen(name[i]),strlen(name[j]));
					for(k=0;k<strlen(name[j]);k++)
						{
							char ch = name[j][k];
							int p = (int)(ch-97);
							ch2[p] = ch2[p]+1;
							sum2=sum2+name[j][k];//sum2 stores the sum of characters of the second word
						}
										/*printf("%s\n",name[j]);
										for(k=0;k<26;k++)
										{
											if(ch2[k]>0)
												printf("ch2[%d] = %d\n",k,ch2[k]);
										}*/
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
					if(count==minlen)//if count=minlen then the two houses are neighbours
						{
										//printf("count and minlen are equal\n");
							int mini=min(sum1,sum2);
							int maxi=max(sum1,sum2);
							adj[i][j]=adj[j][i]=maxi-mini;//the edge weight equal to |sum1-sum2|	
						}
					if(count!=minlen)
						{
										//printf("count and minlen not equal\n");
							adj[i][j]=adj[j][i]=0.0;
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
		printf("\nThe edge weight matrix is :\n");
	printMatrix(adj,N);
	printf("\n\n");
	primMST(adj,N);
		return;
	}


















