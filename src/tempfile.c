include "graph.h";
#define GRAPH_SIZE 26

//struct Node* node_create(uint32_t vertex){
//    Node *newNode = (Node *)malloc(1 * sizeof(Node));
//    newNode->vertex = vertex;
//    return newNode;
//}

struct Graph* graph_create(){
    Graph *newGraph = (Graph *)malloc(1 * sizeof(Graph));
    newGraph->visited = (uint32_t *)calloc(GRAPH_SIZE, sizeof(uint32_t));
    newGraph->adjList = (uint32_t **)malloc(GRAPH_SIZE * sizeof(int*));
    //newGraph->adjList = malloc(GRAPH_SIZE * sizeof(Node *));
    for(int i = 0; i < GRAPH_SIZE; i++){
        newGraph->adjList[i] = (uint32_t*)malloc(GRAPH_SIZE * sizeof(uint32_t));
        newGraph->adjList[i] = NULL;
    }

    for(int i = 0; i < GRAPH_SIZE; i++){
        for(int j = 0; j < GRAPH_SIZE; j++){
            newGraph->adjList[i][j] = 0;
        }
    }
    return newGraph;
}

void graph_delete(Graph *g){
    free(g->visited);
    free(g->adjList);
    free(g);
}

void add_edge(Graph *g, uint32_t src, uint32_t dest){
    node* newNode = node_create(dest);
    newNode->next = graph->adjList[src]; 
    graph->adjLists[src] = newNode;

    //newNode = createNode(src);
    //newNode->next = g->adjList[dest];
    //g->adjList[dest] = newNode;
   // g->adjList[src][dest] = 1;
};