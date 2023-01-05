#include <check.h>
#include <stdio.h>

// This name matters
extern Suite *singly_linked_list_test_suite(void);
extern Suite *doubly_linked_list_test_suite(void);

int main(int argc, char** argv)
{
    // Suppress unused parameter warnings
    (void) argv[argc];

    // create test suite runner
    SRunner *sr_sll = srunner_create(NULL);
    SRunner *sr_dll = srunner_create(NULL);

    // prepare the test suites
    // the name in here matters
    srunner_add_suite(sr_sll, singly_linked_list_test_suite());
    srunner_add_suite(sr_dll, doubly_linked_list_test_suite());

    // run the Linked List test suites
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("                                           LINKED LIST TESTS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    srunner_run_all(sr_sll, CK_VERBOSE);
    printf("\n");
    srunner_run_all(sr_dll, CK_VERBOSE);

    // report the test failed status
    int tests_failed = 0;

    tests_failed = srunner_ntests_failed(sr_sll);
    srunner_free(sr_sll);
    tests_failed = srunner_ntests_failed(sr_dll);
    srunner_free(sr_dll);

    // return 1 or 0 based on whether or not tests failed
    return (tests_failed == 0) ? 0 : 1;
}
