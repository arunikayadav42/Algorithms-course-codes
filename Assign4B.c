#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//the singe bit multipication takes place here
int multiplySingleBit(char x[],char y[])
	{
		return (x[0]-'0')*(y[0]-'0');
	}
//function to perform the binary addition with or without carry
char *addBinary(char x[],char y[])
	{
		int n,i;
		int l1=strlen(x);
		int l2=strlen(y);
		char a[25],b[25];
		char *c;
		c=(char *)malloc(sizeof(char)*25);
		//making both the strings storing a sequence of binary numbers of equal length
		if(l1<l2)
			{
				for(i=0;i<l2-l1;i++)
					{
							a[i]='0';//appending zeroes in the start if the string is of shorter length
					}
				a[l2-l1]=0;
				strncpy(b,x,l1);
				b[l1]=0;
				x=strcat(a,b);//number of characters in x become equal to those in y after adding zeroes in the start
				x[l2]=0;
				n=l2;
			}
		if(l1>l2)
			{
				for(i=0;i<l1-l2;i++)
					{
							a[i]='0';//appending zeroes in the start if the string is of shorter length
					}
				a[l1-l2]=0;
				strncpy(b,y,l2);
				b[l2]=0;
				y=strcat(a,b);//number of characters in x become equal to those in y after adding zeroes in the start
				y[l1]=0;
				n=l1;
			}
			if(l1==l2)
				n=l1;
		int sum[n],carry=0;
		//finding the sum of the numbers
		for(i=n-1;i>=0;i--)
		{
			int x1=x[i]-'0';
			int y1=y[i]-'0';
			//adding the numbers according to the rules of the binary addition
			if(x1==0 && y1==0 && carry==0)
			{
				sum[i]=0;
				carry=0;
			}
			else if(x1==0 && y1==0 && carry==1)
			{
				sum[i]=1;
				carry=0;
			}
			else if(((x1==1 && y1==0) || (x1==0 && y1==1)) && carry==0)
			{
				sum[i]=1;
				carry=0;
			}
			else if(((x1==1 && y1==0) || (x1==0 && y1==1)) && carry==1)
			{
				sum[i]=0;
				carry=1;
			}
			else if(x1==1 && y1==1 && carry==0)
			{
				sum[i]=0;
				carry=1;
			}
			else if(x1==1 && y1==1 && carry==1)
			{
				sum[i]=1;
				carry=1;
			}
			}	
		for(i=0;i<n;i++)
			{
				c[i]=sum[i]+'0';
			}
		//if there is an extra carry left it is attached at the start of the binary string
		if(carry)
			{
				char a[20];
				a[0]=carry+'0';
				strncpy(a+1,c,strlen(c));
				strcpy(c,a);
				c[n+1]=0;
			}
		else
				c[n]=0;//making the last character to be null
		return c;
	}
	
//function to multiply two binary strings recursively
int multiply(char x[],char y[])
{
	int l1=strlen(x),l2=strlen(y),i=0,n;
	char a[25],b[25];
	//making both the strings of equal length
		if(l1<l2)
			{
				for(i=0;i<l2-l1;i++)
					{
							a[i]='0';
					}
				a[l2-l1]=0;
				strncpy(b,x,l1);
				b[l1]=0;
				x=strcat(a,b);	
				x[l2]=0;
				n=l2;
			}
		if(l1>l2)
			{
				for(i=0;i<l1-l2;i++)
					{
							a[i]='0';
					}
				a[l1-l2]=0;
				strncpy(b,y,l2);
				b[l2]=0;
				y=strcat(a,b);
				y[l1]=0;
				n=l1;
			}
		if(l1==l2)
			n=l1;
	if(n==0)//base case
		return;
	if(n==1) //base case
		return multiplySingleBit(x,y);
	int l=n/2,r=n-l;//finding the lengths of the left and right paths
	char xl[20],xr[20],yl[20],yr[20];
	strncpy(xl,x,l);//the left part of the first binary string
	xl[l]=0;
	strncpy(xr,x+l,r);//the right part of the first binary string
	xr[r]=0;
	strncpy(yl,y,l);//the left part of the second binary string
	yl[l]=0;
	strncpy(yr,y+l,r);//the right part of the second binary string
	yr[r]=0;
	int p1=multiply(xl,yl);//multiplying the left parts of both
	int p2=multiply(xr,yr);//multiplying the right parts of both the strings
	int p3=multiply(addBinary(xl,xr),addBinary(yl,yr));//calculating (xl+xr)(yl+yr)
		return p1*(1<<(2*r))+(p3-p1-p2)*(1<<r)+p2;// calculating the multiplication ,recursive case
}
main()
	{
		printf("Enter x and y\n");
		char x[100],y[100];
		scanf("%s",x);//the first string
		scanf("%s",y);//the second string
		int p=multiply(x,y);
		printf("the result is : %d\n",p);//the result
	}
