# pathfinder
Stack recursion program that finds paths from node A to node Z given a map input.

**Project Files**:
> *src*
> - pathfinder.c:
>   - This is the main file for the progra. It contains the algorithm that creates a graph, finds paths, and parses through options.
> - graph.c/h:
>   - This file contains functions and structures used to create, delete, and manipulate a graph.
> - stack.c/h:
>   - This file contains functions and structures used to create, delete, and manipulate a stack.
> *test_scripts*
> - simple_directed_path.sh:
>   - This file is the test file testing a directed graph with 3 paths.
> - simple_path.sh:
>   - This file is the test file testing a non-directed graph with 2 paths.
> - utils.sh:
>   - This file contains functions used by the test files.
> *test_files*
> - simple_path.txt:
>   - This file is the file contains an input graph (verticies and edges) that is used as input for the shell tests.
> *Others*
> - Makefile:
>   - This file is used to create a binary executable "pathfinder" for the program.
> - README.md:
>   - This file is the README.md. It contains a description of the project and the files contained in it.
> - test.sh:
>   - This is the main test file. When ran it executes the other test files and gives useful feedback.

**Running the Program**
> To execute the program create the binary executable by typing "make" or "make all" from the same directory as the Makefile.

> Run the program using the command "./pathfinder [options ...]"

> By default the graph will be created using input from STDIN and will be non-directed.

**Options**
> - -i <inputfile.txt> : file to create the graph from.
> - -u: makes the graph undirected.
> - -d: makes the graph directed.
> - -m: specifies that the adjacency matrix be printed. 

