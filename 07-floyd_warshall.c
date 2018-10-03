#include <stdio.h>
#include <math.h>

#include "prettyprint.h"
#include "graph.h"

#define SIZE 10

void floyd_warshall(Graph *g, double *distances_output) {
    for (int i = 0; i < g->size; i++)
        for (int j = 0; j < g->size; j++)
            if (g->adjacency_matrix[i * g->size + j])
                distances_output[i * g->size + j] = g->adjacency_matrix[i * g->size + j];
            else
                distances_output[i * g->size + j] = INFINITY;

    for (int i = 0; i < g->size; i++)
        distances_output[i * g->size + i] = 0;

    for (int k = 0; k < g->size; k++)
        for (int i = 0; i < g->size; i++)
            for (int j = 0; j < g->size; j++)
                if (distances_output[i * g->size + j] > distances_output[i * g->size + k] + distances_output[k * g->size + j])
                    (distances_output[i * g->size + j] = distances_output[i * g->size + k] + distances_output[k * g->size + j]);

}

void main() {
    double values[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int source_node;
    double distances[SIZE * SIZE];
    
    Graph *G = make_graph(SIZE);

    fill(G, values, SIZE);
    connect_w(G, 0, 2, 2);
    connect_w(G, 1, 3, 2);
    connect_w(G, 2, 1, 3);
    connect_w(G, 3, 0, 3);
    connect_w(G, 3, 1, 4);
    connect_w(G, 3, 4, 5);
    connect_w(G, 4, 8, 3);
    connect_w(G, 5, 2, 7);
    connect_w(G, 5, 4, 3);
    connect_w(G, 5, 6, 1);
    connect_w(G, 6, 7, 3);
    connect_w(G, 6, 8, 2);
    connect_w(G, 7, 8, 6);
    connect_w(G, 8, 4, 9);
    connect_w(G, 8, 5, 1);
    connect_w(G, 9, 4, 1);

    printf("Values of the nodes:\n");
    print_array(G->node_values, SIZE);

    printf("\nAdjacency matrix:");
    print_adjm(G->adjacency_matrix, SIZE);

    source_node = 0;
    floyd_warshall(G, distances);

    printf("\nDistances between vertices:");
    print_matrix(distances, SIZE);

    destroy_graph(G); 
}
