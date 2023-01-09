#ifndef DESTROY_H
#define DESTROY_H

#include <stdlib.h>

typedef void (*destroy_function)(void *data, const void *context);

typedef struct
{
    destroy_function destroy;
    const void *context;
} destroy_ctx;

#endif