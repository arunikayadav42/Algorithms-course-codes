#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

int **adj;
int *visited_cities;
char *name,*name1,*name2;
char **name3;
int min,cost,limit;

int tsp(int c)
{
      int count, nearest_city = 999;
      int minimum = 999, temp;
      for(count = 0; count < limit; count++)
      {
            if((adj[c][count] != 0) && (visited_cities[count] == 0))
            {
                  if(adj[c][count] < minimum)
                  {
                        minimum = adj[count][0] + adj[c][count];
                  }
                  temp = adj[c][count];
                  nearest_city = count;
            }
      }
      if(minimum != 999)
      {
            cost = cost + temp;
      }
      return nearest_city;
}
 
void minimum_cost(int city)
{
      int nearest_city;
      visited_cities[city] = 1;
      printf("%d ", city + 1);
      nearest_city = tsp(city);
      if(nearest_city == 999)
      {
            nearest_city = 0;
            printf("%d", nearest_city + 1);
            cost = cost + adj[city][nearest_city];
            return;
      }
      minimum_cost(nearest_city);
}


void main()
{
	int n=8;
	name=(char *)malloc((n+1) * sizeof(char));//name array to store the names all in small
	name1=(char *)malloc((n+1) * sizeof(char));//name array to compare and help store the current word order in the function mincost
	name2=(char *)malloc((n+1) * sizeof(char));//name array to store the current permutation with minimum cost
	name3=(char **)malloc((n+1) * sizeof(char *));//2-D array to store the full names of the cities
	visited_cities=(int *)malloc((n)*sizeof(int));
	int i,j,k;
	for(i=0;i<n;i++)
	{
		name3[i]=(char *)malloc((100)*sizeof(char));//allocating memory
		visited_cities[i]=0;
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
	 minimum_cost(0);
     printf("\n\nMinimum Cost: \t");
     printf("%d\n", cost);
     return;
	}