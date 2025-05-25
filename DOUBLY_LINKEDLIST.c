#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* previous;
    int data;
    struct node* next;
};
typedef struct node* nodeptr;

nodeptr head = NULL;

void insert(int item) 
{
    nodeptr temp = (nodeptr)malloc(sizeof(struct node));
    temp->data = item;
    temp->next = head;
    temp->previous = NULL;
    if (head != NULL)
        head->previous = temp;
    head = temp;
}

int deleteBeginning() 
{
    if (head == NULL) 
    {
        return -1; // List is empty
    }

    nodeptr temp = head;
    int item = temp->data;

    // Update head to the next node
    head = head->next;

    if (head != NULL) 
    {
        head->previous = NULL; // Set the new head's previous to NULL
    }

    free(temp); // Free the memory of the deleted node
    return item; // Return the deleted item's value
}

void display() 
{
    nodeptr temp = head;
    if (temp == NULL) 
    {
        printf("List is empty\n");
        return;
    }

    printf("List: ");
    while (temp != NULL) 
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) 
{
    int choice, item;
    while (1) 
    {
        printf("Enter\n 1. Insert\n 2. Delete from Beginning\n 3. Display\n 4. Exit\n");
        scanf("%d", &choice);
        switch (choice) 
        {
        case 1:
            printf("Enter data to be inserted: ");
            scanf("%d", &item);
            insert(item);
            break;
        case 2:
            item = deleteBeginning();
            if (item == -1)
                printf("List is empty, cannot delete\n");
            else
                printf("Element deleted: %d\n", item);
            break;
        case 3:
            display();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
