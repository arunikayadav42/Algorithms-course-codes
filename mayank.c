#include<stdio.h>
#include<stdlib.h>

int **adj;															//adjaency matrix
int n,e;															//number of vertices and edges global
int *deg;															//degree array 
int *ver;															//vertex category array
int *visit;															//visit array
char **nod;
int flag;															//path matrix

int min(int a,int b){												//function to find minimum of two numbers
	if(a<b) return a;
	else return b;
}

int checkconnected(char *a,char *b){								//function to check wheter two nodes with given strings are connected or not
	int i,count=0;
	int n[26]={0},m[26]={0};
	for(i=1;i<5;i++){
		n[a[i]-97]++;
	}
	for(i=0;i<5;i++){
		m[b[i]-97]++;
	}
	for(i=0;i<26;i++){
		count=count + min(m[i],n[i]);
	}
	if(count==4){
		return 1;
	}
	else return 0;
}

void DFS(int vertex,int num){										//function to check and assign connected component numbers to vertices
	int i;
	visit[vertex]=1;
	ver[vertex]=num;
	for(i=0;i<n;i++){
		if(adj[vertex][i]!=0 && visit[i]==0){
			DFS(i,num);
		}
	}
}

void DFSfindcycle(int vertex){										//function to find whether the graph is cyclic or not
	int i;
	visit[vertex]=1;
	for(i=0;i<n;i++){
		if(adj[vertex][i]!=0 && visit[i]==1 && i!=vertex){
			flag=1;
			}
		if(adj[vertex][i]!=0 && visit[i]==0){
			DFSfindcycle(i);
		}
	}
}

void printmatrix(){													//function to print the adjacency matrix
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",adj[i][j]);
		}
		printf("\n");
	}
}

int main(){															//main function
	int i,j,x,y,num=1;
	printf("Enter the number of vertices/nodes : ");				//user input
	scanf("%d",&n);

	int **path=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++){
		path[i]=(int *)calloc(n,sizeof(int));
	}
	deg=(int*)calloc(n,sizeof(int));
	ver=(int*)calloc(n,sizeof(int));
	visit=(int*)calloc(n,sizeof(int));
	adj=(int**)malloc(n*sizeof(int*));
	for(i=0;i<n;i++){
		adj[i]=(int *)calloc(n,sizeof(int));
	}
	nod=(char **)malloc(n*sizeof(char *));
	for(i=0;i<n;i++){
		nod[i]=(char *)malloc(5*sizeof(char));
	}
	printf("Please enter the nodes : \n");							//user input of nodes
	for(i=0;i<n;i++){
		scanf(" %s",nod[i]);
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i!=j){
				adj[i][j]=checkconnected(nod[i],nod[j]);				//checking which vertices are connected and which are not
			}
			if(i==j) adj[i][j]=0;
			if(adj[i][j]==1){
				deg[j]++;
			}
		}
	}
    flag=0;

	printf("The degree set is :\n");
	for (i = 0; i < n; ++i){
		printf("%d ",deg[i]);}
	printf("\n\n\n");
	printmatrix();
	printf("\n");


	for(i=0;i<n;i++){												//finding if cycle exist in any connected component or not
		if(visit[i]==0){
			DFSfindcycle(i);
			for(j=0;j<n;j++) visit[j]=0;
		}
	}
	if(flag==1){printf("\n\nThe graph is CYCLIC\n");}
	else printf("\n\nThe graph is ACYCLIC\n");
	
	for (i = 0; i < n; i++){										// reset visit value to 0
		visit[i]=0;
	}
/*
	for(i=0;i<n;i++){												//assigning numbers to vertices of same components
		if(visit[i]==0){
			DFS(i,num);n
			num++;}
	}*/

/*	printf("The vertex set is : \n");
	for (i = 0; i < n; ++i){
		printf("%d\t",ver[i]);
	}*/

	for(i=0;i<n;i++){
	DFSfindcycle(i);												//if vertices belong to same conncted component path exists otherwise not 
		for(j=0;j<n;j++){
			if(visit[j]==1)
				path[i][j]=1;
		}
		path[i][j]=visit[j];
		for (j = 0; i < n; i++){										// reset visit value to 0
			visit[i]=0;
		}
		
	}
	printf("\n\nTHE PATH MATRIX IS : \n\n" );						//printing the path matrix

	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
		printf("%d ",path[i][j] );}
	printf("\n");
	}

}