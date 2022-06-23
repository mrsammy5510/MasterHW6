#include <stdlib.h>
#include <stdio.h>

struct column
{
    int data;        //沒有data
    column* next;
};

int main()
{
    const char* filename = "facebook_combined.txt";
    FILE* input_file = fopen(filename, "r");
    int node, linking_node;
    column graph [5000];
    column* current;
    if (!input_file)
        exit(EXIT_FAILURE);

    for(int i = 0;i<=4999;i++)
    {
        graph[i].data = -1;
    }
    char *contents = NULL;
    size_t len = 0;
    /*while (getline(&contents, &len, input_file) != -1){
        printf("%d %d", contents);
    }*/
    while(fscanf(input_file, "%d %d", &node, &linking_node)!= -1)
    {
        current = &graph[node];
        printf("%d",current->data);
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
    }
    fclose(input_file);
    free(contents);

    exit(EXIT_SUCCESS);
}