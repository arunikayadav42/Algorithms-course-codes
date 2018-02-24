#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define true 1
#define false 0
int j=0;

/*function to check if the copy the character ch is present in the word*/
void extractWord(char c[],char ch,int size,int i)
	{
		/*if the start index->i becomes equal to the size of the word the copy of the word is not present in the word */
		
		if(i==size)
			{       
				/*to specify that the word is not even in the isEvenWord function,j is made equal to the size*/
				j=size;
				return;
			}

		/*checking if the copy of the character ch is present in the word,size->size of the array c[],i is the start index,ch is the character for which the check is to be perfomed*/
		
		if(ch==c[i] && i!=strlen(c)-1)/*ch is always the last character in the array hence the last index is not to be considered*/
			{
				
				j=i;
				return;
			}

		/*incrementing the start index to traverse the array*/
		i++;
		extractWord(c,ch,size,i);
	}
//extractWord ends

/*isEvenWord starts ,to check if the word is even or not*/
bool isEvenWord(char c[])
        {
		int q,f;
		/*if the length of the word falls to zero then it is definitely an even word*/
		if(strlen(c)==0)
			{
				return true;
			}
        	char ch;
		/*ch contains the last element of the array*/
                ch=c[strlen(c)-1];
		extractWord(c,ch,strlen(c),0);
		/*if the word length has not completely fallen to zero and j has become equal to the size of the word then a copy of the character ch does not exist and the word is not even*/
		if(strlen(c)!=0 && strlen(c)==j)
			{
				return false;
			}
		/*after finding the copy of the word trucating the word from the last by one character*/
              	c[strlen(c)-1]='\0';
		/*to find two substrings of the word so that it c does not contain the character ch and it's copy*/
              	char *w1,*w2;
              	w1=(char *)malloc(sizeof(char)*strlen(c));
              	w2=(char *)malloc(sizeof(char)*strlen(c));
		/*if j is a valid index then the copy of ch existed and j stores the index of that copy and this copy now has to be removed from the array c*/
              	if(j>0)
              		{
				/*part of the word from the start uptil j-1*/
              			strncpy(w1,c,j);
				/*setting the last element in the w1 array to null,to make it a valid char array representing a string*/
              			w1[j]=0;
				 /*part of the word from the j+1 uptil the last*/
              			strncpy(w2,c+j+1,strlen(c)-j);
				/*setting the last element in the w2 array to null,to make it a valid char array representing a string*/
              			w2[strlen(c)-j]=0;
				/*concating w1 and w2 to regenerate c*/
         			c=strcat(w1,w2);
              		}
		/*if j==0,then only one of w1 or w2 will be sufficent to remove the copy of ch found at index 0*/
              	else
              		{
              			strncpy(w1,c+1,strlen(c)-1);
              			w1[strlen(c)-1]=0;
              			c=w1;
	         	}
		/*recursively calling isEvenWord*/
                 return isEvenWord(c);
                                
        }
main()
        {
                char w[100];
                printf("Enter the string\n");
                scanf("%s",&w);
                j=strlen(w);
		int p=isEvenWord(w);
		/*if p comes out to be 1 then the word is even otherwise it is odd*/
		if(p==1)
			printf("EVEN\n");
		else
			printf("NOT EVEN\n");
        }

