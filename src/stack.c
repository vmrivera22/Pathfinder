#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Function to initialize a stack.
Stack *stack_create()
{
    Stack *s = (Stack *)malloc(1 * sizeof(Stack));
    s->item = (uint32_t *)calloc(MINIMUM, sizeof(uint32_t));
    s->capacity = MINIMUM;
    s->top = -1;
    return s;
}

// Function to clear memory allocated to a stack.
void stack_delete(Stack *s)
{
    free(s->item);
    free(s);
}

// Function to check if a stack is empty.
bool stack_empty(Stack *s)
{
    if (s->capacity < 26)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to the size of the stack.
uint32_t stack_size(Stack *s){
    return s->top + 1;
}

// Function to add an item to the stack.
bool stack_push(Stack *s, uint32_t item)
{
    if (s->capacity <= 0)
    {
        return false;
    }
    s->capacity -= 1;
    s->top += 1;
    s->item[s->top] = item;
    return true;
}

// Function to remove an item from a stack.
bool stack_pop(Stack *s, uint32_t *item)
{
    if (stack_empty(s))
    {
        return false;
    }
    s->capacity += 1;
    *item = s->item[s->top];
    s->top -= 1;
    return true;
}

// Function to print the contents of a stack without popping.
void stack_print(Stack *s)
{
    for (int i = 0; i <= s->top; i++)
    {
        printf("%c", (char)s->item[i]);
        if (i != s->top)
        {
            printf("->");
        }
    }
    printf("\n");
}
