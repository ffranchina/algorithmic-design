#include <stdlib.h>

typedef struct t_graph {
    int size;
    double *node_values;
    short *adjacency_matrix;
} Graph;

Graph *make_graph(int node_number) {
    Graph *g = malloc(sizeof(Graph));

    g->size = node_number;
    g->node_values = malloc(sizeof(double) * node_number);
    g->adjacency_matrix = calloc(node_number * node_number, sizeof(short));

    return g;
}

int fill(Graph *g, double *values, int len) {
    if (len > g->size)
        return -1;
    
    int i;
    for (i = 0; i < len; i++)
        g->node_values[i] = values[i];

    return i; // returns the number of inserted nodes
}

int connect_w(Graph *g, int pos_a, int pos_b, int weight) {
    if (pos_a > g->size || pos_b > g->size || weight < 1)
        return 1;

    g->adjacency_matrix[pos_a * g->size + pos_b] = weight;

    return 0;
}

int connect(Graph *g, int pos_a, int pos_b) {
    if (pos_a > g->size || pos_b > g->size)
        return 1;

    g->adjacency_matrix[pos_a * g->size + pos_b] = 1;

    return 0;
}

void destroy_graph(Graph *g) {
    free(g->node_values);
    free(g->adjacency_matrix);
    free(g);
}
