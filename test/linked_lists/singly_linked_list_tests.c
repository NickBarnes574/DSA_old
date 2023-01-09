#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../lists/linked_lists/singly_linked_list/singly_linked_list.h"
#include "../../utilities/void_pointer_functions/void_pointer_functions.h"
#include "../../utilities/exit_codes/exit_codes.h"

struct sll_node
{
    void *data;
    sll_node_t *next;
};

struct singly_linked_list
{
    sll_node_t *head;
    sll_node_t *tail;
    size_t current_size;
};

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new singly-linked list is created
START_TEST(test_sll_create)
{
    singly_linked_list_t *list = sll_create();
    ck_assert_ptr_ne(list, NULL);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_create_tests[] =
{
    test_sll_create,
    NULL
};

// PUSH HEAD TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(sll_push_head_single_int)
{
    singly_linked_list_t *list = sll_create();

    int num = 10;

    sll_push_head(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    sll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(sll_push_head_double_int)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    sll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(sll_push_head_triple_int)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 50);
    ck_assert_int_eq(*((int *)list->tail->data), 10);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);

    sll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(sll_push_head_single_string)
{
    singly_linked_list_t *list = sll_create();

    const char *str = "hello";

    sll_push_head(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_push_head_tests[] =
{
    sll_push_head_single_int,
    sll_push_head_double_int,
    sll_push_head_triple_int,
    sll_push_head_single_string,
    NULL
};

// PUSH TAIL TESTS
//***********************************************************************************************
// ensure a new integer is added to the list
START_TEST(sll_push_tail_single_int)
{
    singly_linked_list_t *list = sll_create();

    int num = 10;

    sll_push_tail(list, &num);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 10);

    sll_destroy_list(&list);
}
END_TEST

// ensure two integers are added to the list
START_TEST(sll_push_tail_double_int)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;

    sll_push_tail(list, &num_1);
    sll_push_tail(list, &num_2);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 25);

    sll_destroy_list(&list);
}
END_TEST

// ensure three integers are added to the list
START_TEST(sll_push_tail_triple_int)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    sll_push_tail(list, &num_1);
    sll_push_tail(list, &num_2);
    sll_push_tail(list, &num_3);
    ck_assert_int_eq(*((int *)list->head->data), 10);
    ck_assert_int_eq(*((int *)list->tail->data), 50);
    ck_assert_int_eq(*((int *)list->head->next->data), 25);

    sll_destroy_list(&list);
}
END_TEST

// ensure a string is added to the list
START_TEST(sll_push_tail_single_string)
{
    singly_linked_list_t *list = sll_create();

    const char *str = "hello";

    sll_push_tail(list, &str);
    ck_assert_int_eq(strcmp(*((char **)list->head->data), str), 0);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_push_tail_tests[] =
{
    sll_push_tail_single_int,
    sll_push_tail_double_int,
    sll_push_tail_triple_int,
    sll_push_tail_single_string,
    NULL
};

// PUSH POSITION TESTS
//***********************************************************************************************
// ensure sll_node is added at position 3
START_TEST(test_sll_push_position_single_70)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    int num_7 = 70;

    sll_push_position(list, &num_7, 3);

    void *data = sll_peek_position(list, 3);
    ck_assert_int_eq(*((int *)data), 70);

    sll_destroy_list(&list);
}
END_TEST

// ensure sll_node is added at position 6
START_TEST(test_sll_push_position_single_20)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    int num_7 = 20;

    sll_push_position(list, &num_7, 6);

    void *data = sll_peek_position(list, 6);
    ck_assert_int_eq(*((int *)data), 20);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_push_position_tests[] =
{
    test_sll_push_position_single_70,
    test_sll_push_position_single_20,
    NULL
};

// PEEK HEAD TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_sll_peek_head)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data = sll_peek_head(list);

    ck_assert_int_eq(*((int *)data), 90);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_peek_head_tests[] =
{
    test_sll_peek_head,
    NULL
};

// PEEK TAIL TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_sll_peek_tail)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data = sll_peek_tail(list);

    ck_assert_int_eq(*((int *)data), 15);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_peek_tail_tests[] =
{
    test_sll_peek_tail,
    NULL
};

