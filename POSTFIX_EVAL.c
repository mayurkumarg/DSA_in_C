#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // Required for isdigit()

typedef enum {
    lparen, rparen, plus, minus, times,
    divide, mod, operand, eos
} precedence;

char Expr[100];
int stack[100];  // Stack to store integers
int top = -1;

void push(int value) {
    stack[++top] = value;
}

int pop() {
    if (top == -1) {
        printf("Error: Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

precedence get_token(char *symbol, int *n) {
    *symbol = Expr[(*n)++];
    if (isdigit(*symbol)) {
        return operand;
    }
    switch (*symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '\0': return eos;
        default:
            printf("Error: Invalid character '%c'\n", *symbol);
            exit(1);
    }
}

int eval() {
    precedence token;
    char symbol;
    int n = 0;
    int op1, op2;

    while ((token = get_token(&symbol, &n)) != eos) {
        if (token == operand) {
            push(symbol - '0');  // Convert char digit to int
        } else {
            op1 = pop();
            op2 = pop();
            switch (token) {
                case plus: push(op2 + op1); break;
                case minus: push(op2 - op1); break;
                case mod: push(op2 % op1); break;
                case divide:
                    if (op1 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    push(op2 / op1);
                    break;
                case times: push(op2 * op1); break;
                default:
                    printf("Error: Unknown operator\n");
                    exit(1);
            }
        }
    }
    return pop();
}

int main() {
    printf("\nEnter the postfix expression: ");
    scanf("%s", Expr);
    int result = eval();
    printf("After the evaluation: %d\n", result);
    return 0;
}
