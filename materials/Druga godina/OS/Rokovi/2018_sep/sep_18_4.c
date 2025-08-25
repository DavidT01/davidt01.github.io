#include <stdio.h>
#include <string.h>

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
     char genre[21]; 
     double rating;
    }MOVIE;       
    
    MOVIE data[n];
    /*--------------------------------------*/
    /*data IMPUT*/
    for(int i=0; i<n; i++)
        scanf("%s %s %lf",data[i].name,
                          data[i].genre,
                         &data[i].rating);
        
    /*--------------------------------------*/
    /*OUTPUT CALCULATION*/
    double best_rating=-1;
    int i,index_best_movie,k=0;
    char selected_genre[21];
    
    scanf("%s",selected_genre);
    for(i=0; i<n; i++)
        if(strcmp(selected_genre,data[i].genre)==0 && 
           best_rating<data[i].rating)
          {
              best_rating=data[i].rating;
              index_best_movie=i;
              k++;
          }
    
    /*OUTPUT*/
    if(k==0)
        printf("-1\n");
    else
        printf("%s\n",data[index_best_movie].name);
    /*--------------------------------------*/
    
 return 0;   
}
