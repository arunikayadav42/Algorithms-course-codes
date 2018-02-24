#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
/*for sorting the array names in lexicographical order*/
void radixSortNames(int n,char **name,int runs[],int min)
	{
		int i,j,k,f=0,m,r;
		/*C[26] array to store the frequency of the letters*/
        int A[n],B[n],C[26];
        char **ch;
        ch=(char **)malloc(sizeof(char *)*n);/*auxiliary array to store the names in the array names*/
        //allocating memory to the array ch
        for(i=0;i<n;i++)
            {
                ch[i]=(char *)malloc(sizeof(char)*20);
			}
		//initializing the array with the value zero	
        for(i=0;i<26;i++)
            C[i]=0;
        /*the loop runs for 'min' number of times*/
        for(i=0;i<min;i++)
           {
                int p=0;
                /*the frequency of the character at the (min-i-1)th index is stored in the array C in the form of the ascii values of the character*/
           	    for(j=0;j<n;j++)
                   {
                        char m=name[j][min-i-1];//m stores the character
                        p=(int)(m-97);//p stores the corresponding ascii value-97
                        ++C[p];
                   }
           		j=0;
            	for(j=1;j<26;j++)
                   {
                        C[j]=C[j]+C[j-1];/*the jth element will store the total number of elements less than or equal to j*/
                   }
                   /*populating the array B with the corresponding elements from the runs array and array ch with the corresponding elements from names array*/
           	    for(j=n-1;j>=0;j--)
					{		
                        char m=name[j][min-i-1];//m stores the character
                        p=(int)(m-97);//p stores the corresponding (ascii value-97)
                        B[C[p]-1]=runs[j];
                        strcpy(ch[C[p]-1],name[j]);
                        --C[p];
                    }
				for(k=0;k<26;k++)//initializing array C with 0 value for the next run of elements
                    C[k]=0;
               	for(k=0;k<n;k++)
               		{
                       	runs[k]=B[k];
                       	strcpy(name[k],ch[k]);
                    }
                }
            printf("\n\n\n");
	}
/*for sorting runs in the decreasing order*/
void radixSortRuns(int n,char **name,int runs[],int count)
        {
                int i,j,k,f=0,m,r;
                /*C[10] array to store the frequency of the digits*/
                int A[n],B[n],C[10];
                char **ch;
                ch=(char **)malloc(sizeof(char *)*n);/*auxiliary array to store the names in the array names*/
                //allocating memory to the array ch
                for(i=0;i<n;i++)
 	               {
    	            	ch[i]=(char *)malloc(sizeof(char)*20);
					}
				//initializing the array with the value zero
                for(i=0;i<10;i++)
                        C[i]=0;
                /*the loop runs for 'count' number of times*/
                for(i=0;i<count;i++)
                        {
                                int p=(int)pow(10,i);
                                /*the frequency of the digit in the number at the jth index is stored in the array C*/
                                for(j=0;j<n;j++)
                                        {
                                        		
                                                int m=(runs[j]/p)%10;//m gives the digits in the jth number
                                                ++C[m];//increasing the value of the elements of the C array
                                        }
                                j=0;
                                for(j=1;j<10;j++)
                                        {

                                                C[j]=C[j]+C[j-1];/*the jth element will store the total number of elements less than or equal to j*/
                                        }
                                /*populating the array B with the corresponding elements from the runs array and array ch with the corresponding elements from names array*/
                                for(j=n-1;j>=0;j--)
										{		
                                                int m=(runs[j]/p)%10;
                                                B[C[m]-1]=runs[j];
                                                strcpy(ch[C[m]-1],name[j]);
                                                --C[m];
                                        }
								for(k=0;k<10;k++)//initializing array C with 0 value for the next run of elements
                                        C[k]=0;
                        		/*the runs array and the names array need to be changed after each pass of the radix sort*/
               					for(k=0;k<n;k++)
               						{
                        				runs[k]=B[k];
                        				strcpy(name[k],ch[k]);
                        			}
                        	}
              	printf("The final array is \n");
                for(i=0;i<n;i++)
                printf("%s  %d\n",ch[i],B[i]);
						
		}
        	
main()
        {
                int n,i=0;
                printf("Enter the number of elements\n");//accepting the number of the elements
                scanf("%d",&n);
                char **name;
                int runs[n],min=10000;
                name=(char **)malloc(sizeof(char *)*n);
                //accepting the names of the elements and the runs of the elements
                for(i=0;i<n;i++)
                        {
                                name[i]=(char *)malloc(sizeof(char)*25);
                                printf("Enter the name in lower case letters\n");
                                scanf("%s",name[i]);
                                printf("Enter the runs\n");
                                scanf("%d",&runs[i]);
                                //keeping a track of the element having the name with minimum length
                                if(min>strlen(name[i]))
                                	{
                                		min=strlen(name[i]);
									}
                        }
                //finding the maximum number of runs stored in the array
                int max=runs[0];
                for(i=0;i<n;i++)
                        {
                                if(max<runs[i])
                                        max=runs[i];
                        }
                int count=0;
                //count stores the number of digits in the maximum run
                while(max!=0)
                        {
                                count++;
                                max=max/10;
                        }
                radixSortNames(n,name,runs,min);//radix sort for sorting the names is called
                radixSortRuns(n,name,runs,count);//radix sort for sorting the runs is called
        }

