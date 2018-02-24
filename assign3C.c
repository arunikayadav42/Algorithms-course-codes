#include <stdio.h>
#include <stdlib.h>

int left_sum=0,right_sum=0,across_array_sum=0;

/*calculating the left array sum from starting from the mid of the array to the 0 index*/
//leftsum starts
void leftsum(int a[],int i,int n,int sum)
        {
		/*if the start index becomes greater than the end index ,no more elements left,hence return*/
                if(n<i)
                        return;
		/*calculate the sum of consecutive elements*/
                sum+=a[n];
		/*left_sum only gets changed if it is less than the sum above*/
                if(left_sum<sum)
                        left_sum=sum;
		/*the last index is decremented on each function call*/
                n--;
                leftsum(a,i,n,sum);
        }
//leftsum ends

/*calculating the right array sum  starting from the mid of the array to the last index*/
//rightsum starts
void rightsum(int a[],int n,int size,int sum)
        {
		/*if the start index {n} becomes equal to the size of the array ,no more elements left,hence return*/
                if(n==size)
                        return;
		/*calculate the sum of consecutive elements*/
                sum+=a[n];
		 /*right_sum only gets changed if it is less than the sum above*/
                if(right_sum<sum)
                        right_sum=sum;
		/*the start index gets incremented on each function call*/
                n++;
                rightsum(a,n,size,sum);
        }
//rightsum ends

//max to find the maximum of two numbers
int max(int a,int b)
	{
		if(a>b)
			return a;
		else
			return b;
	}
//max ends

main()
        {
                int i,n;
                printf("Enter the size of array\n");
                scanf("%d",&n);
                int a[n];
		//accepting the array elements
                for(i=0;i<n;i++)
                        {
                                printf("Enter the value of n\n");
                                scanf("%d",&a[i]);
                        }
		
                int mid=n/2,sum=0;
		//leftsum is called
                leftsum(a,0,mid,sum);
                sum=0;
		//rightsum is called
                rightsum(a,mid+1,n,sum);
                sum=0;
		//across_array_sum will be the sum of the leftsum and rightsum
                across_array_sum=left_sum+right_sum;
		//maximum of the three is printed
                printf("Maximum subarray sum = %d\n",max(max(left_sum,right_sum),across_array_sum));   	   
        }

