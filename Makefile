FLAGS=-Wall -Wextra -Werror -Wpedantic
LDFLAGS= -lm
CC=clang $(CFLAGS)

all	:	pathfinder pathfinder.o stack.o graph.o
.PHONY	:	all
pathfinder	:	pathfinder.o stack.o graph.o
		$(CC) $(LDFLAGS) -o pathfinder pathfinder.o stack.o graph.o
pathfinder.o	:	./src/pathfinder.c
	$(CC) -c ./src/pathfinder.c
stack.o	:	./src/stack.c
	$(CC) -c ./src/stack.c
graph.o	:	./src/graph.c
	$(CC) -c ./src/graph.c
clean	:
	rm -rf pathfinder pathfinder.o stack.o graph.o infer-out
infer	:	clean
	infer-capture -- make
	infer-analyze -- make
valgrind	:	pathfinder
		valgrind ./pathfinder