#include <stdio.h>
/*------------------MACROS------------------*/
#define EXIT {printf("-1\n"); return 0;}

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
     char surname[21]; 
     double succ;
     int year;
    }STUDENT;       
    
    STUDENT data[n];
    /*--------------------------------------*/
    /*data IMPUT*/
    for(int i=0; i<n; i++)
        scanf("%s %s %lf %d",data[i].name,
                             data[i].surname,
                            &data[i].succ,
                            &data[i].year);
        
    /*--------------------------------------*/
    /*OUTPUT*/
    int eligable=0;
    for(int i=0; i<n; i++)
        if(data[i].succ>9 && data[i].year==4)
            eligable++;
        
    printf("%d\n",eligable);
    /*--------------------------------------*/
 return 0;       
}
