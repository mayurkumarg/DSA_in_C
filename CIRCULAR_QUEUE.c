#include<stdio.h>
#include<stdlib.h>
#define MALLOC(x,size,type)(x=(type*)malloc(size*sizeof(type)))

typedef struct CIRCULAR_QUEUE
{
    int n;
}element;

int front=0,rear=0,capacity;

element *queue;

void copy(element *start,element *end, element *newqueue)
{
    for(element *i=newqueue,*j=start;j<=end;i++,j++)
    {
        *i=*j;
    }
}

void queuefull()
{
    element *newqueue;
    MALLOC(newqueue,capacity*2,element);
    int start=(front+1)%capacity;
    if(start<2)
    {
        copy(queue+start,queue+start+capacity-1,newqueue);
    }
    else{
        copy(queue+start,queue+capacity,newqueue);
        copy(queue,queue+rear+1,newqueue+capacity-start);
    }
    front=2*capacity-1;
    rear=capacity-1;
    capacity*=2;
    free(queue);
    queue=newqueue;
}

void addq(element i)
{
    rear=(rear+1)%capacity;
    if(front==rear)
    {
        queuefull();
    }
    
    queue[rear]=i;
}
element deleteq()
{
    
    if(front==rear)
    {
        element item = { .n = -1 };
        return item;
    }
    front=(front+1)%capacity;
    return queue[front];
    
}


void displayq()
{
    if(front==rear)
    {
        printf("The queue is still empty");
    }
    for(int i=(front+1)%capacity;i!=rear;i=(i+1)%capacity)
    {
        printf("  %d  ",queue[i].n);
    }
    
    printf("  %d \n ",queue[rear].n);

}

int main() {
    int choice;
    element item;
    printf("Enter initial size: ");
    scanf("%d", &capacity);
    MALLOC(queue, capacity, element);
    while (1) {
        printf("1. Add\n2. Delete\n3. Display\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &item.n);
                addq(item);
                break;
            case 2:
                item = deleteq();
                if (item.n == -1)
                    printf("Queue Empty\n");
                else
                    printf("Deleted: %d\n", item.n);
                break;
            case 3:
                displayq();
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}