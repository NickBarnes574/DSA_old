#ifndef CIRCULAR_DOUBLY_LINKED_LIST_H
#define CIRCULAR_DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"

typedef struct cdll_node cdll_node_t;
typedef struct circular_doubly_linked_list circular_doubly_linked_list_t;

/// @brief Creates a doubly-linked list container.
/// @param  void Takes no parameters.
/// @return circular_doubly_linked_list_t (returns a doubly-linked list).
circular_doubly_linked_list_t *cdll_create(void);

/// @brief Adds a node to the front of a linked list.
/// @param list The list to append.
/// @param data The data to be added.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_push_head(circular_doubly_linked_list_t *list, void *data);

/// @brief Adds a node to the back of a linked list.
/// @param list The list to append.
/// @param data The data to be added.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_push_tail(circular_doubly_linked_list_t *list, void *data);

/// @brief Adds a node at a specific position in a linked list.
/// @param list The list to append.
/// @param data The data to be added.
/// @param position The position at which to insert the node.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_push_position(circular_doubly_linked_list_t *list, void *data, size_t position);

/// @brief Gets the value at the head of a linked list.
/// @param list The list to get the head value from.
/// @return The value at the head of the list.
void *cdll_peek_head(circular_doubly_linked_list_t* list);

/// @brief Gets the value at the tail of a linked list.
/// @param list The list to get the tail value from.
/// @return The value at the tail of the list.
void *cdll_peek_tail(circular_doubly_linked_list_t* list);

/// @brief Gets the value at a specific position of a linked list.
/// @param list The list to get the value from.
/// @param position The position at which the value is stored.
/// @return The value at the specific position of the list.
void *cdll_peek_position(circular_doubly_linked_list_t *list, size_t position);

/// @brief Gets the value at the head of a linked list and then removes the item from the list.
/// @param list The list to pop the value from.
/// @return The value at the head of the list.
void *cdll_pop_head(circular_doubly_linked_list_t *list);

/// @brief Gets the value at the tail of a linked list and then removes the item from the list.
/// @param list The list to pop the value from.
/// @return The value at the tail of the list.
void *cdll_pop_tail(circular_doubly_linked_list_t *list);

/// @brief Gets the value a specific position of a linked list and then removes the item from the list.
/// @param list The list to pop the value from.
/// @param position The position at which the value is stored.
/// @return The value at the specific position of the list.
void *cdll_pop_position(circular_doubly_linked_list_t *list, size_t position);

/// @brief Removes the first node of a linked list.
/// @param list The list to remove the first node from.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_remove_head(circular_doubly_linked_list_t *list);

/// @brief Removes the last node of a linked list.
/// @param list The list to remove the last node from.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_remove_tail(circular_doubly_linked_list_t *list);

/// @brief Removes the node at a specific position of a linked list.
/// @param list The list to remove from.
/// @param position The position at which the node is to be removed.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_remove_position(circular_doubly_linked_list_t *list, size_t position);

/// @brief Prints a linked list.
/// @param list The list to be printed.
/// @param function_ptr A function pointer to print a specified data type.
/// @param reverse A flag that if set to TRUE, prints the list in reverse.
/// @return exit_code_t (E_SUCCESS for success, anything else is considered a failure).
exit_code_t cdll_print_list(circular_doubly_linked_list_t *list, void (*function_ptr)(void *), bool reverse);

/// @brief Clears all nodes from a linked list.
/// @param list The address of the list.
void cdll_clear_list(circular_doubly_linked_list_t **list);

/// @brief Destroys a linked list.
/// @param list The address of the list
void cdll_destroy_list(circular_doubly_linked_list_t **list);

#endif
