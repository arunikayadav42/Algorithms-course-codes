#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int **cap,**radj,**flow,**G,**cf;
char **name,**name1;
int count,front,rear;
int *h,*e,*queue;

int min(int a,int b)
	{
		if(a<b)
			return a;
		else if(b<a)
			return b;
		else if(a==b)
			return a;
	}
void enqueue(int p)
{
	queue[++rear]=p;
}
int dequeue()
{
	return queue[++front];
}
int isEmpty()
{
	if(front>=rear)
		return 1;
	else
		return 0;
}
void printMatrix(int n,int **m)
	{
		int i,j;
		count=0;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				{
					printf("%d,",cap[i][j]);
					if(cap[i][j]>0)
						count++;
				}
			printf("\n");
		}
	}
void preflow(int n)
{
	int s=0;
	h=(int *)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++)
		h[i]=0;
	h[0]=n;
	e=(int *)malloc(n*sizeof(int));
	flow=(int **)malloc(n*sizeof(int *));
	for(i=0;i<n;i++)
		flow[i]=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		if(G[s][i]>0)
		{
			int v=G[s][i];
			flow[s][v]=cap[s][v];
			flow[v][s]=-cap[s][v];
			e[v]=cap[s][v];
			e[s]-=cap[s][v];
			cf[s][v]=cap[s][v]-flow[s][v];
			cf[v][s]=cap[v][s]-flow[v][s];
		}

	}

}
void push(int u,int v)
{
	printf("push executed\n");
	int temp=min(e[u],cf[u][v]);
	flow[u][v]+=temp;
	flow[v][u]-=temp;
	e[u]=e[u]-temp;
	e[v]=e[v]+temp;
	cf[u][v]=cap[u][v]-flow[u][v];
	cf[v][u]=cap[v][u]-flow[v][u];
}
void maxflow(int n)
{
	preflow(n);
	front=-1;
	rear=-1;
	printMatrix(n,cf);
	queue=(int *)malloc(n*sizeof(int));
	int *status=(int *)malloc(n*sizeof(int));
	int i,j;
	enqueue(0);
	for(i=1;i<n-1;i++)
	{
		if(G[0][i]>0)
		{
		enqueue(G[0][i]);
		status[G[0][i]]=1;
		}
	}
	for(i=front+1;i<=rear;i++)
		printf("%d ",queue[i]);
	printf("\n");
	while(!isEmpty())
	{
		int u=dequeue();
		int m=-1,v;
		printf("%d dequeued\n",u);
		/*printf("while loop entered\n");*/
		for(i=0;i<n && e[u]>0;i++)
		{
			/*printf("for loop enetered\n");*/
			v=G[u][i];
			if(cf[u][v]>0)
			{
				if(h[u]>h[v])
				{
					push(u,v);
					if(status[v]==0 && v!=0 && v!=n-1)
					{
						enqueue(v);
						status[v]=1;
						printf("Enqueued v is %d\n",v);
					}
				}
				else if(m==-1)
					m=h[v];
				else
					m=min(m,h[v]);
				for(j=front+1;j<=rear;j++)
					printf("%d ",queue[j]);
				printf("\n");
			}
		}
		if(e[u]!=0)
			h[u]=1+m;
		else
		{
			status[u]=0;
			printf("%d dequeued\n",dequeue());
		}
	}
	for(i=0;i<n;i++)
		printf("%d ",e[i]);
	printf("The maxflow is %d\n",e[n-1]);
}

void main()
{
	printf("Enter the number of cities\n");
	int n;
	scanf("%d",&n);
	cap=(int **)malloc(n*sizeof(int *));
	G=(int **)malloc(n*sizeof(int *));
	cf=(int **)malloc(n*sizeof(int *));
	int i,j,k;
	for(i=0;i<n;i++)
		{
			cap[i]=(int *)malloc(n*sizeof(int));
			G[i]=(int *)malloc(n*sizeof(int));
			cf[i]=(int *)malloc(n*sizeof(int));
		}
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
							cap[i][k]=2*count;
							G[i][k]=k;
						}
					for(j=0;j<26;j++)
						ch2[j]=0;
						}
					if(i==k)
						cap[i][k]=0;
				}
			for(j=0;j<26;j++)
				ch1[j]=0;
		}
	for(i=1;i<n-1;i++)
		{
			int count1=0,count2=0;
			for(j=1;j<n-1;j++)
			{
				if(cap[j][i]==0)
					count1++;
				if(cap[i][j]==0)
					count2++;
			}
			if(count1==n-2)
				{
					cap[0][i]=20;
					G[0][i]=i;
				}
			if(count2==n-2)
				{
					G[i][n-1]=n-1;
					cap[i][n-1]=20;
				}
		}
	printMatrix(n,cap);
	/*int max_flow=maxflow(n);*/
	maxflow(n);
	return;
}
















