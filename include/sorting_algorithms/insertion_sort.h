#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utilities/swap.h"
#include "utilities/comparisons.h"
#include "exit_codes.h"

exit_code_t insertion_sort(void *array, size_t num_elements, size_t element_size, const compare_ctx *compare_ctx, const equal_ctx *equal_ctx);

#endif