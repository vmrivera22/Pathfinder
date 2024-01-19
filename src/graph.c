#include "graph.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph* graph_create(){
    struct Graph *newGraph = (struct Graph *)malloc(1 * sizeof(struct Graph));
    newGraph->visited = (uint32_t *)calloc(GRAPH_SIZE, sizeof(uint32_t));
    newGraph->adjList = (uint32_t **)malloc(GRAPH_SIZE * sizeof(uint32_t*));
    for(int i = 0; i < GRAPH_SIZE; i++){
        newGraph->adjList[i] = (uint32_t*)malloc(GRAPH_SIZE * sizeof(uint32_t));
    }
    for(int i = 0; i < GRAPH_SIZE; i++){
        for(int j = 0; j < GRAPH_SIZE; j++){
            newGraph->adjList[i][j] = 0;
        }
    }
    return newGraph;
}

void graph_delete(struct Graph *g){
    for(int i = 0; i < GRAPH_SIZE; i++){
        free(g->adjList[i]);
    }
    free(g->adjList);
    free(g->visited);
    free(g);
}

void add_edge(struct Graph *g, uint32_t src, uint32_t dest, bool bi_directional){
    g->adjList[src-65][dest-65] = 1;
    if(bi_directional){
        g->adjList[dest-65][src-65] = 1;
    }
    return;
};

void print_graph(struct Graph *g){
    for(int i = 0; i < GRAPH_SIZE; i++){
        for(int j = 0; j < GRAPH_SIZE; j++){
            if(g->adjList[i][j]){
                printf("[%c->%c]", (char)i+65, (char)j+65);
            }
        }
    }
    printf("\n");
}