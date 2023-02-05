#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "linked_lists/circular_singly_linked_list.h"
#include "void_pointer_functions.h"
#include "exit_codes.h"

struct csll_node
{
    void *data;
    csll_node_t *next;
};

struct circular_singly_linked_list
{
    csll_node_t *head;
    csll_node_t *tail;
    size_t current_size;
};

static circular_singly_linked_list_t *list;

void csll_setup(void)
{
    list = csll_create();
}

void csll_teardown(void)
{
    csll_destroy_list(&list);
}

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new singly-linked list is created
void test_csll_create(void)
{
    CU_ASSERT_PTR_NOT_EQUAL(list, NULL);
}

// PUSH HEAD TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
void csll_push_head_single_int(void)
{
    int num = 10;

    csll_push_head(list, &num);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure two integers are added to the list
void csll_push_head_double_int(void)
{
    int num_1 = 10;
    int num_2 = 25;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 25);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure three integers are added to the list
void csll_push_head_triple_int(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 50);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->head->next->data), 25);
}

// ensure a string is added to the list
void csll_push_head_single_string(void)
{
    const char *str = "hello";

    csll_push_head(list, &str);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->head->data), str), 0);
}

// PUSH TAIL TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
void csll_push_tail_single_int(void)
{
    int num = 10;

    csll_push_tail(list, &num);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 10);
}

// ensure two integers are added to the list
void csll_push_tail_double_int(void)
{
    int num_1 = 10;
    int num_2 = 25;

    csll_push_tail(list, &num_1);
    csll_push_tail(list, &num_2);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 25);
}

// ensure three integers are added to the list
void csll_push_tail_triple_int(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_tail(list, &num_1);
    csll_push_tail(list, &num_2);
    csll_push_tail(list, &num_3);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 50);
    CU_ASSERT_EQUAL(*((int *)list->head->next->data), 25);
}

// ensure a string is added to the list
void csll_push_tail_single_string(void)
{
    const char *str = "hello";

    csll_push_tail(list, &str);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->head->data), str), 0);
}

// PUSH POSITION TESTS
//***********************************************************************************************
// ensure csll_node is added at position 3
void test_csll_push_position_single_70(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    int num_7 = 70;

    csll_push_position(list, &num_7, 3);

    void *data = csll_peek_position(list, 3);
    CU_ASSERT_EQUAL(*((int *)data), 70);  
}

// ensure csll_node is added at position 6
void test_csll_push_position_single_20(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    int num_7 = 20;

    csll_push_position(list, &num_7, 6);

    void *data = csll_peek_position(list, 6);
    CU_ASSERT_EQUAL(*((int *)data), 20);
}

// PEEK HEAD TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_csll_peek_head(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data = csll_peek_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 90);
}

// PEEK TAIL TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_csll_peek_tail(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data = csll_peek_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 15); 
}

// PEEK POSITION TESTS
//***********************************************************************************************
// ensure the returned value is 90
void test_csll_peek_position(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data_1 = csll_peek_position(list, 1);
    void *data_2 = csll_peek_position(list, 2);
    void *data_3 = csll_peek_position(list, 3);
    void *data_4 = csll_peek_position(list, 4);
    void *data_5 = csll_peek_position(list, 5);
    void *data_6 = csll_peek_position(list, 6);

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
void test_csll_pop_head(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data = csll_pop_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 90);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// POP TAIL TESTS
//***********************************************************************************************
// ensure 15 is popped from the list
void test_csll_pop_tail(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data = csll_pop_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 15);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// POP POSITION TESTS
//***********************************************************************************************
// ensure 60 is popped from the list
void test_csll_pop_position(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    void *data = csll_pop_position(list, 3);

    CU_ASSERT_EQUAL(*((int *)data), 60);
    CU_ASSERT_EQUAL(list->current_size, 5);
}

// REMOVE HEAD TESTS
//***********************************************************************************************
// ensure the first csll_node in the list is removed
void test_csll_remove_head(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_head(list);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 25);
    csll_remove_head(list);
    CU_ASSERT_EQUAL(*((int *)list->head->data), 10);
}

// REMOVE TAIL TESTS
//***********************************************************************************************
// ensure the first csll_node in the list is removed
void test_csll_remove_tail(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_tail(list);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 25);
    csll_remove_tail(list);
    CU_ASSERT_EQUAL(*((int *)list->tail->data), 50);
}

// REMOVE POSITION TESTS
//***********************************************************************************************
// ensure the middle csll_node in the list is removed
void test_csll_remove_position_middle(void)
{
    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_position(list, 2);

    CU_ASSERT_EQUAL(list->current_size, 2);
}

// ensure the front sll_node in the list is removed
void test_csll_remove_position_front(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    csll_remove_position(list, 1);

    void *data = csll_peek_head(list);

    CU_ASSERT_EQUAL(*((int *)data), 75);   
}

// ensure the back sll_node in the list is removed
void test_csll_remove_position_back(void)
{
    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    csll_push_head(list, &num_4);
    csll_push_head(list, &num_5);
    csll_push_head(list, &num_6);

    csll_remove_position(list, 6);

    void *data = csll_peek_tail(list);

    CU_ASSERT_EQUAL(*((int *)data), 30);
}

static CU_TestInfo circular_singly_linked_list_tests[] =
{
    // Create List
    {"Create List", test_csll_create},

    // Push
    {"Push Head - 10", csll_push_head_single_int},
    {"Push Head - 10, 25", csll_push_head_double_int},
    {"Push Head - 10, 25, 50", csll_push_head_triple_int},
    {"Push Head - \"Hello\"", csll_push_head_single_string},

    {"Push Tail - 10", csll_push_tail_single_int},
    {"Push Tail - 10, 25", csll_push_tail_double_int},
    {"Push Tail - 10, 25, 50", csll_push_tail_triple_int},
    {"Push Tail - \"Hello\"", csll_push_tail_single_string},

    {"Push Position - 70", test_csll_push_position_single_70},
    {"Push Position - 20", test_csll_push_position_single_20},

    // Peek
    {"Peek Head", test_csll_peek_head},
    {"Peek Tail", test_csll_peek_tail},
    {"Peek Position", test_csll_peek_position},

    // Pop
    {"Pop Head", test_csll_pop_head},
    {"Pop Tail", test_csll_pop_tail},
    {"Pop Position", test_csll_pop_position},

    // Remove
    {"Remove Head", test_csll_remove_head},
    {"Remove Tail", test_csll_remove_tail},

    {"Remove Position - Front", test_csll_remove_position_front},
    {"Remove Position - Back", test_csll_remove_position_back},
    {"Remove Position - Middle", test_csll_remove_position_middle},
    CU_TEST_INFO_NULL
};

CU_SuiteInfo circular_singly_linked_list_test_suite =
{
    "Circular Singly Linked List Tests",
    NULL,
    NULL,
    csll_setup,
    csll_teardown,
    circular_singly_linked_list_tests
};
