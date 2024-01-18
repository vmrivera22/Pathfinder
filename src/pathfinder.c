#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char **argv)
{
    int c;
    bool directed = false;
    bool print_matrix = false;
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
            printf("%s", input);
        }
    }
    return 0;
}