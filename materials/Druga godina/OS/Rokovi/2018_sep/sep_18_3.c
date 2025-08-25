#include <stdio.h>

/*---------------MACROS---------------*/
#define len 100

/*--------------FUNCTIONS-------------*/
/*CHECKS IF VALUES IN DIAGONAL ARE EQUAL*/
int is_diagonal_equal(float data[len][len],int n)
{
    int k=0;
    for(int i=0;i<n-1;i++)
       if(data[i][i]!=data[i+1][i+1])
       {k++; break;}
    
    if(k>0)
       return 0;
    else
       return 1;  
    
    
}

/*CHECKS IF COSSYMIETIC*/
int is_cossymetric(float data[len][len],int n)
{
    if(is_diagonal_equal(data,n))
    {
        int k=0; 
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i==j)
                    continue;
                else if(data[i][j]!=data[j][i]*-1)
                    k++; 
          
    if(k>0)
        return 0;
    else
        return 1;
    }
    else 
        return 0;

}

/*CALCUALTES MIN*/
float min(float data[len][len],int n)
{
    float min=999999999;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(data[i][j]<=min)
                min=data[i][j];
            
   return min;            
}

/*CALCUALTES MIN*/
float max(float data[len][len],int n)
{
    float max=-999999999;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(data[i][j]>=max)
                max=data[i][j];
            
   return max;            
}

/*----------------MAIN----------------*/
int main()
{
    int n; 
    float matrix[len][len];
    scanf("%d",&n);
    
    if(n<=1)
        {printf("-1\n"); return 0;}
      
    /*INPUT*/
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
           scanf("%f",&matrix[i][j]);
       
    if(is_cossymetric(matrix,n))
        printf("%.2f\n",min(matrix,n));
    else
        printf("%.2f\n",max(matrix,n));
            
 return 0;      
}
