#include "linked_list.h"

struct node
{
    void *data;
    node_t *next;
    node_t *prev;
};

struct linked_list
{
    node_t *head;
    node_t *tail;
    size_t current_size;
};

/// @brief Creates a new node
/// @param data The data to be added.
/// @return new_node_t
static node_t *create_new_node(void *data);

linked_list_t *create_list(void)
{
    // 1. Create the list
    linked_list_t *list = calloc(1, sizeof(linked_list_t));

    // 2. Check if memory allocation was successful
    if (NULL != list)
    {
        list->current_size = 0;
        list->head = NULL;
        list->tail = NULL;
    }

    return list;
}

exit_code_t push_head(linked_list_t *list, void *data)
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

    node_t *new_node = create_new_node(data); // Create a new node

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
    return exit_code;
}

exit_code_t push_tail(linked_list_t *list, void *data)
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

    node_t *new_node = create_new_node(data); // Create a new node

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
    return exit_code;
}

exit_code_t push_position(linked_list_t *list, void *data, size_t position)
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

    node_t *new_node = create_new_node(data); // Create a new node

    // 4. Determine links based on whether or not list is empty
    if (NULL == list->head)
    {
        // a. Insert node as the first node in the list if list is empty
        list->head = new_node;
        list->tail = new_node;
    }    
    else
    {
        size_t middle_position = list->current_size / 2; // Get the middle position of the list
        size_t end_position = list->current_size; // Get the end position of the list
        node_t *current_node = NULL;

        // Check if the position is in the first or second half of the list
        if (position <= middle_position)
        {
            current_node = list->head;

            // Start searching from the head
            for (size_t current_pos = 1; current_pos < position; current_pos++)
            {
                current_node = current_node->next;
            }
        }
        else
        {
            current_node = list->tail;

            // Start searching from the tail
            for (size_t current_pos = end_position; current_pos > position; current_pos--)
            {
                current_node = current_node->prev;
            }
        }
        
        current_node->prev->next = new_node;
        new_node->prev = current_node->prev;

        new_node->next = current_node;
        current_node->prev = new_node;

        current_node = new_node;
    }

    // 4. Increment the size of the list
    list->current_size += 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

void *peek_head(linked_list_t *list)
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

void *peek_tail(linked_list_t *list)
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

void *peek_position(linked_list_t *list, size_t position)
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

    size_t middle_position = list->current_size / 2; // Get the middle position of the list
    size_t end_position = list->current_size; // Get the end position of the list
    node_t *current_node = NULL;
    void *data = NULL;

    // Check if the position is in the first or second half of the list
    if (position <= middle_position)
    {
        current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < position; current_pos++)
        {
            current_node = current_node->next;
        }
        
        data = current_node->data;
    }
    else
    {
        current_node = list->tail;

        // Start searching from the tail
        for (size_t current_pos = end_position; current_pos > position; current_pos--)
        {
            current_node = current_node->prev;
        }

        data = current_node->data;
    }

    return data;
}

void *pop_head(linked_list_t *list)
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
    remove_head(list);

    return data;
}

void *pop_tail(linked_list_t *list)
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
    remove_tail(list);

    return data;
}

void *pop_position(linked_list_t *list, size_t position)
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

    size_t middle_position = list->current_size / 2; // Get the middle position of the list
    size_t end_position = list->current_size; // Get the end position of the list
    node_t *current_node = NULL;
    void *data = NULL;

    // Check if the position is in the first or second half of the list
    if (position <= middle_position)
    {
        current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < position; current_pos++)
        {
            current_node = current_node->next;
        }
        
        data = current_node->data;
        remove_position(list, position);
    }
    else
    {
        current_node = list->tail;

        // Start searching from the tail
        for (size_t current_pos = end_position; current_pos > position; current_pos--)
        {
            current_node = current_node->prev;
        }
        
        data = current_node->data;
        remove_position(list, position);
    }

    return data;
}

exit_code_t remove_head(linked_list_t *list)
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
        node_t *temp = list->head->next;

        free(list->head);
        list->head = NULL;

        list->head = temp;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t remove_tail(linked_list_t *list)
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
    if (NULL == list->tail->prev)
    {
        free(list->tail);
        list->tail = NULL;
    }
    else
    {
        node_t *temp = list->tail->prev;

        free(list->tail);
        list->tail = NULL;

        list->tail = temp;
        list->tail->next = NULL;
    }

    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t remove_position(linked_list_t *list, size_t position)
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
        exit_code = remove_head(list);

        return exit_code;    
    }

    // 5. Check if position is at the tail
    if (position == list->current_size)
    {
        exit_code = remove_tail(list);

        return exit_code;  
    }

    size_t middle_position = list->current_size / 2; // Get the middle position of the list
    size_t end_position = list->current_size; // Get the end position of the list
    node_t *current_node = NULL;

    // Check if the position is in the first or second half of the list
    if (position <= middle_position)
    {
        current_node = list->head;

        // Start searching from the head
        for (size_t current_pos = 1; current_pos < position; current_pos++)
        {
            current_node = current_node->next;
        }
    }
    else
    {
        current_node = list->tail;

        // Start searching from the tail
        for (size_t current_pos = end_position; current_pos > position; current_pos--)
        {
            current_node = current_node->prev;
        }
    }

    current_node->prev->next = current_node->next;
    current_node->next->prev = current_node->prev->next;

    free(current_node);
    
    // 4. Increment the size of the list
    list->current_size -= 1;

    exit_code = E_SUCCESS;
    return exit_code;    
}

exit_code_t print_list(linked_list_t *list, void (*function_ptr)(void *), bool reverse)
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

    node_t *current_node = NULL; // Create a current node

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

    return E_SUCCESS;
}

void clear_list(linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        return;
    }

    node_t *current_node = (*list)->head;
    node_t *next_node = NULL;

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

void destroy_list(linked_list_t **list)
{
    // 1. Check if list is empty
    if (NULL == list)
    {
        return;
    }

    // 2. Clear out all the nodes
    clear_list(list);

    // 3. Destroy the list container
    free(*list);
    *list = NULL;
}

node_t *create_new_node(void *data)
{
    // 1. Allocate memory for new node
    node_t *new_node = calloc(1, sizeof(node_t));
    if (NULL == new_node)
    {
        return NULL;
    }

    // 2. Initialize pointers
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}
