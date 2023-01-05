#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "linked_lists/singly_linked_list.h"
#include "array_list.h"

typedef struct vertex
{
    size_t label;
    singly_linked_list_t *neighbors;
} vertex_t;

typedef struct edge
{
    size_t label;
    double weight;
} edge_t;

typedef struct adj_list
{
    bool is_directed;
    array_list_t *vertices;
} adj_list_t;

adj_list_t *adj_list_create(size_t vertices);

exit_code_t adj_list_add_vertex(adj_list_t *adj_list, void *vertex);

exit_code_t adj_list_add_edge(adj_list_t *adj_list, void *src, void *dst);

exit_code_t adj_list_remove_vertex(adj_list_t *adj_list, void **vertex);

exit_code_t adj_list_remove_edge(adj_list_t *adj_list, void *src, void **dst);

exit_code_t adj_list_get_list(adj_list_t *adj_list, void *vertex, singly_linked_list_t **list);

int adj_list_is_adjacent(adj_list_t *adj_list, void *src, void *dest);

singly_linked_list_t adj_list_get_lists(adj_list_t *adj_list);

int adj_list_vertex_count(adj_list_t *adj_list);

int adj_list_edge_count(adj_list_t *adj_list);

void adj_list_destroy();

void adj_list_print(adj_list_t *adj_list);

#endif