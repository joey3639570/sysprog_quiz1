#include <stdio.h>
#include <stdlib.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

int main()
{
    node_t *new_node = malloc(sizeof(node_t));
    node_t *new_node_2 = malloc(sizeof(node_t));
    node_t *head = new_node;
    //node_t **indirect = head;
    new_node->value = 1;
    new_node->next = new_node_2;
    new_node_2->value = 2;
    new_node_2->next = NULL;
    
    printf("head %d\n",head);
    printf("new_node %d\n",new_node);    

    //indirect = &((*indirect)->next);
    
    free(new_node);
    free(new_node_2);
    return 0;
}
