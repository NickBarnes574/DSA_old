#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "linked_lists/singly_linked_list.h"

typedef struct vertex
{
    size_t label;
    singly_linked_list_t *neighbors;
} vertex_t;

typedef struct graph
{
    bool is_directed;
    array_list_t *vertices;
} graph_t;

graph_t *adj_list_create(size_t vertices);

exit_code_t add_vertex(graph_t *graph, void *vertex);

exit_code_t adj_list_add_edge(graph_t *graph, void *src, void *dst);

exit_code_t adj_list_remove_vertex(graph_t *graph, void **vertex);

exit_code_t adj_list_remove_edge(graph_t *graph, void *src, void **dst);

exit_code_t adj_list_get_list(graph_t *graph, void *vertex, singly_linked_list_t **list);

int adj_list_is_adjacent(graph_t *graph, void *src, void *dest);

singly_linked_list_t adj_list_get_lists(graph_t *graph);

int adj_list_vertex_count(graph_t *graph);

int adj_list_edge_count(graph_t *graph);

void adj_list_destroy();

void adj_list_print(graph_t *graph);

#endif