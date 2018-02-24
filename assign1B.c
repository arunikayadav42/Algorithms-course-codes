#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int max1;/*finding the maximum digit in the number*/
//to find the maximum of two numbers
int max(int x,int y)
        {
              if(x>y)
                return x;
              else
                return y;
        }
/*find the largest sum*/
int findLargest(int a[],int size)
        {
        		/*array to store the largest sum*/
              int *sum=(int *)malloc(sizeof(int)*size);
              int i;
              /*finding the maximum sum such that no two elements are adjacent*/
              for(i=0;i<size;i++)
              {
              	if(i==0)
              	sum[0]=a[0];
              	else if(i==1)
              	sum[1]=max(sum[0],a[1]);
              	else
              	sum[i]=max(sum[i-2]+a[i],sum[i-1]);
			  }
			  /*returning the maximum sum*/
			  return sum[size-1];
        }
/*finding the largest digit in the given sum*/
void LargeDigit(int p)
        {
                if(p==0)
                        return;
                else
                        {
                                int n=p%10;
                                if(max1<n)
                                        max1=n;
                                LargeDigit(p/10);
                        }
        }
main()
        {
                int n,i;
                printf("Enter the number of boxes");
                scanf("%d",&n);
                int a[n];
                for(i=0;i<n;i++)
                        {
                                printf("enter the number of chocolates in the box\n");
                                scanf("%d",&a[i]);
                        }
                int p=findLargest(a,n);
                printf("%d\n",p);/*printing the maximum sum*/
                max1=p%10;
                LargeDigit(p/10);
                printf("%d",max1);/*printing the maximum digit in the sum*/
        }

