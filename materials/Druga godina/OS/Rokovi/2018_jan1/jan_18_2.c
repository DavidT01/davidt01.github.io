#include <stdio.h>
#include <string.h>

/*--------------------------FUNCTIONS-------------------------*/

/*ROTATES STRING*/
void rotate(char string[31])
{
    char temp[31];
    strcpy(temp,string);
    int i,j,n=strlen(string);
    for(i=n-1,j=0; i>=0; i--, j++)
        string[i]=temp[j];
}

/*CHECKS IF STRING suffix IS SUFFIX FOR STRING word*/
int is_suffix(char word[31], char suffix[31])
{   
    int j = (int)strlen(suffix),n=0;
    
    for(int i=0;i<j;i++)
        if(word[i]!=suffix[i])
            n++;
     
     if(n>0)
         return 0;
     else 
         return 1;
}

/*COMPARES LENGHTS OF STRINGS AND SWAPS THEM ACCORDINGLY*/       
int cmpNswap(char st[31], char nd[31])
{
    char temp[31];
    
    if(strlen(st)>strlen(nd))
        return 1;
    else if(strlen(st)==strlen(nd))
        return 2;
    else
    {
        strcpy(temp,st);
        strcpy(st,nd);
        strcpy(nd,temp);
        return 0;
    }
}


/*----------------------------MAIN---------------------------*/

int main()
{
    char first[31],second[31];
    scanf("%s %s",first,second);
    
    if(cmpNswap(first,second)==2)
        {printf("-1\n"); return 0;}

    rotate(first);
    rotate(second);
    
    if(is_suffix(first,second))
        printf("%d\n",(int)(strlen(first)-strlen(second)));
    else
        printf("-1\n");
    
    return 0;
}
