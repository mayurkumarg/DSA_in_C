#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node* next;
};

typedef struct node *qptr;

qptr front=NULL;
qptr rear=NULL;

void enqueue(int data)
{
    qptr temp;
    temp=(qptr)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    if(rear)
    {
        rear->next=temp;
    }
    else{
        front=temp;
    }
    rear=temp;
}

int dequeue()
{
   qptr temp;
   int item;
   if(front)
   {
    temp=front;
    item=front->data;
    front=front->next;
    if(front==NULL)
    {
        rear=NULL;
    }
    free(temp);
   }
   else{
    item=-1;
   }
   return item;
}

void display()
{
    qptr temp;
    temp=front;
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
        printf("\nEnter\n1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\nEnter element to Enqueue: ");
                scanf("%d", &item);
                enqueue(item);
                break;
            case 2:
                item = dequeue();
                if (item == -1)
                    printf("\nStack Underflow!\n");
                else
                    printf("\nPopped element: %d\n", item);
                break;
            case 3:
                printf("\nQueue: ");
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
