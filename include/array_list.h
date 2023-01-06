#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_codes.h"

typedef struct array_list array_list_t;

array_list_t *array_list_create(size_t initial_size);

exit_code_t array_list_insert_element(array_list_t *list, void *data);

void *array_list_get_element(array_list_t *list, size_t index);

void **array_list_get_list(array_list_t *list);

exit_code_t array_list_set_element(array_list_t *list, size_t index, void *data);

int array_list_get_size(array_list_t *list);

int array_list_get_total_capacity(array_list_t *list);

void array_list_destroy(array_list_t **list);

#endif