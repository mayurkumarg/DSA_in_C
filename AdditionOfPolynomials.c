#include <stdio.h>

typedef struct AdditionOfPolynomials
{
    int coef;
    int expo;
}term;

term poly[100];
int avail=0;

int compare(int x,int y)
{
    if(x>y)
    {
        return -1;
    }
    else if(x<y){
        return 1;
    }
    else{
        return 0;
    }
}

void attach(int c, int e)
{
    poly[avail].coef=c;
    poly[avail].expo=e;
    avail++;
}

void add(int startA,int finishA,int startB,int finishB)
{
    while((startA<=finishA) && (startB<=finishB))
    {
        switch(compare(poly[startA].expo,poly[startB].expo))
        {
            case -1: attach(poly[startA].coef,poly[startA].expo);
            startA++;
            break;
            case 1: attach(poly[startB].coef,poly[startB].expo);
            startB++;
            break;
            case 0: attach(poly[startA].coef+poly[startB].coef,poly[startA].expo);
            startA++;
            startB++;
            break;
        }
    }

    while(startA<=finishA)
    {
        attach(poly[startA].coef,poly[startA].expo);
        startA++;   
    }
    while(startB<=finishB)
    {
        attach(poly[startB].coef,poly[startB].expo);
        startB++;   
    }
}

void display(int start, int end)
{
    for(int i=start;i<=end;i++)
    {
        printf(" %dX^%d ",poly[i].coef,poly[i].expo);
        if(i!=end)
        {
            printf(" + ");
        }
    }
    printf("\n");
}

int main() {
    int n1, n2;
    
    // Input first polynomial
    printf("Enter the number of terms in the first polynomial: ");
    scanf("%d", &n1);
    int startA = avail;
    for (int i = 0; i < n1; i++) {
        int coef, expo;
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coef, &expo);
        attach(coef, expo);
    }
    int finishA = avail - 1;

    // Input second polynomial
    printf("Enter the number of terms in the second polynomial: ");
    scanf("%d", &n2);
    int startB = avail;
    for (int i = 0; i < n2; i++) {
        int coef, expo;
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coef, &expo);
        attach(coef, expo);
    }
    int finishB = avail - 1;

    printf("\nFirst Polynomial: ");
    display(startA, finishA);

    printf("Second Polynomial: ");
    display(startB, finishB);

    // Perform addition
    int startC = avail;
    add(startA, finishA, startB, finishB);
    int finishC = avail - 1;

    printf("\nResultant Polynomial after Addition: ");
    display(startC, finishC);

    return 0;
}