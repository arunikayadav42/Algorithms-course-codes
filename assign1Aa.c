#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char **A;
int n;
struct node//defining the linked list
        {
                char *s;
                struct node* next;
        };
struct node *head=NULL;//declaring the head of the linked list

//function to create the head of the linked list
struct node *create(char s[]) 
        {
                struct node *p=NULL,*q=NULL;
                p=(struct node*)malloc(sizeof(struct node));
                p->s=(char*)malloc(sizeof(char)*100);
                p->next=NULL;
                strcpy(p->s,s);
                return p;
        }
/*function to compare a given name with the other names to find the part of the word through which it is uniquely determined*/
char *strcmp1(char a[],int i)
        {
                int j,k;
                char w[100],*w1;
                struct node *p=NULL,*q=NULL;
                w1=(char *)malloc(sizeof(char)*100);//to store the unique initials of the given word 
                for(j=0;j<100;j++)//everytime setting the initial value of all the characters to null
                        w[j]='\0';
                for(j=0;j<n;j++)
                        {
                                if(i!=j)//comparing the given word with every other word in the array
                                {
                                        for(k=0;k<strlen(a);k++)
                                        {
                                                if(a[k]!=A[j][k])//when a different character in the word is found ,break is executed
                                                {
                                                        w[k]=a[k];
                                                        break;
                                                }
                                                else
                                                w[k]=a[k];//if a different character is not found the common initials are stored
                                        }
                                }
                                if(strlen(w1)<strlen(w)) /*the longest part of the given word which uniquely determines the word in the array is built otherwise*/
                                        {
                                                strcpy(w1,w);
                                        }
                        }
                return w1;//w1 is returned
        }

//the list is sorted depending on the initials
void sortlist()
        {
                struct node *p=head,*r=head;
                char w[100];
                while(p->next!=NULL)//p is the current element
                        {
                                r=head;//r is used to access and compare p with every other word in the linked list
                                while(r!=NULL && r!=p)//loop does not run for r=p
                                        {
                                                if(strcmp(r->s,p->s)>0)//if to sort the array in ascending order of ascii codes of the words
                                                        {
                                                                strcpy(w,r->s);
                                                                strcpy(r->s,p->s);
                                                                strcpy(p->s,w);
                                                        }
                                                r=r->next;
                                        }
                                p=p->next;
                        }
        }
void main()
        {
                struct node *p=NULL,*q=NULL;
                printf("Enter the value of n\n");
                scanf("%d",&n);
                int i;
				 A=(char **)malloc(n*sizeof(char*));
                for(i=0;i<n;i++)
                        {
                                printf("Enter the string\n");
                                A[i]=(char*)malloc(100*sizeof(char));
                                scanf("%s",A[i]);
                        }
                //building the linked list in the required form
                for(i=0;i<n;i++)
                        {
                                char *c=strcmp1(A[i],i);//getting the unique initials of the name
                                p=create(c);//creating the node using the unique initials
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
                        }
                p=head;
                sortlist();//sorting the list in alphabetical order
                while(p!=NULL)
                        {
                                printf("%s\n",p->s);
                                p=p->next;
                        }
                p=head;
                /*Printing the whole name from the array after comparing it with the contents of the linked list*/
                while(p!=NULL)
                        {
                                for(i=0;i<n;i++)
                                        {
                                                if(strstr(A[i],p->s))
                                                        {
                                                                printf("%s->",A[i]);
                                                        }
										        
                                        }
                                p=p->next;
                        }
		return;
                }
	
