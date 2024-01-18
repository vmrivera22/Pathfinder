#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create()
{
    Stack *s = (Stack *)malloc(1 * sizeof(Stack));
    s->item = (uint32_t *)calloc(MINIMUM, sizeof(uint32_t));
    s->capacity = MINIMUM;
    s->top = -1;
    return s;
}

void stack_delete(Stack *s)
{
    free(s->item);
    free(s);
}

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

bool stack_pop(Stack *s, uint32_t *item)
{
    if (stack_empty(s))
    {
        return false;
    }
    s->capacity += 1;
    item = &s->item[s->top];
    s->top -= 1;
    return true;
}

void stack_print(Stack *s)
{
    for (int i = s->top; i >= 0; i--)
    {
        printf("%u", s->item[i]);
        if (i != 0)
        {
            printf("->");
        }
    }
}
