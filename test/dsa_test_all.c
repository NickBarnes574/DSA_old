#include <check.h>
#include <stdio.h>
#include <stdbool.h>

// This name matters
extern Suite *singly_linked_list_test_suite(void);
extern Suite *doubly_linked_list_test_suite(void);
extern Suite *circular_singly_linked_list_test_suite(void);
extern Suite *array_list_test_suite(void);

int run_linked_list_tests()
{
    //create test suite runner
    SRunner *sr_sll = srunner_create(NULL);
    SRunner *sr_dll = srunner_create(NULL);
    SRunner *sr_csll = srunner_create(NULL);

    // prepare the test suites
    srunner_add_suite(sr_sll, singly_linked_list_test_suite());
    srunner_add_suite(sr_dll, doubly_linked_list_test_suite());
    srunner_add_suite(sr_csll, circular_singly_linked_list_test_suite());

    // run the Linked List test suites
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                           LINKED LIST TESTS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    srunner_run_all(sr_sll, CK_VERBOSE);
    printf("\n");
    srunner_run_all(sr_dll, CK_VERBOSE);
    printf("\n");
    srunner_run_all(sr_csll, CK_VERBOSE);
    printf("\n");

    // report the test failed status
    int tests_failed = 0;

    // Linked List
    tests_failed = srunner_ntests_failed(sr_sll);
    if (0 != tests_failed)
    {
        perror("singly linked list test failure\n");
        goto END;
    }

    tests_failed = srunner_ntests_failed(sr_dll);
    if (0 != tests_failed)
    {
        perror("doubly linked list test failure\n");
        goto END;
    }

    tests_failed = srunner_ntests_failed(sr_csll);
    if (0 != tests_failed)
    {
        perror("circular doubly linked list test failure\n");
        goto END;
    }


END:
    srunner_free(sr_sll);
    srunner_free(sr_dll);
    srunner_free(sr_csll);
    // return 1 or 0 based on whether or not tests failed
    return (tests_failed == 0) ? 0 : 1;
}

int run_array_list_tests()
{
    //create test suite runner
    SRunner *sr_al = srunner_create(NULL);

    // prepare the test suites
    srunner_add_suite(sr_al, array_list_test_suite());

    // run the Linked List test suites
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                           ARRAY LIST TESTS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    srunner_run_all(sr_al, CK_VERBOSE);
    printf("\n");

    // report the test failed status
    int tests_failed = 0;

    // Array List
    tests_failed = srunner_ntests_failed(sr_al);
    if (0 != tests_failed)
    {
        perror("array list test failure\n");
        goto END;
    }

END:
    srunner_free(sr_al);
    // return 1 or 0 based on whether or not tests failed
    return (tests_failed == 0) ? 0 : 1;
}

int main(int argc, char** argv)
{
    // Suppress unused parameter warnings
    (void) argv[argc];

    int result = 0;

    bool linked_list = true;
    bool array_list = true;

    // Run linked list tests
    if (true == linked_list)
    {
        result = run_linked_list_tests();
        if (0 != result)
        {
            goto END;
        }
    }

    // Run array list tests
    if (true == array_list)
    {
        result = run_array_list_tests();
        if (0 != result)
        {
            goto END;
        }
    }

END:
    return result;
}
