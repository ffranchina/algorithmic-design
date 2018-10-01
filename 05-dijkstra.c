#include <stdio.h>
#include <math.h>

#include "prettyprint.h"
#include "graph.h"
#include "list.h"

#define SIZE 10

int nearest_node(NodeList *queue, double *distances) {
    double min_dist = INFINITY;
    int node;

    while (queue) {
        double dist = distances[queue->value];

        if (dist < min_dist) {
            min_dist = dist;
            node = queue->value;
        }

        queue = queue->next;
    }

    return node;
}

void dijkstra(Graph *g, int source_node, double *distances_output) {
    int q[g->size];
    NodeList *queue = NULL;

    for (int i = 0; i < g->size; i++) {
        distances_output[i] = INFINITY;
        add(&queue, i);
    }

    distances_output[source_node] = 0;

    while (queue->next) {
        int node = nearest_node(queue, distances_output);

        del(&queue, node);

        for (int j = 0; j < g->size; j++) {
            if (g->adjacency_matrix[node * g->size + j]) {
                double alt = distances_output[node] + g->adjacency_matrix[node * g->size + j];

                if (alt < distances_output[j])
                    distances_output[j] = alt;
            }
        }
    }
}

void main() {
    double values[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int source_node;
    double distances[SIZE];
    
    Graph *G = make_graph(SIZE);

    fill(G, values, SIZE);
    connect_w(G, 0, 1, 2);
    connect_w(G, 0, 3, 1);
    connect_w(G, 1, 2, 3);
    connect_w(G, 2, 0, 7);
    connect_w(G, 2, 4, 1);
    connect_w(G, 2, 5, 5);
    connect_w(G, 4, 6, 3);
    connect_w(G, 4, 7, 1);
    connect_w(G, 4, 9, 6);
    connect_w(G, 5, 6, 2);
    connect_w(G, 6, 7, 2);
    connect_w(G, 8, 3, 5);
    connect_w(G, 9, 8, 2);

    printf("Values of the nodes:\n");
    print_array(G->node_values, SIZE);

    printf("\nAdjacency matrix:");
    print_adjm(G->adjacency_matrix, SIZE);

    source_node = 0;
    dijkstra(G, source_node, distances);

    printf("\nDistances from the source node (%d):\n", source_node);
    print_array(distances, SIZE);

    destroy_graph(G); 
}
