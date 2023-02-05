#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>

#include "array_list.h"
#include "void_pointer_functions.h"
#include "exit_codes.h"

struct array_list
{
    void **elements;
    size_t current_size;
    size_t total_capacity;
};

static array_list_t *list;
static exit_code_t exit_code;

void array_list_setup(void)
{
    list = array_list_create(NULL, NULL);
    exit_code = E_DEFAULT_ERROR;
}

void array_list_teardown(void)
{
    array_list_destroy(&list);
}

// CREATE LIST TESTS
//***********************************************************************************************
// ensure a new array list is created
void test_array_list_create(void)
{
    CU_ASSERT_PTR_NOT_EQUAL(list, NULL);
}

// INSERT TESTS
//***********************************************************************************************
void test_array_list_insert_NULL_list(void)
{
    int num_1 = 10;
    
    exit_code = array_list_insert(NULL, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_LIST_ERROR);
}

void test_array_list_insert_NULL_data(void)
{
    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, NULL);
    CU_ASSERT_EQUAL(exit_code, E_NULL_POINTER);
}

void test_array_list_insert_int_single(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[0]), 10); 
}

void test_array_list_insert_int_multi(void)
{
    int num_array[] = {13, 52, 36, 41, 76, 85};

    array_list_t *list = array_list_create(NULL, NULL);

    //************************************
    // Insert elements
    //************************************

    // Ensure 13 at index 0
    exit_code = array_list_insert(list, 0, &num_array[0]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[0]), 13);

    // Ensure 52 at index 1
    exit_code = array_list_insert(list, 1, &num_array[1]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[1]), 52);

    // Ensure 36 at index 2
    exit_code = array_list_insert(list, 2, &num_array[2]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[2]), 36);

    // Ensure 41 at index 3
    exit_code = array_list_insert(list, 3, &num_array[3]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[3]), 41);

    // Ensure 76 at index 4
    exit_code = array_list_insert(list, 3, &num_array[4]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[4]), 76);

    //************************************
    // Verify capacity
    //************************************

    // Ensure that capacity is at 5
    CU_ASSERT_EQUAL(list->total_capacity, 5);

    //************************************
    // Insert additional element
    //************************************

    // Ensure 85 at index 5
    exit_code = array_list_insert(list, 5, &num_array[5]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(*((int *)list->elements[5]), 85);

    //************************************
    // Verify capacity again
    //************************************

    // Ensure that capacity has doubled by this point
    CU_ASSERT_EQUAL(list->total_capacity, 10);
}

void test_array_list_insert_string_single(void)
{
    const char *str = "hello";

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &str);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[0]), str), 0);
}

void test_array_list_insert_string_multi(void)
{
    const char *words[] = {"hello", "world", "I", "am", "big", "chungus"};

    array_list_t *list = array_list_create(NULL, NULL);

    //************************************
    // Insert elements
    //************************************

    // Ensure "hello" at index 0
    exit_code = array_list_insert(list, 0, &words[0]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[0]), words[0]), 0);

    // Ensure "world" at index 1
    exit_code = array_list_insert(list, 1, &words[1]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[1]), words[1]), 0);

    // Ensure "I" at index 2
    exit_code = array_list_insert(list, 2, &words[2]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[2]), words[2]), 0);

    // Ensure "am" at index 3
    exit_code = array_list_insert(list, 3, &words[3]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[3]), words[3]), 0);

    // Ensure "big" at index 4
    exit_code = array_list_insert(list, 4, &words[4]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[4]), words[4]), 0);

    //************************************
    // Verify capacity
    //************************************

    // Ensure that capacity is at 5
    CU_ASSERT_EQUAL(list->total_capacity, 5);

    //************************************
    // Insert additional element
    //************************************

    // Ensure "chungus" at index 5
    exit_code = array_list_insert(list, 5, &words[5]);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[5]), words[5]), 0);

    //************************************
    // Verify capacity again
    //************************************

    // Ensure that capacity has doubled by this point
    CU_ASSERT_EQUAL(list->total_capacity, 10);
}

// GET ELEMENT TESTS
//***********************************************************************************************
void test_array_list_get_NULL_list(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    void *data_1 = array_list_get(NULL, 0);
    CU_ASSERT_PTR_EQUAL(data_1, NULL);
}

void test_array_list_get_int(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    void *data_1 = array_list_get(list, 0);
    CU_ASSERT_EQUAL(*((int *)data_1), 10);
}

void test_array_list_get_string(void)
{
    const char *str = "hello";

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &str);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    void *data_1 = array_list_get(list, 0);
    CU_ASSERT_EQUAL(strcmp(*((char **)data_1), str), 0);
}

// SET ELEMENT TESTS
//***********************************************************************************************
void test_array_list_set_NULL_list(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    int num_2 = 76;

    exit_code = array_list_set(NULL, 0, &num_2);
    CU_ASSERT_EQUAL(exit_code, E_LIST_ERROR);
    CU_ASSERT_EQUAL(num_1, 10);
}

void test_array_list_set_NULL_data(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    exit_code = array_list_set(list, 0, NULL);
    CU_ASSERT_EQUAL(exit_code, E_NULL_POINTER);
    CU_ASSERT_EQUAL(num_1, 10);
}

void test_array_list_set_int(void)
{
    int num_1 = 10;

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &num_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    // Ensure the first index now points to 'num_1'
    CU_ASSERT_EQUAL(*((int *)list->elements[0]), 10);

    int num_2 = 76;

    exit_code = array_list_set(list, 0, &num_2);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    // Ensure the first index now points to 'num_2'
    CU_ASSERT_EQUAL(*((int *)list->elements[0]), 76);
}

void test_array_list_set_string(void)
{
    const char *str_1 = "hello";

    array_list_t *list = array_list_create(NULL, NULL);
    exit_code = array_list_insert(list, 0, &str_1);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    // Ensure the first index points to 'str_1'
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[0]), str_1), 0);

    const char *str_2 = "world";

    exit_code = array_list_set(list, 0, &str_2);
    CU_ASSERT_EQUAL(exit_code, E_SUCCESS);

    // Ensure the first index now points to 'str_2'
    CU_ASSERT_EQUAL(strcmp(*((char **)list->elements[0]), str_2), 0);
}

static CU_TestInfo array_list_tests[] =
{
    // Create List
    {"Create List", test_array_list_create},

    // Insert
    {"Insert - NULL list", test_array_list_insert_NULL_list},
    {"Insert - NULL data", test_array_list_insert_NULL_data},
    {"Insert - 10", test_array_list_insert_int_single},
    {"Insert - 13, 52, 36, 41, 76, 85", test_array_list_insert_int_multi},
    {"Insert - \"hello\"", test_array_list_insert_string_single},
    {"Insert - multi string", test_array_list_insert_string_multi},

    // Get Element
    {"Get - NULL list", test_array_list_get_NULL_list},
    {"Get - int", test_array_list_get_int},
    {"Get - string", test_array_list_get_string},

    // Set Element
    {"Set - NULL list", test_array_list_set_NULL_list},
    {"Set - NULL data", test_array_list_set_NULL_data},
    {"Set - int", test_array_list_set_int},
    {"Set - string", test_array_list_set_string},
    CU_TEST_INFO_NULL
};

CU_SuiteInfo array_list_test_suite =
{
    "Array List Tests",
    NULL,
    NULL,
    array_list_setup,
    array_list_teardown,
    array_list_tests
};
