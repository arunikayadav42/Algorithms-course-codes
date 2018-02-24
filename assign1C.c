#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
        {
                int SNo;
                char *Title;
                char *Author;
                char IssueStatus[50];
                struct node *next;
        }Node;
Node *head=NULL;
/*creating a linked list*/
Node *create()
	{
		Node *p,*q=NULL;
    	char w[100];
		p=(Node*)malloc(sizeof(Node));
    	printf("Make a new entry of the book\n");
		printf("Enter the serial Number\ntitle\nauthor\nissue status\n");
    	scanf("%d",&p->SNo); 
   	 	scanf(" %[^\n]s",w);
    	p->Title=(char*)malloc(sizeof(char)*(strlen(w)+1));
    	strcpy(p->Title,w);
    	w[0]='\0';
    	scanf(" %[^\n]s",w);
    	p->Author=(char*)malloc(sizeof(char)*(strlen(w)+1));
    	strcpy(p->Author,w);
    
    	scanf(" %[^\n]s",p->IssueStatus);
    	p->next=NULL;
		return p;
	}
	/*function to showcase the list of books which are not issued*/
void showlist()
	{
		Node *p=head;
		while(p!=NULL)
			{
				if(strcmp(p->IssueStatus,"Not Issued")==0)
				{
				printf("Serial Number:%d\n",p->SNo);
    			printf("Title:%s\n",p->Title);
    			printf("Author:%s\n",p->Author);
				printf("Issue Status:%s\n",p->IssueStatus);		
				}
			p=p->next;
		}
		if(p==NULL)
			printf("No such book\n");
	}
/*function to change the issue status of the issued books from Not Issued to Issued*/
void issuebook(int i)
	{
		Node *p=head;
		while(p!=NULL && p->SNo!=i)
		p=p->next;
		if(p==NULL)
			{
				printf("No such book\n");
				return;
			}
		strcpy(p->IssueStatus,"Issued");
		
	}
/*function to change the issue status of the returned books from Issued to Not Issued*/
void returnbook(int i)
	{
		Node *p=head;
		while(p!=NULL && p->SNo!=i)
		p=p->next;
		if(p==NULL)
			{
				printf("No such book\n");
				return;
			}
		strcpy(p->IssueStatus,"Not Issued");
	}
main()
        {
                Node *p=head,*q=NULL,*r=NULL;
                int i=0;
                char c;
                char name[100];
                while(1)
                        {
                                printf("Enter the choice\n");
                                scanf(" %c",&c);
                                switch(c)
                                        {
                                                case 'a':/*create the list*/
                                                        r=create();
                                                        if(head==NULL)
    	    												{
    	   	    												head=r;
    	        												q=r;
    	    												}
    													else
       														{
       	       													q->next=r;
                												q=r;
        													}
                                                        break;
                                                case 'b':/* view the list of books*/
                                                		if(head==NULL)
                                                		{
                                                			printf("empty list\n");
                                                			break;
														}
                                                        printf("view details of the book\n");
                                                        printf("i) By serial No.\nii) By Title\niii) By Author\n");
                                                        scanf("%d",&i);
                                                        p=head;
                                                        if(i==1)/*View the books by serial number*/
                                                        {
                                                        	printf("Enter the serial number\n");
                                                        	scanf("%d",&i);
                                                        	while(p!=NULL && p->SNo!=i)
																p=p->next;
															if(p==NULL)
																{
																	printf("No such book exists\n");
																	break;
																}
															printf("Serial Number:%d\n",p->SNo);
    														printf("Title:%s\n",p->Title);
    														printf("Author:%s\n",p->Author);
															printf("Issue Status:%s\n",p->IssueStatus);	
														}
														else if(i==2)/*view the books by their title*/
														{
														printf("Enter the title\n");
														scanf("%s",name);
															while(p!=NULL && strcmp(p->Title,name)!=0)
																p=p->next;
															if(p==NULL)
																{
																	printf("No such book exists\n");
																	break;
																}
															printf("Serial Number:%d\n",p->SNo);
    														printf("Title:%s\n",p->Title);
    														printf("Author:%s\n",p->Author);
															printf("Issue Status:%s\n",p->IssueStatus);		
														}
														else/*view the books by their author name*/
														{
														printf("Enter the author\n");
														scanf("%s",name);
														p=head;
														while(p!=NULL)
															{
																if(strcmp(p->Author,name)==0)
																	{
																		printf("Serial Number:%d\n",p->SNo);
    																	printf("Title:%s\n",p->Title);
    																	printf("Author:%s\n",p->Author);
																		printf("Issue Status:%s\n",p->IssueStatus);
																	}
																p=p->next;
															}
															if(p==NULL)
																{
																	printf("No such book exists\n");
																	break;
																}
														}
                                                        break;
                                                case 'c':/*show the list of available books*/
                                                			if(head==NULL)
                                                		{
                                                			printf("empty list\n");
                                                			break;
														}
                                                        printf("Show list of available books\n");
                                                        showlist();
                                                        break;
                                                case 'd':/*to issue the book*/
                                                			if(head==NULL)
                                                		{
                                                			printf("empty list\n");
                                                			break;
														}
                                                        printf("Issue a book\n");
                                                        printf("Enter the serial number\n");
                                                        scanf("%d",&i);
                                                        issuebook(i);
                                                        break;
                                                case 'e':/*to return the book*/
                                                			if(head==NULL)
                                                		{
                                                			printf("empty list\n");
                                                			break;
														}
                                                        printf("return a book\n");
                                                         printf("Enter the serial number\n");
                                                        scanf("%d",&i);
                                                        returnbook(i);
                                                        break;
                                                case 'f':/*to exit the program*/
                                                		exit(0);
                    							default:
                    								printf("Wrong input\n");
                    								break;
                                        }
                            }
            }
