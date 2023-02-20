#include "linked_lists/circular_singly_linked_list.h"

struct csll_node
{
    void *data;
    csll_node_t *next;
};

struct circular_singly_linked_list
{
    csll_node_t *head;
    csll_node_t *tail;
    size_t current_size;
};

typedef struct results
{
    csll_node_t *previous_node;
    csll_node_t *current_node;
} results_t;

/// @brief Creates a new node
/// @param data The data to be added.
/// @return new_csll_node_t
static csll_node_t *create_new_node(void *data);

static exit_code_t get_nodes_at_pos(results_t **results_p, circular_singly_linked_list_t *list, size_t position);

circular_singly_linked_list_t *csll_create(void)
{
    // 1. Create the list
    circular_singly_linked_list_t *list = calloc(1, sizeof(circular_singly_linked_list_t));

    // 2. Check if memory allocation was successful
    if (NULL != list)
    {
        list->current_size = 0;
        list->head = NULL;
        list->tail = NULL;
    }

    return list;
}

exit_code_t csll_push_head(circular_singly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    csll_node_t *new_node = create_new_node(data); // Create a new node

    // 3. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
        list->tail->next = list->head;
    }    
    else
    {
        // b. Insert node at the front of the list
        new_node->next = list->tail->next;
        list->tail->next = new_node;
        list->head = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t csll_push_tail(circular_singly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    csll_node_t *new_node = create_new_node(data); // Create a new node

    // 3. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
        list->tail->next = list->head;
    }    
    else
    {
        // b. Insert node at the back of the list
        list->tail->next = new_node;
        list->tail = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t csll_push_position(circular_singly_linked_list_t *list, void *data, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 3. Check if position is out of range
    if ((position > list->current_size) || (position == 0))
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    csll_node_t *new_node = create_new_node(data); // Create a new node

    // 4. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        // Retrieve the node at the current position, as well as the previous adjacent node
        results_t *results = NULL;
        exit_code = get_nodes_at_pos(&results, list, position);
        if (E_SUCCESS != exit_code)
        {
            free(results);
            results = NULL;
            goto END;
        }

        new_node->next = results->current_node;
        results->previous_node->next = new_node;

        results->current_node = new_node;

        free(results);
        results = NULL;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void *csll_peek_head(circular_singly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;

END:
    return data;
}

void *csll_peek_tail(circular_singly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->tail->data;

END:
    return data;
}

void *csll_peek_position(circular_singly_linked_list_t *list, size_t position)
{
    void *data = NULL;

    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    // Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        goto END;
    }

    // Retrieve the node at the current position
    results_t *results = NULL;
    exit_code_t exit_code = get_nodes_at_pos(&results, list, position);
    if (E_SUCCESS != exit_code)
    {
        free(results);
        results = NULL;
        goto END;
    }

    data = results->current_node->data;

    free(results);
    results = NULL;

END:
    return data;
}

void *csll_pop_head(circular_singly_linked_list_t *list)
{
    void *data = NULL;
    
    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;
    csll_remove_head(list);

END:
    return data;
}

void *csll_pop_tail(circular_singly_linked_list_t *list)
{
    void *data = NULL;
    
    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->tail->data;
    csll_remove_tail(list);

END:
    return data;
}

void *csll_pop_position(circular_singly_linked_list_t *list, size_t position)
{
    void *data = NULL;
    
    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        goto END;
    }

    // Retrieve the node at the current position
    results_t *results = NULL;
    exit_code_t exit_code = get_nodes_at_pos(&results, list, position);
    if (E_SUCCESS != exit_code)
    {
        free(results);
        results = NULL;
        goto END;
    }


    data = results->current_node->data;

    free(results);
    results = NULL;

    csll_remove_position(list, position);

END:
    return data;
}

exit_code_t csll_remove_head(circular_singly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // 1. Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 3. Check if there is only one node in the list
    if (NULL == list->head->next)
    {
        free(list->head);
        list->head = NULL;
    }
    else
    {
        csll_node_t *temp = list->head->next;

        free(list->head);
        list->head = NULL;

        list->head = temp;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t csll_remove_tail(circular_singly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // 1. Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->tail))
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 3. Check if there is only one node in the list
    if (NULL == list->head->next)
    {
        free(list->tail);
        list->tail = NULL;
    }
    else
    {
        results_t *results = NULL;
        exit_code = get_nodes_at_pos(&results, list, list->current_size);
        if (E_SUCCESS != exit_code)
        {
            free(results);
            results = NULL;
            goto END;
        }

        list->tail = results->previous_node;

        free(results);
    }

    free(list->tail->next);
    list->tail->next = list->head;

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t csll_remove_position(circular_singly_linked_list_t *list, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    // 4. Check if position is at the head
    if (position == 1)
    {
        exit_code = csll_remove_head(list);
        goto END; 
    }

    // 5. Check if position is at the tail
    if (position == list->current_size)
    {
        exit_code = csll_remove_tail(list);
        goto END;  
    }

    // Retrieve the node at the current position, as well as the previous adjacent node
    results_t *results = NULL;
    exit_code = get_nodes_at_pos(&results, list, position);
    if (E_SUCCESS != exit_code)
    {
        free(results);
        results = NULL;
        goto END;
    }

    results->previous_node->next = results->current_node->next;

    free(results->current_node);
    results->current_node = NULL;

    free(results);
    results = NULL;
    
    // 4. Increment the size of the list
    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;    
}

exit_code_t csll_print_list(circular_singly_linked_list_t *list, void (*function_ptr)(void *))
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if list exists
    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 2. Check for NULL function pointer
    if (NULL == function_ptr)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    csll_node_t *current_node = NULL; // Create a current node

    current_node = list->head;
    

    // 4. Print the list
    //while (NULL != current_node)
    for (int idx = 0; idx < list->current_size * 2; idx++)
    {
        (*function_ptr)(current_node->data);

        current_node = current_node->next;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void csll_clear_list(circular_singly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    csll_node_t *current_node = (*list)->head;
    csll_node_t *next_node = NULL;

    // 2. Clear out all the nodes in the list
    for (size_t idx = 0; idx < (*list)->current_size; idx++)
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }

    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->current_size = 0;

END:
    return;
}

void csll_destroy_list(circular_singly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    // 2. Clear out all the nodes
    csll_clear_list(list);

    // 3. Destroy the list container
    free(*list);
    *list = NULL;

END:
    return;
}

csll_node_t *create_new_node(void *data)
{
    // 1. Allocate memory for new node
    csll_node_t *new_node = calloc(1, sizeof(csll_node_t));
    if (NULL == new_node)
    {
        goto END;
    }

    // 2. Initialize pointers
    new_node->data = data;
    new_node->next = NULL;

END:
    return new_node;
}

exit_code_t get_nodes_at_pos(results_t **results_p, circular_singly_linked_list_t *list, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    results_t *results = calloc(1, sizeof(results_t));
    if (NULL == results)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

	results->previous_node = NULL;
	results->current_node = NULL;

	if ((NULL == list) || (NULL == list->head))
	{
        exit_code = E_LIST_ERROR;
		goto END;
	}

	if ((position > list->current_size) || (position == 0))
	{
        exit_code = E_OUT_OF_BOUNDS;
		goto END;
	}

    results->current_node = list->head;

    // Start searching from the head
    for (size_t current_pos = 1; current_pos < position; current_pos++)
    {
        results->previous_node = results->current_node;
        results->current_node = results->current_node->next;
    }

    *results_p = results;
    exit_code = E_SUCCESS;
END:
    return exit_code;
}