#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <inttypes.h>
//for setting the pivot to the correct position in the array without arranging the array
//start->start of the subarray of array a
//end->end of the subarray of array a
int partition(long long *a,long long start,long long end,int pivottype)
        {
                /* pivot is the element such that all elements less than that are towards the left of the array and all elements greater than that are towards the right */
                long long pivot=a[end];
                /*pindex to find the index of the pivot element*/
                long long pindex=start;
                long long j;
                /*traversing the subarray from the current start index to the current last index-1 as the last index has the pivot itself*/
                for(j=start;j<=end-1;j++) 
                {
                        if(a[j]<=pivot)
                        {
                                long long temp=a[j];
                                a[j]=a[pindex];
                                a[pindex]=temp;
                                pindex++;
                        }
                        /*if the current element is greater than the pivot it is not swapped and pindex also does not get incremented*/
                }
                /*if the element at pindex is greater than the pivot,they are swapped*/
                if(a[pindex]>pivot)
                        {
                                long long temp=a[pindex];
                                a[pindex]=pivot;
                                pivot=temp;
                        }
                return pindex;
        }
long long *quicksort1(long long *a,long long start,long long end,int pivottype)
        {
                /*if start > end then that will be an invalid subarray*/
                if(start<=end)
                {
                        /*for the case when the pivot element is the element at the start index*/
                        if(pivottype==0)
						   {
                                        /*the element at the start index is swapped with the element at the end index to make partitioning easier*/
                                        long long temp=a[start];
                                        a[start]=a[end];
                                        a[end]=temp;
                                }
                        /*for the case when the pivot element is randomly selected element from the array*/
                        else if(pivottype==1)
                                {
                                        srand(time(NULL));
                                        long long p;
                                        /*q contains the total number of elements in the current subarray*/
                                        long long q=end-start+1;
                                        while(1)
                                                {
                                                        //selecting a random index from the array
                                                        p=rand()%q+start;
                                                        if(p<=end)
                                                                break;
                                                }
                                        //swapping this random element with the last element to make partitioning easier
                                        long long temp=a[p];
                                        a[p]=a[end];
                                        a[end]=temp;
                                }
                        /*for the case when the pivot element is randomly selected element from the array*/
                        else if(pivottype==2)
                                {
                                        /*selecting the indices r,s and t s required in the question*/
                                        long long r=start;
                                        long long s=(end-start+1)/2;
                                        long long t=end-1;
                                        long long p=(r+s+t)/3;
                                        //swapping this random element with the last element to make partitioning easier
                                        r=a[p];
                                        a[p]=a[end];
                                        a[end]=r;
                                }
						 /*for the case when the pivot element is randomly selected element from the array*/
                        else if(pivottype==3)
                                {
                                        /*selecting the indices r,s and t s required in the question*/
                                        long long r=(end-start+1)/4;
                                        long long s=(end-start+1)/2;
                                        long long t=((end-start+1)*3)/4;
                                        long long p=(r+s+t)/3;
                                        //swapping this random element with the last element to make partitioning easier
                                        r=a[p];
                                        a[p]=a[end];
                                        a[end]=r;
                                }
                        /*here q stores the index of the final index of the pivot*/
                        long long q=partition(a,start,end,pivottype);
                        /*calling the quicksort function for sorting the array and subsequent subarrays*/
                        quicksort1(a,start,q-1,pivottype);
                        quicksort1(a,q+1,end,pivottype);
                }
                else//base condition
                        return a;
        }
/*this function calls the actual quicksort function*/
long long *quicksort(long long *a,long long n,int pivottype)
        {
                long long *b;
                /*b stores the sorted array*/
                b=quicksort1(a,0,n,pivottype);
                return b;
        }
main()
        {
                srand(time(NULL));
                long long n;
                printf("Enter the value of  n = pow(10,k) , k = 4, 5, 6, 7\n");
                scanf("%lld",&n);
                long long i,j;
                printf("n\t\tPivot Type\t\tRandom\t\tSorted\t\tAlmost Sorted\n%lld",n);
                for(j=0;j<4;j++)
					   {
                                long long *a,*b;/*a stores the initial array and b stores the sorted array for each pivottype and different calls for the same pivot type*/
                                a=(long long *)malloc(sizeof(long long)*n);
                                for(i=0;i<n;i++)
                                        a[i]=0;
                                /*for the case 0->pivot is the first element in the array*/
                                for(i=0;i<n;i++)
                                        {
                                                a[i]=rand()%1000000000;
                                        }
                                
                                if(j==0)
                                        printf("\t\tFIRST\t\t\t");
                                else if(j==1)
                                        printf("%lld\t\tRANDOM\t\t\t",n);
                                else if(j==2)
                                        printf("%lld\t\tMEDIAN OF THREE 1\t",n);
                                else if(j==3)
                                        printf("%lld\t\tMEDIAN OF THREE 2\t",n);
                                /*for measuring the runtime of each function call*/
                                clock_t c1, c2;
                                double runtime;
                                /*case 0:pivottype=0*/
                                c1=clock();
                                b=quicksort(a,n,j);/*case 0:quicksort called on the random array*/
                                c2=clock();
                                runtime=(double)(c2-c1)/(double)CLOCKS_PER_SEC;
                                printf("%lf\t",runtime);
                                c1=clock();
                                b=quicksort(b,n,j);/*case 0:quicksort called on the sorted array*/
                                c2=clock();
                                runtime=(double)(c2-c1)/(double)CLOCKS_PER_SEC;
                                printf("%lf\t",runtime);
                                long k=n/100;
                                /*swapping k pair of elements*/
                                for(i=0;i<k;i++)
                                        {
                                                long long m=rand()%n;
                                                long long l=rand()%n;
                                                if(m!=l)
                                                        {
                                                                long long temp=b[l];
                                                                b[l]=b[m];
                                                                b[m]=temp;
                                                        }
                                        }
                                c1=clock();
                                b=quicksort(b,n,j);/*case 0:quicksort called on the almost sorted array*/
                                c2=clock();
                                runtime=(double)(c2-c1)/(double)CLOCKS_PER_SEC;
                                printf("%lf\t\t\n",runtime);
                        }
                }

