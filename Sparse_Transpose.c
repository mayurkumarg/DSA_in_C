#include<stdio.h>

typedef struct Sparse_Transpose
{
    int r;
    int c;
    int v;
}sparse;



void SparseMatrix(int arr[50][50],int row,int col,sparse s[])
{
    int k=1;

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(arr[i][j]!=0)
            {
                s[k].r=i;
                s[k].c=j;
                s[k].v=arr[i][j];
                k++;
            }
        }
    }
    s[0].c=col;
    s[0].r=row;
    s[0].v=k-1;
}

void SimpleTranspose(sparse s[],sparse t[])
{
    for(int i=0;i<s[0].v;i++)
    {
        t[i].r=s[i].c;
        t[i].c=s[i].r;
        t[i].v=s[i].v;
    }
}

void FastTranspose(sparse s[], sparse t[])
{
    int starting_pos[50] = {0}, row_term[50] = {0};

    for (int i = 1; i <= s[0].v; i++)  
    {
        row_term[s[i].c]++;
    }

    starting_pos[0] = 1;  
    for (int i = 1; i < s[0].c; i++) 
    {
        starting_pos[i] = starting_pos[i - 1] + row_term[i - 1];
    }

    for (int i = 1; i <= s[0].v; i++)  
    {
        int j = starting_pos[s[i].c]; 
        t[j].r = s[i].c;
        t[j].c = s[i].r;
        t[j].v = s[i].v;
        starting_pos[s[i].c]++; 
    }

    t[0].r = s[0].c;
    t[0].c = s[0].r;
    t[0].v = s[0].v;
}

void PrintSparse(sparse s[])
{
    for(int i=0;i<s[0].v;i++)
    {
        printf("%d\t%d\t%d\n",s[i].r,s[i].c,s[i].v);
    }
}


int main()
{
    int row, col;
    int arr[50][50];

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &row, &col);

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    sparse s[100], t[100];

    SparseMatrix(arr, row, col, s);

    printf("\nOriginal Sparse Matrix:\n");
    PrintSparse(s);

    SimpleTranspose(s, t);

    printf("\nSimple Transpose:\n");
    PrintSparse(t);

    FastTranspose(s, t);

    printf("\nFast Transpose:\n");
    PrintSparse(t);

    return 0;
}