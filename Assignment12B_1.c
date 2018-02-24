#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int **adj,**radj;
char **name,**name1;
int count;

struct Edge{
	int flow,capacity,u,v;
};

struct Vertex{
	int h,e_flow;
};
struct Edge *edge;
struct Vertex *ver;
int min(int a,int b)
	{
		if(a<b)
			return a;
		else if(b<a)
			return b;
		else if(a==b)
			return a;
	}
void preflow(int n)
{
	/*printf("Entered preflow\n");*/
	ver=(struct Vertex *)malloc(n*sizeof(struct Vertex));
	edge=(struct Edge *)malloc(100*sizeof(struct Edge));
	int i,j,k;
	for(i=0;i<n;i++)
	{
		ver[i].h=0;
		ver[i].e_flow=0;
	}

	k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(adj[i][j]>0)
			{
				edge[k].flow=0;
				edge[k].u=i;
				edge[k].v=j;
				edge[k].capacity=adj[i][j];
				k++;
			}
			
		}
	}
	ver[0].h=n;
	for(i=0;i<count;i++)
	{
		printf("%d %d ",edge[i].flow,edge[i].capacity);
	}
	int count1=count;
	for(i=0;i<count;i++)	
	{
		if(edge[i].u==0)
		{
			edge[i].flow=edge[i].capacity;
			/*printf("edge value assigned\n");*/
			ver[edge[i].v].e_flow+=edge[i].flow;
			/*printf("vertex value assigned\n");*/
			edge[count1].flow=-edge[i].flow;
			edge[count1].capacity=0;
			edge[count1].u=edge[i].v;
			edge[count1].v=0;
			/*printf("edge set initialized again\n");*/
			count1++;
		}
		
	}
	count=count1;
	/*printf("preflow ends\n");*/
}
int overflowvertex(int n)
{
	/*printf("Entered overflowvertex\n");*/
	int i;
	for(i=1;i<n;i++)
		if(ver[i].e_flow>0)
			return i;
	return -1;
}
void updateReverseEdgeFlow(int i,int flow)
{
	printf("Entered updateReverseEdgeFlow\n");
	int u=edge[i].v;
	int v=edge[i].u;
	int j;
	for(j=0;j<count;j++)
	{
		if(edge[j].v==v && edge[j].u==u)
		{
			edge[j].flow-=flow;
			return;
		}
	}
	edge[count].flow=0;
	edge[count].capacity=flow;
	edge[count].u=u;
	edge[count].v=v;
	count++;
}
void relabel(int u)
{
	printf("Entered relabel\n");
	int minh=INF;
	int i;
	for(i=0;i<count;i++)
	{
		if(edge[i].u==u)
		{
			if(edge[i].flow==edge[i].capacity)
				continue;
			if(ver[edge[i].v].h<minh)
			{
				minh=ver[edge[i].v].h;
				ver[u].h=minh+1;
			}
		}
	}
}
int push(int u)
{
	printf("Entered push\n");
	int i;
	for(i=0;i<count;i++)
	{
		if((edge[i].u)==u)
		{
			if(edge[i].flow==edge[i].capacity)
				continue;
			if(ver[u].h>ver[edge[i].v].h)
			{
				int flow=min(edge[i].capacity-edge[i].flow,ver[u].e_flow);
				ver[edge[i].v].e_flow+=flow;
				edge[i].flow+=flow;
				updateReverseEdgeFlow(i,flow);
				return 1;
			}
		}
	}
	return 0;
}
int getMaxFlow(int n)
{
	printf("Entered getMaxFlow\n");
	radj=(int **)malloc(n*sizeof(int *));
	int i,j;
	for(i=0;i<n;i++)
	{
		radj[i]=(int *)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			radj[i][j]=adj[i][j];
	}
	preflow(n);
	while(overflowvertex(n)!=-1)
	{
		printf("looping in getMaxFlow\n");
		int u=overflowvertex(n);
		if(!push(u))
			relabel(u);
	}
	return ver[n-1].e_flow;
}
void printMatrix(int n)
	{
		int i,j;
		count=0;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				{
					printf("%d\t",adj[i][j]);
					if(adj[i][j]>0)
						count++;
				}
			printf("\n");
		}
	}
