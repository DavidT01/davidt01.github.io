#include <stdio.h>
#include <math.h>

/*---------------MACROS---------------*/
#define len 101

/*--------------FUNCTIONS-------------*/
/*CALCULATES SUM OF ALL ELEMENTS OF ARRAY*/
float sum(float data[len][len],int n)
{
    float sum=0;
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           sum+=data[i][j];
    return sum;
}

/*----------------MAIN----------------*/
int main()
{
    int n; 
    float A[len][len];
    scanf("%d",&n);
    
    if(n%2==0|| n<0)
        {printf("-1\n"); return 0;}
    
    /*INPUT*/
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           scanf("%f",&A[i][j]);
     
    /*CHECKS IF IS DIAGONALY DOMINANT*/
    for(int i=0;i<n;i++)
    {
        float sum_row=0;
        for(int j=0;j<n;j++)
            if(i!=j)
                sum_row+=fabs(A[i][j]);
        if(fabs(A[i][i])<sum_row)
            {printf("0\n"); return 0;}
    }     
    
    printf("%.2f\n",sum(A,n));
        
    
    return 0;
}
