#include <stdio.h>

/*---------------MACROS---------------*/
#define len 100

/*--------------FUNCTIONS-------------*/

/*CLACULATES SUMS OF ROWS*/
void calculate_rows(int data[len][len], int n, int row[len])
{   
    int sum;
    for(int i=0;i<n;i++)
    {  
        sum=0;
        for(int j=0;j<n;j++)
           sum+=data[i][j];
        row[i]=sum;
    }
}

/*CLACULATES SUMS OF COLUMNS*/
void calculate_columns(int data[len][len], int n, int column[len])
{   
    int sum;
    for(int i=0;i<n;i++)
    {
        sum=0;
        for(int j=0;j<n;j++)
           sum+=data[j][i];
        column[i]=sum;
    }
}

int is_all_equal(int data[],int n)
{
    for(int i=0;i<n-1;i++)
        if(data[i]!=data[i+1])
        {return 0; break;}
        
    return 1;
}

/*CALCULATES SUM OF ALL ELEMENTS OF ARRAY*/
int sum(int data[len][len],int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           sum+=data[i][j];
    return sum;
}


/*----------------MAIN----------------*/
int main()
{
    int n, element[len][len],row[len],column[len];
    scanf("%d",&n);
    
    if(n<=0)
        {printf("-1\n"); return 0;}
      
    /*INPUT*/
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           scanf("%d",&element[i][j]);
    
    calculate_rows(element,n,row);
    calculate_columns(element,n,column); 
    
    if(is_all_equal(row,n))
        printf("%d\n",sum(element,n));
    else if(is_all_equal(column,n))   
        printf("%d\n",sum(element,n));
    else
        printf("0\n");
    return 0;
}
