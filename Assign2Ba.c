#include <stdio.h>
#include <stdlib.h>
int  search(int a[],int n,int p)
        {
                int i;
                for(i=0;i<n;i++)
                        {
                                if(a[i]==p)
                                        return 1;
                        }
                if(i==n)
                        return 0;
        }
main()
        {
                int i=0,j=0,n,p,k=0;
                printf("Enter the number of elements in the array in ascending order\n");
                scanf("%d",&n);
                int a[n];
                for(i=0;i<n;i++)
                        {
                                printf("Enter the elements of the array\n");
                                scanf("%d",&a[i]);
                        }
                printf("Enter the element to be searched\n");
                scanf("%d",&p);
                if(n%5==0)
                {
                	int b[2*(n/5)],c[3*(n/5)];
                	for(i=0;i<2*(n/5);i++)
                		b[i]=a[i];
                	for(i=2*(n/5);i<n;i++)
                		c[i-2*(n/5)]=a[i];
                	i=0,j=0;
                	if(p<=a[2*(n/5)])
                		{
                			i=search(b,2*(n/5),p);
                			if(i==1)
                				printf("Found in first part\n");
                		}
                	else if(p<=a[n-1])
                		{
                			j=search(c,3*(n/5),p);
                			if(j==1)
                				printf("Found in second part\n");
						}
                	
				}
				else if(n%5==1)
				{
					int b[2*(n/5)],c[3*(n/5)+1];
                	for(i=0;i<2*(n/5);i++)
                		b[i]=a[i];
                	for(i=2*(n/5);i<n;i++)
                		c[i-2*(n/5)]=a[i];
                	i=0,j=0;
                	if(p<=a[2*(n/5)])
                		{
                			i=search(b,2*(n/5),p);
                			if(i==1)
                				printf("Found in first part\n");
                		}
                	else if(p<=a[n-1])
                		{
                			j=search(c,3*(n/5)+1,p);
                			if(j==1)
                				printf("Found in second part\n");
						}
                	
				}
				else if(n%5==2)
				{
					int b[2*(n/5)+1],c[3*(n/5)+1];
                	for(i=0;i<2*(n/5)+1;i++)
                		b[i]=a[i];
                	for(i=2*(n/5)+1;i<n;i++)
                		c[i-2*(n/5)-1]=a[i];
                		for(i=0;i<3*(n/5)+1;i++)
                			printf("%d\n",c[i]);
                	i=0,j=0;
                	
                	if(p<=a[2*(n/5)+1])
                		{
                			i=search(b,2*(n/5)+1,p);
                			if(i==1)
                				printf("Found in first part\n");
                			else
                				printf("Not found\n");
                		}
                	else if(p<=a[n-1])
                		{
                			j=search(c,3*(n/5)+1,p);
                			if(j==1)
                				printf("Found in second part\n");
                			else
                				printf("Not found\n");
						}
					else
						printf("Not found\n");
                	
				}
				else if(n%5==3)
				{
					int b[2*(n/5)+1],c[3*(n/5)+2];
                	for(i=0;i<2*(n/5)+1;i++)
                		b[i]=a[i];
                	for(i=2*(n/5)+1;i<n;i++)
                		c[i-2*(n/5)-1]=a[i];
                		for(i=0;i<3*(n/5)+2;i++)
                			printf("%d\n",c[i]);
                	i=0,j=0;
                	
                	if(p<=a[2*(n/5)+1])
                		{
                			i=search(b,2*(n/5)+1,p);
                			if(i==1)
                				printf("Found in first part\n");
                			else
                				printf("Not found\n");
                		}
                	else if(p<=a[n-1])
                		{
                			j=search(c,3*(n/5)+2,p);
                			if(j==1)
                				printf("Found in second part\n");
                			else
                				printf("Not found\n");
						}
					else
						printf("Not found\n");
                	
				}
				else if(n%5==4)
				{
					int b[2*(n/5)+2],c[3*(n/5)+2];
                	for(i=0;i<2*(n/5)+2;i++)
                		b[i]=a[i];
                	for(i=2*(n/5)+2;i<n;i++)
                		c[i-2*(n/5)-2]=a[i];
                		for(i=0;i<3*(n/5)+2;i++)
                			printf("%d\n",c[i]);
                	i=0,j=0;
                	
                	if(p<=a[2*(n/5)+2])
                		{
                			i=search(b,2*(n/5)+2,p);
                			if(i==1)
                				printf("Found in first part\n");
                			else
                				printf("Not found\n");
                		}
                	else if(p<=a[n-1])
                		{
                			j=search(c,3*(n/5)+2,p);
                			if(j==1)
                				printf("Found in second part\n");
                			else
                				printf("Not found\n");
						}
					else
						printf("Not found\n");
                	
				}
			
		}
