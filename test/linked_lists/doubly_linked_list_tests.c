#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "linked_lists/doubly_linked_list.h"
#include "void_pointer_functions.h"
#include "exit_codes.h"

struct dll_node
{
    void *data;
    dll_node_t *next;
    dll_node_t *prev;
};

struct doubly_linked_list
{
    dll_node_t *head;
    dll_node_t *tail;
    size_t current_size;
};

static doubly_linked_list_t *list;

void dll_setup(void)
{
    list = dll_create();
}

void dll_teardown(void)
{
    dll_destroy_list(&list);
}

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new doubly-linked list is created
void test_dll_create(void)
{
    CU_ASSERT_PTR_NOT_EQUAL(list, NULL);
}

// PUSH HEAD TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
void dll_push_head_single_int(void)
{
    int num = 10;

    dll_push_head(list, &num);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure two integers are added to the list
void dll_push_head_double_int(void)
{
    int num_1 = 10;
    int num_2 = 25;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 25);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure three integers are added to the list
void dll_push_head_triple_int(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 50);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->head->next->data), 25);
    CU_ASSERT_EQUAL(*((int *)list->tail->prev->data), 25);
}

// ensure a string is added to the list
void dll_push_head_single_string(void)
{
    const char *str = "hello";

    dll_push_head(list, &str);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->head->data), str), 0);
}

// PUSH TAIL TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
void dll_push_tail_single_int(void)
{
    int num = 10;

    dll_push_tail(list, &num);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure two integers are added to the list
void dll_push_tail_double_int(void)
{
    int num_1 = 10;
    int num_2 = 25;

    dll_push_tail(list, &num_1);
    dll_push_tail(list, &num_2);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 25);
}

// ensure three integers are added to the list
void dll_push_tail_triple_int(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_tail(list, &num_1);
    dll_push_tail(list, &num_2);
    dll_push_tail(list, &num_3);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 50);
    CU_ASSERT_EQUAL(*((int *)list->head->next->data), 25);
    CU_ASSERT_EQUAL(*((int *)list->tail->prev->data), 25);
}

// ensure a string is added to the list
void dll_push_tail_single_string(void)
{
    const char *str = "hello";

    dll_push_tail(list, &str);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->head->data), str), 0);  
}

// PUSH POSITION TESTS
//***********************************************************************************************
// ensure dll_node is added at position 3
void test_dll_push_position_single_70(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    int num_7 = 70;

    dll_push_position(list, &num_7, 3);

    void *data = dll_peek_position(list, 3);
    CU_ASSERT_EQUAL(*((int *)data), 70);
}

// ensure dll_node is added at position 6
void test_dll_push_position_single_20(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    int num_7 = 20;

    dll_push_position(list, &num_7, 6);

    void *data = dll_peek_position(list, 6);
    CU_ASSERT_EQUAL(*((int *)data), 20);
}

// PEEK HEAD TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_dll_peek_head(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data = dll_peek_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 90);
}

// PEEK TAIL TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_dll_peek_tail(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data = dll_peek_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 15);
}

// PEEK POSITION TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_dll_peek_position(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data_1 = dll_peek_position(list, 1);
    void *data_2 = dll_peek_position(list, 2);
    void *data_3 = dll_peek_position(list, 3);
    void *data_4 = dll_peek_position(list, 4);
    void *data_5 = dll_peek_position(list, 5);
    void *data_6 = dll_peek_position(list, 6);

    CU_ASSERT_EQUAL(*((int *)data_1), 90);
    CU_ASSERT_EQUAL(*((int *)data_2), 75);
    CU_ASSERT_EQUAL(*((int *)data_3), 60);
    CU_ASSERT_EQUAL(*((int *)data_4), 45);
    CU_ASSERT_EQUAL(*((int *)data_5), 30);
    CU_ASSERT_EQUAL(*((int *)data_6), 15);
}

// POP HEAD TESTS
//***********************************************************************************************
// ensure ensure 90 is popped from the list
void test_dll_pop_head(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data = dll_pop_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 90);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// POP TAIL TESTS
//***********************************************************************************************
// ensure 15 is popped from the list
void test_dll_pop_tail(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data = dll_pop_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 15);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// POP POSITION TESTS
//***********************************************************************************************
// ensure 60 is popped from the list
void test_dll_pop_position(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    void *data = dll_pop_position(list, 3);

    CU_ASSERT_EQUAL(*((int *)data), 60);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// REMOVE HEAD TESTS
//***********************************************************************************************
// ensure the first dll_node in the list is removed
void test_dll_remove_head(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_head(list);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 25);
    dll_remove_head(list);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
}

// REMOVE TAIL TESTS
//***********************************************************************************************
// ensure the first dll_node in the list is removed
void test_dll_remove_tail(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_tail(list);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 25);
    dll_remove_tail(list);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 50);
}

// REMOVE POSITION TESTS
//***********************************************************************************************
// ensure the middle sll_node in the list is removed
void test_dll_remove_position_middle(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_position(list, 2);

    CU_ASSERT_EQUAL(list->current_size, 2);
}

// ensure the front dll_node in the list is removed
void test_dll_remove_position_front(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    dll_remove_position(list, 1);

    void *data = dll_peek_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 75);
}

// ensure the back dll_node in the list is removed
void test_dll_remove_position_back(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    dll_push_head(list, &num_4);
    dll_push_head(list, &num_5);
    dll_push_head(list, &num_6);

    dll_remove_position(list, 6);

    void *data = dll_peek_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 30);
}

static CU_TestInfo doubly_linked_list_tests[] =
{
    // Create List
    {"Create List", test_dll_create},

    // Push
    {"Push Head - 10", dll_push_head_single_int},
    {"Push Head - 10, 25", dll_push_head_double_int},
    {"Push Head - 10, 25, 50", dll_push_head_triple_int},
    {"Push Head - \"Hello\"", dll_push_head_single_string},

    {"Push Tail - 10", dll_push_tail_single_int},
    {"Push Tail - 10, 25", dll_push_tail_double_int},
    {"Push Tail - 10, 25, 50", dll_push_tail_triple_int},
    {"Push Tail - \"Hello\"", dll_push_tail_single_string},

    {"Push Position - 70", test_dll_push_position_single_70},
    {"Push Position - 20", test_dll_push_position_single_20},

    // Peek
    {"Peek Head", test_dll_peek_head},
    {"Peek Tail", test_dll_peek_tail},
    {"Peek Position", test_dll_peek_position},

    // Pop
    {"Pop Head", test_dll_pop_head},
    {"Pop Tail", test_dll_pop_tail},
    {"Pop Position", test_dll_pop_position},

    // Remove
    {"Remove Head", test_dll_remove_head},
    {"Remove Tail", test_dll_remove_tail},

    {"Remove Position - Front", test_dll_remove_position_front},
    {"Remove Position - Back", test_dll_remove_position_back},
    {"Remove Position - Middle", test_dll_remove_position_middle},
    CU_TEST_INFO_NULL
};

CU_SuiteInfo doubly_linked_list_test_suite =
{
    "Doubly Linked List Tests",
    NULL,
    NULL,
    dll_setup,
    dll_teardown,
    doubly_linked_list_tests
};
