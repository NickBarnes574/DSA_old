#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "linked_list.h"

typedef struct graph
{
    size_t num_vertices;
    linked_list_t *adj_lists;
} graph_t;

graph_t *graph_create(size_t vertices);

exit_code_t add_edge(graph_t *graph, void *src, void *dest);

void graph_print(graph_t *graph);

#endif