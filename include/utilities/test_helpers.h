#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "utilities/comparison_helpers.h"

void assert_true(bool b, const char *msg) {
    if (!b) {
        if (msg) {
            printf("%s\n", msg);
        }
        printf("Test failure\n");
        exit(-1);
    }
}

void assert_false(bool b, const char *msg) { assert_true(!b, msg); }

void assert_null(const void *ptr, const char *msg) { assert_true(ptr == NULL, msg); }

void assert_nonnull(const void *ptr, const char *msg) {
    assert_true(ptr != NULL, msg);
}

void assert_equal(const void *x, const void *y, const equal_ctx *equal_ctx, const char *msg) {
    assert_true((!equal_ctx && x == y) || (equal_ctx && equal_ctx->equal(x, y, equal_ctx->ctx)), msg);
}

void assert_nequal(const void *x, const void *y, const equal_ctx *equal_ctx, const char *msg) {
    assert_true((!equal_ctx && x != y) || (equal_ctx && !equal_ctx->equal(x, y, equal_ctx->ctx)), msg);
}

void assert_equal_int(int x, int y, const char *msg) {
    assert_equal(&x, &y, &int_eq_ctx, msg);
}

void assert_nequal_int(int x, int y, const char *msg) {
    assert_nequal(&x, &y, &int_eq_ctx, msg);
}

void assert_lt(const void *x, const void *y, const compare_ctx *comp_ctx, const char *msg) {
    assert_true(comp_ctx->compare(x, y, comp_ctx->ctx) < 0, msg);
}

void assert_le(const void *x, const void *y, const compare_ctx *comp_ctx, const char *msg) {
    assert_true(comp_ctx->compare(x, y, comp_ctx->ctx) <= 0, msg);
}

void assert_sorted(const void *x, size_t n, size_t item_size, const compare_ctx *comp_ctx, const char *msg) {
    for (size_t i = 0; n > 0 && i < n - 1; i++) {
        assert_le((char *) x + i * item_size, (char *) x + (i + 1) * item_size, comp_ctx, msg);
    }
}

void assert_sorted_int(const int *x, size_t n, const char *msg) {
    assert_sorted(x, n, sizeof(int), &int_comp_ctx, msg);
}

void print_string(const void *key) { printf("%s",(char *)key); }

void print_int(const void *key) { printf("%d", * (int *)key);}
    
#endif