#include <stdio.h>
#include <string.h>

/*--------------MACROS-----------------*/
#define LEN 101

/*-------------FUNCTIONS---------------*/

/*REMOVES REOCURING CHARACTERS*/
void rmv_dupes(char string[LEN])
{
    char *r, no_dupes[LEN];
    int n=strlen(string),j=0;
    for(int i=0; i<n; i++)
    {
        if(!(r=strchr(no_dupes,string[i])))
        {
            no_dupes[j]=string[i];
            j++;
        }
    }
   strcpy(string,no_dupes);
}

/*CHECKS IF c IS ONE OF string(t) */
int is_in_string(char c,char t[LEN])
{
    int n=strlen(t),k=0;
    for(int j=0;j<n;j++)
        if(c==t[j])
            k++;
        
    if(k==1)
        return 1;
    else 
        return 0;
}

/*---------------MAIN------------------*/
int main()
{
    char s[LEN],t[LEN];
    scanf("%s %s",s,t);
    rmv_dupes(t);
    
    int n=strlen(s),counter=0;
    
    for(int i=0;i<n;i++) 
        if(is_in_string(s[i],t))
            counter++;
        else 
            break;
        
    printf("%d\n",counter);
    return 0;
}
