#include <check.h>
#include <stdio.h>
#include <stdlib.h>

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

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new doubly-linked list is created
START_TEST(test_dll_create)
{
    doubly_linked_list_t *list = dll_create();
    ck_assert_ptr_ne(list, NULL);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_create_tests[] =
{
    test_dll_create,
    NULL
};

// PUSH HEAD TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(dll_push_head_single_int)
{
    doubly_linked_list_t *list = dll_create();

    int num = 10;

    dll_push_head(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    dll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(dll_push_head_double_int)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    dll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(dll_push_head_triple_int)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 50);
    ck_assert_int_eq(*((int *)list->tail->data), 10);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);
    ck_assert_int_eq(*((int *)list->tail->prev->data), 25);

    dll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(dll_push_head_single_string)
{
    doubly_linked_list_t *list = dll_create();

    const char *str = "hello";

    dll_push_head(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_push_head_tests[] =
{
    dll_push_head_single_int,
    dll_push_head_double_int,
    dll_push_head_triple_int,
    dll_push_head_single_string,
    NULL
};

// PUSH TAIL TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(dll_push_tail_single_int)
{
    doubly_linked_list_t *list = dll_create();

    int num = 10;

    dll_push_tail(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    dll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(dll_push_tail_double_int)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;

    dll_push_tail(list, &num_1);
    dll_push_tail(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 25);

    dll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(dll_push_tail_triple_int)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_tail(list, &num_1);
    dll_push_tail(list, &num_2);
    dll_push_tail(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 50);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);
    ck_assert_int_eq(*((int *)list->tail->prev->data), 25);

    dll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(dll_push_tail_single_string)
{
    doubly_linked_list_t *list = dll_create();

    const char *str = "hello";

    dll_push_tail(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_push_tail_tests[] =
{
    dll_push_tail_single_int,
    dll_push_tail_double_int,
    dll_push_tail_triple_int,
    dll_push_tail_single_string,
    NULL
};

// PUSH POSITION TESTS
//***********************************************************************************************
// ensure dll_node is added at position 3
START_TEST(test_dll_push_position_single_70)
{
    doubly_linked_list_t *list = dll_create();

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
    ck_assert_int_eq(*((int *)data), 70);

    dll_destroy_list(&list);
}
END_TEST

// ensure dll_node is added at position 6
START_TEST(test_dll_push_position_single_20)
{
    doubly_linked_list_t *list = dll_create();

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
    ck_assert_int_eq(*((int *)data), 20);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_push_position_tests[] =
{
    test_dll_push_position_single_70,
    test_dll_push_position_single_20,
    NULL
};

// PEEK HEAD TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_dll_peek_head)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 90);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_peek_head_tests[] =
{
    test_dll_peek_head,
    NULL
};

// PEEK TAIL TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_dll_peek_tail)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 15);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_peek_tail_tests[] =
{
    test_dll_peek_tail,
    NULL
};

// PEEK POSITION TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_dll_peek_position)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data_1), 90);
    ck_assert_int_eq(*((int *)data_2), 75);
    ck_assert_int_eq(*((int *)data_3), 60);
    ck_assert_int_eq(*((int *)data_4), 45);
    ck_assert_int_eq(*((int *)data_5), 30);
    ck_assert_int_eq(*((int *)data_6), 15);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_peek_position_tests[] =
{
    test_dll_peek_position,
    NULL
};

// POP HEAD TESTS
//***********************************************************************************************
// ensure ensure 90 is popped from the list
START_TEST(test_dll_pop_head)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 90);
    ck_assert_int_eq(list->current_size, 5);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_pop_head_tests[] =
{
    test_dll_pop_head,
    NULL
};

// POP TAIL TESTS
//***********************************************************************************************
// ensure 15 is popped from the list
START_TEST(test_dll_pop_tail)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 15);
    ck_assert_int_eq(list->current_size, 5);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_pop_tail_tests[] =
{
    test_dll_pop_tail,
    NULL
};

// POP POSITION TESTS
//***********************************************************************************************
// ensure 60 is popped from the list
START_TEST(test_dll_pop_position)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 60);
    ck_assert_int_eq(list->current_size, 5);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_pop_position_tests[] =
{
    test_dll_pop_position,
    NULL
};

// REMOVE HEAD TESTS
//***********************************************************************************************
// ensure the first dll_node in the list is removed
START_TEST(test_dll_remove_head)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    dll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 10);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_remove_head_tests[] =
{
    test_dll_remove_head,
    NULL
};

// REMOVE TAIL TESTS
//***********************************************************************************************
// ensure the first dll_node in the list is removed
START_TEST(test_dll_remove_tail)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 25);
    dll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 50);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_remove_tail_tests[] =
{
    test_dll_remove_tail,
    NULL
};

// REMOVE POSITION TESTS
//***********************************************************************************************
// ensure LLLL
START_TEST(test_dll_remove_position_middle)
{
    doubly_linked_list_t *list = dll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    dll_push_head(list, &num_1);
    dll_push_head(list, &num_2);
    dll_push_head(list, &num_3);

    dll_remove_position(list, 2);

    ck_assert_int_eq(list->current_size, 2);
    dll_destroy_list(&list);
}
END_TEST

START_TEST(test_dll_remove_position_front)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 75);

    dll_destroy_list(&list);
}
END_TEST

