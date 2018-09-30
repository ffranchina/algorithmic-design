#include <stdio.h>
#include <string.h>

#include "prettyprint.h"
#include "graph.h"
#include "list.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define SIZE 5

void find_scc(Graph *g, char *sets_output, int *indexes, int *lowlinks, int *idx, NodeList **stack, int node) {
    indexes[node] = *idx;
    lowlinks[node] = *idx;
    (*idx)++;
    push(stack, node);

    for (int j = 0; j < g->size; j++)
        if (g->adjacency_matrix[node * g->size + j] && !indexes[j]) {
            find_scc(g, sets_output, indexes, lowlinks, idx, stack, j);
            lowlinks[node] = MIN(lowlinks[node], lowlinks[j]);
        } else if (g->adjacency_matrix[node * g->size + j] && is_in(*stack, j)) {
            lowlinks[node] = MIN(lowlinks[node], indexes[j]);
        }

    if (lowlinks[node] == indexes[node]) {
        int from_stack;
        do {
            from_stack = pop(stack);
            sets_output[from_stack] = 'A' + lowlinks[node];
        } while (from_stack != node);
    }
}

void tarjan(Graph *g, char *sets_output) {
    int index = 0;
    int indexes[g->size], lowlinks[g->size];
    NodeList *stack = NULL;

    memset(indexes, 0, g->size * sizeof(int));
    memset(lowlinks, 0, g->size * sizeof(int));

    for (int i = 0; i < g->size; i++) 
        if (!indexes[i])
            find_scc(g, sets_output, indexes, lowlinks, &index, &stack, i);
}

void main() {
    double values[SIZE] = {3.14, 66.3, 2.81, 6.27, 99.9};
    char scc_sets[SIZE];
    
    Graph *G = make_graph(SIZE);

    fill(G, values, SIZE);
    connect(G, 0, 2);
    connect(G, 2, 0);
    connect(G, 2, 1);
    connect(G, 2, 3);
    connect(G, 3, 1);
    connect(G, 3, 4);

    printf("Values of the nodes:\n");
    print_array(G->node_values, SIZE);

    printf("\nAdjacency matrix:");
    print_adjm(G->adjacency_matrix, SIZE);

    tarjan(G, scc_sets);

    printf("\nSCC for the graph: [ %s ]\n", scc_sets);

    destroy_graph(G);
}
