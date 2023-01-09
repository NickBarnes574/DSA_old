#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lists/linked_lists/circular_singly_linked_list/circular_singly_linked_list.h"
#include "../../utilities/void_pointer_functions/void_pointer_functions.h"
#include "../../utilities/exit_codes/exit_codes.h"

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

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new singly-linked list is created
START_TEST(test_csll_create)
{
    circular_singly_linked_list_t *list = csll_create();
    ck_assert_ptr_ne(list, NULL);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_create_tests[] =
{
    test_csll_create,
    NULL
};

// PUSH HEAD TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(csll_push_head_single_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num = 10;

    csll_push_head(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    csll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(csll_push_head_double_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    csll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(csll_push_head_triple_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 50);
    ck_assert_int_eq(*((int *)list->tail->data), 10);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);

    csll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(csll_push_head_single_string)
{
    circular_singly_linked_list_t *list = csll_create();

    const char *str = "hello";

    csll_push_head(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_push_head_tests[] =
{
    csll_push_head_single_int,
    csll_push_head_double_int,
    csll_push_head_triple_int,
    csll_push_head_single_string,
    NULL
};

// PUSH TAIL TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(csll_push_tail_single_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num = 10;

    csll_push_tail(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    csll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(csll_push_tail_double_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;

    csll_push_tail(list, &num_1);
    csll_push_tail(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 25);

    csll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(csll_push_tail_triple_int)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_tail(list, &num_1);
    csll_push_tail(list, &num_2);
    csll_push_tail(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 50);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);

    csll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(csll_push_tail_single_string)
{
    circular_singly_linked_list_t *list = csll_create();

    const char *str = "hello";

    csll_push_tail(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_push_tail_tests[] =
{
    csll_push_tail_single_int,
    csll_push_tail_double_int,
    csll_push_tail_triple_int,
    csll_push_tail_single_string,
    NULL
};

// PUSH POSITION TESTS
//***********************************************************************************************
// ensure csll_node is added at position 3
START_TEST(test_csll_push_position_single_70)
{
    circular_singly_linked_list_t *list = csll_create();

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
    ck_assert_int_eq(*((int *)data), 70);

    csll_destroy_list(&list);
}
END_TEST

// ensure csll_node is added at position 6
START_TEST(test_csll_push_position_single_20)
{
    circular_singly_linked_list_t *list = csll_create();

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
    ck_assert_int_eq(*((int *)data), 20);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_push_position_tests[] =
{
    test_csll_push_position_single_70,
    test_csll_push_position_single_20,
    NULL
};

// PEEK HEAD TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_csll_peek_head)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 90);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_peek_head_tests[] =
{
    test_csll_peek_head,
    NULL
};

// PEEK TAIL TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_csll_peek_tail)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 15);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_peek_tail_tests[] =
{
    test_csll_peek_tail,
    NULL
};

// PEEK POSITION TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_csll_peek_position)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data_1), 90);
    ck_assert_int_eq(*((int *)data_2), 75);
    ck_assert_int_eq(*((int *)data_3), 60);
    ck_assert_int_eq(*((int *)data_4), 45);
    ck_assert_int_eq(*((int *)data_5), 30);
    ck_assert_int_eq(*((int *)data_6), 15);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_peek_position_tests[] =
{
    test_csll_peek_position,
    NULL
};

// POP HEAD TESTS
//***********************************************************************************************
// ensure ensure 90 is popped from the list
START_TEST(test_csll_pop_head)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 90);
    ck_assert_int_eq(list->current_size, 5);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_pop_head_tests[] =
{
    test_csll_pop_head,
    NULL
};

// POP TAIL TESTS
//***********************************************************************************************
// ensure 15 is popped from the list
START_TEST(test_csll_pop_tail)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 15);
    ck_assert_int_eq(list->current_size, 5);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_pop_tail_tests[] =
{
    test_csll_pop_tail,
    NULL
};

// POP POSITION TESTS
//***********************************************************************************************
// ensure 60 is popped from the list
START_TEST(test_csll_pop_position)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 60);
    ck_assert_int_eq(list->current_size, 5);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_pop_position_tests[] =
{
    test_csll_pop_position,
    NULL
};

// REMOVE HEAD TESTS
//***********************************************************************************************
// ensure the first csll_node in the list is removed
START_TEST(test_csll_remove_head)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    csll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 10);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_remove_head_tests[] =
{
    test_csll_remove_head,
    NULL
};

// REMOVE TAIL TESTS
//***********************************************************************************************
// ensure the first csll_node in the list is removed
START_TEST(test_csll_remove_tail)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 25);
    csll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 50);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_remove_tail_tests[] =
{
    test_csll_remove_tail,
    NULL
};

// REMOVE POSITION TESTS
//***********************************************************************************************
// ensure LLLL
START_TEST(test_csll_remove_position_middle)
{
    circular_singly_linked_list_t *list = csll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    csll_push_head(list, &num_1);
    csll_push_head(list, &num_2);
    csll_push_head(list, &num_3);

    csll_remove_position(list, 2);

    ck_assert_int_eq(list->current_size, 2);
    csll_destroy_list(&list);
}
END_TEST

START_TEST(test_csll_remove_position_front)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 75);

    csll_destroy_list(&list);
}
END_TEST

