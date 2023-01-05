#include <check.h>
#include <stdio.h>

// This name matters
extern Suite *singly_linked_list_test_suite(void);
extern Suite *doubly_linked_list_test_suite(void);
extern Suite *circular_singly_linked_list_test_suite(void);
extern Suite *array_list_test_suite(void);

int main(int argc, char** argv)
{
    // Suppress unused parameter warnings
    (void) argv[argc];

    // create test suite runner
    // SRunner *sr_sll = srunner_create(NULL);
    // SRunner *sr_dll = srunner_create(NULL);
    // SRunner *sr_csll = srunner_create(NULL);
    SRunner *sr_al = srunner_create(NULL);

    // prepare the test suites

    // // Linked List
    // srunner_add_suite(sr_sll, singly_linked_list_test_suite());
    // srunner_add_suite(sr_dll, doubly_linked_list_test_suite());
    // srunner_add_suite(sr_csll, circular_singly_linked_list_test_suite());
    srunner_add_suite(sr_al, array_list_test_suite());

    // // run the Linked List test suites
    // printf("-------------------------------------------------------------------------------------------------------\n");
    // printf("                                           LINKED LIST TESTS\n");
    // printf("-------------------------------------------------------------------------------------------------------\n");
    // srunner_run_all(sr_sll, CK_VERBOSE);
    // printf("\n");
    // srunner_run_all(sr_dll, CK_VERBOSE);
    // printf("\n");
    // srunner_run_all(sr_csll, CK_VERBOSE);

    // run the Linked List test suites
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                           ARRAY LIST TESTS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    srunner_run_all(sr_al, CK_VERBOSE);
    printf("\n");

    // report the test failed status
    int tests_failed = 0;

    // // Linked List
    // tests_failed = srunner_ntests_failed(sr_sll);
    // srunner_free(sr_sll);
    // tests_failed = srunner_ntests_failed(sr_dll);
    // srunner_free(sr_dll);
    // tests_failed = srunner_ntests_failed(sr_csll);
    // srunner_free(sr_csll);

    // Array List
    tests_failed = srunner_ntests_failed(sr_al);
    srunner_free(sr_al);


    // return 1 or 0 based on whether or not tests failed
    return (tests_failed == 0) ? 0 : 1;
}
