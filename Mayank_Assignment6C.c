#include<stdio.h>
#include<stdlib.h>


int s[1000],x=0;


int min(int a,int b){												//function to return lesser of two numbers
	if (a<=b) return a;
	else if(a>=b) return b;
}

int minimumdifference(int *a,int sum,int i,int n,int **dp){			//function to find the minimum difference between sum of two sets
	if (sum-(2*a[i])<0)	{
		dp[sum][i]=sum;
		return sum;}
	if(dp[sum][i]!= -1){											//if the element of dp is already stored use it
		return dp[sum][i];}
		else{
		int res=min(minimumdifference(a,sum-(2*a[i]),i+1,n,dp),minimumdifference(a,sum,i+1,n,dp));				//finding solution using recursion top down and storing it in dp a every step
		dp[sum][i]=res;
		return res;}												//returning the answer
}


void trace(int *a,int **dp,int n,int ans,int sum){					//function to traceback the path
	int i,k=0,j=0;
	while(sum!=ans && sum>=0){		
		for(i=k;i<n;i++){											//checking which element is taken
			//printf("%d|%d\t%d|%d\t",sum,i,(sum-(2*a[i])),i+1);
			if(dp[sum][i]==dp[(sum-(2*a[i]))][i+1])
				{				//repeating the subproblems using dp
				s[x]=a[i];											//storing solution for the set 1 in s[x]
				//printf("yes\n");
				k=i+1;
				x++;
				break;
				}//	printf("no\n");
		}sum=(sum-(2*a[i]));										//decreasing the sum by twice that element as it has been taken in other set
	}
}

int main(){															//main function	
	int i,j,n;
	printf("Enter the number of elements :");						//user input
	scanf("%d",&n);
	int *a=malloc(n*sizeof(int));
	printf("Enter the elements :\n");								//user input
	for(i=0;i<n;i++){
  	scanf("%d",&a[i]);}
	int sum=0;
	for(i=0;i<n;i++){												//finding sum of all elements
		sum=sum+a[i];
	}
	int **dp=(int **)malloc((sum+1)*sizeof(int*));					//allocating dp space
	for(i=0;i<=sum;i++){
		dp[i]=(int*)malloc((n+1)*sizeof(int));
	} 

	for(i=0;i<=sum;i++){											//initializig dp to -1
		for(j=0;j<=n;j++){
			dp[i][j]=-1;
		}
	}
	int res=minimumdifference(a,sum,0,n,dp);						//finding minimum difference in result

	trace(a,dp,n,res,sum);

 	printf("\n");
/* 	for(i=0;i<=n;i++){												//dp matrix
 		for(j=0;j<=sum;j++){
 			printf("%d\t",dp[j][i]);
 		}
 		printf("\n");
 	}*/

	printf("Set 1:  ");												//printing set 1
	for(i=0;i<x;i++){
		printf("%d  ",s[i]);
	}
	int flag,k=0;	
	printf("\nSet 2:  ");											//finding and printing set 2
	for(i=0;i<n;i++){flag=0;
		for(j=k;j<x;j++){
			if(a[i]==s[j]){
				flag=1;
				k=j+1;
				break;
			}
		}if(flag!=1){
			printf("%d  ",a[i]);}
	}
	printf("\n|Set1 - Set2| = %d\n\n",res);							//printing the result

	

}
