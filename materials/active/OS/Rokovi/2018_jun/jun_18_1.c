#include <stdio.h>
#include <stdlib.h>

/*-------------FUNCTIONS---------------*/
int is_correct(int number)
{
    number=abs(number);
    int sum=0, j=number%10;
    number/=10;
    while(number>0)
    {
        sum+=number%10;
        number/=10;
    }
    
    if(j>sum)
        return 1;
    else 
        return 0;
}

/*----------------MAIN-----------------*/
int main()
{
    int number;
    while((scanf("%d",&number))!=EOF)
     if(is_correct(number))
        printf("%d ",number);
    
    return 0;
}
