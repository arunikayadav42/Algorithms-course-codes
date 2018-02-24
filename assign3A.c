#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int *a;
//for setting the pivot to the correct position in the array without arranging the array
//start->start of the subarray of array a
//end->end of the subarray of array a
int partition(int start,int end)
	{
		/* pivot is the element such that all elements less than that are towards the left of the array and all elements greater than that are towards the right */
		int pivot=a[end];
		/*pindex to find the index of the pivot element*/
		int pindex=start;
		int i;
		/*traversing the subarray from the current start index to the current last index-1 as the last index has the pivot itself*/
		for(i=start;i<=end-1;i++)
			{
				/*if the current element is less than pivot it goes to the left and pindex is incremented*/
				if(a[i]<pivot)
				{
					int temp=a[i];
					a[i]=a[pindex];
					a[pindex]=temp;
					pindex=pindex+1;
				}
				/*if the current element is greater than the pivot it is not swapped and pindex also does not get incremented*/
			}
			/*if the element at pindex is greater than the pivot,they are swapped*/
			if(a[pindex]>pivot)
			{
				int temp=a[pindex];
				a[pindex]=a[end];
				a[end]=temp;
			} 
		return pindex;
	}	
int find_median(int start,int end,int k)
	{
		/*if start > end then that will be an invalid subarray,start<'='end because when one element is left that will be the median*/
		if(start<=end)
			{
				/*setting the seed value so that each time a different random element is picked up from the array*/
				srand(time(NULL));
				int p;
				/*q gives the number of elements in the current subarray*/
				int q=end-start+1;
				/*the random number is generated until it is less than  or equal to the current end index*/
				while(1)
					{
						/*rand()%q+start +start so that the generated number is >=start and less than equal to end index*/
						p=rand()%q+start;
						if(p<=end)
						break;
					}
				/*swapping the random pivot with the last element in the subarray to make partitioning easier*/
				int temp=a[p];
				a[p]=a[end];
				a[end]=temp;
				int i;
				/*pindex gives the index of the pivot element in the array a i.e. the index is with respect to the original array*/
				int pindex=partition(start,end);
				/*if the pivot index equals to n/2 or (n+1)/2 ,the median is found { k=n/2 or k=(n+1)/2 }*/
				if(pindex==k)
					return a[k];
				else if(pindex<k)
					{
						/*median is present in the right part of the array after the pivot,start now equals pindex+1 and end remains the same*/
						find_median(pindex+1,end,k);
					}
				else if(pindex>k)
					{
						 /*median is present in the left part of the array before the pivot,end now equals pindex-1 and start remains the same*/
						find_median(start,pindex-1,k);
					}
			}
	}
main()
        {
                int n,i;
                printf("enter n\n");
                scanf("%d",&n);
                a=(int *)malloc(sizeof(int)*n);
                int k;
		//accepting the elements from the user
                for(i=0;i<n;i++)
                        {
                                printf("enter the element\n");
                                scanf("%d",&a[i]);
                        }
                        
                        if(n%2==0)
                        	k=n/2;
                        else
                        	k=(n+1)/2;
                        printf("the median is %d\n",find_median(0,n-1,k));
        }

