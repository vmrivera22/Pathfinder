#include "graph.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function used to initialize a graph structure.
struct Graph* graph_create(){
    struct Graph *new_graph = (struct Graph *)malloc(1 * sizeof(struct Graph));
    new_graph->visited = (uint32_t *)calloc(GRAPH_SIZE, sizeof(uint32_t));
    new_graph->adj_list = (uint32_t **)malloc(GRAPH_SIZE * sizeof(uint32_t*));
    for(int i = 0; i < GRAPH_SIZE; i++){
        new_graph->adj_list[i] = (uint32_t*)malloc(GRAPH_SIZE * sizeof(uint32_t));
    }
    for(int i = 0; i < GRAPH_SIZE; i++){ // Make a matrix of GRAPH_SIZE X GRAPH_SIZE to represent all possible edges.
        for(int j = 0; j < GRAPH_SIZE; j++){
            new_graph->adj_list[i][j] = 0;
        }
    }
    return new_graph;
}

// Function to free up memory that was allocated to a graph.
void graph_delete(struct Graph *g){
    for(int i = 0; i < GRAPH_SIZE; i++){ // Free the memory allocated to edges nxn matrix.
        free(g->adj_list[i]);
    }
    free(g->adj_list);
    free(g->visited);
    free(g);
}

// Function to add an edge between two "nodes".
void add_edge(struct Graph *g, uint32_t src, uint32_t dest, bool bi_directional){
    g->adj_list[src-ASCII_A][dest-ASCII_A] = 1; // Set edge from src to dest.
    if(bi_directional){
        g->adj_list[dest-ASCII_A][src-ASCII_A] = 1; // Set edge from dest to src.
    }
    return;
};

// Function to print a graph - for debug purposes.
void print_graph(struct Graph *g){
    for(int i = 0; i < GRAPH_SIZE; i++){
        for(int j = 0; j < GRAPH_SIZE; j++){
            if(g->adj_list[i][j]){ // Print nodes if there is an edge between them.
                printf("[%c->%c]", (char)i+ASCII_A, (char)j+ASCII_A);
            }
        }
    }
    printf("\n");
}