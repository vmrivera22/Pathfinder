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

// Function returns the file descriptor of the newly created temp file containing STDIN data.
int copy_stdin(){
  int temp_file = open("temporary.txt",  O_RDWR | O_CREAT); // O_TMPFILE
  uint8_t *file_out = (uint8_t *)calloc(4096, sizeof(uint8_t)); // Buffer to hold stdin input before writing to file.
  int buffer_size = BUFF_SIZE;
  int count = 0;
  while((read(STDIN_FILENO, file_out, 1)) > 0){ // Read from stdin
    count++;
    write(temp_file, file_out, 1);
    if(count == buffer_size){ // If the buffer is full then double its size.
      buffer_size = buffer_size * 2;
      file_out = (uint8_t *)realloc(file_out, buffer_size);
    }
  }
  return temp_file;
}

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

/*
uint32_t *buffer = (uint32_t*)calloc(BUFF_SIZE+1, sizeof(uint32_t));
    while(read_buffer(buffer, BUFF_SIZE, input_file) > 0){
        //printf("%s", (char*)buffer);
        char *token = strtok((char*)buffer, "\n\r");
        while(token != NULL) {
            printf("->%s\n", token);
            token = strtok(NULL, "\n\r");
        }

    }
    printf("\n");
*/

struct Graph* file_graph(char *input){
    struct Graph *g = graph_create();
    FILE *fp = fopen(input, "r+");
    if(fp == NULL){//input_file == -1){
        fprintf(stdout, "Unable to open input file. Make sure the file exists and the path is correct.\n");
        exit(1);
    }
    int end_of_file = 1;
    char a[2];
    char b[2];
    while(end_of_file > 0){
        end_of_file = fscanf(fp, "%c%c\n", a, b);
        if(end_of_file <= 0){
            break;
        }
        add_edge(g, (uint32_t)a[0], (uint32_t)b[0], false);
    }
    fclose(fp);
    //print_graph(g);
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
            uint32_t item; //= (uint32_t *)calloc(1, sizeof(uint32_t));
            stack_pop(s, &item);
            printf("ITEM: %c\n", (char)item);
            g->visited[item-65] = 0;       
        }
    } // for all possible next node:
    return;


    // push current node
    // stack_search(next_node)
    // path.pop()
    // return
}

int main(int argc, char **argv)
{
    int c;
    bool directed = false;
    bool print_matrix = false;
    //uint32_t input_file = -2;
    char *input;
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
    //if(fp == NULL){//input_file == -2){
        //input_file = copy_stdin();
    //}
    struct Graph *g = file_graph(input);
    Stack *stack = stack_create();
    stack_search(stack, g, 0);
    return 0;
}