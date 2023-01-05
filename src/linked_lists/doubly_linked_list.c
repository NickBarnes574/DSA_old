#include "linked_lists/doubly_linked_list.h"

struct dll_node
{
    void *data;
    dll_node_t *next;
    dll_node_t *prev;
};

struct doubly_linked_list
{
    dll_node_t *head;
    dll_node_t *tail;
    size_t current_size;
};

typedef struct results
{
    dll_node_t *previous_node;
    dll_node_t *current_node;
} results_t;

/// @brief Creates a new node
/// @param data The data to be added.
/// @return new_dll_node_t
static dll_node_t *create_new_node(void *data);

static results_t *get_nodes_at_pos(doubly_linked_list_t *list, size_t position);
static void free_results(results_t *results);

doubly_linked_list_t *dll_create(void)
{
    // 1. Create the list
    doubly_linked_list_t *list = calloc(1, sizeof(doubly_linked_list_t));

    // 2. Check if memory allocation was successful
    if (NULL != list)
    {
        list->current_size = 0;
        list->head = NULL;
        list->tail = NULL;
    }

    return list;
}

exit_code_t dll_push_head(doubly_linked_list_t *list, void *data)
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

    dll_node_t *new_node = create_new_node(data); // Create a new node

    // 3. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        // b. Insert node at the front of the list
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t dll_push_tail(doubly_linked_list_t *list, void *data)
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

    dll_node_t *new_node = create_new_node(data); // Create a new node

    // 3. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        // b. Insert node at the back of the list
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t dll_push_position(doubly_linked_list_t *list, void *data, size_t position)
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
    if (position > list->current_size || position == 0)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    dll_node_t *new_node = create_new_node(data); // Create a new node

    // 4. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        results_t *results = get_nodes_at_pos(list, position);
        
        results->current_node->prev->next = new_node;
        new_node->prev = results->current_node->prev;

        new_node->next = results->current_node;
        results->current_node->prev = new_node;

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

void *dll_peek_head(doubly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;

END:
    return data;
}

void *dll_peek_tail(doubly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->tail))
    {
        goto END;
    }

    data = list->tail->data;

END:
    return data;
}

void *dll_peek_position(doubly_linked_list_t *list, size_t position)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        goto END;
    }

    results_t *results = get_nodes_at_pos(list, position);

    data = results->current_node->data;

    free(results);
    results = NULL;

END:
    return data;
}

void *dll_pop_head(doubly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;
    dll_remove_head(list);

END:
    return data;
}

void *dll_pop_tail(doubly_linked_list_t *list)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->tail))
    {
        goto END;
    }

    data = list->tail->data;
    dll_remove_tail(list);

END:
    return data;
}

void *dll_pop_position(doubly_linked_list_t *list, size_t position)
{
    void *data = NULL;

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        goto END;
    }

    results_t *results = get_nodes_at_pos(list, position);
        
    data = results->current_node->data;
    dll_remove_position(list, position);

    free(results);

END:
    return data;
}

exit_code_t dll_remove_head(doubly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // Check if list does not exist or is empty
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
        dll_node_t *temp = list->head->next;

        free(list->head);
        list->head = NULL;

        list->head = temp;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t dll_remove_tail(doubly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // Check if list does not exist or is empty
    if ((NULL == list) || (NULL == list->tail))
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    // 3. Check if there is only one node in the list
    if (NULL == list->tail->prev)
    {
        free(list->tail);
        list->tail = NULL;
    }
    else
    {
        dll_node_t *temp = list->tail->prev;

        free(list->tail);
        list->tail = NULL;

        list->tail = temp;
        list->tail->next = NULL;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t dll_remove_position(doubly_linked_list_t *list, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // Check if list does not exist or is empty
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
        exit_code = dll_remove_head(list);

        return exit_code;    
    }

    // 5. Check if position is at the tail
    if (position == list->current_size)
    {
        exit_code = dll_remove_tail(list);

        return exit_code;  
    }

    results_t *results = get_nodes_at_pos(list, position);

    results->current_node->prev->next = results->current_node->next;
    results->current_node->next->prev = results->current_node->prev->next;

    free(results->current_node);
    free(results);
    
    // 4. Increment the size of the list
    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;    
}

exit_code_t dll_print_list(doubly_linked_list_t *list, void (*function_ptr)(void *), bool reverse)
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

    dll_node_t *current_node = NULL; // Create a current node

    // 3. Set the current node to tail if reverse flag is true
    if (reverse)
    {
        current_node = list->tail;
    }
    else
    {
        current_node = list->head;
    }
    
    // 4. Print the list
    while (NULL != current_node)
    {
        (*function_ptr)(current_node->data);

        // a. Print the list in reverse if reverse flag is set
        if (reverse)
        {
            current_node = current_node->prev;
        }
        else
        {
            current_node = current_node->next;
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void dll_clear_list(doubly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    dll_node_t *current_node = (*list)->head;
    dll_node_t *next_node = NULL;

    // 2. Clear out all the nodes in the list
    while (NULL != current_node)
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

void dll_destroy_list(doubly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    // 2. Clear out all the nodes
    dll_clear_list(list);

    // 3. Destroy the list container
    free(*list);
    *list = NULL;

END:
    return;
}

dll_node_t *create_new_node(void *data)
{
    // 1. Allocate memory for new node
    dll_node_t *new_node = calloc(1, sizeof(dll_node_t));
    if (NULL != new_node)
    {
        new_node->data = data;
        new_node->next = NULL;
        new_node->prev = NULL;
    }

    return new_node;
}

results_t *get_nodes_at_pos(doubly_linked_list_t *list, size_t position)
{
    results_t *results = calloc(1, sizeof(results_t));
    if (NULL == results)
    {
        goto END;
    }

	results->previous_node = NULL;
	results->current_node = NULL;

	if ((NULL == list) || (NULL == list->head))
	{
		goto END;
	}

	if ((position > list->current_size) || (position == 0))
	{
		goto END;
	}

    size_t middle_position = list->current_size / 2; // Get the middle position of the list
    size_t end_position = list->current_size; // Get the end position of the list

    if (position <= middle_position)
    {
        results->current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < position; current_pos++)
        {
            results->previous_node = results->current_node;
            results->current_node = results->current_node->next;
        }
    }

    else
    {
        results->current_node = list->tail;

        // Start searching from the tail
        for (size_t current_pos = end_position; current_pos > position; current_pos --)
        {
            results->previous_node = results->current_node;
            results->current_node = results->current_node->prev;
        }
    }

END:
    return results;
}

static void free_results(results_t *results)
{
    free(results->current_node);
    results->current_node = NULL;
    free(results->previous_node);
    results->previous_node = NULL;
    free(results);
}