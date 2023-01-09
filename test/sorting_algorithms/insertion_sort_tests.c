#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "array_list.h"
#include "sorting_algorithms/insertion_sort.h"
#include "utilities/test_helpers.h"

// CREATE LIST TESTS
//***********************************************************************************************
// ensure insertion sort works
START_TEST(test_insertion_sort)
{
    int arr[] = {5, 1, 8, 11, 3, 4, 15};

    printf("before:\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    insertion_sort(arr, 7, sizeof(int), &int_comp_ctx, &int_eq_ctx);
    assert_sorted_int(arr, 7, NULL);

    printf("after:\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
END_TEST

START_TEST(test_insertion_sort_array_list)
{
    array_list_t *list = array_list_create(NULL, &int_eq_ctx);

    int numbers[] = {5, 1, 8, 11, 3, 4, 15};

    for (size_t idx = 0; idx < 7; idx++)
    {
        array_list_push(list, *(int *)numbers[idx]);
    }

    printf("before:\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", *(int *)array_list_get(list, (int)i));
    }
    printf("\n");

    insertion_sort(list, 7, sizeof(int), &int_comp_ctx, &int_eq_ctx);
    //assert_sorted_int(list, 7, NULL);

    printf("after:\n");
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", *(int *)array_list_get(list, (int)i));
    }
    printf("\n");
}
END_TEST

// TEST LIST
static TFun insertion_sort_tests[] =
{
    test_insertion_sort,
    test_insertion_sort_array_list,
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

Suite *insertion_sort_test_suite(void)
{
    Suite *insertion_sort_test_suite = suite_create("Insertion Sort Tests");

    // Create insertion_sort tests
    TFun *insertion_sort_test_list = insertion_sort_tests;
    TCase *insertion_sort_test_cases = tcase_create(" insertion_sort() Tests");
    add_tests(insertion_sort_test_cases, insertion_sort_test_list);
    suite_add_tcase(insertion_sort_test_suite, insertion_sort_test_cases);

    return insertion_sort_test_suite;
}