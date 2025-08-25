#include <stdio.h>
#define len 100

int main()
{
    int ranking[len][len],n,m,points[len];
    
    scanf("%d %d",&n,&m);
    
    if(n<3 || m<2)
     {printf("-1\n"); return 0;}

    /*INPUT*/
    for(int i=0;i<n;i++)
       for(int j=0;j<m;j++)
       {
           scanf("%d",&ranking[i][j]);
           if(ranking[i][j]<0)
           {printf("-1\n"); return 0;}
       }
    
    /*CALCULATES POINTS AND SORSTS THEM INTO ARRAY*/
    for(int i=0;i<n;i++)
    {
        int sum=0; 
        for(int j=0;j<m;j++)
            sum+=ranking[i][j];
        points[i]=sum;
    }
    
    /*CALCULATES HOW MUCH POINTS THE WINNER HAS*/
    int max=-1;
    for(int i=0;i<n;i++)
        if(max<points[i])
         max=points[i];
        
    /*CHECKS FOR PLACE SHARING AND PRINTS WINNER ROW VALUE*/
    for(int i=0;i<n;i++)
        if(points[i]==max)
    printf("%d\n",i);
    
    return 0;
}