void main()
{
	printf("Enter the number of cities\n");
	int n;
	scanf("%d",&n);
	adj=(int **)malloc(n*sizeof(int *));
	int i,j,k;
	for(i=0;i<n;i++)
		adj[i]=(int *)malloc(n*sizeof(int));
	name=(char **)malloc(n*sizeof(char *));
	name1=(char **)malloc(n*sizeof(char *));
	for(i=0;i<n;i++)
		{
			name[i]=(char *)malloc(n*sizeof(char));	
			name1[i]=(char *)malloc(n*sizeof(char));
			scanf("%s",name[i]);
			strcpy(name1[i],name[i]);
			for(j=0;j<strlen(name[i]);j++)
				{
					if(name[i][j]>=65 && name[i][j]<=90)
						name[i][j]=name[i][j]+32;
				}
		}
	for(i=0;i<n;i++)
		{
			if(strcmp(name[i],"goa")==0)
				{
					char s1[100],s2[100];
					strcpy(s1,name1[i]);
					strcpy(name1[i],name1[0]);
					strcpy(name1[0],s1);
					strcpy(s2,name[i]);
					strcpy(name[i],name[0]);
					strcpy(name[0],s2);
				}
			if(strcmp(name[i],"thiruvananthapuram")==0)
				{
					char s1[100],s2[100];
					strcpy(s1,name1[i]);
					strcpy(name1[i],name1[n-1]);
					strcpy(name1[n-1],s1);
					strcpy(s2,name[i]);
					strcpy(name[i],name[n-1]);
					strcpy(name[n-1],s2);
				}
		}
	int *ch1=(int *)malloc(26*sizeof(int));
	int *ch2=(int *)malloc(26*sizeof(int));
	for(i=0;i<26;i++)
		{
			ch1[i]=0;
			ch2[i]=0;
		}
	for(i=1;i<n-1;i++)
		{
			for(j=0;j<strlen(name[i]);j++)
				{
					int q=(int)name[i][j];
					int p=(int)(q-97);
					//printf("p:(ch1)%d   ",p);
					ch1[p]++;
				}
			
			for(k=1;k<n-1;k++)
				{
					if(k!=i)
						{
							for(j=0;j<strlen(name[k]);j++)
						{
							int q=(int)name[k][j];
							int p=(int)(q-97);
							//printf("p:(ch2)%d     ",p);
							ch2[p]++;
						}
					/*for(j=0;j<26;j++)
						printf("%d ",ch1[j]);
					printf("\n");*/
					int count=0;
					/*for(j=0;j<26;j++)
						printf("%d ",ch2[j]);*/
					for(j=0;j<26;j++)
						{
							if(ch1[j]>0 && ch2[j]>0)
								{
									if(ch1[j]==ch2[j])
										count=count+ch1[j];
									else if(ch1[j]!=ch2[j])
										{
											int p=min(ch1[j],ch2[j]);
											count=count+p;
											ch2[j]=ch2[j]-p;
										}
								}
						}
					/*printf("between %s and %s is count : %d\n",name[i],name[k],count);*/
					if(strlen(name[k])-strlen(name[i])==1 && count>=1 && i!=k)
						{
							adj[i][k]=2*count;
						}
					for(j=0;j<26;j++)
						ch2[j]=0;
						}
					if(i==k)
						adj[i][k]=0;
				}
			for(j=0;j<26;j++)
				ch1[j]=0;
		}
			for(i=1;i<n-1;i++)
		{
			int count1=0,count2=0;
			for(j=1;j<n-1;j++)
			{
				if(adj[j][i]==0)
					count1++;
				if(adj[i][j]==0)
					count2++;
			}
			if(count1==n-2)
				{
					adj[0][i]=20;
				}
			if(count2==n-2)
				{
					adj[i][n-1]=20;
				}
		}
	printMatrix(n);
	int max_flow=getMaxFlow(n);
	printf("The maxflow is %d\n",max_flow);
	return;
}
















