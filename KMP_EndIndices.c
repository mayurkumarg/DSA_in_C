#include<stdio.h>
#include<string.h>

int pi[100];

void pitable(char pattern[20])
{
    int j=0, m=strlen(pattern);
    pi[0]=0;

    for(int i=1;i<m;i++)
    {
        while(j>0 && pattern[j]!=pattern[i])
        {
            j=pi[j-1];
        }
        if(pattern[j]==pattern[i])
        {
            j++;
        }
        pi[i]=j;
    }
}

void KMP(char pattern[20],char text[40])
{
    int m=strlen(pattern),n=strlen(text);
    int i=0,j=0,found=0;

    while(i<n)
    {
        if(text[i]==pattern[j])
        {
            i++,j++;
        }
        if(j==m)
        {
            printf(" Pattern found at index: %d",i-j);
            j=pi[j-1];
            found=1;
        }

        else if(i<n && text[i]!=pattern[j])
        {
            if(j!=0)
            {
                j=pi[j-1];
            }
            else{
                i++;
            }
        }
    }
    if(found==0)
            {
                printf("pattern does not exist !!");
            }
}

void End_Indices(char pattern[20],char text[30])
{
    int patLen=strlen(pattern),texLen=strlen(text);
    int count=0,index=0;

    for(int i=0;i<=texLen-patLen;i++)
    {
        count=0;
        if(pattern[0]==text[i] && pattern[patLen-1]==text[i+patLen-1])
        {
            int pos=i;
            index=i;
            for(int j=0;j<patLen;j++)
            {
                if(pattern[j]==text[pos])
                {
                    pos++;
                    count++;
                }
                if(count==patLen)
                {
                    printf("Pattern found at index %d : ",index);
                    return;
                }
            }
        }
    }
    printf("Not found !! ");
}



int main()
{
    char text[40], pattern[20];

    printf("Enter the text: ");
    scanf("%s", text);

    printf("Enter the pattern: ");
    scanf("%s", pattern);

    pitable(pattern);

    printf("\nPerforming KMP Algorithm:\n");
    KMP(pattern, text);

    printf("\nFinding End Indices:\n");
    End_Indices(pattern, text);

    return 0;
}