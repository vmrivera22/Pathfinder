#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define GRAPH_SIZE 26

struct Graph {
    uint32_t numVertices;
    uint32_t numEdges;
    uint32_t* visited;
    uint32_t** adjList;
};

struct Graph* graph_create(void);
void graph_delete(struct Graph *g);
void add_edge(struct Graph *g, uint32_t src, uint32_t dest, bool bi_directional);
void print_graph(struct Graph *g); 