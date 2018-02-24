#include<stdio.h>
#include<stdlib.h>

int pi;
int quicksort(int*,int,int,int);
void swap(int *ar,int i,int j){
	int temp;
	temp=ar[i];
	ar[i]=ar[j];

	ar[j]=temp;
}

int insertionsort(int *ar, int low ,int high){
   int i,key,j;
   for (i = low+1; i <=high; i++){
       key = ar[i];
       j=i-1;
       while (j >=low && ar[j] > key){
           ar[j+1]=ar[j];
           j--;
       }
       ar[j+1] = key;
	}
	return ar[(high-low+1)/2];
}

void medianofmedians(int *ar,int low,int high){
	if(low==high || high==0) {
		pi=ar[low];
	}
	else if(low<high){
	int i,*med,j;
	int count=0;
	int size = high-low+1;
	int a=size/5;
	i=low;
	j=0;
	med=(int*)malloc((a+1)*sizeof(int));
	while(i<=size && count < a){
		med[j]=insertionsort(ar,i,i+4);
		i=i+5;
		j++;
		count++;
	}
	if(size % 5 != 0)
	  med[j]=insertionsort(ar,(5*a),high);

	medianofmedians(med,0,j);}
}

int partition (int *ar, int low, int high){
	int mid,j,i,piv;
	medianofmedians(ar,low,high);
    int pivot =pi;
    printf("median of medians : %d\n",pi );
    for(i=low;i<=high;i++){
    	if(ar[i] == pivot)
    		break;
    }
    piv = i;
    swap(ar,piv,high);
    i=low-1; 
 
    for(j=low;j<high;j++){
        if (ar[j]<=pivot){
            i++;    
            swap(ar,i,j);}
    	}
    swap(ar,i+1,high);
    return (i+1);
}
 

int quicksort(int *ar, int low, int high,int d){
	//if(low==high) return ar[low];
    if(low<high){
        int pi=partition(ar,low,high);
        int u=pi-low+1;
        if(u==d){
        	return ar[pi];
        }
        else if(d <u){
        	printf("entered elseif\n");
			return quicksort(ar,low,pi-1,d);
        }
		else if(d >u){
			printf("Entered else\n");
      		return quicksort(ar,pi+1,high,d-u);
		}

    }
}

int main(){
	int i,d,n;
	printf("Please enter the number of elements : ");
	scanf("%d",&n);
	int *ar=(int *)malloc((n)*sizeof(int));
	printf("Enter the elements :");
	for(i=0;i<n;i++){
		scanf("%d",&ar[i]);
	}
	printf("Enter the value of i :");
	scanf("%d",&d);
	printf("The i-th smallest element is :%d",quicksort(ar,0,n-1,d));
}



