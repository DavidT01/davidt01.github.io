#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*-------------FUNCTIONS---------------*/
int  transform(int number)
{
    int i=0,copy=number;
    while(copy>0)
    {i++; copy/=10;}
    
    int last=number%10;
    int middle=(number%(int)pow(10,i-1))/10;
    int first=number/pow(10,i-1);
    
    number=first+middle*10+last*pow(10,i-1);
    return number;
}

/*----------------MAIN-----------------*/
int main()
{
    int number;
    while((scanf("%d",&number))!=EOF)
     if(number<0)
     {printf("-1\n"); return 0;}
     else if(number<10)
        printf("%d ",number);
     else
        printf("%d ",transform(number));
     
    printf("\n");
    return 0;
}
