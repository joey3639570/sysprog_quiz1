#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void reverse(node_t **head)
{
    node_t *cursor = NULL;
    while (*head) {
        node_t *next = (*head)->next;
       (*head)->next = cursor; 
        cursor = *head;
        *head = next;
    }
    *head = cursor;
}

node_t *rev_recursive(node_t *head)
{
    // If there isn't any node left or not even node, return head.
    if(!head || !head->next){
        return head;
    }
    node_t *rev_head = rev_recursive(head->next);
    head->next->next = head;
    head->next = NULL;
    return rev_head;
}

void recursive_reverse(node_t **head)
{
    *head = rev_recursive(*head);
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

void randomize ( node_t **head ){ 
    // Use a different seed value so that we don't get same 
    // result each time we run this program 
    srand ( time(NULL) ); 
    node_t *old_head, *cursor, **indirect;
    int range = 0;
    old_head = cursor = *head;
    // get list length
    while(cursor){
        range += 1;
        cursor = cursor->next;
    }
    *head = NULL;
    for(;range > 0; --range){
        // Start from old head
        indirect = &old_head;
        // move to selected node
        for(int i = rand() % range;i > 0; --i)
            indirect = &(*indirect)->next;
        // move selected node to new list
        // Down below is the part for swapping
        node_t *tmp = *indirect;
        *indirect = (*indirect)->next;
        tmp->next = *head;
        *head = tmp;
    }
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;
    printf("Nothing first ::\n");
    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);
    printf("After Adding ::\n");
    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);
    printf("After removing ::\n");
    print_list(head);

    swap_pair(&head);
    printf("After Swapping Pair ::\n");
    print_list(head);

    reverse(&head);
    printf("After reverse ::\n");
    print_list(head);

    recursive_reverse(&head);
    printf("After recursive_reverse ::\n");
    print_list(head);

    randomize(&head);
    printf("Randomize ::\n");
    print_list(head);

    return 0;
}
