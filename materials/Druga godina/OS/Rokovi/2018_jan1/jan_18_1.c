#include <stdio.h>

/*-----------------------MACROS----------------------*/
#define CODE printf("-1 \n");
#define EXIT return 0;

/*----------------------FUNCTIONS--------------------*/

/*TRANSFORMS THE NUMBER ACCORDINGLY*/
int transform(int num)
{
    int st=num/1000;
    int nd=num%10;
    
    if(st%2==0 && nd%2==0)
        num=(num%1000/10)*10+nd*1000+st;
    else   
        num=num%1000/10;
    
    return num;
}

/*CHECKS IF THE INPUT IS CORRECT*/
int not_correct_num(int number)
{
    if((number>=1000 && number<=9999)|| number==0)
        return 0;
    else 
        return 1;
}

/*-------------------------MAIN-----------------------*/
int main()
{
    int num;
    do{
        scanf("%d",&num);
        if(not_correct_num(num))
            {CODE EXIT}
        else if (num==0)
            {EXIT}
        else
            printf("%d ",transform(num));
    }while(1);
    
    printf("\n");
    return 0;
}