// PEEK POSITION TESTS
//***********************************************************************************************
// ensure the returned value is 90
START_TEST(test_sll_peek_position)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data_1 = sll_peek_position(list, 1);
    void *data_2 = sll_peek_position(list, 2);
    void *data_3 = sll_peek_position(list, 3);
    void *data_4 = sll_peek_position(list, 4);
    void *data_5 = sll_peek_position(list, 5);
    void *data_6 = sll_peek_position(list, 6);

    ck_assert_int_eq(*((int *)data_1), 90);
    ck_assert_int_eq(*((int *)data_2), 75);
    ck_assert_int_eq(*((int *)data_3), 60);
    ck_assert_int_eq(*((int *)data_4), 45);
    ck_assert_int_eq(*((int *)data_5), 30);
    ck_assert_int_eq(*((int *)data_6), 15);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_peek_position_tests[] =
{
    test_sll_peek_position,
    NULL
};

// POP HEAD TESTS
//***********************************************************************************************
// ensure ensure 90 is popped from the list
START_TEST(test_sll_pop_head)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data = sll_pop_head(list);

    ck_assert_int_eq(*((int *)data), 90);
    ck_assert_int_eq(list->current_size, 5);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_pop_head_tests[] =
{
    test_sll_pop_head,
    NULL
};

// POP TAIL TESTS
//***********************************************************************************************
// ensure 15 is popped from the list
START_TEST(test_sll_pop_tail)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data = sll_pop_tail(list);

    ck_assert_int_eq(*((int *)data), 15);
    ck_assert_int_eq(list->current_size, 5);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_pop_tail_tests[] =
{
    test_sll_pop_tail,
    NULL
};

// POP POSITION TESTS
//***********************************************************************************************
// ensure 60 is popped from the list
START_TEST(test_sll_pop_position)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    void *data = sll_pop_position(list, 3);

    ck_assert_int_eq(*((int *)data), 60);
    ck_assert_int_eq(list->current_size, 5);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_pop_position_tests[] =
{
    test_sll_pop_position,
    NULL
};

// REMOVE HEAD TESTS
//***********************************************************************************************
// ensure the first sll_node in the list is removed
START_TEST(test_sll_remove_head)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);

    sll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 25);
    sll_remove_head(list);
    ck_assert_int_eq(*((int *)list->head->data), 10);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_remove_head_tests[] =
{
    test_sll_remove_head,
    NULL
};

// REMOVE TAIL TESTS
//***********************************************************************************************
// ensure the first sll_node in the list is removed
START_TEST(test_sll_remove_tail)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);

    sll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 25);
    sll_remove_tail(list);
    ck_assert_int_eq(*((int *)list->tail->data), 50);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_remove_tail_tests[] =
{
    test_sll_remove_tail,
    NULL
};

// REMOVE POSITION TESTS
//***********************************************************************************************
// ensure LLLL
START_TEST(test_sll_remove_position_middle)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 10;
    int num_2 = 25;
    int num_3 = 50;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);

    sll_remove_position(list, 2);

    ck_assert_int_eq(list->current_size, 2);
    sll_destroy_list(&list);
}
END_TEST

START_TEST(test_sll_remove_position_front)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    sll_remove_position(list, 1);

    void *data = sll_peek_head(list);

    ck_assert_int_eq(*((int *)data), 75);

    sll_destroy_list(&list);
}
END_TEST

START_TEST(test_sll_remove_position_back)
{
    singly_linked_list_t *list = sll_create();

    int num_1 = 15;
    int num_2 = 30;
    int num_3 = 45;
    int num_4 = 60;
    int num_5 = 75;
    int num_6 = 90;

    sll_push_head(list, &num_1);
    sll_push_head(list, &num_2);
    sll_push_head(list, &num_3);
    sll_push_head(list, &num_4);
    sll_push_head(list, &num_5);
    sll_push_head(list, &num_6);

    sll_remove_position(list, 6);

    void *data = sll_peek_tail(list);

    ck_assert_int_eq(*((int *)data), 30);

    sll_destroy_list(&list);
}
END_TEST

