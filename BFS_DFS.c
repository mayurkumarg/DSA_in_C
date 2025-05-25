#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct node{
    int vertex;
    struct node* next;
}node;

node* G[MAX]={NULL};
int visited[MAX]={0};

node* createnode(int v)
{
    node* newnode=(node*)malloc(sizeof(node));
    newnode->vertex=v;
    newnode->next=NULL;
    return newnode;
}

void addEdge(int u, int v)
{
    node* newNode = createNode(v);
    newNode->next = G[u];
    G[u] = newNode;

    newNode = createNode(u);
    newNode->next = G[v];
    G[v] = newNode;

}

void BFS(int i)
{
    int queue[MAX],front=0,rear=0;
    queue[rear++]=i;
    visited[i]=1;
    printf(" %d ",i);
    while(front<rear)
    {
        int v=queue[front++];
        for(node* p=G[v];p!=NULL;p=p->next)
        {
            if(!visited[p->vertex])
            {
                queue[rear++]=p->vertex;
                visited[p->vertex]=1;
                printf(" %d ",p->vertex);
            }
        }
    }
}

void DFS(int i)
{

    visited[i]=1;
    printf(" %d ",i);

    for(node* p=G[i];p!=NULL;p=p->next)
    {
        if(!visited[p->vertex])
        {
            DFS(p->vertex);
        }
    }
    
}

int main()
{
    int v,u, edges, vertices,start;
    printf("Enter the edges: ");
    scanf("%d",&edges);
    printf("Enter the vertices: ");
    scanf("%d",&vertices);

    for(int i=0;i<edges;i++)
    {
        scanf("%d %d",&u,&v);
        addEdge(u,v);
    }
    
    printf("Enter the starting vertex for traversal: ");
    scanf("%d", &start);


    printf("DFS TRAVERSAL: ");
    for(int d=0;d<vertices;d++)
    {
        visited[d]=0;
    }
    DFS(start);

    printf("BFS TRAVERSAL: ");
    for(int d=0;d<vertices;d++)
    {
        visited[d]=0;
    }
    BFS(start);


    return 0;

}