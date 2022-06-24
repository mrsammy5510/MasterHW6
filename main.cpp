#include <stdlib.h>
#include <stdio.h>
#define QUEUE_SIZE 5000
struct column
{
    int data;        
    column* next;
};
int queue[QUEUE_SIZE] = {'\0'};
int visited[QUEUE_SIZE] = {0};
int front = 0;
int rear = 0;
column* current;
column graph [5000];

int Isemptyqueue(void)          //無法分辨Q滿或Q空
{
    if(rear==front)
        return 0;               //迴圈的判斷條件是0或非0
    else
        return 1;
}
void enqueue(int data)
{
    rear = (rear+1)%QUEUE_SIZE;
    if(rear==front)
        return;
    else
        queue[rear] = data;
}
int dequeue(void)
{
    int data;
    if(rear == front)
        return -1;
    else
    {
        front = (front+1)%QUEUE_SIZE;
        data = queue[front];
        return data;
    }
}
void BFS(int vertex)
{
    int bfs_now;
    visited[vertex] = 1;
    enqueue(vertex);
    while(Isemptyqueue())
    {
        bfs_now = dequeue();
        printf("%d ",bfs_now);
        current = &graph[bfs_now];

        while(current->data!=-1)
        {
            if(visited[current->data]!=1)
            {
                enqueue(current->data);
                visited[current->data] = 1;
            }
            current = current->next;
        }
        
    }
}
int main()
{
    const char* filename = "facebook_combined.txt";
    FILE* input_file = fopen(filename, "r");
    int node, linking_node,vertex;
    
    
    if (!input_file)
        exit(EXIT_FAILURE);

    for(int i = 0;i<=4999;i++)
    {
        graph[i].data = -1;
    }
    char *contents = NULL;
    size_t len = 0;

    while(fscanf(input_file, "%d %d", &node, &linking_node)!= -1)
    {
        current = &graph[node];                                     //node edge
        if(graph[node].data == -1) //還未寫入過連接點
        {
            graph[node].data = linking_node;
            graph[node].next = (column*)malloc(sizeof(column));
            (graph[node].next)->data = -1;
        }
        else //已寫入過
        {
            while(current->data != -1)
                current = current->next;

            current->data = linking_node;
            current->next = (column*)malloc(sizeof(column));
            (current->next)->data = -1;
        }

        current = &graph[linking_node];                             //linking node edge
        if(graph[linking_node].data == -1) //還未寫入過連接點
        {
            graph[linking_node].data = node;
            graph[linking_node].next = (column*)malloc(sizeof(column));
            (graph[linking_node].next)->data = -1;
        }
        else //已寫入過
        {
            while(current->data != -1)
                current = current->next;

            current->data = node;
            current->next = (column*)malloc(sizeof(column));
            (current->next)->data = -1;
        }
    }
    fclose(input_file);
    free(contents);
    printf("輸入要做BFS和DFS的數字:");
    scanf("%d",&vertex);
    BFS(vertex);
    exit(EXIT_SUCCESS);
}