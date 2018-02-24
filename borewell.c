#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define min(a,b) (((a)<(b))?(a):(b))
int n;

//this stores the frequency of each letter of string in count array
int* freq_bucket(char* string)
{
        int* count=(int*)malloc(26*sizeof(int));
         int i;
         for(i=0;i<26;i++)
                count[i]=0;

        for(i=0;string[i] != '\0';i++)
        {
      // Considering string has characters from 'a' to 'z' only
         count[string[i]-'a']++;
   }

   return count;
}
//this returns no. of common characters in 2 strings str1 and str2
int match_com(char* str1,char* str2)
{
        int* lfreq1=freq_bucket(str1);
        int* lfreq2=freq_bucket(str2);

        int i,common=0;
        for(i=0;i<26;i++)
                common+= min(lfreq1[i],lfreq2[i]);

        return common;
}
//this returns 1 if the edge exists(are neighbours) between the two owner names s1 and s2 else 0
int isedge(char* s1,char* s2)
{

                int l1=strlen(s1);
                int l2=strlen(s2);

        if(abs(l1-l2)==1)
        {
        	if(match_com(s1,s2)==strlen(s1)-1||(match_com(s1,s2)==strlen(s1)))
                return 1;
        }
        else
        return 0;
}

int calc_w(char* s1)
{
        int l1=strlen(s1),i,w1=0;
        for(i=0;s1[i]!='\0';i++)
                w1+=s1[i];
        return w1;
}

int w_edge(char* s1,char* s2)
{

        int w=(calc_w(s1) - calc_w(s2));
        if(w<0)
        	w = -(w);
        return w;
}

float w_vertex(char* s1)
{
                int l1=strlen(s1);
               float w=(float)calc_w(s1)/l1;

                return w;
}

int** creategraph(char** word,int n)
{
        int i,j;
        int** gr=(int**)malloc((n+1)*(sizeof(int*)));

        for(i=1;i<=n;i++)
        {
                gr[i]=(int*)malloc((n+1)*(sizeof(int)));
                for(j=1;j<=n;j++)
                {
                                if(i!=j && (isedge(word[i],word[j])==1))
                                gr[i][j]=w_edge(word[i],word[j]);
                                else
                                gr[i][j]=0;
                }

        }
        return gr;
}

int min_key(float key[],int mstset[])
{
        int imin,min=100000;    //10^5 as infinity
        int v;
        for(v=1;v<=n;v++)
                if(mstset[v]==0 && min>=key[v])
                        {
                                min=key[v];imin=v;
                        }
        return imin;
}

void printsol(float key[],int parent[],int** gr)
{
	int i;
	printf("water supply\n");
   for ( i = 1; i <=n; i++)
   {
   	if(parent[i]==i)
   	printf("%d borewell at cost %f\n",i,key[i]);
   	else
      printf("%d -pipeline from %d  at cost %d \n", i,parent[i], gr[i][parent[i]]);
	}
}

void primmst(int** gr,char** word)
{
        int mstset[n+1],parent[n+1];           
		float key[n+1];
        int i;
        for(i=0;i<=n;i++)
        {
                key[i]=w_vertex(word[i]);
                mstset[i]=0;             // Initialize all keys as vertex weight(borewell) and mstset[] as 0
                parent[i]=i;
        }

    int v,u;
        for(i=1;i<=n-1;i++)
        {
                u=min_key(key,mstset);    // Pick the minimum weight vertex from the set of vertices not      
				 // yet processed. u is always equal to src with min cost of borewell in first iteration.
                mstset[u]=1;
                for(v=1;v<=n;v++)
                {
                        
                        if(!mstset[v] && gr[u][v] && key[v]>gr[u][v])
                        {
                                key[v]=gr[u][v];
                                parent[v]=u;
                        }
                }
        }
            printsol(key,parent,gr);
            float tot=0;
            for(i=1;i<=n;i++)
            tot+=key[i];
            
            printf("\n total min. cost:%f",tot);
}

int main()
{
        int i,j;
        printf("enter n(no. of house owners):");
        scanf("%d",&n);

        char** word=(char**)malloc((n+1)*(sizeof(char*)));
        word[0]=(char*)malloc(6*sizeof(char));
        for(i=1;i<=n;i++)
        {
                word[i]=(char*)malloc(6*sizeof(char));  
                printf("enter name%d",i);                                       //,all in lowercase
                scanf("%s",word[i]);

        }
        printf(" graph :adjacency matrix\n");
        int** gr=creategraph(word,n);
        for(i=1;i<=n;i++)
        {
                for(j=1;j<=n;j++)
                        printf("%d ",gr[i][j]);
                        printf("\n");
        }

		primmst(gr,word);
		
        return 0;
}

