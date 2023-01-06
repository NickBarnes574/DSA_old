#include "array_list.h"

struct array_list
{
    void **elements;
    size_t current_size;
    size_t total_capacity;
};

static exit_code_t array_list_reallocate(array_list_t *list);
static void clear_list(array_list_t **list);

array_list_t *array_list_create(size_t initial_size)
{
    array_list_t *array_list = calloc(1, sizeof(array_list_t));
    if (NULL == array_list)
    {
        goto END;
    }

    array_list->elements = calloc(initial_size, sizeof(void*));
    if (NULL == array_list->elements)
    {
        free(array_list);
        goto END;
    }

    array_list->current_size = 0;
    array_list->total_capacity = initial_size;

END:
    return array_list;
}

exit_code_t array_list_insert_element(array_list_t *list, void *data)
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

    list->elements[list->current_size++] = data;

    // Check if space needs to be reallocated
    if (list->current_size == list->total_capacity)
    {
        exit_code = array_list_reallocate(list);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void *array_list_get_element(array_list_t *list, size_t index)
{
    void *element = NULL;

    if (NULL == list)
    {
        goto END;
    }

    if (index >= list->current_size)
    {
        goto END;
    }

    element = list->elements[index];

END:
    return element;
}

void **array_list_get_list(array_list_t *list)
{
    void **result = NULL;

    if (NULL == list)
    {
        goto END;
    }

    result = list->elements;

END:
    return result;
}

exit_code_t array_list_set_element(array_list_t *list, size_t index, void *data)
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

    if (index >= list->current_size)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    list->elements[index] = data;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

int array_list_get_size(array_list_t *list)
{
    int size = -1; // Set fail state

    if (list == NULL)
    {
        goto END;
    }

    size = (int)list->current_size;

END:
    return size;
}

int array_list_get_total_capacity(array_list_t *list)
{
    int capacity = -1; // Set fail state

    if (list == NULL)
    {
        goto END;
    }

    capacity = (int)list->total_capacity;

END:
    return capacity;
}


void array_list_destroy(array_list_t **list)
{
    if (NULL == list)
    {
        goto END;
    }

    clear_list(list);

    free(*list);
    list = NULL;

END:
    return;
}

void clear_list(array_list_t **list)
{
    if (NULL == list)
    {
        goto END;
    }

    free((*list)->elements);
    (*list)->elements = NULL;

END:
    return;
}

exit_code_t array_list_reallocate(array_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    void **temp = realloc(list->elements, (list->total_capacity * 2) * (sizeof(*list->elements)));
    if (NULL == temp)
    {
        exit_code = E_CMR_FAILURE;
        list->current_size--;
        goto END;
    }

    list->total_capacity *= 2;
    list->elements = temp;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}