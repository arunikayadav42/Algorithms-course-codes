#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int **adj;
int *cost;
char *name,*name1,*name2;
char **name3;
int min;
//function to calculate the cost for each permutation
int minCost(char *s)
{
	int i,j,count=0,index1=0,index2=0;
	//finding the original indexes of the characters in the permutted word in the orginal word
	for(i=0;i<=6;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(name1[j]==s[i])
				index1=j;
			if(name1[j]==s[i+1])
				index2=j;
		}
		count+=adj[index1][index2];//calculating the cost each time
	}
	/*printf("cost : %d \n",count);*/
	//update the minimum if required
	if(min>count)
		{
			min=count;
			for(j=0;j<8;j++)
			{
				name2[j]=s[j];//obtain the corresponding word order
			}
		}
	/*printf("min : %d \n",min);*/
	return count;
}
//function to swap the characters
void swap(char *a,char *b)
{
	char temp=*a;
	*a=*b;
	*b=temp;
}
//function to find all the permutations of a given word
void permute(char *a,int l,int r)
{
	int i;
	/*printf("entered permute\n");*/
	if(l==r)
	{
		int p=minCost(a);//calling mincost function for each permutation

	}
	else
	{
		for(i=l;i<=r;i++)
		{
			swap(a+l,a+i);
			permute(a,l+1,r);
			swap(a+l,a+i);
		}
	}
}
void main()
{
	int n=8;
	name=(char *)malloc((n+1) * sizeof(char));//name array to store the names all in small
	name1=(char *)malloc((n+1) * sizeof(char));//name array to compare and help store the current word order in the function mincost
	name2=(char *)malloc((n+1) * sizeof(char));//name array to store the current permutation with minimum cost
	name3=(char **)malloc((n+1) * sizeof(char *));//2-D array to store the full names of the cities
	
	int i,j,k;
	for(i=0;i<n;i++)
	{
		name3[i]=(char *)malloc((100)*sizeof(char));//allocating memory
	}
	name[0]='C';
	name[1]='K';
	name[2]='I';
	name[3]='B';
	name[4]='N';
	name[5]='R';
	name[6]='G';
	name[7]='H';
	name1[0]='C';
	name1[1]='K';
	name1[2]='I';
	name1[3]='B';
	name1[4]='N';
	name1[5]='R';
	name1[6]='G';
	name1[7]='H';
	name2[0]='C';
	name2[1]='K';
	name2[2]='I';
	name2[3]='B';
	name2[4]='N';
	name2[5]='R';
	name2[6]='G';
	name2[7]='H';
	adj=(int **)malloc((n)*sizeof(int *));//defining the cost matrix
	for(i=0;i<n;i++)
	{
		adj[i]=(int *)malloc((n)*sizeof(int));
		adj[i][i]=0;
	}
	 adj[0][1] = 1400;
  	adj[0][2] = 1200;
  	adj[0][3] = 300;
  	adj[0][4] = 900;
  	adj[0][5] = 1300;
  	adj[0][6] = 1900;
  	adj[0][7] = 500;
  	adj[1][2] = 1300;
  	adj[1][3] = 1500;
  	adj[1][4] = 1000;
  	adj[1][5] = 300;
  	adj[1][6] = 500;
  	adj[1][7] = 1200;
  	adj[2][3] = 1100;
  	adj[2][4] = 400;
  	adj[2][5] = 1000;
  	adj[2][6] = 1600;
  	adj[2][7] = 700;
  	adj[3][4] = 900;
  	adj[3][5] = 1400;
  	adj[3][6] = 2000;
  	adj[3][7] = 500;
  	adj[4][5] = 700;
  	adj[4][6] = 1400;
  	adj[4][7] = 400;
  	adj[5][6] = 700;
  	adj[5][7] = 1000;
  	adj[6][7] = 1700;
	for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
				{
					adj[j][i]=adj[i][j];
				}
		}
		min=INF;
		permute(name,0,7);//calling the permute function
		/*for(i=0;i<n;i++)
			printf("%c->",name2[i]);*/
		//printing the schedule of the matches
		printf("THE SCHEDULE TO BE FOLLOWED IS \n:");
		for(i=0;i<n;i++)
		{
			if(name2[i]=='C')
				strcpy(name3[i],"MA Chidambaram Stadium, Chennai");
			if(name2[i]=='K')
				strcpy(name3[i],"Eden Gardens, Kolkata");
			if(name2[i]=='I')
				strcpy(name3[i],"Holkar Cricket Stadium, Indore");
			if(name2[i]=='B')
				strcpy(name3[i],"M.Chinnaswamy Stadium, Bengaluru");
			if(name2[i]=='N')
				strcpy(name3[i],"Vidarbha Cricket Association Ground, Nagpur");
			if(name2[i]=='R')
				strcpy(name3[i],"JSCA International Stadium Complex, Ranchi");
			if(name2[i]=='H')
				strcpy(name3[i],"Rajiv Gandhi International Stadium, Hyderabad");
			if(name2[i]=='G')
				strcpy(name3[i],"Barsapara Cricket Stadium, Guwahati");
		}
		//printing the final result with cost
		for(i=0;i<n;i++)
			printf("%s->\n",name3[i]);
		printf("\nThe minimum cost is : %d\n",min);
	}