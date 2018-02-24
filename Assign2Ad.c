#include <stdio.h>
int min,max;
void maxmin(int a[],int m,int n)
{
	printf("m=%d n=%d\n",m,n);
	if(n<=m)
		return;
		else
		{
	if(max<a[n-1])
		max=a[n-1];
	else if(min>a[n-1])
		min=a[n-1];
		printf("max:%d\n",max);
		printf("min:%d\n",min);
		n--;
	maxmin(a,m,n);
	}
}
int *sort(int a[],int i,int n,int size)
{
	if(i>n || n<0)
		return a;
			max=-10000;
		min=10000;
	maxmin(a,i,n);
	int j,temp;
	for(j=i;j<n;j++)
	{
		if(a[j]==min)
			{
				temp=a[i];
				a[i]=min;
				a[j]=temp;
			}
		if(a[j]==max)
			{
				temp=a[size-i-1];
				a[size-1-i]=max;
				a[j]=temp;
			}
	}
	for(j=0;j<size;j++)
	{
		printf("%d->",a[j]);
	}
	i++;
	n--;
	sort(a,i,n,size);
}
main()
{
	int n,i,j;
	printf("Enter the number of elements in the array\n");
	scanf("%d",&n);
	int a[n];
	for(i=0;i<n;i++)
	{
		printf("enter the element\n");
		scanf("%d",&a[i]);
	}
	int *b=sort(a,0,n,n);
	printf("\n");
	for(i=0;i<n;i++)
	{
		printf("%d->",b[i]);
	}
}
