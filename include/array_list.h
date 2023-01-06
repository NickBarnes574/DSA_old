#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "exit_codes.h"
#include "utilities/destroy.h"
#include "utilities/comparisons.h"

#define INITIAL_CAPACITY 5

typedef struct array_list array_list_t;

array_list_t *array_list_create(const destroy_ctx *destroy, const equal_ctx *equal);

exit_code_t array_list_insert(array_list_t *list, size_t index, void *data);

exit_code_t array_list_remove(array_list_t *list, size_t index);

bool array_list_contains(array_list_t *list, void *data);

void *array_list_get(array_list_t *list, size_t index);

exit_code_t array_list_set(array_list_t *list, size_t index, void *data);

size_t array_list_size(array_list_t *list);

void array_list_destroy(array_list_t **list);

#endif