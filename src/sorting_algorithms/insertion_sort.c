#include "sorting_algorithms/insertion_sort.h"

exit_code_t insertion_sort(void *array, size_t num_elements, size_t element_size, const compare_ctx *compare_ctx, const equal_ctx *equal_ctx)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == array)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    for(size_t idx = 0; idx < num_elements - 1; idx++)
    {
        void *min = (char *) array + idx * element_size; // initialize the min value as the first element
        void *idx_current = (char *) array + idx * element_size;

        for(size_t jdx = idx + 1; jdx < num_elements; jdx++)
        {
            void *jdx_current = (char *) array + jdx * element_size;
            if (compare_ctx->compare(jdx_current, min, compare_ctx->ctx) < 0)
            {
                min = jdx_current;
            }
        }

        if (equal_ctx->equal(min, idx_current, equal_ctx->ctx) == false)
        {
            swap(min, idx_current, element_size);
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}