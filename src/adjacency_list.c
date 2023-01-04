#include "adjacency_list.h"

graph_t *graph_create(size_t vertices)
{
    // Create a graph
    graph_t *graph = calloc(1, sizeof(graph_t));
    if (NULL == graph)
    {
        goto END;
    }

    // Initialize vertices
    graph->num_vertices = vertices;

    // Create an adjacency list for each vertex
    graph->adj_lists = calloc(vertices, sizeof(linked_list_t));
    if (NULL == graph->adj_lists)
    {
        free(graph);
        graph = NULL;
        goto END;
    }

END:
    return graph;
}

exit_code_t add_edge(graph_t *graph, void *src, void *dest)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = push_head(graph->adj_lists, dest)

}