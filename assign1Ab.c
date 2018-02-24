#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char **A;
int n;
char *stack1;
char *stack2;
int top1=-1,top2=-1;

//Linked list for first x elements
typedef struct node
	{
		char s;
		struct node *next;
	}Node1;
	
//Linked list for last y elements
typedef struct node2
	{
		char s1;
		struct node2 *next1;
	}Node2;
Node1 *head1=NULL;
Node2 *head2=NULL;

//to check if the character is a vowel
int isVowel(char c)
	{
		return(c=='A' || c=='E' || c=='I' || c=='O' || c=='U' );
	}
	
//build a stack using the elements of linked list for checking for palindromes
void pushList1(char s)
	{
		stack1[++top1]=s;	
	}
	
//build a stack using the elements of linked list for checking for palindromes
void pushList2(char s)
	{
		stack2[++top2]=s;	
	}
//function to check for palindromes
void palindrome(char stack[],int n)
	{
		char s1[100];
		int i,j,k,f=0;
		for(i=0;i<n;i++)
			{
				char c=stack[i];/*accessing element by element*/
				for(j=i+1;j<n;j++)
					{
						if(c==stack[j])//a palindrome exists only if c character exists at a jth position too
							{
								f=0;
								for(k=0;k<=j-i;k++)/*extracting the characters starting from c at ith position to c at jth position*/
									{
										s1[k]=stack[k+i];			
									}
								for(k=0;k<strlen(s1);k++)//checking if the reverse and the original string are equal
									{
										if(s1[k]!=s1[strlen(s1)-k-1])
											{
												f=1;//flag value to keep a track of palindromes and non-palindromes
												break;
											}
									}
								if(f==0)/*if all the characters are same in the reverse string and the original string then it is a palindrome*/
									{
										printf("Palindrome:%s\n",s1);
									}
							}	
					}
						
						
			}	
	}
main()
        {
        		Node1 *p=NULL,*q=NULL;
        		Node2 *r=NULL,*s=NULL;
                printf("Enter the value of n\n");
                scanf("%d",&n);
                int i,j,k;
                A=(char **)malloc(n*sizeof(char*));
                stack1=(char *)malloc(sizeof(char)*(n/2));
                stack2=(char *)malloc(sizeof(char)*(n-n/2));
                for(i=0;i<n;i++)
                        {
                                printf("Enter the string\n"); 
                                A[i]=(char*)malloc(100*sizeof(char));
                                scanf("%s",A[i]);
                        }
                        /*for first x nodes*/
                for(i=0;i<n/2;i++)
                	{	
                		p=(Node1*)malloc(sizeof(Node1));
                		p->next=NULL;
                		p->s=A[i][0];
                		if(head1==NULL)
                			{
                				head1=p;
                				q=p;
							}
						else
							{
								q->next=p;
								q=p;
							}
					}
					/*for next y nodes*/
					for(i=n/2;i<n;i++)
                		{	
                			r=(Node2*)malloc(sizeof(Node2));
                			r->next1=NULL;
                			r->s1=A[i][0];
                			if(head2==NULL)
                				{
                					head2=r;
                					s=r;
								}
							else
								{
									s->next1=r;
									s=r;
								}		
						}
					Node1 *cur=head1,*vow=NULL;
					q=head1;
					p=head1;
					/*to see if there are nodes with vowels in the beginning*/
					while(isVowel(p->s))
						p=p->next;
					while(cur!=NULL)/*cur stores the current node of the linked list */
						{
							if(isVowel(cur->s) && cur>p)/*if cur contains a vowel and p contains a consonant and if cur is located after p only then swap*/
								{
									/*swapping occurs*/
									char c=cur->s;
									cur->s=p->s;
									p->s=c;
									q=p;/*stores the address of the vowel node which was just swapped*/
									/*if there are any consonants between the two swapped values arranging them in oreder to maintain the original order of consonants */
									if(p->next!=NULL)
										{
											p=p->next;
											while(!isVowel(p->s) && p!=cur && p->next!=NULL)
												{
													char c=cur->s;
													cur->s=p->s;
													p->s=c;
													p=p->next;
												}
										}
									p=q->next;/*setting p to the very consonant node*/
								}
							cur=cur->next;
						}
					Node2 *cur1=head2;
					s=head2;
					r=head2;
					/*to see if there are nodes with vowels in the beginning*/
					/*same as for the list above*/
					while(isVowel(r->s1))
						r=r->next1;
					while(cur1!=NULL)
						{
							if(isVowel(cur1->s1) && cur1>r)
								{
									char c=cur1->s1;
									cur1->s1=r->s1;
									r->s1=c;
									s=r;
									if(r->next1!=NULL)
										{
											r=r->next1;
											while(!isVowel(r->s1) && r!=cur1 && r->next1!=NULL)
												{
													char c=cur1->s1;
													cur1->s1=r->s1;
													r->s1=c;
													r=r->next1;
												}
										}
									r=s->next1;
								}
							cur1=cur1->next1;
						}
					p=head1;
					/*pushing the list contents into a stack*/
					while(p!=NULL)
						{
							pushList1(p->s);
							p=p->next;
						}
					r=head2;
					/*pushing the list contents into a stack*/
					while(r!=NULL)
						{
							pushList2(r->s1);
							r=r->next1;
						}
						/*checking for palindrome*/
					palindrome(stack1,n/2);
					printf("\n");
					palindrome(stack2,n-n/2);
		   	}
