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
     char surname[21]; 
     double height;
     double mass;
    }BMI;       
    
    BMI data[n];
    /*--------------------------------------*/
    /*data IMPUT*/
    for(int i=0; i<n; i++)
    {
        scanf("%s %s %lf %lf",data[i].name,
                              data[i].surname,
                             &data[i].height,
                             &data[i].mass);
        if(data[i].height<=0 || data[i].mass<=0)
            EXIT//
    }
    /*--------------------------------------*/
    /*BMI CALCULATION FOR data[i]*/
    double bmi[n];
        for(int i=0; i<n; i++)
            bmi[i]=data[i].mass/(data[i].height*data[i].height);
        
    /*--------------------------------------*/
    int category,k=0;
    scanf("%d",&category);
     switch(category) 
     {
         /*-------------------------*/
         /*OUTPUT IF 1*/
         case 1:
             for(int i=0; i<n; i++)
                 if(bmi[i]<18.5){
                     printf("%s %s\n",data[i].name,data[i].surname);
                     k++;}
             /*OUTPUT IF 0 FOUND*/        
             if(k==0)
                 O_FOUND//
             break;
         /*-------------------------*/    
         /*OUTPUT IF 2*/
         case 2:
             for(int i=0; i<n; i++)
                 if(bmi[i]>=18.5 && bmi[i]<25){
                     printf("%s %s\n",data[i].name, data[i].surname);
                     k++;}
             /*OUTPUT IF 0 FOUND*/        
             if(k==0)
                 O_FOUND//
             break;
         /*-------------------------*/    
         /*OUTPUT IF 3*/    
         case 3:
             for(int i=0; i<n; i++)
                 if(bmi[i]>=25 && bmi[i]<30){
                     printf("%s %s\n",data[i].name,data[i].surname); 
                     k++;}
             /*OUTPUT IF 0 FOUND*/        
             if(k==0)
                 O_FOUND//        
             break;
         /*-------------------------*/
         /*OUTPUT IF 4*/
         case 4:
             for(int i=0; i<n; i++)
                 if(bmi[i]>=30){
                     printf("%s %s\n",data[i].name,data[i].surname);
                     k++;}
            /*OUTPUT IF 0 FOUND*/         
            if(k==0)
                 O_FOUND//
             break;
         /*-------------------------*/   
         /*OUTPUT IF INVALID category*/    
         default :
             EXIT//
     }
    
    return 0;
}
