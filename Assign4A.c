#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//structure to store the details of the patient ,name and arrival time
typedef struct node
{
        char *w1,*w2;
        float min;
        struct node *next;
}patient;

//creating the node for the patient
patient *create()
        {
                patient *p=(patient *)malloc(sizeof(patient));
                char w[100];
                float hr,min;
                printf("Enter the name of the patient\n");
                scanf("%s",w);
                p->w1=(char *)malloc(sizeof(char)*(strlen(w)+1));//w1 to store the modified names after removal of any duplicates
                p->w2=(char *)malloc(sizeof(char)*(strlen(w)+1));//w2 to store the original names without removal of any duplicates
                strcpy(p->w1,w);
                strcpy(p->w2,w);
                printf("Enter the time when the patient arrived\n");
                scanf("%f %f",&hr,&min);
                float time1=hr*60+min;//converting time to minutes
                p->min=time1;
                p->next=NULL;
                return p;//returning the node
        }
//function to count the number of characters in the patient's name matching with those of the doctor's name
int *nameFrequency(patient *head,char w[],int name[],int size)
        {
                patient *p=head;
                int i=0,j=0,k=0;
                while(p!=NULL)
                        {
                        	name[k]=0;
                        	for(j=0;j<strlen(p->w1);j++)
                       		{
                                char c=p->w1[j];//extrcating chARACTER from the name for comparing
                        		for(i=0;i<size;i++)
									{
                                        	if(w[i]==c)//w contains the doctor's name
                                                name[k]++;//if c and w[i] match increment the value of the frequency array element
                                	}
                        	}
                        	k++;//increment k for the next name
                        	p=p->next;//move to the next list item
                        }
        		return name;//returning the frequency array
        }
void main()
        {
                int n;
                printf("Enter the number of patients\n");
                scanf("%d",&n);
                int i=1,j=0,k=0;
                char *w,*w1,**w4;
                w=(char *)malloc(sizeof(char)*100);
                w1=(char *)malloc(sizeof(char)*100);
                patient *head=NULL,*q=NULL,*p=NULL;
                //forming the linked list
                while(i<=n)
                        {
                                p=create();
                                if(head==NULL)
                                        {
                                                head=p;
                                                q=p;
                                        }
                                else
                                        {
                                                q->next=p;
                                                q=p;
                                        }
                                i++;
                        }
                printf("Enter the name of the doctor\n");
                scanf("%s",w);
                p=head;
				while(p!=NULL)
                        {
                                w1=p->w1;
                                //removing the duplicate characters if any from the name and finally storing them in p->w1
				printf("Removing duplicate characters\n");
                                for(j=0;j<strlen(w1)-1;j++)
                                        {
                                                for(k=j+1;k<strlen(w);k++)
                                                        {
                                                                if(w1[j]==w1[k])
                                                                        {
                                                                                char *w2,*w3;
                                                                                w2=(char *)malloc(strlen(w1)*sizeof(char));
                                                                                 w3=(char *)malloc(strlen(w1)*sizeof(char));
                                                                                strncpy(w2,w1,k);
                                                                                strncpy(w3,w1+k+1,strlen(w1)-k);
                                                                                w2[k]=0;
                                                                                w3[strlen(w1)-k]=0;
                                                                                w1=strcat(w2,w3);
                                                                                w1[strlen(w1)]=0;
                                                                                p->w1=w1;
                                                                        }
                                                        }
                                        }
                                p=p->next;
                        }
                        //removing the duplicate characters from the name of the doctor
                 for(j=0;j<strlen(w)-1;j++)
                                        {
                                                char ch=w[j];
                                                for(k=j+1;k<strlen(w);k++)
                                                        {
                                                                if(w[j]==w[k])
                                                                {
                                                               		char *w2,*w3;
                                                                	w2=(char *)malloc(strlen(w1)*sizeof(char));
                                                                	w3=(char *)malloc(strlen(w1)*sizeof(char));
                                                                	strncpy(w2,w,k);
                                                                	strncpy(w3,w+k+1,strlen(w)-k);
									w2[k]=0;
                                                                	w3[strlen(w)-k]=0;
                                                               		w=strcat(w2,w3);
                                                                	w[strlen(w)-1]=0;
                                                                }
                                                        }
                                        }
                int name[n],time[n];
                p=head;
                //name1 contains the frequencies of matching
                int *name1=nameFrequency(head,w,name,strlen(w));
                p=head;
                i=0;
                w4=(char **)malloc(sizeof(char *)*n);
                //creating the time array
                while(p!=NULL)
                        {
                                time[i]=p->min;
                                w4[i]=(char *)malloc(sizeof(char)*(strlen(p->w2)+1));
                                strcpy(w4[i],p->w2);
                                i++;
                                p=p->next;
                        }
                    //sorting the names according to the frequency array
				for(i=0;i<n-1;i++)
				{
					int pos=i;
					int min1=name1[i],min2;
					for(j=i+1;j<n;j++)
						{
							if(name1[j]>name1[i])
							{	
								min1=name1[j];
								min2=time[j];
								pos=j;
							}
						}
					int temp=name1[i];
					name1[i]=name1[pos];
					name1[pos]=temp;
					temp=time[i];
					time[i]=time[pos];
					time[pos]=temp;
					char *s;
					s=(char *)malloc(sizeof(char)*10);
					strcpy(s,w4[i]);
					strcpy(w4[i],w4[pos]);
					strcpy(w4[pos],s);
				}
				//sorting the array on the basis of arrival time if two frequencies match
				for(i=0;i<n;i++)
				{
					k=i;
					int m=i;
					while(name1[i]==name1[i+1])
						{
							k++;
							i++;
						}
					int p;
					for(p=m;p<=k-1;p++)
						{
							int min=time[p];
							int pos=p;
							for(j=p+1;j<=k;j++)
								{
									if(time[j]<min)
										{
											min=time[j];
											pos=j;
										}
								}
							char *s;
							s=(char *)malloc(sizeof(char)*10);
							strcpy(s,w4[p]);
							strcpy(w4[p],w4[pos]);
							strcpy(w4[pos],s);
						}
				}
				//printing the sorted list
				for(i=0;i<n;i++)
				{
					printf("%s \n",w4[i]);
				}
		return;
        }

