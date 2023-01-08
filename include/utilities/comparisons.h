#ifndef COMPARISONS_H
#define COMPARISONS_H

#include <stdbool.h>

typedef int (*compare_function)(const void *key1, const void *key2, const void *ctx);
typedef bool (*equal_function)(const void *data_1, const void *data_2, const void *ctx);

typedef struct
{
    compare_function compare;
    const void *ctx;
} compare_ctx;

typedef struct
{
    equal_function equal;
    const void *ctx;
} equal_ctx;

#endif