START_TEST(test_dll_remove_position_back)
{
    doubly_linked_list_t *list = dll_create();

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

    ck_assert_int_eq(*((int *)data), 30);

    dll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun dll_remove_position_tests[] =
{
    test_dll_remove_position_middle,
    test_dll_remove_position_front,
    test_dll_remove_position_back,
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

Suite *doubly_linked_list_test_suite(void)
{
    Suite *doubly_linked_list_test_suite = suite_create("Doubly Linked List Tests");

    //Create dll_create tests
    TFun *dll_create_test_list = dll_create_tests;
    TCase *dll_create_test_cases = tcase_create(" dll_create() Tests");
    add_tests(dll_create_test_cases, dll_create_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_create_test_cases);

    //Create dll_push_head tests
    TFun *dll_push_head_test_list = dll_push_head_tests;
    TCase *dll_push_head_test_cases = tcase_create(" dll_push_head() Tests");
    add_tests(dll_push_head_test_cases, dll_push_head_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_push_head_test_cases);

    //Create dll_push_tail tests
    TFun *dll_push_tail_test_list = dll_push_tail_tests;
    TCase *dll_push_tail_test_cases = tcase_create(" dll_push_tail() Tests");
    add_tests(dll_push_tail_test_cases, dll_push_tail_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_push_tail_test_cases);

    //Create dll_push_position tests
    TFun *dll_push_position_test_list = dll_push_position_tests;
    TCase *dll_push_position_test_cases = tcase_create(" dll_push_position() Tests");
    add_tests(dll_push_position_test_cases, dll_push_position_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_push_position_test_cases);

    //Create dll_peek_head tests
    TFun *dll_peek_head_test_list = dll_peek_head_tests;
    TCase *dll_peek_head_test_cases = tcase_create(" dll_peek_head() Tests");
    add_tests(dll_peek_head_test_cases, dll_peek_head_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_peek_head_test_cases);

    //Create dll_peek_tail tests
    TFun *dll_peek_tail_test_list = dll_peek_tail_tests;
    TCase *dll_peek_tail_test_cases = tcase_create(" dll_peek_tail() Tests");
    add_tests(dll_peek_tail_test_cases, dll_peek_tail_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_peek_tail_test_cases);

    //Create dll_peek_position tests
    TFun *dll_peek_position_test_list = dll_peek_position_tests;
    TCase *dll_peek_position_test_cases = tcase_create(" dll_peek_position() Tests");
    add_tests(dll_peek_position_test_cases, dll_peek_position_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_peek_position_test_cases);

    //Create dll_pop_head tests
    TFun *dll_pop_head_test_list = dll_pop_head_tests;
    TCase *dll_pop_head_test_cases = tcase_create(" dll_pop_head() Tests");
    add_tests(dll_pop_head_test_cases, dll_pop_head_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_pop_head_test_cases);

    //Create dll_pop_tail tests
    TFun *dll_pop_tail_test_list = dll_pop_tail_tests;
    TCase *dll_pop_tail_test_cases = tcase_create(" dll_pop_tail() Tests");
    add_tests(dll_pop_tail_test_cases, dll_pop_tail_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_pop_tail_test_cases);

    //Create dll_pop_position tests
    TFun *dll_pop_position_test_list = dll_pop_position_tests;
    TCase *dll_pop_position_test_cases = tcase_create(" dll_pop_position() Tests");
    add_tests(dll_pop_position_test_cases, dll_pop_position_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_pop_position_test_cases);

    //Create dll_remove_head tests
    TFun *dll_remove_head_test_list = dll_remove_head_tests;
    TCase *dll_remove_head_test_cases = tcase_create(" dll_remove_head() Tests");
    add_tests(dll_remove_head_test_cases, dll_remove_head_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_remove_head_test_cases);

    //Create dll_remove_tail tests
    TFun *dll_remove_tail_test_list = dll_remove_tail_tests;
    TCase *dll_remove_tail_test_cases = tcase_create(" dll_remove_tail() Tests");
    add_tests(dll_remove_tail_test_cases, dll_remove_tail_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_remove_tail_test_cases);

    //Create dll_remove_position tests
    TFun *dll_remove_position_test_list = dll_remove_position_tests;
    TCase *dll_remove_position_test_cases = tcase_create(" dll_remove_position() Tests");
    add_tests(dll_remove_position_test_cases, dll_remove_position_test_list);
    suite_add_tcase(doubly_linked_list_test_suite, dll_remove_position_test_cases);

    return doubly_linked_list_test_suite;
}
