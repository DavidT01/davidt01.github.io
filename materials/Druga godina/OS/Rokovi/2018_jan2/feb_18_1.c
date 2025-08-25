#include <stdio.h>
#include <stdlib.h>

/*-------------------------FUNCTIONS--------------------------*/
int is_correct(int number)
{
    int sum=0,n=0;
    number=abs(number);
    while(number>0)
    {
        n++;
        sum+=number%10;
        number/=10;
    }
    
    if(sum%2==0 || n%2==0)
        return 1;
    else 
        return 0;
}

/*----------------------------MAIN----------------------------*/
int main()
{
    int number;
    while((scanf("%d",&number))!=EOF)
     if(is_correct(number))
        printf("%d ",number);
    
    
    return 0;
}
