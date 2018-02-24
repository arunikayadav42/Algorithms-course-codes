#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000000000

int n;
int **adj;
char **name;

int min(int a,int b){												//function to find minimum of two numbers
	if(a<b) return a;
	else return b;
}

int setselfcost(char *name){
	int i,sum=0;
	for(i=0;i<strlen(name);i++){
		sum=sum+name[i];
	}
	sum=sum/strlen(name);
	return sum;
}

int mod(int x){
	if(x<0){
		return (-1*x);
	}
	else return x;
}

int checkconnected(char *a,char *b){								//function to check wheter two nodes with given strings are connected or not
	int i,count=0;
	int n[26]={0},m[26]={0};
	int x,sum1=0,sum2=0;

	x=min(strlen(a),strlen(b));

	for(i=0;i<strlen(a);i++){
		n[a[i]-97]++;
		sum1=sum1+a[i];
	}
	for(i=0;i<strlen(b);i++){
		m[b[i]-97]++;
		sum2=sum2+b[i];
	}
/*	for(i=0;i<26;i++){
		printf("%c\t%d\t%d\n",i+97,n[i],m[i]);
	}*/
	for(i=0;i<26;i++){
		count=count + min(m[i],n[i]);
	}
/*	printf("Common characters = %d\n",count);
	printf("SUM 1 : %d\n",sum1);
	printf("SUM 2 : %d\n",sum2);*/

	if(count==x && mod(strlen(a)-strlen(b))==1){
		return mod(sum1-sum2);
	}
	else return 0;
}

int minKey(int *key, int *incSet){
   int min = MAX, mind;
 
    for (int i = 0; i < n; i++)
    	if (incSet[i] == 0 && key[i] < min){
        min = key[i];
        mind = i;
    	}
 
   return mind;
}
 
int printMST(int *parent, int **graph){
   printf("Edge\t\t\t\tWeight\n");
   for (int i = 1; i < n; i++)
      printf("%s - %s\t\t\t%d \n", name[parent[i]], name[i], graph[i][parent[i]]);
}

void primMST(int **graph){
    int parent[n];
   	int key[n];
    int incSet[n];

    for (int i = 0; i < n; i++){
        key[i] = MAX;
        incSet[i] = 0;
    }
 
    key[0] = 0;
    parent[0] = -1;
 
    for (int count = 0; count < n-1; count++){
        int u = minKey(key, incSet);
        incSet[u] = 1;
        for (int v = 0; v < n; v++)
          	if (graph[u][v]!=0 && incSet[v]==0 && graph[u][v]<key[v]){
                parent[v]  = u;
                key[v]=graph[u][v];
            }
/*            printf("AFTER ROUND %d\n",count);
    		for(int i=0;i<n;i++){
				printf("%d\t",key[i]);
			}
			printf("\n\n");*/
     	}

    printf("The minimum cost will be acquired when we connect : \n\n\n");
    printMST(parent,graph);
}

int main(){
	int i,j;
	printf("Enter the number of houses in the city :");
	scanf("%d",&n);
	n=n+1;
	name=(char **)malloc(n*sizeof(char *));
	for(i=0;i<n;i++){
		name[i]=(char *)malloc(20 *sizeof(char));
	}
	adj=(int **)malloc(n*sizeof(int *));
		for(i=0;i<n;i++){
			adj[i]=(int *)calloc(n,sizeof(int));
		}
	printf("Enter the names of the owners : \n");
	for(i=1;i<n;i++){
		scanf(" %s",name[i]);
	}
	strcpy(name[0],"borewell");

/*	for(i=0;i<n;i++){
		printf(" %s",name[i]);
	}*/
	printf("\n\n");

	for(i=1;i<n;i++){
		adj[i][0]=adj[0][i]=setselfcost(name[i]);
	}
	for(i=1;i<n;i++){
		for(j=1;j<=i;j++){
			if(i!=j){
				adj[i][j]=adj[j][i]=checkconnected(name[i],name[j]);				//checking which vertices are connected and which are not
			}
			else if(i==j) adj[i][j]=0;
		}
	}

/*	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d\t",adj[i][j]);
		}
		printf("\n");
	}*/

	primMST(adj);

}