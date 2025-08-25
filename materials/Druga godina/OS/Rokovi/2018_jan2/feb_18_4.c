#include <stdio.h>
/*------------------MACROS------------------*/
#define EXIT {printf("-1\n"); return 0;}
#define O_FOUND printf("0\n");

/*-------------------MAIN-------------------*/
int main()
{
    int n;
    scanf("%d",&n);
     if(n<1 || n>100)
        EXIT//
     
    /*--------------------------------------*/
    typedef struct{
     char name[21];   
     double amount;
     double price_g;
    }INGIREDIENT;       
    
    INGIREDIENT data[n];
    /*--------------------------------------*/
    /*data IMPUT*/
    for(int i=0; i<n; i++)
    {
        scanf("%s %lf %lf",data[i].name,
                          &data[i].amount,
                          &data[i].price_g);
        if(data[i].amount<=0 || data[i].price_g<=0)
            EXIT//
    }
    /*--------------------------------------*/
    /*OUTPUT*/
    double price=0;
    for(int i=0; i<n; i++)
        price+=(data[i].amount/100)*data[i].price_g;
    
    printf("%.2lf\n",price);
    /*--------------------------------------*/
    
 return 0;   
}
