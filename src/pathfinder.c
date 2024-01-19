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

#define BUFF_SIZE 4096

int read_buffer(void *buffer, int byte_num, int infile){
    memset(buffer, '\0', byte_num);
    int t_bread = 0;
    int check = 1;
    while((t_bread < byte_num) && (check > 0)){
        check = read(infile, buffer+t_bread, byte_num-t_bread);
        t_bread += check;
    }
    if(check < 0){
        fprintf(stderr, "%s\n", strerror(errno));
    }
    return t_bread;
}

struct Graph* file_graph(char *input, bool directed){
    FILE *fp = stdin;
    struct Graph *g = graph_create();
    if(input){
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
        end_of_file = fscanf(fp, "%c%c\n", a, b);
        if(end_of_file <= 0){
            break;
        }
        printf("a\n");
        add_edge(g, (uint32_t)a[0], (uint32_t)b[0], true);
        printf("b\n");
    }
    print_graph(g);
    printf("\n");
    fclose(fp);
    return g;
}

void stack_search(Stack *s, struct Graph *g, uint32_t curr_node){
    if(curr_node == 25){
        stack_print(s);
        return;
    }

    for(int i = 0; i < GRAPH_SIZE; i++){
        if(g->adjList[curr_node][i] && !g->visited[i]){
            if(stack_empty(s)){
                stack_push(s, 65);
                g->visited[0] = 1;
            }
            g->visited[i] = 1;
            stack_push(s, i+65);
            stack_search(s, g, i);
            uint32_t item;
            stack_pop(s, &item);
            printf("ITEM: %c\n", (char)item);
            g->visited[item-65] = 0;       
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
    //if(input == NULL){
    //    input = copy_stdin();
    //}
    struct Graph *g = file_graph(input, directed);
    Stack *stack = stack_create();
    stack_search(stack, g, 0);
    graph_delete(g);
    stack_delete(stack);
    return 0;
}