#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
};

typedef struct node *stckptr;

stckptr top=NULL;

void push(int data)
{
    stckptr newNode;
    newNode=(stckptr)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->next=top;
    top=newNode;
}

int pop()
{
    stckptr temp;
    int item;
    if(top==NULL)
    {
        return -1;
    }
    temp=top;
    item=temp->data;
    top=top->next;
    free(temp);
    return item;
}

void display()
{
    stckptr temp;
    temp=top;
    while(temp!=NULL)
    {
        printf(" %d ",temp->data);
        temp=temp->next;
    }
}

int main() {
    int item;
    int choice;
    
    while (1) {
        printf("\nEnter\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\nEnter element to push: ");
                scanf("%d", &item);
                push(item);
                break;
            case 2:
                item = pop();
                if (item == -1)
                    printf("\nStack Underflow!\n");
                else
                    printf("\nPopped element: %d\n", item);
                break;
            case 3:
                printf("\nStack: ");
                display();
                break;
            case 4:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
