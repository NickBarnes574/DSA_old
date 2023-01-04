#ifndef VOID_POINTER_FUNCTIONS_H
#define VOID_POINTER_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_codes.h"

// INTEGER FUNCTIONS

/// @brief A Function to print an integer
/// @param num The integer to print
void print_int(void *num);

void **array_int_to_void(const int **int_arr, int size);

// FLOAT FUNCTIONS

/// @brief A Function to print a float
/// @param flt The float to print
void print_float(void *flt);

void print_string(void *str);

int compare_int(void *num_1, void *num_2);

/// @brief A Function to determine whether or not two strings are equal by ASCII character.
/// @param str_1 The first string.
/// @param str_2 The second string.
/// @return 
///         - 0 if strings are equal.
///         - greater than 0 if the first non-matching character in str_1 is greater than that of str_2.
///         - less than 0 if the first non_matching character in str_1 is lower than that of str_2.
int compare_string_ASCII(void *str_1, void *str_2);

/// @brief A Function to determin whether or not two strings are of equal length.
/// @param str_1 The first string.
/// @param str_2 The second string.
/// @return
///         - 0 if strings are equal.
///         - greater than 0 if str_1 is longer than str_2.
///         - less than 0 if str_1 is shorter than str_2.
int compare_string_length(void *str_1, void *str_2);

void default_free(void *val);
void free_string(void *str);
#endif
