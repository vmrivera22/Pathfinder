#include "stack.h"
#include "graph.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define Z 25

// Function used to create a graph from the input file.
// input: a character array containing the file to read from - if NULL then read from stdin.
// directed: indicates if the graph should be a directed or undirected graph.
struct Graph* file_graph(char *input, bool directed){
    FILE *fp = stdin; // Set file pointer to stdin.
    struct Graph *g = graph_create();
    if(input){ // If the input argument is not null open the file and set fd to the FILE *.
        fp = fopen(input, "r+");
        if(fp == NULL){
            fprintf(stdout, "Unable to open input file. Make sure the file exists and the path is correct.\n");
            exit(1);
        }
    }
    int end_of_file = 1;
    char a[2];
    char b[2];
    while(end_of_file > 0){
        end_of_file = fscanf(fp, "%c%c\n", a, b); // Read 2 characters from the file at a time.
        if(end_of_file <= 0){
            break;
        }
        add_edge(g, (uint32_t)a[0], (uint32_t)b[0], true); // Add an edge between the two read in "nodes".
    }
    fclose(fp);
    return g;
}

// DFS function used to find all possible paths from "node" A to "node" Z.
// s: pointer to stack that will hold the current route.
// g: pointer to the graph that was created using the input file or stdin.
// curr_node: the index current row of the matrix i.e. the current "node".
void stack_search(Stack *s, struct Graph *g, uint32_t curr_node){
    if(curr_node == Z){ // If the current node is Z a path was found.
        stack_print(s);
        return;
    }

    for(int i = 0; i < GRAPH_SIZE; i++){ // Iterate through all possible edges of the current node.
        if(g->adjList[curr_node][i] && !g->visited[i]){ // If there is a connection that we have not visited take it.
            if(stack_empty(s)){ // Initial push of "A" node.
                stack_push(s, 65);
                g->visited[0] = 1;
            }
            g->visited[i] = 1; // Mark the next node as visited.
            stack_push(s, i+65); // Push the next node.
            stack_search(s, g, i); // Recursivly check for connections to the next node.
            uint32_t item;
            stack_pop(s, &item);
            printf("ITEM: %c\n", (char)item);
            g->visited[item-65] = 0; // Make the removed item from the stack unvisited.       
        }
    }
    return;
}

int main(int argc, char **argv)
{
    int c;
    bool directed = false;
    bool print_matrix = false;
    char *input = NULL;
    while ((c = getopt(argc, argv, "udmi:")) != -1)
    {
        switch (c)
        {
        case 'u':
            directed = false;
            break;
        case 'd':
            directed = true;
            break;
        case 'm':
            print_matrix = true;
            break;
        case 'i':
            input = optarg;
            break;
        }
    }

    struct Graph *g = file_graph(input, directed); // Create the graph.
    Stack *stack = stack_create();
    stack_search(stack, g, 0); // Find the paths from node "A" to node "Z" in the graph.
    
    // Clean up allocated memory.
    graph_delete(g);
    stack_delete(stack);
    return 0;
}