START_TEST(test_csll_remove_position_back)
{
    circular_singly_linked_list_t *list = csll_create();

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

    ck_assert_int_eq(*((int *)data), 30);

    csll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun csll_remove_position_tests[] =
{
    test_csll_remove_position_middle,
    test_csll_remove_position_front,
    test_csll_remove_position_back,
    NULL
};

static void add_tests(TCase * test_cases, TFun * test_functions)
{
    while (* test_functions)
    {
        // add the test from the core_tests array to the tcase
        tcase_add_test(test_cases, * test_functions);
        test_functions++;
    }
}

Suite *circular_singly_linked_list_test_suite(void)
{
    Suite *circular_singly_linked_list_test_suite = suite_create("Circular Singly Linked List Tests");

    //Create csll_create tests
    TFun *csll_create_test_list = csll_create_tests;
    TCase *csll_create_test_cases = tcase_create(" csll_create() Tests");
    add_tests(csll_create_test_cases, csll_create_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_create_test_cases);

    //Create csll_push_head tests
    TFun *csll_push_head_test_list = csll_push_head_tests;
    TCase *csll_push_head_test_cases = tcase_create(" csll_push_head() Tests");
    add_tests(csll_push_head_test_cases, csll_push_head_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_push_head_test_cases);

    //Create csll_push_tail tests
    TFun *csll_push_tail_test_list = csll_push_tail_tests;
    TCase *csll_push_tail_test_cases = tcase_create(" csll_push_tail() Tests");
    add_tests(csll_push_tail_test_cases, csll_push_tail_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_push_tail_test_cases);

    //Create csll_push_position tests
    TFun *csll_push_position_test_list = csll_push_position_tests;
    TCase *csll_push_position_test_cases = tcase_create(" csll_push_position() Tests");
    add_tests(csll_push_position_test_cases, csll_push_position_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_push_position_test_cases);

    //Create csll_peek_head tests
    TFun *csll_peek_head_test_list = csll_peek_head_tests;
    TCase *csll_peek_head_test_cases = tcase_create(" csll_peek_head() Tests");
    add_tests(csll_peek_head_test_cases, csll_peek_head_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_peek_head_test_cases);

    //Create csll_peek_tail tests
    TFun *csll_peek_tail_test_list = csll_peek_tail_tests;
    TCase *csll_peek_tail_test_cases = tcase_create(" csll_peek_tail() Tests");
    add_tests(csll_peek_tail_test_cases, csll_peek_tail_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_peek_tail_test_cases);

    //Create csll_peek_position tests
    TFun *csll_peek_position_test_list = csll_peek_position_tests;
    TCase *csll_peek_position_test_cases = tcase_create(" csll_peek_position() Tests");
    add_tests(csll_peek_position_test_cases, csll_peek_position_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_peek_position_test_cases);

    //Create csll_pop_head tests
    TFun *csll_pop_head_test_list = csll_pop_head_tests;
    TCase *csll_pop_head_test_cases = tcase_create(" csll_pop_head() Tests");
    add_tests(csll_pop_head_test_cases, csll_pop_head_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_pop_head_test_cases);

    //Create csll_pop_tail tests
    TFun *csll_pop_tail_test_list = csll_pop_tail_tests;
    TCase *csll_pop_tail_test_cases = tcase_create(" csll_pop_tail() Tests");
    add_tests(csll_pop_tail_test_cases, csll_pop_tail_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_pop_tail_test_cases);

    //Create csll_pop_position tests
    TFun *csll_pop_position_test_list = csll_pop_position_tests;
    TCase *csll_pop_position_test_cases = tcase_create(" csll_pop_position() Tests");
    add_tests(csll_pop_position_test_cases, csll_pop_position_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_pop_position_test_cases);

    //Create csll_remove_head tests
    TFun *csll_remove_head_test_list = csll_remove_head_tests;
    TCase *csll_remove_head_test_cases = tcase_create(" csll_remove_head() Tests");
    add_tests(csll_remove_head_test_cases, csll_remove_head_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_remove_head_test_cases);

    //Create csll_remove_tail tests
    TFun *csll_remove_tail_test_list = csll_remove_tail_tests;
    TCase *csll_remove_tail_test_cases = tcase_create(" csll_remove_tail() Tests");
    add_tests(csll_remove_tail_test_cases, csll_remove_tail_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_remove_tail_test_cases);

    //Create csll_remove_position tests
    TFun *csll_remove_position_test_list = csll_remove_position_tests;
    TCase *csll_remove_position_test_cases = tcase_create(" csll_remove_position() Tests");
    add_tests(csll_remove_position_test_cases, csll_remove_position_test_list);
    suite_add_tcase(circular_singly_linked_list_test_suite, csll_remove_position_test_cases);

    return circular_singly_linked_list_test_suite;
}
