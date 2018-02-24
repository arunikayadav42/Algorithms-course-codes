#include <stdio.h>
#include <stdlib.h>
#define INF 1000000000
int ithsmallestelement(int *a,int l,int r,int i);
/*to sort the subarrays using insertion sort which is linear for small number of elements*/
int findMedian(int *a,int n)
	{
		int i,j;
		//printf("\n");
		for(i=1;i<n;i++)
		{
			j=i-1;
			int key=a[i];
			while(j>=0 && a[j]>key)
			{
				a[j+1]=a[j];
				j--;
			}
			a[j+1]=key;
		}
		//printf("After sorting the array \n");
		//for(i=0;i<n;i++)
		//	printf("%d\t",a[i]);
		return a[(n)/2];/*returning the median*/
	}
	/*partition function to find the index of the pivot*/
int partition(int *a,int l,int r,int x)
{
	int i;
	//printf("pivot : %d\n",x);
	/*searching for the position of the medians of medians in the array*/
	for(i=l;i<=r;i++)
	{
		if(a[i]==x)
			break;
	}
	//if(i>r)
	//	return ithsmallestelement(a,l,r,(r-l+1)/2);
	int temp=a[i];
	a[i]=a[r];
	a[r]=temp;
	int j=l-1;
	for(i=l;i<r;i++)
	{
		if(a[i]<a[r])
		{
			j++;
			temp=a[j];
			a[j]=a[i];
			a[i]=temp;
		}
	}
	temp=a[j+1];
	a[j+1]=a[r];
	a[r]=temp;
	//printf("after partitioning the array\n");
	//for(i=l;i<=r;i++)
	//	printf("%d  ",a[i]);
	//printf("\n");
	return j+1;/*returning the index of the pivot*/
}
/*to find the ith smallest element in the array*/
int ithsmallestelement(int *a,int l,int r,int i)
	{
		int n=r-l+1,m=0;
		int j,k=0;
		int *median;
		/*dividing the array into ceil[n/5] groups and sorting them and finding their medians*/
		if(i>0 && i<=n)
			{
				median=(int *)malloc((((n+4)/5))*sizeof(int));
				for(j=0;j<(n/5);j++)
					{
						//printf("\n");
								/*for(m=k;m<=k+4;m++)
									printf("%d\t",a[m]);
								printf("\n");*/
								median[j]=findMedian(a+l+5*j,5);
					}	
					if(5*j<n)
					{
						median[j]=findMedian(a+l+5*j,n%5);
						j++;
					}
				/*	printf("\n");
				for(j=0;j<(n/5)+1;j++)
					printf("%d \n",median[j]);*/
					//printf("\nj : %d \n",j);
					/*finding the medians of medians using the function recursively*/
					int x=(j==1)?median[j-1]:ithsmallestelement(median,0,j-1,j/2);
					//printf("x : %d l : %d r :%d \n",x,l,r);
					int q=partition(a,l,r,x);/*partitioning the array around the medians of medians*/
					//printf("q : %d\n",q);
					k=q-l+1;
					//printf("k  : %d ,i : %d \n",k,i);
					/*if the index matches element found else execute else if*/
					if(i==k)
					{
						return a[q];
					}
					else if(i<k)
					{
						//printf("Entered first if else");
						ithsmallestelement(a,l,q-1,i);
					}
					else if(i>k)
					{
						//printf("Entered second else if");
						ithsmallestelement(a,q+1,r,i-k);
					}
			}
			//return max;
	} 
void main()
	{
		int n;
		printf("Enter the number of elements\n");
		scanf("%d",&n);
		int j;
		int *a;
		a=(int *)malloc(n*sizeof(int));
		for(j=0;j<n;j++)
			{
				printf("Enter the elements\n");
				scanf("%d",&a[j]);
			}
		printf("Enter the value of i\n");
		int i;
		scanf("%d",&i);
		if(i>n)
		{
			printf("Wrong input\n");
			exit(0);
		}
		/*printing the ith smallest element*/
		int p=ithsmallestelement(a,0,n-1,i);
		printf("\n%dth smallest element : %d\n",i,p);
		//printf("ith smallest element is : %d\n",i);
	}
