#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sign_check(char,int *,int *);						//Prototype declaration of sign_check 
void addition(char*,char*,int,int,char*,int,int);		//Prototype declaration of addition
void substraction(char*,char*,int,int,char*,int,int);	//Prototype declaration of substraction

int main()
{
	char num1[100],num2[100],sum[200];		//Variable declaration
	int i,j,carry,x,len_num1,len_num2,len_sum,sign_num1,sign_num2,reduce_num1,reduce_num2;
	
	printf("Enter the 1st number :");
	gets(num1);
	printf("Enter the 2nd number :");
	gets(num2);
		   
	sign_check(num1[0],&sign_num1,&reduce_num1);	//Calling sign_check function for num1
	sign_check(num2[0],&sign_num2,&reduce_num2);	//Calling sign_check function for num1

	len_num1=strlen(num1);	
	strrev(num1);
	if(reduce_num1==1)			//Removing the sign if sign exists for num1
		num1[--len_num1]='\0';	
			
	len_num2=strlen(num2);
	strrev(num2);
	if(reduce_num2==1)			//Removing the sign if sign exists for num2
		num2[--len_num2]='\0';
		
	printf("\n\nEntered values are :\n");
	printf("Number 1 is :");
	puts(strrev(num1));
	printf("Number 2 is :");
	puts(strrev(num2));
	
	strrev(num1);
	strrev(num2);
	
	if(sign_num1*sign_num2>0)	//Checking wheather the given sum will be addition or substraction
		addition(num1,num2,len_num1,len_num2,sum,sign_num1,sign_num2);		//Calling addition function
	else	
		substraction(num1,num2,len_num1,len_num2,sum,sign_num1,sign_num2);	//Calling substraction function
	return 0;		
}

void sign_check(char ch,int *sign_num,int *reduce_num)	//Defination of sign_check function
{
	if(ch=='-')			
	{
		*sign_num=-1;
		*reduce_num=1;	
	}
	else if(ch=='+')
	{
		*sign_num=1;
		*reduce_num=1;		
	}
	else
	{
		*sign_num=1;
		*reduce_num=0;
	}	
}


void addition(char* num1,char* num2,int len_num1,int len_num2,char* sum,int sign_num1,int sign_num2)	//Defination of addition function
{
	int carry=0;
	int i,x,len_sum;
	
	i=0;
	while(i < len_num1 && i < len_num2)
	{
		x=(num1[i]-48)+(num2[i]-48)+carry;
		carry=x/10;
		x=x%10;
		sum[i]=x+48;
		i++;
	}
	if(i<len_num1)
	{	
		while(num1[i]!='\0')
		{
			x=(num1[i]-48)+carry;
			carry=x/10;
			x=x%10;
			sum[i]=x+48;
			i++;	
		}
	}
	else
	{
	    while(num2[i]!='\0')
		{
			x=(num2[i]-48)+carry;
			carry=x/10;
			x=x%10;
			sum[i]=x+48;
			i++;
		}	
	}
	if(carry!=0)
		sum[i++]=carry+48;
	sum[i]='\0';
	strrev(sum);
	len_sum=strlen(sum);
	
	if(sign_num1==-1 && sign_num2==-1)
	{
		for(i=len_sum-1;i>=0;i--)
			sum[i+1]=sum[i];
		sum[0]='-';
	}
	printf("\nResult is:");
	puts(sum);
}


void substraction(char* num1,char* num2,int len_num1,int len_num2,char* sum,int sign_num1,int sign_num2)	//Defination of substraction function
{
	int i,k;
	char operand1[100],operand2[100];
	int len_sum,result_sign;
	
	len_num1=strlen(num1);		
	len_num2=strlen(num2);
	
	i=strcmp(num1,num2);
	if(i==0)
	{
		printf("Resilt is 0\n");
	}
	else
	{
	if(len_num1!=len_num2)
	{
		if(len_num1>len_num2)
		{	
			strcpy(operand1,num1);
			strcpy(operand2,num2);
			//printf("\noperand1 is larger");
			result_sign=sign_num1;			
		}
		else
		{	
			strcpy(operand1,num2);
			strcpy(operand2,num1);
			//printf("\noperand2 is larger");
			result_sign=sign_num2;
		}
	}
	else
	{
		i=len_num1;
		//printf("\nlen_num1=%d",len_num1);
		while(i>=0)
		{
			if(num1[i]==num2[i])
			{
				i--;
				continue;
			}
			else
			{
				if((num1[i]-48)>(num2[i]-48))
				{
					strcpy(operand1,num1);
					strcpy(operand2,num2);
					result_sign=sign_num1;
					
					break;				
				}
				else
				{
				strcpy(operand1,num2);
				strcpy(operand2,num1);
				result_sign=sign_num2;
				break;
				}
			}
		}
		
	if(i==-1)	
		result_sign=1;
	}
	//printf("\nvalue of operand1=");
	
	//puts(operand1);
	//printf("\nvalue of opeand2=");
	
	//puts(operand2);
	//printf("sign=%d",result_sign);
	
	i=0;
	//printf("\n Intermediate step...\n");
    while(operand1[i]!='\0' && operand2[i]!='\0')
	{
		//printf("\n %c  %c  ",operand1[i],operand2[i]);
		if((operand1[i]-48)>=(operand2[i]-48))	
			sum[i]=((operand1[i]-48)-(operand2[i]-48)+48);
		else
			{
				k=i+1;
				while(operand1[k]=='0')
				{
					operand1[k]='9';
					k++;
				}
				
				operand1[k]=(operand1[k]-48-1)+48;
				sum[i]=((operand1[i]-48)-(operand2[i]-48)+10)+48;
			}	
			//printf("%c",sum[i]);
		i++;
	}
	while(operand1[i]!='\0')
	{
		sum[i]=operand1[i];
		i++;	
	}
	//printf("\n");
	sum[i]='\0';
	//puts(sum);
	len_sum=strlen(sum);
	
	i=len_sum-1;
	while(sum[i]=='0')
	{
		i--;
	}
	len_sum=i+1;
	sum[len_sum]='\0';
   	strrev(sum);
	//puts(sum);
	
	if(result_sign==-1)
	{
		for(i=len_sum-1;i>=0;i--)
			sum[i+1]=sum[i];
		sum[0]='-';
	}
	sum[len_sum+1]='\0';
	printf("The result is=");
	puts(sum);
}
}	
