/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stack_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_stack_node_t* upo_stack_node_create(void *data)
{
    upo_stack_node_t *node = malloc(sizeof(upo_stack_node_t));
    if (node == NULL)
    {
        perror("Unable to create a node stack");
        abort();
    }

    node->data = data;
    node->next = NULL;

    return node;
}

upo_stack_t upo_stack_create()
{
    upo_stack_t stack = malloc(sizeof(struct upo_stack_s));
    if (stack == NULL)
    {
        perror("Unable to create a stack");
        abort();
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void upo_stack_destroy(upo_stack_t stack, int destroy_data)
{
    if (stack != NULL)
    {
        upo_stack_clear(stack, destroy_data);
        free(stack);
    }
}

void upo_stack_push(upo_stack_t stack, void *data)
{
    if(stack!=NULL){
        upo_stack_node_t *nodo=malloc(sizeof(upo_stack_node_t));
        if(nodo!=NULL)
        {
            nodo->data=data;
            nodo->next=stack->top;
            stack->top=nodo;
            stack->size+=1;
        }
    }   
}

void upo_stack_pop(upo_stack_t stack, int destroy_data)
{
    if(!upo_stack_is_empty(stack))
    {
        upo_stack_node_t *nodo=stack->top;
        stack->top=stack->top->next;
        stack->size-=1;

        if(destroy_data) free(nodo->data);

        free(nodo);
    }
}

    
void* upo_stack_top(const upo_stack_t stack)
{
        if(upo_stack_is_empty(stack)==0) return stack->top->data;
        return NULL;
}

int upo_stack_is_empty(const upo_stack_t stack)
{
    if(stack!=NULL){
        if(stack->size==0) return 1;
        else return 0;
    }
    else return 1;
}

size_t upo_stack_size(const upo_stack_t stack)
{
    if(stack!=NULL) return stack->size;  
    else return 0; 
}

void upo_stack_clear(upo_stack_t stack, int destroy_data)
{
    if(stack!=NULL){
        for(;stack->size>0;stack->size-=1){
            upo_stack_node_t *nodo=stack->top;
            stack->top=stack->top->next;
            if(destroy_data!=0) free(nodo->data);
            free(nodo);
        }
    }
}
