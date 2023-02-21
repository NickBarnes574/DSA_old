#include "linked_lists/circular_doubly_linked_list.h"

struct cdll_node
{
    void *data;
    cdll_node_t *next;
    cdll_node_t *prev;
};

struct circular_doubly_linked_list
{
    cdll_node_t *head;
    cdll_node_t *tail;
    size_t current_size;
    void (*custom_free)(void *);
    int (*compare)(void *, void *);
    void (*print)(void *);
};

typedef struct results
{
    cdll_node_t *previous_node;
    cdll_node_t *current_node;
} results_t;

/// @brief Creates a new node
/// @param data The data to be added.
/// @return new_cdll_node_t
static cdll_node_t *create_new_node(void *data);

static exit_code_t get_nodes_at_pos(results_t **results_p, circular_doubly_linked_list_t *list, size_t position);

circular_doubly_linked_list_t *cdll_create(
    void (*custom_free)(void *),
    int (*compare)(void *, void *),
    void (*print)(void *))
{
    circular_doubly_linked_list_t *list = calloc(1, sizeof(circular_doubly_linked_list_t));

    if (NULL != list)
    {
        list->current_size = 0;
        list->head = NULL;
        list->tail = NULL;
    }

    if (NULL == custom_free)
    {
        list->custom_free = NULL;
    }
    else
    {
        list->custom_free = custom_free;
    }

    list->compare = compare;
    list->print = print;

    return list;
}

exit_code_t cdll_push_head(circular_doubly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    cdll_node_t *new_node = create_new_node(data);

    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }    
    else
    {
        // b. Insert node at the front of the list
        new_node->next = list->tail->next;
        list->tail->next = new_node;
        list->head = new_node;
    }

    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t cdll_push_tail(circular_doubly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    cdll_node_t *new_node = create_new_node(data);

    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }    
    else
    {
        // b. Insert node at the back of the list
        new_node->next = list->tail->next;
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t cdll_push_position(circular_doubly_linked_list_t *list, void *data, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    if ((position > list->current_size) || (position == 0))
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    cdll_node_t *new_node = create_new_node(data);

    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }    
    else
    {
        cdll_node_t *temp = list->head;
        while (position > 2) // first position is 1, and we need to grab the node before it
        {
            temp = temp->next;
            position --;
        }

        // b. Insert node at the specified position
        new_node->prev = temp;
        new_node->next = temp->next;
        temp->next->prev = new_node;
        temp->next = new_node;

        if (temp == list->tail)
        {
            list->tail = list->tail->next;
        }
    }

    list->current_size += 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void *cdll_peek_head(circular_doubly_linked_list_t *list)
{
    void *data = NULL;

    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;

END:
    return data;
}

void *cdll_peek_tail(circular_doubly_linked_list_t *list)
{
    void *data = NULL;

    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->tail->data;

END:
    return data;
}

void *cdll_peek_position(circular_doubly_linked_list_t *list, size_t position)
{
    void *data = NULL;

    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    if (position > list->current_size || position == 0)
    {
        goto END;
    }

    cdll_node_t *temp = list->head;
    while (position > 1) // first position is 1, and we need to grab the node before it
    {
        temp = temp->next;
        position --;
    }

    data = temp->data;

END:
    return data;
}

void *cdll_pop_head(circular_doubly_linked_list_t *list)
{
    void *data = NULL;
    
    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->head->data;
    cdll_remove_head(list);

END:
    return data;
}

void *cdll_pop_tail(circular_doubly_linked_list_t *list)
{
    void *data = NULL;
    
    // Check if list exists or is empty
    if ((NULL == list) || (NULL == list->head))
    {
        goto END;
    }

    data = list->tail->data;
    cdll_remove_tail(list);

END:
    return data;
}

void *cdll_pop_position(circular_doubly_linked_list_t *list, size_t position)
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
    cdll_node_t *temp = list->head;
    while (position > 1) // first position is 1, and we need to grab the node before it
    {
        temp = temp->next;
        position --;
    }

    data = temp->data;

    cdll_remove_position(list, position);

END:
    return data;
}

exit_code_t cdll_remove_head(circular_doubly_linked_list_t *list)
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
        cdll_node_t *temp = list->head->next;

        free(list->head);
        list->head = NULL;

        list->head = temp;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t cdll_remove_tail(circular_doubly_linked_list_t *list)
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
        cdll_node_t *temp = list->head;
        size_t position = list->current_size;
        while (position > 2) // first position is 1, and we need to grab the node before it
        {
            temp = temp->next;
            position --;
        }

        list->tail = temp;
    }

    free(list->tail->next);
    list->tail->next = list->head;

    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t cdll_remove_position(circular_doubly_linked_list_t *list, size_t position)
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
        exit_code = cdll_remove_head(list);
        goto END; 
    }

    // 5. Check if position is at the tail
    if (position == list->current_size)
    {
        exit_code = cdll_remove_tail(list);
        goto END;  
    }

    // Retrieve the node at the current position, as well as the previous adjacent node
    cdll_node_t *temp = list->head;
    while (position > 2) // first position is 1, and we need to grab the node before it
    {
        temp = temp->next;
        position --;
    }

    temp = temp->next;

    free(temp->next);
    
    // 4. Increment the size of the list
    list->current_size -= 1;

    exit_code = E_SUCCESS;
END:
    return exit_code;    
}

exit_code_t cdll_print_list(circular_doubly_linked_list_t *list, void (*function_ptr)(void *), bool reverse)
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

    cdll_node_t *current_node = NULL; // Create a current node

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
    //while (NULL != current_node)
    for (int idx = 0; idx < list->current_size * 2; idx++)
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

void cdll_clear_list(circular_doubly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    cdll_node_t *current_node = (*list)->head;
    cdll_node_t *next_node = NULL;

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

void cdll_destroy_list(circular_doubly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        goto END;
    }

    // 2. Clear out all the nodes
    cdll_clear_list(list);

    // 3. Destroy the list container
    free(*list);
    *list = NULL;

END:
    return;
}

cdll_node_t *create_new_node(void *data)
{
    // 1. Allocate memory for new node
    cdll_node_t *new_node = calloc(1, sizeof(cdll_node_t));
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

exit_code_t get_nodes_at_pos(results_t **results_p, circular_doubly_linked_list_t *list, size_t position)
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

    size_t middle_position = list->current_size / 2; // Get the middle position of the list
    size_t end_position = list->current_size; // Get the end position of the list

    if (position <= middle_position)
    {
        results->current_node = list->head;
        results->previous_node = list->head->prev;

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
        results->previous_node = list->tail->prev;

        // Start searching from the tail
        for (size_t current_pos = end_position; current_pos > position; current_pos --)
        {
            results->previous_node = results->current_node;
            results->current_node = results->current_node->prev;
        }
    }

    *results_p = results;
    exit_code = E_SUCCESS;
END:
    return exit_code;
}