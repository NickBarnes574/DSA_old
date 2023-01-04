#include "linked_lists/singly_linked_list.h"

struct sll_node
{
    void *data;
    sll_node_t *next;
};

struct singly_linked_list
{
    sll_node_t *head;
    sll_node_t *tail;
    size_t current_size;
};

/// @brief Creates a new node
/// @param data The data to be added.
/// @return new_sll_node_t
static sll_node_t *create_new_node(void *data);

singly_linked_list_t *sll_create(void)
{
    // 1. Create the list
    singly_linked_list_t *list = calloc(1, sizeof(singly_linked_list_t));

    // 2. Check if memory allocation was successful
    if (NULL != list)
    {
        list->current_size = 0;
        list->head = NULL;
        list->tail = NULL;
    }

    return list;
}

exit_code_t sll_push_head(singly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        return E_NULL_POINTER;
    }

    sll_node_t *new_node = create_new_node(data); // Create a new node

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
        new_node->next = list->head;
        list->head = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t sll_push_tail(singly_linked_list_t *list, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        return E_NULL_POINTER;
    }

    sll_node_t *new_node = create_new_node(data); // Create a new node

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
        list->tail = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t sll_push_position(singly_linked_list_t *list, void *data, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if data exists
    if (NULL == data)
    {
        return E_NULL_POINTER;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        return E_OUT_OF_BOUNDS;
    }

    sll_node_t *new_node = create_new_node(data); // Create a new node

    // 4. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        sll_node_t *previous_node = NULL;
        sll_node_t *current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < position; current_pos++)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }

        new_node->next = current_node;
        previous_node->next = new_node;

        current_node = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

void *sll_peek_head(singly_linked_list_t *list)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->head)
    {
        return NULL;
    }

    return list->head->data;
}

void *sll_peek_tail(singly_linked_list_t *list)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->tail)
    {
        return NULL;
    }

    return list->tail->data;
}

void *sll_peek_position(singly_linked_list_t *list, size_t position)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->head)
    {
        return NULL;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        return NULL;
    }

    sll_node_t *current_node = NULL;
    void *data = NULL;

    current_node = list->head;

    // Start searching from the head
    for (size_t current_pos = 1; current_pos < position; current_pos++)
    {
        current_node = current_node->next;
    }
    
    data = current_node->data;

    return data;
}

void *sll_pop_head(singly_linked_list_t *list)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->head)
    {
        return NULL;
    }

    void *data = list->head->data;
    sll_remove_head(list);

    return data;
}

void *sll_pop_tail(singly_linked_list_t *list)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->tail)
    {
        return NULL;
    }

    void *data = list->tail->data;
    sll_remove_tail(list);

    return data;
}

void *sll_pop_position(singly_linked_list_t *list, size_t position)
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return NULL;
    }

    // 2. Check if list is empty
    if (NULL == list->head)
    {
        return NULL;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        return NULL;
    }

    sll_node_t *current_node = NULL;
    void *data = NULL;

    current_node = list->head;

    // Start searching from the head
    for (size_t current_pos = 1; current_pos < position; current_pos++)
    {
        current_node = current_node->next;
    }
    
    data = current_node->data;
    sll_remove_position(list, position);

    return data;
}

exit_code_t sll_remove_head(singly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // 1. Check if the list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if the list is empty
    if (NULL == list->head)
    {
        return E_CONTAINER_EMPTY;
    }

    // 3. Check if there is only one node in the list
    if (NULL == list->head->next)
    {
        free(list->head);
        list->head = NULL;
    }
    else
    {
        sll_node_t *temp = list->head->next;

        free(list->head);
        list->head = NULL;

        list->head = temp;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t sll_remove_tail(singly_linked_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // set the fail state

    // 1. Check if the list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if the list is empty
    if (NULL == list->tail)
    {
        return E_CONTAINER_EMPTY;
    }

    // 3. Check if there is only one node in the list
    if (NULL == list->head->next)
    {
        free(list->tail);
        list->tail = NULL;
    }
    else
    {
        sll_node_t *previous_node = NULL;
        sll_node_t *current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < list->current_size; current_pos++)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }

        list->tail = previous_node;

        free(list->tail->next);
        list->tail->next = NULL;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t sll_remove_position(singly_linked_list_t *list, size_t position)
{
    exit_code_t exit_code = E_DEFAULT_ERROR; // Set the fail state

    // 1. Check if list exists
    if (NULL == list)
    {
        return E_CONTAINER_DOES_NOT_EXIST;
    }

    // 2. Check if list is empty
    if (NULL == list->head)
    {
        return E_CONTAINER_EMPTY;
    }

    // 3. Check if position is out of range
    if (position > list->current_size || position == 0)
    {
        return E_OUT_OF_BOUNDS;
    }

    // 4. Check if position is at the head
    if (position == 1)
    {
        exit_code = sll_remove_head(list);

        return exit_code;    
    }

    // 5. Check if position is at the tail
    if (position == list->current_size)
    {
        exit_code = sll_remove_tail(list);

        return exit_code;  
    }

    sll_node_t *current_node = list->head;
    sll_node_t *previous_node = NULL;

    // Start searching from the head
    for (size_t current_pos = 1; current_pos < position; current_pos++)
    {
        previous_node = current_node;
        current_node = current_node->next;
    }

    previous_node->next = current_node->next;

    free(current_node);
    
    // 4. Increment the size of the list
    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;    
}

exit_code_t sll_print_list(singly_linked_list_t *list, void (*function_ptr)(void *))
{
    // 1. Check if list exists
    if (NULL == list)
    {
        return E_CONTAINER_EMPTY;
    }

    // 2. Check for NULL function pointer
    if (NULL == function_ptr)
    {
        return E_NULL_POINTER;
    }

    sll_node_t *current_node = NULL; // Create a current node

    current_node = list->head;
    

    // 4. Print the list
    while (NULL != current_node)
    {
        (*function_ptr)(current_node->data);

        current_node = current_node->next;
    }

    return E_SUCCESS;
}

void sll_clear_list(singly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        return;
    }

    sll_node_t *current_node = (*list)->head;
    sll_node_t *next_node = NULL;

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
}

void sll_destroy_list(singly_linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        return;
    }

    // 2. Clear out all the nodes
    sll_clear_list(list);

    // 3. Destroy the list container
    free(*list);
    *list = NULL;
}

sll_node_t *create_new_node(void *data)
{
    // 1. Allocate memory for new node
    sll_node_t *new_node = calloc(1, sizeof(sll_node_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    // 2. Initialize pointers
    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}