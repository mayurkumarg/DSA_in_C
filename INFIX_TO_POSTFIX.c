#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

precedence stack[30];
int top = -1;
char EXPR[MAX];

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

void push(precedence token) {
    stack[++top] = token;
}

precedence pop() {
    return stack[top--];
}

precedence get_token(char *symbol, int *n) {
    *symbol = EXPR[(*n)++];
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

void print_token(precedence token) {
    if (token == plus) printf("+");
    else if (token == minus) printf("-");
    else if (token == times) printf("*");
    else if (token == divide) printf("/");
    else if (token == mod) printf("%%");
}

void postfix() {
    char symbol;
    precedence token;
    int n = 0;
    top = 0;
    stack[0] = eos;                                                // Initialize stack with end-of-stack marker

    while ((token = get_token(&symbol, &n)) != eos) {
        if (token == operand) {
            printf("%c", symbol);                                  // Print operand directly
        } else if (token == rparen) {
            while (stack[top] != lparen) {
                print_token(pop());                                // Pop and print until '(' is found
            }
            pop();                                                 // Remove '(' from stack
        } else {
            while (isp[stack[top]] >= icp[token]) {
                print_token(pop());                               // Pop higher precedence operators
            }
            push(token);                                         // Push current operator
        }
    }

    while ((token = pop()) != eos) {
        print_token(token);                                     // Print remaining operators in stack
    }

    printf("\n");
}


int main() {
    printf("\nEnter the infix expression: ");
    scanf("%s", EXPR);
    postfix();
    return 0;
}
