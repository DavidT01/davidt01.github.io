#include <stdio.h>
#include <string.h>

void rmv_until_c(char s[31],char c,char mod2[31])
{
    int j=0;
    for(int i=0; s[i]!=c; i++,j++)
        mod2[i]=s[i];
    mod2[j]=c;
    mod2[j+1]='\0';   
}

int main()
{
    char s[31],c,*right,mod[31],mod2[31];
    
    scanf("%s %c",s,&c);
    if((right=strchr(s,c)))
    {
        strcpy(mod,right+1);
        rmv_until_c(s,c,mod2);
        strcat(mod,mod2);
        strcpy(s,mod);
        printf("%s",s);
    }
    else
        printf("%s",s);
    
    printf("\n");
    return 0;
}
