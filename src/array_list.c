#include "array_list.h"

struct array_list
{
    void **elements;
    size_t current_size;
    size_t total_capacity;
    const destroy_ctx *destroy;
    const equal_ctx *equal;
};

static exit_code_t array_list_reallocate(array_list_t *list);
static void clear_list(array_list_t **list);

array_list_t *array_list_create(const destroy_ctx *destroy, const equal_ctx *equal)
{
    array_list_t *array_list = calloc(1, sizeof(array_list_t));
    if (NULL == array_list)
    {
        goto END;
    }

    array_list->elements = calloc(INITIAL_CAPACITY, sizeof(void*));
    if (NULL == array_list->elements)
    {
        free(array_list);
        goto END;
    }

    array_list->current_size = 0;
    array_list->total_capacity = INITIAL_CAPACITY;
    array_list->destroy = destroy;
    array_list->equal = equal;

END:
    return array_list;
}

exit_code_t array_list_insert(array_list_t *list, size_t index, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (index >= list->current_size)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // Check if space needs to be reallocated
    if (list->current_size == list->total_capacity)
    {
        exit_code = array_list_reallocate(list);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }

    // Get the data at the current index (src) and shift it up to the next index (dst)
    void *dst = list->elements + index + 1;
    void *src = list->elements + index;
    size_t num_bytes = (--list->current_size - index) * sizeof(*list->elements);
    memmove(dst, src, num_bytes);

    list->elements[list->current_size++] = data;
    
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

void *array_list_get(array_list_t *list, size_t index)
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

exit_code_t array_list_set(array_list_t *list, size_t index, void *data)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (index >= list->current_size)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    if (NULL == data)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    if (list->destroy)
    {
        list->destroy->destroy(list->elements[index], list->destroy->context);
    }

    list->elements[index] = data;

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t array_list_remove(array_list_t *list, size_t index)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == list)
    {
        exit_code = E_LIST_ERROR;
        goto END;
    }

    if (index >= list->current_size)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    if (list->destroy)
    {
        list->destroy->destroy(list->elements[index], list->destroy->context);
    }

    // Get the data at the next index (src) and shift it down to the current index (dst)
    void *dst = list->elements + index;
    void *src = list->elements + index + 1;
    size_t num_bytes = (--list->current_size - index) * sizeof(*list->elements);
    memmove(dst, src, num_bytes);

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

size_t array_list_size(array_list_t *list)
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

bool array_list_contains(array_list_t *list, void *data)
{
    bool contains_data = false;

    if ((NULL == list) || (NULL == data))
    {
        goto END;
    }

    for (size_t idx = 0; idx < list->current_size; idx++)
    {
        if (true == list->equal->equal(list->elements[idx], data, list->equal->ctx))
        {
            contains_data = true;
        }
    }

END:
    return contains_data;
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

    if ((*list)->destroy)
    {
        for (size_t idx = 0; idx < (*list)->current_size; idx++)
        {
            (*list)->destroy->destroy((*list)->elements[idx], (*list)->destroy->context);
        }
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