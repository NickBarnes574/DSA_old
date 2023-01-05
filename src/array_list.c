#include "array_list.h"

struct array_list
{
    void **elements;
    size_t current_size;
    size_t total_capacity;
};

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

    memcpy(list->elements[list->current_size++], data, sizeof(data));

END:
    return exit_code;
}

exit_code_t array_list_reallocate(array_list_t *list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (list->current_size == list->total_capacity)
    {
        void **temp = realloc(list->elements, (list->total_capacity * 2) * (sizeof(*list->elements)));
        if (NULL == temp)
        {
            exit_code = E_CMR_FAILURE;
            list->current_size--;
            goto END;
        }
    }

END:
    return exit_code;
}

void destroy(array_list_t *list)
{
    if (NULL == list)
    {
        goto END;
    }

    for (size_t idx = 0; idx < list->current_size; idx++)
    {
        free(list->elements[idx]);
        list->elements[idx] = NULL;
    }

    free(list->elements);
    list->elements = NULL;

    free(list);
    list = NULL;

END:
    return;
}