// TEST LIST
static TFun sll_remove_position_tests[] =
{
    test_sll_remove_position_middle,
    test_sll_remove_position_front,
    test_sll_remove_position_back,
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

Suite *singly_linked_list_test_suite(void)
{
    Suite *singly_linked_list_test_suite = suite_create("Singly Linked List Tests");

    //Create sll_create tests
    TFun *sll_create_test_list = sll_create_tests;
    TCase *sll_create_test_cases = tcase_create(" sll_create() Tests");
    add_tests(sll_create_test_cases, sll_create_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_create_test_cases);

    //Create sll_push_head tests
    TFun *sll_push_head_test_list = sll_push_head_tests;
    TCase *sll_push_head_test_cases = tcase_create(" sll_push_head() Tests");
    add_tests(sll_push_head_test_cases, sll_push_head_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_push_head_test_cases);

    //Create sll_push_tail tests
    TFun *sll_push_tail_test_list = sll_push_tail_tests;
    TCase *sll_push_tail_test_cases = tcase_create(" sll_push_tail() Tests");
    add_tests(sll_push_tail_test_cases, sll_push_tail_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_push_tail_test_cases);

    //Create sll_push_position tests
    TFun *sll_push_position_test_list = sll_push_position_tests;
    TCase *sll_push_position_test_cases = tcase_create(" sll_push_position() Tests");
    add_tests(sll_push_position_test_cases, sll_push_position_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_push_position_test_cases);

    //Create sll_peek_head tests
    TFun *sll_peek_head_test_list = sll_peek_head_tests;
    TCase *sll_peek_head_test_cases = tcase_create(" sll_peek_head() Tests");
    add_tests(sll_peek_head_test_cases, sll_peek_head_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_peek_head_test_cases);

    //Create sll_peek_tail tests
    TFun *sll_peek_tail_test_list = sll_peek_tail_tests;
    TCase *sll_peek_tail_test_cases = tcase_create(" sll_peek_tail() Tests");
    add_tests(sll_peek_tail_test_cases, sll_peek_tail_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_peek_tail_test_cases);

    //Create sll_peek_position tests
    TFun *sll_peek_position_test_list = sll_peek_position_tests;
    TCase *sll_peek_position_test_cases = tcase_create(" sll_peek_position() Tests");
    add_tests(sll_peek_position_test_cases, sll_peek_position_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_peek_position_test_cases);

    //Create sll_pop_head tests
    TFun *sll_pop_head_test_list = sll_pop_head_tests;
    TCase *sll_pop_head_test_cases = tcase_create(" sll_pop_head() Tests");
    add_tests(sll_pop_head_test_cases, sll_pop_head_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_pop_head_test_cases);

    //Create sll_pop_tail tests
    TFun *sll_pop_tail_test_list = sll_pop_tail_tests;
    TCase *sll_pop_tail_test_cases = tcase_create(" sll_pop_tail() Tests");
    add_tests(sll_pop_tail_test_cases, sll_pop_tail_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_pop_tail_test_cases);

    //Create sll_pop_position tests
    TFun *sll_pop_position_test_list = sll_pop_position_tests;
    TCase *sll_pop_position_test_cases = tcase_create(" sll_pop_position() Tests");
    add_tests(sll_pop_position_test_cases, sll_pop_position_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_pop_position_test_cases);

    //Create sll_remove_head tests
    TFun *sll_remove_head_test_list = sll_remove_head_tests;
    TCase *sll_remove_head_test_cases = tcase_create(" sll_remove_head() Tests");
    add_tests(sll_remove_head_test_cases, sll_remove_head_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_remove_head_test_cases);

    //Create sll_remove_tail tests
    TFun *sll_remove_tail_test_list = sll_remove_tail_tests;
    TCase *sll_remove_tail_test_cases = tcase_create(" sll_remove_tail() Tests");
    add_tests(sll_remove_tail_test_cases, sll_remove_tail_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_remove_tail_test_cases);

    //Create sll_remove_position tests
    TFun *sll_remove_position_test_list = sll_remove_position_tests;
    TCase *sll_remove_position_test_cases = tcase_create(" sll_remove_position() Tests");
    add_tests(sll_remove_position_test_cases, sll_remove_position_test_list);
    suite_add_tcase(singly_linked_list_test_suite, sll_remove_position_test_cases);

    return singly_linked_list_test_suite;
}
