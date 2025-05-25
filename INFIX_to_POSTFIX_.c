#include<stdio.h>
#include<stdlib.h>

typedef enum{
    lparen, rparen,plus,minus,times,
    divide,mod,operand,eos
}precedence;

int isp[]={0,19,12, 12, 13, 13, 13, 0};
int icp[]={20,19,12, 12, 13, 13, 13, 0};

char Expr[100];
precedence stack[100];
int top=-1;

void push(precedence token)
{
    stack[++top]=token;
}

precedence pop()
{
    return stack[top--];
}

precedence get_token(char *symbol, int *n)
{
    *symbol=Expr[(*n)++];
    switch (*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '\0': return eos;
        default: return operand;
    }
}

void print_token(precedence token)
{
    if (token == plus) printf("+");
    else if (token == minus) printf("-");
    else if (token == times) printf("*");
    else if (token == divide) printf("/");
    else if (token == mod) printf("%%");
}

void postfix()
{
    char symbol;
    int n=0;
    top=0;
    precedence token;
    stack[top] = eos;
    while((token=get_token(&symbol,&n))!=eos)
    {
        if(token==operand)
        {
            printf("%c",symbol);
        }
        else if(token==rparen)
        {
            while(stack[top] !=lparen)
            {
                print_token(pop());
            }
            pop();
        }
        else{
            while (isp[stack[top]] >= icp[token]) {
                print_token(pop());
            }
            push(token);
        }
    }
    while((token=pop())!=eos)
    {
        print_token(token);
    }
    printf("\n");

}

int main() {
    printf("\nEnter the infix expression: ");
    scanf("%s", Expr);
    postfix();
    return 0;
}
