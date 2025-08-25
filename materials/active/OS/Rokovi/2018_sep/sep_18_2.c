#include <stdio.h>
#include <string.h>

/*--------------MACROS-----------------*/
#define LEN 101

/*-------------FUNCTIONS---------------*/

/*FUNCTION RECIEVES POINTER TO string[i] AND CHECKS IF 
ALL CHARACTERS OF sub[LEN] ARE EQUAL TO CHARACTERS FROM
THE [i] POINT OF string[LEN] TO strlen(sub) */
int is_substring(char string[LEN],char sub[LEN])
{   
    int n=strlen(sub),k=1;
    for(int i=0;i<n;i++)
        if(string[i]!=sub[i])
        {k=0; break;}
        
    if(k==0)
        return 0;
    else
        return 1;
}
/*---------------MAIN------------------*/
int main()
{
    char s[LEN],t[LEN];
    scanf("%s %s",s,t);
    /*========================*/
    int n=strlen(s),counter=0;
    /*========================*/
    for(int i=0;i<n;i++) 
        if(is_substring(s+i,t))
            counter++;
    /*========================*/
    printf("%d\n",counter);
    return 0;
}
