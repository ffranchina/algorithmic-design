#include <stdlib.h>

typedef struct t_node_list {
    int value;
    struct t_node_list *next;
} NodeList;


NodeList *push(NodeList **root, int value) {
    NodeList *new_node = malloc(sizeof(NodeList));
    new_node->value = value;
    new_node->next = *root;

    *root = new_node;

    return new_node;
}

int pop(NodeList **root) {
    if (!(*root)) return -1;

    int value = (*root)->value;
    NodeList *tmp = *root;

    *root = (*root)->next;
    free(tmp);

    return value;
}

int is_in(NodeList *root, int value) {
    NodeList *tmp = root;
    
    if (!tmp) return 0;

    while (tmp->value != value && tmp->next != NULL)
        tmp = tmp->next;

    if (tmp->value == value)
        return 1;
    else
        return 0;
}
